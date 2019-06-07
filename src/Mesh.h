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
