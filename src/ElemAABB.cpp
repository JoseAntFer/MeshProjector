#include "ElemAABB.h"

#include <algorithm>


template<unsigned int nsd>
ElemAABB<nsd>::ElemAABB()
{
}

template<unsigned int nsd>
ElemAABB<nsd>::ElemAABB(Mesh & mesh, unsigned int elem_i)
{
    // Index
    this->elem_i = elem_i;

    // Axes Alligned Bounding Box
    for (unsigned int dim = 0; dim < nsd; dim++) {
        this->bottom(dim) = mesh.getCoordByElem(elem_i, 0, dim);
        this->top(dim) = mesh.getCoordByElem(elem_i, 0, dim);
    }

    for (unsigned int loc_node_i = 1; loc_node_i < (nsd + 1); loc_node_i++) {
        for (unsigned int dim = 0; dim < nsd; dim++) {
            this->bottom(dim) = std::min(this->bottom(dim), mesh.getCoordByElem(elem_i, loc_node_i, dim));
            this->top(dim)    = std::max(this->top(dim), mesh.getCoordByElem(elem_i, loc_node_i, dim));
        }
    }
}

template<unsigned int nsd>
ElemAABB<nsd>::~ElemAABB()
{
}

template class ElemAABB<4>;
template class ElemAABB<3>;
template class ElemAABB<2>;