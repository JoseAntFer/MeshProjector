#include "PointIt.h"



PointIt::PointIt()
{
}

PointIt::PointIt(std::vector<double>::iterator it)
{
    this->it = it;
}


PointIt::~PointIt()
{
}

const double & PointIt::operator()(unsigned int pos) const
{
    return *(it + pos);
}

const unsigned int PointIt::getIndex(Array<double> &arr)
{
    return (unsigned int)(this->it - arr.data.begin())/arr.cols;
}

void PointIt::print(unsigned int nsd)
{
    std::cout << "[ ";
    for (unsigned int dim = 0; dim < nsd; dim++) {
        std::cout << (*this)(dim) << ", ";
    }
    std::cout << " ]" << std::endl;
}
