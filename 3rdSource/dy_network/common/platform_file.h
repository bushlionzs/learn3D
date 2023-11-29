#ifndef __PLATFORM_FILE_H__
#define __PLATFORM_FILE_H__
#include <string>
#include <stdint.h>
#include <vector>
#include <string>

bool get_file_content(const char* filename, std::string& content);
bool save_file_content(const char* filename, const std::string& content);
bool save_file_content(const char* filename, const char* data, uint32_t size);

bool delete_file(const char* filename);
void traverse_dir(const char* path, std::vector<std::string>& filelist, uint32_t day);
void traverse_dir(const char* path, std::vector<std::string>& filelist);

bool platform_copy_file(const char* srcname, const char* dstname);
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
