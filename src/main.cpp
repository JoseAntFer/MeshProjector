/*
MIT License

Copyright (c) 2019 Jose Antonio Fernandez Fernandez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <stddef.h>
#include <iostream>
#include <chrono>
#include <string>

#include "Array.h"
#include "Mesh.h"
#include "Projector.h"
#include "Matrix.h"
#include "path_utilities.h"

/*       TIMING FUNCTIONS       */
std::chrono::time_point<std::chrono::high_resolution_clock> time() {
	return std::chrono::high_resolution_clock::now();
}

void printTiming(std::chrono::time_point<std::chrono::high_resolution_clock> t1,
	std::chrono::time_point<std::chrono::high_resolution_clock> t2,
	std::string message)
{
	std::cout << message << " " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
		<< " milliseconds\n";
}
/*       END TIMING FUNCTIONS       */



int main(int argc, char *argv[]) 
{
	auto t1 = time();

    // Argument processing
    //// Wrong argument pattern
    if ((argc < 7) || (argc > 10)) {
        std::cout << "Wrong numer of arguments. Please, try:" << std::endl;
        std::cout << "./mesh_projector number_of_dimensions in_coordinates in_connectivity in_data out_coordinates out_data [-swap_endianness] [-fortran_indexing] [-verbose]" << std::endl;
        abort();
    }
    
    //// Set mandatory arguments
	int nsd = std::stoi(argv[1]);
    std::string in_mxyz_path = argv[2];
    std::string in_mien_path = argv[3];
    std::string in_data_path = argv[4];
    std::string out_mxyz_path = argv[5];
    std::string out_data_path = argv[6];

    //// Process optional arguments
    bool fortran_indexing = false;  // default
    bool swap_endianness = false;  // default
    bool verbose = false;  // default
    for (int arg_i = 7; arg_i < argc; arg_i++) {
        std::string str_arg = argv[arg_i];
        if (str_arg == "-swap_endianness") {
            swap_endianness = true;
        }
        if (str_arg == "-fortran_indexing") {
            fortran_indexing = true;
        }
        if (str_arg == "-verbose") {
			verbose = true;
        }
    }

    // Loading data from drive
	if (verbose)
		std::cout << "Reading arrays..." << std::endl;

	Array<double> in_mxyz;
	Array<unsigned int> in_mien;
	Array<double> in_data;
	Array<double> out_mxyz;
	in_mxyz.readBinaryFile(in_mxyz_path, -1, nsd);
	in_mien.readBinaryFile(in_mien_path, -1, nsd+1);
	in_data.readBinaryFile(in_data_path, in_mxyz.rows, -1);
	out_mxyz.readBinaryFile(out_mxyz_path, -1, nsd);

	//// Swap bytes
	if (swap_endianness) {
		if (verbose)
			std::cout << "Swapping bytes..." << std::endl;

		in_mxyz.swapBytes();
		in_mien.swapBytes();
		in_data.swapBytes();
		out_mxyz.swapBytes();
	}
		
	//// Fortran indexing
	if (fortran_indexing) {
		if (verbose)
			std::cout << "Fortran indexing..." << std::endl;

		for (unsigned int i = 0; i < in_mien.data.size(); i++) {
			in_mien.data[i] -= 1;
		}
	}

	if (verbose) {
		std::cout << "Input mesh coordinates:" << std::endl;
		in_mxyz.print();
		std::cout << std::endl;

		std::cout << "Input mesh connectivity:" << std::endl;
		in_mien.print();
		std::cout << std::endl;

		std::cout << "Input mesh data:" << std::endl;
		in_data.print();
		std::cout << std::endl;

		std::cout << "Input target point coordinates:" << std::endl;
		out_mxyz.print();
		std::cout << std::endl;
	}


	// To Mesh class
	Mesh in_mesh(in_mxyz, in_mien);

    // Execute projection
	if (verbose)
		std::cout << "Projecting..." << std::endl;

    Array<double> out_data;
    if (in_mesh.nsd == 4) {
        Projector<4> projector(in_mesh, out_mxyz, in_data);
        out_data = projector.run();
    }
    else if (in_mesh.nsd == 3) {
        Projector<3> projector(in_mesh, out_mxyz, in_data);
        out_data = projector.run();
    }
    else if (in_mesh.nsd == 2) {
        Projector<2> projector(in_mesh, out_mxyz, in_data);
        out_data = projector.run();
    }

	if (verbose) {
		std::cout << "Output projected data:" << std::endl;
		out_data.print();
		std::cout << std::endl;
	}

    // Save result to drive
	if (verbose)
		std::cout << "Writing solution..." << std::endl;
	
	if (swap_endianness) {
        out_data.swapBytes();
    }
    out_data.writeBinaryFile(out_data_path);

	// Print time taken
	auto t2 = time();
	printTiming(t1, t2, "MeshProjector run successfully. It took ");

    return 0;
}
