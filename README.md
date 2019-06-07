# MeshProjector
MeshProjector takes a volumetric mesh with data at its nodes and a cloud of 
points and interpolates the data from the volumetric mesh nodes to the points in
the cloud. The projection works in 2, 3 and 4 dimensions. The input mesh must
be exclusively made out of simplices: triangles, tetrahedra or pentatopes for 
2D, 3D and 4D, respectively.

MeshProjector works by finding which element in the volumetric mesh contains 
which point in the cloud of points. Then, the value of the point is interpolated 
from the values at the element vertices using linear baricentric interpolation. 
For points that are not inside any element, the closest one is selected and the 
projection is computed via extrapolation.

The process is accelerated by using binary classification: both the elements
and the points are recursively classified left or right of a splitting plane.
When a certain depth of recursion or minimum number of elements or nodes is 
matched the classification is stopped and the projection of this small subset of
neighboring elements and points is carried out by brute force.

The complexity of this algorithm is O(n logn). 

## Requirements
- A C++ compiler with support for C++14 and OpenMP 2.0.
- CMake (3.1 or higher) (optional)

## Usage
MeshProjector is used as a command line program. The mandatory arguments (in 
order) are:
- **number of dimensions**: 2, 3 or 4.
- **in_coordinates**: Path to binary file of type `double` containing the input mesh vertices coordinates (row-major ordering).
- **in_connectivity**: Path to binary file of type `int` containing the input mesh connectivity (row-major ordering).
- **in_data**: Path to binary file of type `double` containing the input mesh nodal data. It can have multiple columns for multiple data per node (row-major ordering).
- **out_coordinates**: Path to binary file of type `double` containing the points coordinates to project the data into (row-major ordering).
- **out_data**: Path to where the interpolated will be written after the projection.

Optional arguments (no especific order between them)
- **-swap_endianness**: If this option is present, the projection will be executed in a different endianness that the input/output data.
- **-fortran_indexing**: Add this option if the *in_connectivity* array contain the indices starting by 1 instead of 0.
- **-verbose**: Print some information at different stages of the process. Useful for debugging.

### Examples
The following command can be executed in the *test* folder with some example data:

``./mesh_projector 3 in_coordinates in_connectivity in_data out_coordinates out_data -swap_endianness -fortran_indexing -verbose``

## Contact
jose.fernandez@rwth-aachen.de
