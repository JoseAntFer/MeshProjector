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
#include <string>
#include <memory>

#include "Array.h"
#include "PointIt.h"

class Mesh
{
public:
    /* Methods */
    Mesh();
    Mesh(Array<double> &mxyz, Array<unsigned int> &mien);
    //Mesh(std::string minf_path, bool swapbytes=false, bool fortran_indexing=false);
    ~Mesh();

    void print();
    //void readMinfFile(std::string minf_path);
    //void readMXYZandMIEN();
    //void readMXYZ();
    double getCoordByElem(unsigned int elem_i, unsigned int loc_node_i, unsigned int dim);

    /* Members */
    unsigned int nn = 0;
    unsigned int ne = 0;
    unsigned int nsd = 0;
    unsigned int nen = 0;
    Array<double> mxyz;
    Array<unsigned int> mien;
    //bool swapped = false;
    //bool index_shifted = false;
    //std::string root_path;
    //std::string minf_path;
    //std::string mxyz_path;
    //std::string mien_path;
};
