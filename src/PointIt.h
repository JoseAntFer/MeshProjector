#pragma once
#include <vector>
#include <iostream>

#include "Array.h"

/*
Point Iterator Class.

Represents a <double> point that is stored in memory in a
continuous std::vector<double> elsewhere. This class only
contains the iterator to the first element and it is 
designed to quickly and cleanly access to the coordinates
of the point without explicit memory copy.
*/
class PointIt
{
public:
    /* Methods */
    PointIt();
    PointIt(std::vector<double>::iterator it);
    ~PointIt();

    const double& operator()(unsigned int pos) const;
    const unsigned int getIndex(Array<double> &arr);
    void print(unsigned int nsd);

    /* Members */
    std::vector<double>::iterator it;
};
