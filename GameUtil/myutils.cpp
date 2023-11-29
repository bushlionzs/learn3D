#include "myutils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <locale>
#include <codecvt>
#include <windows.h>


std::string getPath(const char* name)
{
    std::string dir = "E:/myproject/opengl_demo/resources/";
    return dir + name;
}


uint64_t getMicroseconds()
{
    static auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - start).count();
}

//std::wstring to_wide_string(const std::string& input)
//{
//    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//    return converter.from_bytes(input);
//}


const char* getSuffix(const std::string& name)
{
	size_t pos = name.find_last_of('.');
	if (pos == std::string::npos)
	{
		return name.c_str() + name.size();
	}

	return name.c_str() + pos;
}

std::string removeSuffix(const std::string& name)
{
    std::string tmp;
    size_t pos = name.find_last_of('.');
    if (pos == std::string::npos)
    {
        return name;
    }

    tmp = name.substr(0, pos);
    return tmp;
}

std::string getShortFilename(const std::string& name)
{
    std::string tmp;
    size_t pos = name.find_last_of('\\');
    if (pos == std::string::npos)
    {
        return name;
    }

    tmp = name.substr(pos + 1);
    return tmp;
}

bool loadStringFromMemory(std::string& str, char*& pCurrentPos)
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

std::string UTF8ToGBK(const char* strUTF8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
    wchar_t* wszGBK = new wchar_t[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char* szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    std::string strTemp(szGBK);
    if (wszGBK) delete[] wszGBK;
    if (szGBK) delete[] szGBK;
    return strTemp;
}

void ai_trim_left(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void ai_trim_right(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

std::string string_trim(std::string & s)
{
    std::string out(s);
    ai_trim_left(out);
    ai_trim_right(out);

    return out;
}

void stringToUpper(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](char& c) {
        return std::toupper(c);
    });
}

void stringToLower(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](char& c) {
        return std::tolower(c);
    });
}