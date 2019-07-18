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
#include "AABB.h"

#include <algorithm>
#include <limits>
#include <iostream>

template<unsigned int nsd>
AABB<nsd>::AABB()
{
}

template<unsigned int nsd>
AABB<nsd>::AABB(Array<double>& arr)
{
    // Initialize bottom and top
    for (unsigned int col = 0; col < nsd; col++) {
        this->bottom(col) = arr(0, col);
        this->top(col)    = arr(0, col);;
    }

    // Compute boundaries
    for (unsigned int row = 1; row < arr.rows; row++) {
        for (unsigned int col = 0; col < nsd; col++) {
            this->bottom(col) = std::min(this->bottom(col), arr(row, col));
            this->top(col)    = std::max(this->top(col),    arr(row, col));
        }
    }
}

template<unsigned int nsd>
AABB<nsd>::AABB(Vector<nsd> &bottom, Vector<nsd> &top)
{
    this->bottom = bottom;
    this->top = top;
}

template<unsigned int nsd>
AABB<nsd>::~AABB()
{
}

template<unsigned int nsd>
unsigned int AABB<nsd>::largestAxis()
{
    unsigned int idx = 0;
    double max_val = this->top(0) - this->bottom(0);

    for (unsigned int i = 1; i < nsd; i++) {
        double new_val = this->top(i) - this->bottom(i);
        if (new_val > max_val) {
            max_val = new_val;
            idx = i;
        }
    }

    return idx;
}

template<unsigned int nsd>
void AABB<nsd>::split(unsigned int pivot_dim, double pivot, AABB & left, AABB & rght)
{
    left.bottom = Vector<nsd>(this->bottom);
    left.top = Vector<nsd>(this->top);

    rght.bottom = Vector<nsd>(this->bottom);
    rght.top = Vector<nsd>(this->top);

    left.top(pivot_dim) = pivot;
    rght.bottom(pivot_dim) = pivot;
}

template<unsigned int nsd>
bool AABB<nsd>::containsPoint(PointIt & point_it)
{
    for (unsigned int dim = 0; dim < nsd; dim++) {
        if ( (point_it(dim) < this->bottom(dim)) || (point_it(dim) > this->top(dim)) ) {
            return false;
        }
    }
    return true;
}

template<unsigned int nsd>
double AABB<nsd>::distanceSqToCentroid(PointIt & point_it)
{
    double dist_sq = 0.0;
    for (unsigned int dim = 0; dim < nsd; dim++) {
        double centroid = 0.5*(this->bottom(dim) + this->top(dim));
        double rel = centroid - point_it(dim);
        dist_sq += rel * rel;
    }
    
    return dist_sq;
}

template class AABB<4>;
template class AABB<3>;
template class AABB<2>;