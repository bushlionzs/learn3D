#include "server_def.h"

const char* get_error_msg(uint32_t error)
{
	switch(error)
	{
	case CONFIG_FILE_NOT_EXIST:
		return "config file not exist";
	case CONFIG_FILE_NOT_JSON:
		return "config file is not valid json";
	case CONFIG_FILE_JSON_FORMAT_ERROR:
		return "json data error";
	default:
		return "";
	}
}