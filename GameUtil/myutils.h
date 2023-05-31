#pragma once
#include <string>
std::string getPath(const char* name);

std::string getContentFromFile(const char* name);

uint64_t getMicroseconds();

std::wstring to_wide_string(const std::string& input);

const char* getSuffix(const std::string& name);

std::string removeSuffix(const std::string& name);

std::string getShortFilename(const std::string& name);

bool loadStringFromMemory(std::string& str, char*& pCurrentPos);

std::string UTF8ToGBK(const char* strUTF8);

std::string string_trim(std::string& s);

void stringToUpper(std::string& str);
void stringToLower(std::string& str);