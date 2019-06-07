#pragma once
#include <vector>

#include "Array.h"
#include "PointIt.h"
#include "Vector.h"

template<unsigned int nsd>
class AABB
{
public:
    /* Methods */
    AABB();
    AABB(Array<double> &arr);
    AABB(Vector<nsd> &bottom, Vector<nsd> &top);
    ~AABB();

    unsigned int largestAxis();
    void split(unsigned int dim, double pivot, AABB &left, AABB &rght);
    bool containsPoint(PointIt &point_it);
    double distanceSqToCentroid(PointIt &point_it);

    /* Members */
    Vector<nsd> bottom;
    Vector<nsd> top;
};

