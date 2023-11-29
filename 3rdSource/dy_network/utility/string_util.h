#pragma once
#include <string>
#include <memory>
#include <vector>

namespace dy
{
	template<typename ... Args>
	static std::string str_format(const char* format, Args ... args)
	{
		auto size_buf = std::snprintf(nullptr, 0, format, args ...) + 1;
		std::unique_ptr<char[]> buf(new(std::nothrow) char[size_buf]);

		if (!buf)
			return std::string("");

		std::snprintf(buf.get(), size_buf, format, args ...);
		return std::string(buf.get(), buf.get() + size_buf - 1);
	}


	std::string get_short_name(std::string& fullname);

	char const* strnchr(char const* str, int ch, int which);
	void to_lower(std::string& content);

	bool hex_to_binary(const std::string& hex, std::string& output);

	void binary_to_hex(const char* data, uint32_t size, std::string& output);

	void split_string(const char* str, char sep, std::vector<std::string>& strlist);

	uint64_t StrToUINT64(const char* szBuff);
}
