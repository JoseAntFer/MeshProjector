#include "Matrix.h"

#include <iostream>


template<unsigned int nsd>
Matrix<nsd>::Matrix()
{
}

template<unsigned int nsd>
Matrix<nsd>::~Matrix()
{
}

template<unsigned int nsd>
inline double & Matrix<nsd>::operator()(unsigned int row, unsigned int col)
{
    return this->data[row*nsd + col];
}

template<>
void Matrix<3>::computeInverseTranspose(Matrix<3>& out)
{
    out(0, 0) = (*this)(1, 1)*(*this)(2, 2) - (*this)(2, 1)*(*this)(1, 2);
    out(0, 1) = (*this)(1, 0)*(*this)(2, 2) - (*this)(1, 2)*(*this)(2, 0);
    out(0, 2) = (*this)(1, 0)*(*this)(2, 1) - (*this)(1, 1)*(*this)(2, 0);
    double invdet = 1 / (+(*this)(0, 0)*out(0, 0)
        - (*this)(0, 1)*out(0, 1)
        + (*this)(0, 2)*out(0, 2));

    out(0, 0) *= invdet;
    out(1, 0) = -((*this)(0, 1)*(*this)(2, 2) - (*this)(0, 2)*(*this)(2, 1))*invdet;
    out(2, 0) = ((*this)(0, 1)*(*this)(1, 2) - (*this)(0, 2)*(*this)(1, 1))*invdet;

    out(0, 1) *= -invdet;
    out(1, 1) = ((*this)(0, 0)*(*this)(2, 2) - (*this)(0, 2)*(*this)(2, 0))*invdet;
    out(2, 1) = -((*this)(0, 0)*(*this)(1, 2) - (*this)(1, 0)*(*this)(0, 2))*invdet;

    out(0, 2) *= invdet;
    out(1, 2) = -((*this)(0, 0)*(*this)(2, 1) - (*this)(2, 0)*(*this)(0, 1))*invdet;
    out(2, 2) = ((*this)(0, 0)*(*this)(1, 1) - (*this)(1, 0)*(*this)(0, 1))*invdet;
}

template<>
void Matrix<2>::computeInverseTranspose(Matrix<2>& out)
{
    double invdet = 1.0 / ((*this)(0, 0)*(*this)(1, 1) - (*this)(0, 1)*(*this)(1, 0));
    
    out(0, 0) = invdet * (*this)(1, 1);
    out(0, 1) = - invdet * (*this)(1, 0);
    out(1, 0) = - invdet * (*this)(0, 1);
    out(1, 1) = invdet * (*this)(0, 0);
}

template<unsigned int nsd>
void Matrix<nsd>::print()
{
    for (unsigned int row = 0; row < nsd; row++) {
        for (unsigned int col = 0; col < nsd; col++) {
            std::cout << (*this)(row, col) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<>
void Matrix<4>::computeInverseTranspose(Matrix<4>& out)
{
    double A2323 = (*this)(2, 2) * (*this)(3, 3) - (*this)(2, 3) * (*this)(3, 2);
    double A1323 = (*this)(2, 1) * (*this)(3, 3) - (*this)(2, 3) * (*this)(3, 1);
    double A1223 = (*this)(2, 1) * (*this)(3, 2) - (*this)(2, 2) * (*this)(3, 1);
    double A0323 = (*this)(2, 0) * (*this)(3, 3) - (*this)(2, 3) * (*this)(3, 0);
    double A0223 = (*this)(2, 0) * (*this)(3, 2) - (*this)(2, 2) * (*this)(3, 0);
    double A0123 = (*this)(2, 0) * (*this)(3, 1) - (*this)(2, 1) * (*this)(3, 0);
    double A2313 = (*this)(1, 2) * (*this)(3, 3) - (*this)(1, 3) * (*this)(3, 2);
    double A1313 = (*this)(1, 1) * (*this)(3, 3) - (*this)(1, 3) * (*this)(3, 1);
    double A1213 = (*this)(1, 1) * (*this)(3, 2) - (*this)(1, 2) * (*this)(3, 1);
    double A2312 = (*this)(1, 2) * (*this)(2, 3) - (*this)(1, 3) * (*this)(2, 2);
    double A1312 = (*this)(1, 1) * (*this)(2, 3) - (*this)(1, 3) * (*this)(2, 1);
    double A1212 = (*this)(1, 1) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1);
    double A0313 = (*this)(1, 0) * (*this)(3, 3) - (*this)(1, 3) * (*this)(3, 0);
    double A0213 = (*this)(1, 0) * (*this)(3, 2) - (*this)(1, 2) * (*this)(3, 0);
    double A0312 = (*this)(1, 0) * (*this)(2, 3) - (*this)(1, 3) * (*this)(2, 0);
    double A0212 = (*this)(1, 0) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 0);
    double A0113 = (*this)(1, 0) * (*this)(3, 1) - (*this)(1, 1) * (*this)(3, 0);
    double A0112 = (*this)(1, 0) * (*this)(2, 1) - (*this)(1, 1) * (*this)(2, 0);

    double det = (*this)(0, 0) * ((*this)(1, 1) * A2323 - (*this)(1, 2) * A1323 + (*this)(1, 3) * A1223)
        - (*this)(0, 1) * ((*this)(1, 0) * A2323 - (*this)(1, 2) * A0323 + (*this)(1, 3) * A0223)
        + (*this)(0, 2) * ((*this)(1, 0) * A1323 - (*this)(1, 1) * A0323 + (*this)(1, 3) * A0123)
        - (*this)(0, 3) * ((*this)(1, 0) * A1223 - (*this)(1, 1) * A0223 + (*this)(1, 2) * A0123);
    det = 1 / det;

    out(0, 0) = det * ((*this)(1, 1) * A2323 - (*this)(1, 2) * A1323 + (*this)(1, 3) * A1223);
    out(1, 0) = det * -((*this)(0, 1) * A2323 - (*this)(0, 2) * A1323 + (*this)(0, 3) * A1223);
    out(2, 0) = det * ((*this)(0, 1) * A2313 - (*this)(0, 2) * A1313 + (*this)(0, 3) * A1213);
    out(3, 0) = det * -((*this)(0, 1) * A2312 - (*this)(0, 2) * A1312 + (*this)(0, 3) * A1212);
    out(0, 1) = det * -((*this)(1, 0) * A2323 - (*this)(1, 2) * A0323 + (*this)(1, 3) * A0223);
    out(1, 1) = det * ((*this)(0, 0) * A2323 - (*this)(0, 2) * A0323 + (*this)(0, 3) * A0223);
    out(2, 1) = det * -((*this)(0, 0) * A2313 - (*this)(0, 2) * A0313 + (*this)(0, 3) * A0213);
    out(3, 1) = det * ((*this)(0, 0) * A2312 - (*this)(0, 2) * A0312 + (*this)(0, 3) * A0212);
    out(0, 2) = det * ((*this)(1, 0) * A1323 - (*this)(1, 1) * A0323 + (*this)(1, 3) * A0123);
    out(1, 2) = det * -((*this)(0, 0) * A1323 - (*this)(0, 1) * A0323 + (*this)(0, 3) * A0123);
    out(2, 2) = det * ((*this)(0, 0) * A1313 - (*this)(0, 1) * A0313 + (*this)(0, 3) * A0113);
    out(3, 2) = det * -((*this)(0, 0) * A1312 - (*this)(0, 1) * A0312 + (*this)(0, 3) * A0112);
    out(0, 3) = det * -((*this)(1, 0) * A1223 - (*this)(1, 1) * A0223 + (*this)(1, 2) * A0123);
    out(1, 3) = det * ((*this)(0, 0) * A1223 - (*this)(0, 1) * A0223 + (*this)(0, 2) * A0123);
    out(2, 3) = det * -((*this)(0, 0) * A1213 - (*this)(0, 1) * A0213 + (*this)(0, 2) * A0113);
    out(3, 3) = det * ((*this)(0, 0) * A1212 - (*this)(0, 1) * A0212 + (*this)(0, 2) * A0112);
}

template class Matrix<3>;
template class Matrix<2>;
template class Matrix<4>;