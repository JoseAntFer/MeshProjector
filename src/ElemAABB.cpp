/*
MIT License

Copyright (c) 2019 Jose Antonio Fernandez Fernandez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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