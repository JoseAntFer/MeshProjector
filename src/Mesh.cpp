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
#include "Mesh.h"

#include <iostream>
#include <fstream>

#include "path_utilities.h"


Mesh::Mesh()
{
}

Mesh::Mesh(Array<double>& mxyz, Array<unsigned int>& mien) :
	mxyz(mxyz), mien(mien)
{
	this->nn = mxyz.rows;
	this->ne = mien.rows;
	this->nsd = mxyz.cols;
	this->nen = mien.cols;
}

Mesh::~Mesh()
{
}

void Mesh::print()
{
    std::cout << "nen: " << this->nen << std::endl;
    std::cout << "nsd: " << this->nsd << std::endl;

    std::cout << "nn: "  << this->nn  << std::endl;
    this->mxyz.print(3);

    std::cout << "ne: "  << this->ne  << std::endl;
    this->mien.print(3);
}

double Mesh::getCoordByElem(unsigned int elem_i, unsigned int loc_node_i, unsigned int dim)
{
    return this->mxyz(this->mien(elem_i, loc_node_i), dim);
}
