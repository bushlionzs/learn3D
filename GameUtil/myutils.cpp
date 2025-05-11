#include "myutils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <locale>
#include <codecvt>
#include <windows.h>

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


