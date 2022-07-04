#include "Utils/Resources.h"

std::string res::loadPath(std::string path)
{
    if (path[0] == '/')
        return "../res" + path;
    else
        return "../res/" + path;
}