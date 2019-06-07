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
