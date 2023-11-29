#ifndef __COMMON_BASE64_H__
#define __COMMON_BASE64_H__

#include <string>  

std::string base64_encode(const unsigned char* data, unsigned int in_len);
std::string base64_decode(const unsigned char* data, uint32_t size);
int md5_translate(uint64_t start_second, const std::string&sec_key, std::string& std_md5_hex, std::string& str_des_key);
std::string base64_encode_random(uint32_t size);
#endif //__COMMON_BASE64_H__