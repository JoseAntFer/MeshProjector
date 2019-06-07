#include "Array.h"

#include <iostream>
#include <fstream>  // Read and write files
#include <utility>  // swap

#include <cstring>

/*         SWAP BYTE FUNCTIONS         */
// int, float
void swap4(void* v)
{
	char    in[4], out[4];
	std::memcpy(in, v, 4);
	out[0] = in[3];
	out[1] = in[2];
	out[2] = in[1];
	out[3] = in[0];
	std::memcpy(v, out, 4);
}

// double
void swap8(void* v)
{
	char    in[8], out[8];
	std::memcpy(in, v, 8);
	out[0] = in[7];
	out[1] = in[6];
	out[2] = in[5];
	out[3] = in[4];
	out[4] = in[3];
	out[5] = in[2];
	out[6] = in[1];
	out[7] = in[0];
	std::memcpy(v, out, 8);
}
/*         END SWAP BYTE FUNCTIONS         */



template<class T>
Array<T>::Array()
{
}

template<class T>
Array<T>::Array(std::vector<T> & data, unsigned int rows, unsigned int cols)
{
    // Set dimensions
    this->rows = rows;
    this->cols = cols;

    // Copy the data
    this->data = std::vector<T>(data);
}

template<class T>
Array<T>::Array(unsigned int rows, unsigned int cols)
{
    this->data.resize(rows*cols);
    this->rows = rows;
    this->cols = cols;
}

template<class T>
Array<T>::~Array()
{
}

template<class T>
void Array<T>::readBinaryFile(std::string filename, int rows, int cols)
{
    // Open the binary file
    std::ifstream infile(filename, std::ios::binary);
    if (!infile) {
        std::cout << "Not possible to read file " << filename << ". \n";
        abort();
    }

    // Infer dimensions
    if ((rows == -1) || (cols == -1)) {
        // Infer dimensions by the file size
        infile.seekg(0, std::ios::end);
        int length = (unsigned int) infile.tellg() / sizeof(T);
        infile.seekg(0, std::ios::beg);

		if (rows == -1) {
			this->cols = cols;
			this->rows = length / cols;
		}
		else {
			this->rows = rows;
			this->cols = length / rows;
		}

		if (this->rows*this->cols != length) {
			std::cout << "Error reading binary file " << filename << ": n_rows*n_cols != file_length." << std::endl;
			abort();
		}
    }

	// User given dimensions
    else {
        this->cols = cols;
        this->rows = rows;
    }

    this->data.resize(this->rows*this->cols);
    infile.read(reinterpret_cast<char*>(&this->data.data()[0]), this->data.size()*sizeof(T));

    infile.close();
}

template<class T>
void Array<T>::writeBinaryFile(std::string filename)
{
    // Open the binary file
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile) {
        std::cout << "Not possible to open file " << filename << ". \n";
    }

	outfile.write(reinterpret_cast<char*>(&this->data.data()[0]), this->data.size() * sizeof(T));
	outfile.close();
}

template<class T>
void Array<T>::resize(unsigned int rows, unsigned int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->data.resize(rows*cols);
}

template<class T>
void Array<T>::print(unsigned int lines)
{
    for (unsigned int row = 0; row < lines; row++) {
        if (row < this->rows) {
            for (unsigned int col = 0; col < this->cols; col++) {
                std::cout << (*this)(row, col) << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
}

template<class T>
bool Array<T>::isEmpty()
{
    return this->data.size() == 0;
}

template<class T>
inline T& Array<T>::operator()(unsigned int row, unsigned int col)
{
    return this->data[row*this->cols + col];
}

template<class T>
inline const T& Array<T>::operator()(unsigned int row, unsigned int col) const
{
    return this->data[row*this->cols + col];
}

template<class T>
void Array<T>::swapBytes()
{
    if (sizeof(T) == 8) {
        for (unsigned int i = 0; i < this->data.size(); i++)
            swap8(&this->data[i]);
    }
    else if (sizeof(T) == 4) {
        for (unsigned int i = 0; i < this->data.size(); i++)
            swap4(&this->data[i]);
    }
}

//template<class T>
//void Array<T>::reorder(short order)
//{
//    if (order == ROW_MAJOR) {
//        if (this->order == ROW_MAJOR)
//            return;
//    }
//    else if (order == COL_MAJOR) {
//        if (this->order == COL_MAJOR)
//            return;
//    }
//    else {
//        std::cout << "Not valid ordering " << order << " in Array<T>::reorder" << std::endl;
//    }
//
//    transpose(this->data.begin(), this->data.end(), this->rows, this->cols);
//    this->order = order;
//    std::swap(this->rows, this->cols);
//}

template<class T>
void Array<T>::fill(T val, unsigned int rows, unsigned int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->data.resize(rows*cols);
    std::fill(this->data.begin(), this->data.end(), val);
}

// explicit instantiations
template class Array<unsigned int>;
template class Array<double>;