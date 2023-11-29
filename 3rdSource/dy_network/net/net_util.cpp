#include "net_util.h"
#include "string_util.h"
#include "net_factory.h"
#include "json.hpp"
namespace dy
{
	void send_http_response(
		NetHandle handle,
		int32_t code,
		const char* codemsg,
		const std::string& content)
	{
		std::string response = str_format("HTTP/1.1 %d %s\r\nConnection: close\r\nServer: kdl/1.0.0\r\nContent-Length: %d\r\n\r\n",
			code, codemsg, content.size());

		response += content;

		NetFactory::GetInstance()->SendData(handle, (const uint8_t*)response.data(), response.size());
	}

	void send_http_json_response(
		NetHandle handle,
		int32_t code,
		const char* codemsg
	)
	{
		std::string dummy;

		nlohmann::json j;

		j["code"] = code;
		j["msg"] = codemsg;

		dummy = j.dump();

		send_http_response(handle, 200, "OK", dummy);
	}
}