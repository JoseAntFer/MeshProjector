#include "Projector.h"
#include <limits>
#include <iostream>
#include <numeric>  // iota
#include <omp.h>
#include <math.h>

#include <algorithm>


template<unsigned int nsd>
Projector<nsd>::Projector()
{
}

template<unsigned int nsd>
Projector<nsd>::Projector(Mesh &in_mesh, Array<double> &out_mxyz, Array<double> &in_data)
{
    // Check the input mesh
    if ((in_mesh.nn == 0) || (in_mesh.ne == 0) || (in_mesh.nen == 0) || (in_mesh.nsd == 0)) {
        std::cout << "Missing dimensionality info in minf.space in the input mesh. Exiting...";
        exit(-1);
    }

    if (in_data.isEmpty()) {
        std::cout << "No data found in the input mesh. Exiting...";
        exit(-1);
    }

    this->in_mesh = &in_mesh;
    this->out_mxyz = &out_mxyz;
    this->in_data = &in_data;

    this->nen = in_mesh.nen;
    this->ndf = in_data.cols;
    this->in_ne  = in_mesh.ne;
    this->out_nn = out_mxyz.rows;
}

template<unsigned int nsd>
Projector<nsd>::~Projector()
{
}

template<unsigned int nsd>
Array<double> & Projector<nsd>::run()
{
    // OMP logic
    this->max_threads = omp_get_num_procs();
    this->parallel_depth = (unsigned int) std::sqrt(this->max_threads) + 1;
    omp_set_nested(1);

    // Shared memory initialization
    std::vector<ElemAABB<nsd>*> in_elems(this->in_ne);
    std::vector<PointIt> out_node_its;
    AABB<nsd> out_aabb;

#pragma omp parallel sections
    {
#pragma omp section
        {
            // Initialize the Element bounding boxes
            #pragma omp parallel for schedule(static) num_threads(this->max_threads*4)
            for (int elem_i = 0; elem_i < (int) this->in_ne; elem_i++) {
                in_elems[elem_i] = new ElemAABB<nsd>(*this->in_mesh, elem_i);
            }
        }
#pragma omp section
        {
            // Create node iterators
            out_node_its.reserve(this->out_nn);
            for (auto point_it = this->out_mxyz->data.begin();
                point_it < this->out_mxyz->data.end();
                std::advance(point_it, nsd))
            {
                out_node_its.push_back(PointIt(point_it));
            }

            // Global AABB
            out_aabb = AABB<nsd>(*this->out_mxyz);

            // Fill the output data array
            double max_double = std::numeric_limits<double>::max();
            this->out_data = std::make_shared<Array<double>>();
            this->out_data->fill(max_double, this->out_nn, this->ndf);
        }
    }

    // Run the algorithm
    this->classify(in_elems, out_node_its, out_aabb);

    // Free memory from the raw pointer vector
    in_elems.clear();

    return *this->out_data;
}

template<unsigned int nsd>
void Projector<nsd>::classify(std::vector<ElemAABB<nsd>*> &in_elems, std::vector<PointIt> &out_node_its, AABB<nsd> &aabb, unsigned int depth)
{
    // Project
    if (out_node_its.size() < this->cap) {
        if ((in_elems.size() > 0) && (out_node_its.size() > 0)) { 
            this->project(in_elems, out_node_its);  // 32%
        }
    }
    
    // Classify further
    else {
        // AABB splitting
        unsigned int dim = aabb.largestAxis();
        double pivot = 0.5*(aabb.bottom(dim) + aabb.top(dim));
        AABB<nsd> left_aabb, rght_aabb;
        aabb.split(dim, pivot, left_aabb, rght_aabb);

        // Node classification
        std::vector<PointIt> left_node_its, rght_node_its;
        left_node_its.reserve(out_node_its.size());
        rght_node_its.reserve(out_node_its.size());

        for (PointIt node_it : out_node_its) {
            if (node_it(dim) < pivot) {
                left_node_its.push_back(node_it);
            }
            else {
                rght_node_its.push_back(node_it);
            }
        }

        //// Free memory
        ////// Parent vector
        std::vector<PointIt>().swap(out_node_its);

        ////// Fit new vectors to their actual size
        left_node_its.shrink_to_fit();
        rght_node_its.shrink_to_fit();


        // Element classification
        std::vector<ElemAABB<nsd>*> left_elems, rght_elems;
        left_elems.reserve(in_elems.size());
        rght_elems.reserve(in_elems.size());

        for (ElemAABB<nsd>* elem_AABB : in_elems) {
            if (elem_AABB->top(dim) < pivot) {
                left_elems.push_back(elem_AABB);
            }
            else if (elem_AABB->bottom(dim) >= pivot) {
                rght_elems.push_back(elem_AABB);
            }
            else {
                left_elems.push_back(elem_AABB);
                rght_elems.push_back(elem_AABB);
            }
        }

        //// Free memory
        ////// Parent vector
        std::vector<ElemAABB<nsd>*>().swap(in_elems);

        ////// Fit new vectors to their actual size
        left_elems.shrink_to_fit();
        rght_elems.shrink_to_fit();



        // Further classification
#pragma omp parallel sections if (depth < this->parallel_depth)
        {
#pragma omp section
            {
                this->classify(left_elems, left_node_its, left_aabb, depth + 1);
            }
#pragma omp section
            {
                this->classify(rght_elems, rght_node_its, rght_aabb, depth + 1);
            }
        }
    }
}

template<unsigned int nsd>
void Projector<nsd>::project(std::vector<ElemAABB<nsd>*> &in_elems, std::vector<PointIt> &out_node_its)
{
    // Projected nodes register
    std::vector<bool> projected(out_node_its.size());

    // Interpolation
    Element<nsd> elem = Element<nsd>();
    for (ElemAABB<nsd>* elem_AABB : in_elems) {
        unsigned int loc_node_i = 0;
        for (PointIt node_it : out_node_its) {
            if (elem_AABB->containsPoint(node_it)) {
                if (elem.projectIfInside(*this->in_mesh, elem_AABB->elem_i, *this->out_mxyz, *this->in_data, *this->out_data, node_it)) {
                    projected[loc_node_i] = true;
                }
            }
            loc_node_i++;
        }
    }
    // Extrapolation
    for (unsigned int loc_node_i = 0; loc_node_i < out_node_its.size(); loc_node_i++) {
        if (!projected[loc_node_i]) {
            PointIt node_it = out_node_its[loc_node_i];

            // Find closest AABB
            ElemAABB<nsd> closest_elemAABB;
            double min_dist_sq = std::numeric_limits<double>::max();
            double dist_sq;
            for (ElemAABB<nsd>* elem_AABB : in_elems) {
                dist_sq = elem_AABB->distanceSqToCentroid(node_it);
                if (dist_sq < min_dist_sq) {
                    closest_elemAABB = *elem_AABB;
                    min_dist_sq = dist_sq;
                }
            }

            // Projection
            elem.project(*this->in_mesh, closest_elemAABB.elem_i, *this->out_mxyz, *this->in_data, *this->out_data, node_it);
        }
    }
}

template class Projector<4>;
template class Projector<3>;
template class Projector<2>;