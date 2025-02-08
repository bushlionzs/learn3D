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
#ifndef _String_H__
#define _String_H__



#if OGRE_COMPILER == OGRE_COMPILER_GNUC || OGRE_COMPILER == OGRE_COMPILER_CLANG
#define OGRE_FORMAT_PRINTF(string_idx, first_to_check) __attribute__ ((format (printf, string_idx, first_to_check)))
#else
#define OGRE_FORMAT_PRINTF(A, B)
#endif

namespace Ogre {
    /** \addtogroup Core
     *  @{
     */
    /** \addtogroup General
     *  @{
     */

    typedef std::vector<std::string> StringVector;
    typedef std::shared_ptr<StringVector> StringVectorPtr;

    /** Utility class for manipulating Strings.  */
    class  StringUtil
    {
    public:
        /** Removes any whitespace characters, be it standard space or
            TABs and so on.
            @remarks
            The user may specify whether they want to trim only the
            beginning or the end of the String ( the default action is
            to trim both).
        */
        static void trim(std::string& str, bool left = true, bool right = true );

        /** Returns a StringVector that contains all the substrings delimited
            by the characters in the passed <code>delims</code> argument.
            @param str
            @param
            delims A list of delimiter characters to split by
            @param
            maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
            parameters is > 0, the splitting process will stop after this many splits, left to right.
            @param
            preserveDelims Flag to determine if delimiters should be saved as substrings
        */
        static std::vector<std::string> split( const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0, bool preserveDelims = false);

        /** Returns a StringVector that contains all the substrings delimited
            by the characters in the passed <code>delims</code> argument,
            or in the <code>doubleDelims</code> argument, which is used to include (normal)
            delimiters in the tokenised string. For example, "strings like this".
            @param str
            @param
            delims A list of delimiter characters to split by
            @param
            doubleDelims A list of double delimiters characters to tokenise by
            @param
            maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
            parameters is > 0, the splitting process will stop after this many splits, left to right.
        */
        static std::vector<std::string> tokenise( const std::string& str, const std::string& delims = "\t\n ", const std::string& doubleDelims = "\"", unsigned int maxSplits = 0);

        /** Lower-cases all the characters in the string.
         */
        static void toLowerCase(std::string& str );

        /** Upper-cases all the characters in the string.
         */
        static void toUpperCase(std::string& str );

        /** Upper-cases the first letter of each word.
         */
        static void toTitleCase(std::string& str );


        /** Returns whether the string begins with the pattern passed in.
            @param str
            @param pattern The pattern to compare with.
            @param lowerCase If true, the start of the string will be lower cased before
            comparison, pattern should also be in lower case.
        */
        static bool startsWith(const std::string& str, const std::string& pattern, bool lowerCase = true);

        /** Returns whether the string ends with the pattern passed in.
            @param str
            @param pattern The pattern to compare with.
            @param lowerCase If true, the end of the string will be lower cased before
            comparison, pattern should also be in lower case.
        */
        static bool endsWith(const std::string& str, const std::string& pattern, bool lowerCase = true);

        /** Method for standardising paths - use forward slashes only, end with slash.
         */
        static std::string standardisePath( const std::string&init);
        /** Returns a normalized version of a file path
            This method can be used to make file path strings which point to the same directory
            but have different texts to be normalized to the same text. The function:
            - Transforms all backward slashes to forward slashes.
            - Removes repeating slashes.
            - Removes initial slashes from the beginning of the path.
            - Removes ".\" and "..\" meta directories.
            - Sets all characters to lowercase (if requested)
            @param init The file path to normalize.
            @param makeLowerCase If true, transforms all characters in the string to lowercase.
        */
        static std::string normalizeFilePath(const std::string& init, bool makeLowerCase = false);


        /** Method for splitting a fully qualified filename into the base name
            and path.
            @remarks
            Path is standardised as in standardisePath
        */
        static void splitFilename(const std::string& qualifiedName,
            std::string& outBasename, std::string& outPath);

        /** Method for splitting a fully qualified filename into the base name,
            extension and path.
            @remarks
            Path is standardised as in standardisePath
        */
        static void splitFullFilename(const std::string& qualifiedName,
            std::string& outBasename, std::string& outExtention,
            std::string& outPath);

        /** Method for splitting a filename into the base name
            and extension.
        */
        static void splitBaseFilename(const std::string& fullName,
            std::string& outBasename, std::string& outExtention);


        /** Simple pattern-matching routine allowing a wildcard pattern.
            @param str String to test
            @param pattern Pattern to match against; can include simple '*' wildcards
            @param caseSensitive Whether the match is case sensitive or not
        */
        static bool match(const std::string& str, const std::string& pattern, bool caseSensitive = true);


        static bool saveStringToFile(const std::string str, FILE* pFile);
        static bool loadStringFromFile(std::string& str, FILE* pFile);
        static bool saveStringToMemory(const std::string str, char*& pCurrentPos);
        static bool loadStringFromMemory(std::string& str, char*& pCurrentPos);
        static bool saveStringToStream(const std::string str, std::ofstream& os);
        static bool loadStringFromStream(std::string& str, std::ifstream& is);

        /** Replace all instances of a sub-string with a another sub-string.
            @param source Source string
            @param replaceWhat Sub-string to find and replace
            @param replaceWithWhat Sub-string to replace with (the new sub-string)
            @return An updated string with the sub-string replaced
        */
        static const std::string replaceAll(const std::string& source, const std::string& replaceWhat, const std::string& replaceWithWhat);

        /** create a string from a printf expression
           *
           * @note this function - like printf - uses a locale dependent decimal point
           */
        static std::string format(const char* fmt, ...);
    };

    typedef ::std::hash< std::string > _StringHash;
    /** @} */
    /** @} */

} // namespace Ogre


#endif // _String_H__
