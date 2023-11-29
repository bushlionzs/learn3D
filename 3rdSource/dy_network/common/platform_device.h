#pragma once
#include <string>
struct plaform_device_t
{
	std::string _cpu;
	std::string _mem;
	std::string _network_card;
	std::string _system;
};

bool platform_get_device(plaform_device_t&);

bool platform_run_one_instance(const std::string& name);

void platform_get_memory_info(std::string& info);