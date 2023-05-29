#ifndef __PLATFORM_FILE_H__
#define __PLATFORM_FILE_H__
#include <string>
#include <stdint.h>
#include <vector>
#include <string>

bool get_file_content(const char* filename, std::string& content);

void trave_dir(const char* path, std::vector<std::string>& filelist, uint32_t day);

#ifdef _WIN32
std::wstring acsi_to_widebyte(const char* name);
std::wstring utf8_to_unicode(const std::string& utf8string);
std::string utf8_to_ansi(const std::string& utf8string);
std::string unicode_to_acsi(const wchar_t* name);
std::string unicode_to_utf8(const std::wstring& strUnicode);
bool is_str_utf8(const char* str);
bool is_str_gbk(const char* str);
#endif
#endif //__PLATFORM_FILE_H__