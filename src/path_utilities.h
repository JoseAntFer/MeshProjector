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
#include <string>


static std::string makePathUNIX(std::string path)
{
    std::string unix_path;

    for (int i = 0; i < (int)path.length(); i++) {
        if (path[i] != '\\') {
            unix_path += path[i];
        }
        else {
            unix_path += '/';
        }
    }

    return unix_path;
}

static std::string getFolderFromPath(std::string path)
{
    for (int i = (int)path.length() - 1; i > 0; i--) {
        if (path[i] == '/') {
            return path.substr(0, i);
        }
    }

    return ".";
}

static std::string getFilenameFromPath(std::string path)
{
    for (int i = (int)path.length() - 1; i > 0; i--) {
        if (path[i] == '/') {
            return path.substr(i, path.length());
        }
    }

    return ".";
}
