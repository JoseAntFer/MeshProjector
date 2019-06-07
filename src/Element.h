#pragma once
#include <vector>
#include <memory>

#include "Array.h"
#include "Mesh.h"
#include "PointIt.h"
#include "Matrix.h"
#include "Vector.h"

template<unsigned int nsd>
class Element
{
public:
    /* Methods */
    Element();
    ~Element();

    void prepareProjection(Mesh &mesh, unsigned int elem_i);
    bool projectIfInside(Mesh &in_mesh, unsigned int elem_i, Array<double> &out_mxyz, Array<double> &in_data, Array<double> &out_data, PointIt &node_it);
    void project(Mesh &in_mesh, unsigned int elem_i, Array<double> &out_mxyz, Array<double> &in_data, Array<double> &out_data, PointIt &node_it);
    bool hasIndex(unsigned int elem_i);

    /* Members */
    Matrix<nsd> TinvT;
    PointIt origin_it;
    unsigned int elem_i = -1;
};
