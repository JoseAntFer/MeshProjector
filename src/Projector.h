#pragma once

#include "Mesh.h"
#include "Element.h"
#include "ElemAABB.h"
#include "AABB.h"
#include "PointIt.h"

template<unsigned int nsd>
class Projector
{
public:
    /* Methods */
    Projector();
    Projector(Mesh &in_mesh, Array<double> &out_mxyz, Array<double> &in_data);
    ~Projector();

    Array<double> & run();
    void classify(std::vector<ElemAABB<nsd>*> &in_elems, std::vector<PointIt> &out_node_its, AABB<nsd> &aabb, unsigned int depth = 0);
    void project(std::vector<ElemAABB<nsd>*> &in_elems, std::vector<PointIt> &out_node_its);

    /* Members */
    Mesh *in_mesh;
    Array<double> *out_mxyz;
    Array<double> *in_data;
    std::shared_ptr<Array<double>> out_data;
    unsigned int nen;
    unsigned int ndf;
    unsigned int in_ne;
    unsigned int out_nn;
    unsigned int cap = 30;
    unsigned int parallel_depth = 0;
    int max_threads = 1;
};

