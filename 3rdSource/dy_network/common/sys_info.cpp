#include "sys_info.h"

#ifdef _WIN32

#include <wtypes.h>
#include <sysinfoapi.h>
#include <Psapi.h>
#include <processthreadsapi.h>

#else

#ifdef __APPLE__

#else

#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <fstream>

#endif

#endif

namespace dy_network
{

#ifdef _WIN32

int64_t query_process_virtual_memory()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (!GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
    {
        return -1;
    }

    return pmc.PrivateUsage;
}

int64_t query_process_physical_memory()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (!GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
    {
        return -1;
    }

    return pmc.WorkingSetSize;
}

int64_t query_process_virtual_peak_memory()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (!GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
    {
        return -1;
    }

    return pmc.PeakPagefileUsage;
}

int64_t query_process_physical_peak_memory()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (!GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
    {
        return -1;
    }

    return pmc.PeakWorkingSetSize;
}

int64_t query_system_used_memory()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (!GlobalMemoryStatusEx(&memInfo))
    {
        return -1;
    }

    return memInfo.ullTotalPhys - memInfo.ullAvailPhys;
}

int64_t query_system_avail_memory()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (!GlobalMemoryStatusEx(&memInfo))
    {
        return -1;
    }

    return memInfo.ullAvailPhys;
}

int64_t query_system_total_memory()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (!GlobalMemoryStatusEx(&memInfo))
    {
        return -1;
    }

    return memInfo.ullTotalPhys;
}

bool query_process_cpu_time(uint64_t *user_cpu_usec, uint64_t *system_cpu_usec)
{
    FILETIME createTime, exitTime, kernelTime, userTime;
    BOOL ret = GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, &kernelTime, &userTime);
    if (!ret)
    {
        return false;
    }

    SYSTEMTIME kernelSystemTime;
    ret = FileTimeToSystemTime(&kernelTime, &kernelSystemTime);
    if (!ret)
    {
        return false;
    }

    SYSTEMTIME userSystemTime;
    ret = FileTimeToSystemTime(&userTime, &userSystemTime);
    if (!ret)
    {
        return false;
    }

    if (user_cpu_usec)
    {
        uint64_t utime_sec = userSystemTime.wHour * 3600 +
                             userSystemTime.wMinute * 60 +
                             userSystemTime.wSecond;

        uint64_t utime_usec = userSystemTime.wMilliseconds * 1000;

        *user_cpu_usec = utime_sec * 1000000 + utime_usec;
    }

    if (system_cpu_usec)
    {
        uint64_t stime_sec = kernelSystemTime.wHour * 3600 +
                             kernelSystemTime.wMinute * 60 +
                             kernelSystemTime.wSecond;

        uint64_t stime_usec = kernelSystemTime.wMilliseconds * 1000;

        *system_cpu_usec = stime_sec * 1000000 + stime_usec;
    }

    return true;
}


#else // !_WIN32

#ifdef __APPLE__

int64_t query_process_virtual_memory()
{
    return -1;
}

int64_t query_process_physical_memory()
{
    return -1;
}

int64_t query_process_virtual_peak_memory()
{
    return -1;
}

int64_t query_process_physical_peak_memory()
{
    return -1;
}

int64_t query_system_used_memory()
{
    return -1;
}

int64_t query_system_avail_memory()
{
    return -1;
}

int64_t query_system_total_memory()
{
    return -1;
}

bool query_process_cpu_time(uint64_t *user_cpu_usec, uint64_t *system_cpu_usec)
{
    return false;
}

#else // !__APPLE__

static bool parse_number(const char *str, int64_t &value)
{
    while ('\0' != *str)
    {
        if (*str >= '0' && *str <= '9')
        {
            break;
        }

        str++;
    }

    if ('0' == *str)
    {
        return false;
    }

    value = 0;
    while ('\0' != *str)
    {
        if (*str < '0' || *str > '9')
        {
            break;
        }

        value = value * 10 + (*str - '0');
        str++;
    }

    return true;
}

static bool parse_key_value_file(const char *filename, const char *key, size_t key_len, int64_t& value)
{
    std::ifstream file(filename);
    if (!file)
    {
        return false;
    }

    char line[128];
    while (file.getline(line, sizeof line))
    {
        if (strncmp(line, key, key_len) == 0)
        {
            return parse_number(line + key_len, value);
        }
    }

    return false;
}

constexpr char PROC_SELF_STATUS_FILE[] = "/proc/self/status";

int64_t query_process_virtual_memory()
{
    int64_t value = 0;
    if (!parse_key_value_file(PROC_SELF_STATUS_FILE, "VmSize:", 7, value))
    {
        return -1;
    }

    return value * 1024;
}

int64_t query_process_physical_memory()
{
    int64_t value = 0;
    if (!parse_key_value_file(PROC_SELF_STATUS_FILE, "VmRSS:", 6, value))
    {
        return -1;
    }

    return value * 1024;
}

int64_t query_process_virtual_peak_memory()
{
    int64_t value = 0;
    if (!parse_key_value_file(PROC_SELF_STATUS_FILE, "VmPeak:", 7, value))
    {
        return -1;
    }

    return value * 1024;
}

int64_t query_process_physical_peak_memory()
{
    int64_t value = 0;
    if (!parse_key_value_file(PROC_SELF_STATUS_FILE, "VmHWM:", 6, value))
    {
        return -1;
    }

    return value * 1024;
}

constexpr char PROC_MEMINFO_FILE[] = "/proc/meminfo";

int64_t query_system_used_memory()
{
    int64_t total_memory = query_system_total_memory();
    if (total_memory < 0)
    {
        return -1;
    }

    int64_t avail_memory = query_system_avail_memory();
    if (avail_memory < 0)
    {
        return -1;
    }

    return total_memory - avail_memory;
}

int64_t query_system_avail_memory()
{
    int64_t value = 0;
    if (parse_key_value_file(PROC_MEMINFO_FILE, "MemAvailable:", 13, value))
    {
        return value * 1024;
    }

    struct sysinfo memInfo;
    if (0 != sysinfo(&memInfo))
    {
        return -1;
    }

    return (memInfo.freeram + memInfo.bufferram) * memInfo.mem_unit;
}

int64_t query_system_total_memory()
{
    int64_t value = 0;
    if (!parse_key_value_file(PROC_MEMINFO_FILE, "MemTotal:", 9, value))
    {
        return -1;
    }

    return value * 1024;
}

bool query_process_cpu_time(uint64_t *user_cpu_usec, uint64_t *system_cpu_usec)
{
    struct rusage usage;
    if (0 != getrusage(RUSAGE_SELF, &usage))
    {
        return false;
    }

    if (user_cpu_usec)
    {
        *user_cpu_usec = usage.ru_utime.tv_sec * 1000000 + usage.ru_utime.tv_usec;
    }

    if (system_cpu_usec)
    {
        *system_cpu_usec = usage.ru_stime.tv_sec * 1000000 + usage.ru_stime.tv_usec;
    }

    return true;
}

#endif // !__APPLE__

#endif // !_WIN32

}
