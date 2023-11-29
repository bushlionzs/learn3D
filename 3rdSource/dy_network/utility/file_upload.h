#pragma once
#include <string>


void syncUploadFile(const std::string& url, const std::string& filename); //Warning!!!, this function will be block
void asyncUploadFile(
	const std::string& url,
	const std::string& filename,
	void (*upload_callback)(int32_t code, const std::string& name, uint64_t size, void*param), void* usr_data);