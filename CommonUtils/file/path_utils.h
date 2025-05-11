#pragma once
#include <string>
#include <vector>
namespace CommonUtils
{
    std::string getPath(const char* name);
    const char* getSuffix(const std::string& name);
    const char* getSuffix(const char* name);
    std::string removeSuffix(const std::string& name);

    std::string getShortFilename(const std::string& name);

    std::string getDirectory(const char* filename);
    std::string getParentDirectory(const char* filename);
}