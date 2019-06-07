#include "Element.h"

#include <iostream>
#include <algorithm>

template<unsigned int nsd>
Element<nsd>::Element()
{
}

template<unsigned int nsd>
Element<nsd>::~Element()
{
}

template<unsigned int nsd>
void Element<nsd>::prepareProjection(Mesh & mesh, unsigned int elem_i)
{
    // Store new index
    this->elem_i = elem_i;

    // xyz of the element with iterators
    PointIt point_its[nsd + 1];
    std::vector<double>::iterator mxyz_start = mesh.mxyz.data.begin();
    for (unsigned int loc_node_i = 0; loc_node_i < (nsd + 1); loc_node_i++) {
        unsigned int glob_node_i = mesh.mien(elem_i, loc_node_i);
        point_its[loc_node_i] = PointIt(mxyz_start + glob_node_i*nsd);
    }
    this->origin_it = point_its[0];

    // Compute Transformation matrix
    Matrix<nsd> T;
    for (unsigned int loc_node_i = 1; loc_node_i < (nsd + 1); loc_node_i++) {
        for (unsigned int dim = 0; dim < nsd; dim++) {
            T(loc_node_i - 1, dim) = point_its[loc_node_i](dim) - this->origin_it(dim);
        }
    }

    // Transpose Inverse of the transformation
    T.computeInverseTranspose(this->TinvT);
}

template<unsigned int nsd>
bool Element<nsd>::projectIfInside(Mesh &in_mesh, unsigned int elem_i, Array<double> &out_mxyz, Array<double> &in_data, Array<double> &out_data, PointIt &node_it)
{
    if (this->elem_i != elem_i) {
        this->prepareProjection(in_mesh, elem_i);
    }

    // Common values
    double qzero = -0.01;
    //double qzero = 0.0;

    // Translation vector
    double trans[nsd];
    for (unsigned int dim = 0; dim < nsd; dim++)
        trans[dim] = node_it(dim) - this->origin_it(dim);

    // Barycentric coordinates of the point
    double barycentric[nsd];
    for (unsigned int dim = 0; dim < nsd; dim++) {
        barycentric[dim] = 0.0;
        for (unsigned int row = 0; row < nsd; row++) {
            barycentric[dim] += this->TinvT(dim, row) * trans[row];
        }
        if (barycentric[dim] < qzero) { return false; }
    }

    //// Check Plane
    double plane = 1.0;
    for (unsigned int dim = 0; dim < nsd; dim++) {
        plane -= barycentric[dim];
    }
    if (plane < qzero) { return false; }

    // Projection
    unsigned int glob_node_idx = node_it.getIndex(out_mxyz);
    for (unsigned int df = 0; df < out_data.cols; df++) {
        double val = in_data(in_mesh.mien(elem_i, 0), df) * plane;
        for (unsigned int loc_node_i = 0; loc_node_i < nsd; loc_node_i++) {
            val += in_data(in_mesh.mien(elem_i, loc_node_i+1), df) * barycentric[loc_node_i];
        }
        out_data(glob_node_idx, df) = val;
    }

    return true;
}

template<unsigned int nsd>
void Element<nsd>::project(Mesh &in_mesh, unsigned int elem_i, Array<double> &out_mxyz, Array<double> &in_data, Array<double> &out_data, PointIt &node_it)
{
    if (this->elem_i != elem_i) {
        this->prepareProjection(in_mesh, elem_i);
    }

    // Common values
    //double qzero = -1e-6;
    double qzero = -0.01;

    // Translation vector
    double trans[nsd];
    for (unsigned int dim = 0; dim < nsd; dim++)
        trans[dim] = node_it(dim) - this->origin_it(dim);

    // Barycentric coordinates of the point
    double barycentric[nsd];
    for (unsigned int dim = 0; dim < nsd; dim++) {
        barycentric[dim] = 0.0;
        for (unsigned int row = 0; row < nsd; row++) {
            barycentric[dim] += this->TinvT(dim, row) * trans[row];
        }
    }

    //// Check Plane
    double plane = 1.0;
    for (unsigned int dim = 0; dim < nsd; dim++) {
        plane -= barycentric[dim];
    }

    // Projection
    unsigned int glob_node_idx = node_it.getIndex(out_mxyz);
    for (unsigned int df = 0; df < out_data.cols; df++) {
        double val = in_data(in_mesh.mien(elem_i, 0), df) * plane;
        for (unsigned int loc_node_i = 0; loc_node_i < nsd; loc_node_i++) {
            val += in_data(in_mesh.mien(elem_i, loc_node_i + 1), df) * barycentric[loc_node_i];
        }
        out_data(glob_node_idx, df) = val;
    }
}

template<unsigned int nsd>
bool Element<nsd>::hasIndex(unsigned int elem_i)
{
    return elem_i == this->elem_i;
}

template class Element<4>;
template class Element<3>;
template class Element<2>;