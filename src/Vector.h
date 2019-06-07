#pragma once

/*
This class is a simple chunk of memory of size nsd. It is useful
though because makes C++ better syntaxis that working directly
with the raw chunk of memory.

I didn't notice a change in performance.
*/
template<unsigned int nsd>
class Vector
{
public:
    Vector();
    ~Vector();

    inline double& operator()(unsigned int pos);

    double data[nsd];
};

