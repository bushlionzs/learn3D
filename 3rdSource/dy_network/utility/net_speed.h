#pragma once

#include <string>


struct NetSpeed
{
	bool _download_success = false;
	bool _upload_success = false;
	std::string _download_url;
	std::string _upload_ip;
	uint16_t _upload_port;
	uint64_t _download_time = 0; //ms
	uint64_t _upload_time = 0; //ms
	uint64_t _upload_bandwidth = 0;
	uint64_t _download_bandwidth = 0;
};



bool net_speed_start(
	const std::string& download_url, 
	const std::string& upload_ip,
	uint16_t upload_port,
	uint32_t upload_time,
	void (*net_speed_callback)(NetSpeed*, void*), void*param);
