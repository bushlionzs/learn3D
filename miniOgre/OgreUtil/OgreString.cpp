/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "OgreHeader.h"
#include "OgreString.h"
#include <iostream>
#include <fstream>

// A quick define to overcome different names for the same function
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WINRT
#   define strnicmp _strnicmp
#else
#   define strnicmp strncasecmp
#endif

namespace Ogre {
    //-----------------------------------------------------------------------
    void StringUtil::trim(String& str, bool left, bool right)
    {
        /*
        size_t lspaces, rspaces, len = length(), i;

        lspaces = rspaces = 0;

        if( left )
        {
            // Find spaces / tabs on the left
            for( i = 0;
                i < len && ( at(i) == ' ' || at(i) == '\t' || at(i) == '\r');
                ++lspaces, ++i );
        }
        
        if( right && lspaces < len )
        {
            // Find spaces / tabs on the right
            for( i = len - 1;
                i >= 0 && ( at(i) == ' ' || at(i) == '\t' || at(i) == '\r');
                rspaces++, i-- );
        }

        *this = substr(lspaces, len-lspaces-rspaces);
        */
        static const String delims = " \t\r\n";
        if(right)
            str.erase(str.find_last_not_of(delims)+1); // trim right
        if(left)
            str.erase(0, str.find_first_not_of(delims)); // trim left
    }

    //-----------------------------------------------------------------------
    StringVector StringUtil::split( const String& str, const String& delims, unsigned int maxSplits, bool preserveDelims)
    {
        StringVector ret;
        // Pre-allocate some space for performance
        ret.reserve(maxSplits ? maxSplits+1 : 10);    // 10 is guessed capacity for most case

        unsigned int numSplits = 0;

        // Use STL methods 
        size_t start, pos;
        start = 0;
        do 
        {
            pos = str.find_first_of(delims, start);
            if (pos == start)
            {
                // Do nothing
                start = pos + 1;
            }
            else if (pos == String::npos || (maxSplits && numSplits == maxSplits))
            {
                // Copy the rest of the string
                ret.push_back( str.substr(start) );
                break;
            }
            else
            {
                // Copy up to delimiter
                ret.push_back( str.substr(start, pos - start) );

                if(preserveDelims)
                {
                    // Sometimes there could be more than one delimiter in a row.
                    // Loop until we don't find any more delims
                    size_t delimStart = pos, delimPos;
                    delimPos = str.find_first_not_of(delims, delimStart);
                    if (delimPos == String::npos)
                    {
                        // Copy the rest of the string
                        ret.push_back( str.substr(delimStart) );
                    }
                    else
                    {
                        ret.push_back( str.substr(delimStart, delimPos - delimStart) );
                    }
                }

                start = pos + 1;
            }
            // parse up to next real data
            start = str.find_first_not_of(delims, start);
            ++numSplits;

        } while (pos != String::npos);



        return ret;
    }
    //-----------------------------------------------------------------------
    StringVector StringUtil::tokenise( const String& str, const String& singleDelims, const String& doubleDelims, unsigned int maxSplits)
    {
        StringVector ret;
        // Pre-allocate some space for performance
        ret.reserve(maxSplits ? maxSplits+1 : 10);    // 10 is guessed capacity for most case

        unsigned int numSplits = 0;
        String delims = singleDelims + doubleDelims;

        // Use STL methods 
        size_t start, pos;
        char curDoubleDelim = 0;
        start = 0;
        do 
        {
            if (curDoubleDelim != 0)
            {
                pos = str.find(curDoubleDelim, start);
            }
            else
            {
                pos = str.find_first_of(delims, start);
            }

            if (pos == start)
            {
                char curDelim = str.at(pos);
                if (doubleDelims.find_first_of(curDelim) != String::npos)
                {
                    curDoubleDelim = curDelim;
                }
                // Do nothing
                start = pos + 1;
            }
            else if (pos == String::npos || (maxSplits && numSplits == maxSplits))
            {
                if (curDoubleDelim != 0)
                {
                    //Missing closer. Warn or throw exception?
                }
                // Copy the rest of the string
                ret.push_back( str.substr(start) );
                break;
            }
            else
            {
                if (curDoubleDelim != 0)
                {
                    curDoubleDelim = 0;
                }

                // Copy up to delimiter
                ret.push_back( str.substr(start, pos - start) );
                start = pos + 1;
            }
            if (curDoubleDelim == 0)
            {
                // parse up to next real data
                start = str.find_first_not_of(singleDelims, start);
            }
            
            ++numSplits;

        } while (start != String::npos);

        return ret;
    }
    //-----------------------------------------------------------------------
    void StringUtil::toLowerCase(String& str)
    {
        std::transform(
            str.begin(),
            str.end(),
            str.begin(),
            tolower);
    }

    //-----------------------------------------------------------------------
    void StringUtil::toUpperCase(String& str) 
    {
        std::transform(
            str.begin(),
            str.end(),
            str.begin(),
            toupper);
    }
    //-----------------------------------------------------------------------
    void StringUtil::toTitleCase(String& str) 
    {
        String::iterator it = str.begin();
        *it = toupper(*it);
        for (; it != str.end() - 1; it++)
        {
            if (*it == ' ') 
            {
                *(it + 1) = toupper(*(it + 1));
            }
        }
    }
    //-----------------------------------------------------------------------
    bool StringUtil::startsWith(const String& str, const String& pattern, bool lowerCase)
    {
        if (pattern.empty())
            return false;

        if (lowerCase)
        {
            return strnicmp(str.c_str(), pattern.c_str(), pattern.size()) == 0;
        }

        return strncmp(str.c_str(), pattern.c_str(), pattern.size()) == 0;
    }
    //-----------------------------------------------------------------------
    bool StringUtil::endsWith(const String& str, const String& pattern, bool lowerCase)
    {
        if (pattern.empty())
            return false;

        size_t offset = str.size() - pattern.size();

        if (lowerCase)
        {
            return strnicmp(str.c_str() + offset, pattern.c_str(), pattern.size()) == 0;
        }

        return strncmp(str.c_str() + offset, pattern.c_str(), pattern.size()) == 0;
    }
    //-----------------------------------------------------------------------
    String StringUtil::standardisePath(const String& init)
    {
        String path = init;

        std::replace( path.begin(), path.end(), '\\', '/' );
        if( path[path.length() - 1] != '/' )
            path += '/';

        return path;
    }
    //-----------------------------------------------------------------------
    String StringUtil::normalizeFilePath(const String& init, bool makeLowerCase)
    {
        const char* bufferSrc = init.c_str();
        int pathLen = (int)init.size();
        int indexSrc = 0;
        int indexDst = 0;
        int metaPathArea = 0;

        char reservedBuf[1024];
        char* bufferDst = reservedBuf;
        bool isDestAllocated = false;
        if (pathLen > 1023)
        {
            //if source path is to long ensure we don't do a buffer overrun by allocating some
            //new memory
            isDestAllocated = true;
            bufferDst = new char[pathLen + 1];
        }

        //The outer loop loops over directories
        while (indexSrc < pathLen)
        {       
            if (indexSrc && ((bufferSrc[indexSrc] == '\\') || (bufferSrc[indexSrc] == '/')))
            {
                //check if we have a directory delimiter if so skip it (we should already
                //have written such a delimiter by this point
                ++indexSrc;
                continue;
            }
            else
            {
                //check if there is a directory to skip of type ".\"
                if ((bufferSrc[indexSrc] == '.') && 
                    ((bufferSrc[indexSrc + 1] == '\\') || (bufferSrc[indexSrc + 1] == '/')))
                {
                    indexSrc += 2;
                    continue;           
                }

                //check if there is a directory to skip of type "..\"
                else if ((bufferSrc[indexSrc] == '.') && (bufferSrc[indexSrc + 1] == '.') &&
                    ((bufferSrc[indexSrc + 2] == '\\') || (bufferSrc[indexSrc + 2] == '/')))
                {
                    if (indexDst > metaPathArea)
                    {
                        //skip a directory backward in the destination path
                        do {
                            --indexDst;
                        }
                        while ((indexDst > metaPathArea) && (bufferDst[indexDst - 1] != '/'));
                        indexSrc += 3;
                        continue;
                    }
                    else
                    {
                        //we are about to write "..\" to the destination buffer
                        //ensure we will not remove this in future "skip directories"
                        metaPathArea += 3;
                    }
                }
            }

            //transfer the current directory name from the source to the destination
            while (indexSrc < pathLen)
            {
                char curChar = bufferSrc[indexSrc];
                if (makeLowerCase) curChar = tolower(curChar);
                if ((curChar == '\\') || (curChar == '/')) curChar = '/';
                bufferDst[indexDst] = curChar;
                ++indexDst;
                ++indexSrc;
                if (curChar == '/') break;
            }
        }
        bufferDst[indexDst] = 0;

        String normalized(bufferDst); 
        if (isDestAllocated)
        {
            delete[] bufferDst;
        }

        return normalized;      
    }
    //-----------------------------------------------------------------------
    void StringUtil::splitFilename(const String& qualifiedName, 
        String& outBasename, String& outPath)
    {
        String path = qualifiedName;
        // Replace \ with / first
        std::replace( path.begin(), path.end(), '\\', '/' );
        // split based on final /
        size_t i = path.find_last_of('/');

        if (i == String::npos)
        {
            outPath.clear();
            outBasename = qualifiedName;
        }
        else
        {
            outBasename = path.substr(i+1, path.size() - i - 1);
            outPath = path.substr(0, i+1);
        }

    }
    //-----------------------------------------------------------------------
    void StringUtil::splitBaseFilename(const String& fullName, 
        String& outBasename, String& outExtention)
    {
        size_t i = fullName.find_last_of('.');
        if (i == String::npos)
        {
            outExtention.clear();
            outBasename = fullName;
        }
        else
        {
            outExtention = fullName.substr(i+1);
            outBasename = fullName.substr(0, i);
        }
    }
    // ----------------------------------------------------------------------------------------------------------------------------------------------
    void StringUtil::splitFullFilename( const String& qualifiedName, 
        String& outBasename, String& outExtention, String& outPath )
    {
        String fullName;
        splitFilename( qualifiedName, fullName, outPath );
        splitBaseFilename( fullName, outBasename, outExtention );
    }
    //-----------------------------------------------------------------------
    bool StringUtil::match(const String& str, const String& pattern, bool caseSensitive)
    {
        String tmpStr = str;
        String tmpPattern = pattern;
        if (!caseSensitive)
        {
            StringUtil::toLowerCase(tmpStr);
            StringUtil::toLowerCase(tmpPattern);
        }

        String::const_iterator strIt = tmpStr.begin();
        String::const_iterator patIt = tmpPattern.begin();
        String::const_iterator lastWildCardIt = tmpPattern.end();
        while (strIt != tmpStr.end() && patIt != tmpPattern.end())
        {
            if (*patIt == '*')
            {
                lastWildCardIt = patIt;
                // Skip over looking for next character
                ++patIt;
                if (patIt == tmpPattern.end())
                {
                    // Skip right to the end since * matches the entire rest of the string
                    strIt = tmpStr.end();
                }
                else
                {
                    // scan until we find next pattern character
                    while(strIt != tmpStr.end() && *strIt != *patIt)
                        ++strIt;
                }
            }
            else
            {
                if (*patIt != *strIt)
                {
                    if (lastWildCardIt != tmpPattern.end())
                    {
                        // The last wildcard can match this incorrect sequence
                        // rewind pattern to wildcard and keep searching
                        patIt = lastWildCardIt;
                        lastWildCardIt = tmpPattern.end();
                    }
                    else
                    {
                        // no wildwards left
                        return false;
                    }
                }
                else
                {
                    ++patIt;
                    ++strIt;
                }
            }

        }
        // If we reached the end of both the pattern and the string, we succeeded
        if ((patIt == tmpPattern.end() || (*patIt == '*' && patIt + 1 == tmpPattern.end())) && strIt == tmpStr.end())
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    bool StringUtil::saveStringToFile(const String str, FILE* pFile)
    {
        if (!str.empty() && pFile)
        {
            //�����ַ���ĩβ��\0ҲҪд��
            unsigned int length = str.length() + 1;
            char end = 0;
            fwrite(&length, 1, sizeof(unsigned int), pFile);
            fwrite(str.c_str(), 1, sizeof(char) * str.length(), pFile);
            fwrite(&end, 1, sizeof(char), pFile);
            return true;
        }
        return false;
    }
    bool StringUtil::loadStringFromFile(String& str, FILE* pFile)
    {
        if (pFile)
        {
            unsigned int length = 0;
            fread(&length, 1, sizeof(unsigned int), pFile);
            char* pStr = new char[length];
            fread(pStr, 1, sizeof(char) * length, pFile);
            pStr[length - 1] = 0;
            str = pStr;
            delete[] pStr;
            return true;
        }
        return false;
    }
    bool StringUtil::saveStringToMemory(const String str, char*& pCurrentPos)
    {
        if (!str.empty() && pCurrentPos)
        {
            unsigned int length = str.length() + 1;
            char end = 0;
            memcpy(pCurrentPos, &length, sizeof(unsigned int));
            pCurrentPos += sizeof(unsigned int);
            memcpy(pCurrentPos, str.c_str(), sizeof(char) * str.length());
            pCurrentPos += sizeof(char) * str.length();
            memcpy(pCurrentPos, &end, sizeof(char));
            pCurrentPos += sizeof(char);
            return true;
        }
        return false;
    }
    bool StringUtil::loadStringFromMemory(String& str, char*& pCurrentPos)
    {
        if (pCurrentPos)
        {
            unsigned int length = *((unsigned int*)(pCurrentPos));
            pCurrentPos += sizeof(unsigned int);
            str = pCurrentPos;
            pCurrentPos += length;
            return true;
        }
        return false;
    }
    bool StringUtil::saveStringToStream(const String str, std::ofstream& os)
    {
        if (!str.empty() && os.is_open())
        {
            unsigned int length = (unsigned int)str.length() + 1;
            char end = 0;
            os << length;
            os << str;
            os << end;
            return true;
        }
        return false;
    }
    bool StringUtil::loadStringFromStream(String& str, std::ifstream& is)
    {
        if (is.is_open())
        {
            unsigned int length = 0;
            is >> length;
            is >> str;
            return true;
        }
        return false;
    }

    //-----------------------------------------------------------------------
    const String StringUtil::replaceAll(const String& source, const String& replaceWhat, const String& replaceWithWhat)
    {
        String result = source;
        String::size_type pos = 0;
        while(1)
        {
            pos = result.find(replaceWhat,pos);
            if (pos == String::npos) break;
            result.replace(pos,replaceWhat.size(),replaceWithWhat);
            pos += replaceWithWhat.size();
        }
        return result;
    }

    String StringUtil::format(const char* fmt, ...)
    {
        // try to use a stack buffer and fall back to heap for large strings
        char sbuf[1024];
        size_t bsize = sizeof(sbuf);
        std::vector<char> hbuf;
        char* pbuf = sbuf;

        while (true)
        {
            va_list va;
            va_start(va, fmt);
            int len = vsnprintf(pbuf, bsize, fmt, va);
            va_end(va);

            assert(len >= 0);
            if (size_t(len) >= bsize)
            {
                hbuf.resize(len + 1);
                pbuf = hbuf.data();
                bsize = hbuf.size();
                continue;
            }
            pbuf[bsize - 1] = 0;
            return String(pbuf, len);
        }
    }
}
