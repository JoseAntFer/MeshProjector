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
