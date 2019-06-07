#pragma once

template<unsigned int nsd>
class Matrix
{
public:
    Matrix();
    ~Matrix();

    inline double& operator()(unsigned int row, unsigned int col);
    void computeInverseTranspose(Matrix<nsd> &out);
    void print();

    double data[nsd*nsd] = {0.0};
};

