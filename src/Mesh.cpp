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
