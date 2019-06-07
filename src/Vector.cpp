#include "Vector.h"


template<unsigned int nsd>
Vector<nsd>::Vector()
{
}

template<unsigned int nsd>
Vector<nsd>::~Vector()
{
}

template<unsigned int nsd>
inline double & Vector<nsd>::operator()(unsigned int pos)
{
    return this->data[pos];
}

template class Vector<4>;
template class Vector<3>;
template class Vector<2>;