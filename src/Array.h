#pragma once

#include <vector>
#include <string>

template<class T>
class Array
{
public:
    /* Methods */
    Array();
    Array(std::vector<T> &data, unsigned int rows, unsigned int cols);
    Array(unsigned int rows, unsigned int cols);
    ~Array();

    void readBinaryFile(std::string filename, int rows = -1, int cols = -1);
    void writeBinaryFile(std::string filename);
    void resize(unsigned int rows, unsigned int cols);
    void print(unsigned int lines = 10);
    bool isEmpty();

    inline T& operator()(unsigned int row, unsigned int col);
    const inline T& operator()(unsigned int row, unsigned int col) const;

    void swapBytes();
    void fill(T val, unsigned int rows, unsigned int cols);

    /* Members */
    unsigned int rows = 0;
    unsigned int cols = 0;
    std::vector<T> data;
};
