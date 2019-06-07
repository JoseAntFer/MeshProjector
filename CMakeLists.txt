cmake_minimum_required(VERSION 3.1)
project(MeshProjector)
set(CMAKE_CXX_STANDARD 14)

# External dependencies
## OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(SOURCE_FILES
    src/AABB.cpp
	src/AABB.h
	src/Array.cpp
	src/Array.h
	src/ElemAABB.cpp
	src/ElemAABB.h
	src/Element.cpp
	src/Element.h
	src/main.cpp
	src/Matrix.cpp
	src/Matrix.h
	src/Mesh.cpp
	src/Mesh.h
	src/PointIt.cpp
	src/PointIt.h
	src/Projector.cpp
	src/Projector.h
	src/Vector.cpp
	src/Vector.h)
    
# Create a standalone executable for the geo module
add_executable(mesh_projector ${SOURCE_FILES})