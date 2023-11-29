#pragma once

#include <stdint.h>

namespace dy_network
{

int64_t query_process_virtual_memory();
int64_t query_process_physical_memory();
int64_t query_process_virtual_peak_memory();
int64_t query_process_physical_peak_memory();

int64_t query_system_used_memory();
int64_t query_system_avail_memory();
int64_t query_system_total_memory();

bool query_process_cpu_time(uint64_t *user_cpu_usec, uint64_t *system_cpu_usec);

}
