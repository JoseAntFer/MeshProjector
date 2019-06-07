#pragma once
#include <memory>

#include "AABB.h"
#include "Mesh.h"

template<unsigned int nsd>
class ElemAABB :
    public AABB<nsd>
{
public:
    ElemAABB();
    ElemAABB(Mesh &mesh, unsigned int elem_i);
    ~ElemAABB();

    unsigned int elem_i;  // TODO: Could be iterator to mien?
};
