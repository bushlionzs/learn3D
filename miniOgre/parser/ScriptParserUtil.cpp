#include "OgreHeader.h"
#include "ScriptParserUtil.h"


std::string NextAfterNewLine(std::stringstream& ss, std::string& nextElement)
{
    std::string skipped = SkipLine(ss);
    ss >> nextElement;
    return skipped;
}

std::string SkipLine(std::stringstream& ss) 
{
    std::string skipped;
    getline(ss, skipped);

    if (skipped.length() >= 2)
    {
        if (skipped.back() == '\n')
        {
            skipped.pop_back();
        }

        if (skipped.back() == '\r')
        {
            skipped.pop_back();
        }
    }
    return skipped;
}

