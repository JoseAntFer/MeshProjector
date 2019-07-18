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
