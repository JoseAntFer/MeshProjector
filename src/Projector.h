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

