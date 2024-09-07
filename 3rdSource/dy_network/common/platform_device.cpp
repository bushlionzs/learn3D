#include "platform_device.h"
#include "string_util.h"
#include "platform_file_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#include <intrin.h>
//#include <atlbase.h>
//#include <atlconv.h>
#include <iphlpapi.h>
#include <psapi.h>
#elif __APPLE__
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>   
#include <sys/types.h>
#include <arpa/inet.h>
#ifdef USE_PCAP
#include <pcap.h>
#endif 
#include <sys/utsname.h>
#include <errno.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>   
#include <sys/types.h>
#include <arpa/inet.h>
#ifdef USE_PCAP
#include <pcap.h>
#endif 
#endif
 

#ifdef _WIN32

BOOL Is_Win_Server()
{
    OSVERSIONINFOEX osvi;
    DWORDLONG dwlConditionMask = 0;
    int op = VER_GREATER_EQUAL;

    // Initialize the OSVERSIONINFOEX structure.

    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    osvi.dwMajorVersion = 5;
    osvi.dwMinorVersion = 0;
    osvi.wServicePackMajor = 0;
    osvi.wServicePackMinor = 0;
    osvi.wProductType = VER_NT_SERVER;

    // Initialize the condition mask.

    VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, op);
    VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, op);
    VER_SET_CONDITION(dwlConditionMask, VER_SERVICEPACKMAJOR, op);
    VER_SET_CONDITION(dwlConditionMask, VER_SERVICEPACKMINOR, op);
    VER_SET_CONDITION(dwlConditionMask, VER_PRODUCT_TYPE, VER_EQUAL);

    // Perform the test.

    return VerifyVersionInfo(
        &osvi,
        VER_MAJORVERSION | VER_MINORVERSION |
        VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR |
        VER_PRODUCT_TYPE,
        dwlConditionMask);
}

bool GetOSVersionName(plaform_device_t& dummy)
{
    const char* name = "unknown";

    /*------------------------*/
    //OS>=win8.1
    BOOL bWin81Over = FALSE;
    char processor[16];
    typedef void(__stdcall* NTPROC)(DWORD*, DWORD*, DWORD*);
    HINSTANCE hinst = LoadLibrary("ntdll.dll");
    DWORD dwMajor, dwMinor, dwBuildNumber;
    NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
    if (proc) proc(&dwMajor, &dwMinor, &dwBuildNumber);

    if (dwMajor == 6 && dwMinor == 3) {
        if (Is_Win_Server())
            name = "Windows Server 2012 R2";
        else
            name = "Windows 8.1";
        bWin81Over = TRUE;
    }
    else if (dwMajor == 10 && dwMinor == 0) {
        if (Is_Win_Server())
            name = "Windows Server 2016";
        else
            name = "Windows 10";
        bWin81Over = TRUE;
    }

    if (bWin81Over) {
        dummy._system = name;
        return TRUE;
    }

    /*------------------------*/
    //OS<win8.1
    OSVERSIONINFOEX osvi;
    BOOL bOsVersionInfoEx;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

    // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
    // If that fails, try using the OSVERSIONINFO structure.

    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if (!(bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*)&osvi)))
    {
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if (!GetVersionEx((OSVERSIONINFO*)&osvi))
            return FALSE;
    }

    /*------------------------*/
    // Call GetNativeSystemInfo if supported
    // or GetSystemInfo otherwise.
    typedef void (WINAPI* PGNSI)(LPSYSTEM_INFO);
    SYSTEM_INFO si;
    ZeroMemory(&si, sizeof(SYSTEM_INFO));
    PGNSI pGNSI = (PGNSI)GetProcAddress(
        GetModuleHandle(TEXT("kernel32.dll")),
        "GetNativeSystemInfo");
    if (NULL != pGNSI) pGNSI(&si);
    else GetSystemInfo(&si);

    switch (si.wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_AMD64:
        strcpy_s(processor, "x64");
        break;
    case PROCESSOR_ARCHITECTURE_IA64:
        strcpy_s(processor, "IA64");
        break;
    default:
        strcpy_s(processor, "x86");
        break;
    }

    /*------------------------*/
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        if (osvi.dwMajorVersion >= 7) {
            // Unknown recent version.
        }
        else if (osvi.dwMajorVersion >= 6) {
            if (osvi.dwMinorVersion >= 4)
                name = "Windows 10";
            else if (osvi.dwMinorVersion >= 3) {
                if (osvi.wProductType == VER_NT_WORKSTATION)
                    name = "Windows 8.1";
                else
                    name = "Windows Server 2012 R2";
            }
            else if (osvi.dwMinorVersion >= 2) {
                if (osvi.wProductType == VER_NT_WORKSTATION)
                    name = "Windows 8";
                else
                    name = "Windows Server 2012";
            }
            else if (osvi.dwMinorVersion >= 1) {
                if (osvi.wProductType == VER_NT_WORKSTATION)
                    name = "Windows 7";
                else
                    name = "Windows Server 2008 R2";
            }
            else {
                if (osvi.wProductType == VER_NT_WORKSTATION)
                    name = "Windows Vista";
                else
                    name = "Windows Server 2008";
            }
        }
        else if (osvi.dwMajorVersion >= 5) {
            if (osvi.dwMinorVersion == 0)
                name = "Windows 2000";
            else if (osvi.dwMinorVersion == 1)
                name = "Windows XP";
            else if (osvi.dwMinorVersion == 2) {
                if (osvi.wProductType == VER_NT_WORKSTATION &&
                    si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
                    name = "Windows XP Professional x64 Edition";
                else if (GetSystemMetrics(SM_SERVERR2) != 0)  //2==GetSystemMetrics(/*SM_SERVERR2*/89)
                    name = "Windows Server 2003 R2";
                else if (osvi.wSuiteMask/* & VER_SUITE_WH_SERVER*/)
                    name = "Windows Home Server";

                if (GetSystemMetrics(SM_SERVERR2) == 0)
                    name = "Windows Server 2003";
            }
        }
        else if (osvi.dwMajorVersion == 4) {
            if (osvi.dwMinorVersion == 0) {
                if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
                    name = "Windows NT 4.0"; //1996
                else if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
                    name = "Windows 95";
            }
            else if (osvi.dwMinorVersion == 10)
                name = "Windows 98";
            else if (osvi.dwMinorVersion == 90)
                name = "Windows Me";
        }
        else
            name = "Windows earlier";
    }

    if (osvi.wServicePackMajor != 0) {
        dummy._system = dy::str_format("%s SP%d(%s)", name, osvi.wServicePackMajor, processor);
    }
    else {
        dummy._system = dy::str_format("%s SP%d(%s)", "%s (%s)", name, processor);
    }

    return TRUE;
}

bool GetMemoryInfo(plaform_device_t& dummy)
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);

    if (GlobalMemoryStatusEx(&statex))
    {
        dummy._mem = dy::str_format("physical memory:%lluM", statex.ullTotalPhys / 1000 / 1000);
        return true;
    }
    return false;
}

/*CPU*/
bool GetCpuInfo(plaform_device_t& dummy)
{
    int cpuInfo[4] = { -1 };
    char cpu_manufacture[32] = { 0 };
    char cpu_type[32] = { 0 };
    char cpu_freq[32] = { 0 };

    __cpuid(cpuInfo, 0x80000002);
    memcpy(cpu_manufacture, cpuInfo, sizeof(cpuInfo));

    __cpuid(cpuInfo, 0x80000003);
    memcpy(cpu_type, cpuInfo, sizeof(cpuInfo));

    __cpuid(cpuInfo, 0x80000004);
    memcpy(cpu_freq, cpuInfo, sizeof(cpuInfo));

    dummy._cpu = dy::str_format("%s %s %s", cpu_manufacture, cpu_type, cpu_freq);

    return true;
}


bool GetNetworkCardInfo(plaform_device_t& dummy)
{
    dummy._network_card.clear();
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;

    pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS)
    {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
    }

    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
    {
        char buffer[1024] = { 0 };
        pAdapter = pAdapterInfo;
        while (pAdapter)
        {
            if (
                strstr(pAdapter->Description, "PCI") // pAdapter->Description中包含"PCI"为：物理网卡
                || pAdapter->Type == 71 // pAdapter->Type是71为：无线网卡
                )
            {
                if (strcmp(pAdapter->IpAddressList.IpAddress.String, "0.0.0.0") != 0)
                {
                    if (!dummy._network_card.empty())
                    {
                        dummy._network_card += "\n";
                    }
                    snprintf(buffer, sizeof(buffer), "AdapterDesc:%s, ip:%s, mac:%02X:%02X:%02X:%02X:%02X:%02X",
                        pAdapter->Description, pAdapter->IpAddressList.IpAddress.String, pAdapterInfo->Address[0],
                        pAdapterInfo->Address[1],
                        pAdapterInfo->Address[2], pAdapterInfo->Address[3],
                        pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

                    dummy._network_card += buffer;
                }
            }
            pAdapter = pAdapter->Next;
        }
    }

    free(pAdapterInfo);
    return true;
}

void platform_get_memory_info(std::string& info)
{
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        info = dy::str_format("current memory:%d KB", pmc.WorkingSetSize / 1024.0f);
    }
}

#elif __APPLE__
bool GetOSVersionName(plaform_device_t& dummy)
{
    utsname aa;
    uname(&aa);

    dummy._system = aa.version;


    return true;
}

bool GetMemoryInfo(plaform_device_t& dummy)
{
    FILE* fp = popen("top -l 1 | head -n 10 | grep PhysMem", "r");

    if (fp == nullptr)
        return false;

    char buffer[1024] = { 0 };

    if (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        dummy._mem += buffer;
        dummy._mem.pop_back();
    }

    pclose(fp);

    return true;
}


bool GetCpuInfo(plaform_device_t& dummy)
{
    FILE* fp = popen("sysctl -n machdep.cpu.brand_string", "r");

    if (fp == nullptr)
        return false;

    char buffer[1024] = { 0 };

    if (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        dummy._cpu += buffer;
        dummy._cpu.pop_back();
    }

    pclose(fp);
    return true;
}

bool GetNetworkCardInfo(plaform_device_t& dummy)
{
#ifdef USE_PCAP
    pcap_if_t* alldevs;
    pcap_if_t* d;
    int i = 0;
    pcap_addr_t* a;
    char errbuf[PCAP_ERRBUF_SIZE];
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        printf("pcap_findalldevices failed, err:%d\n", errno);
        return false;
    }
    for (d = alldevs; d; d = d->next)
    {
        for (a = d->addresses; a; a = a->next)
        {
            if (a->addr->sa_family != AF_INET)
                continue;
            dummy._network_card += str_format("name:%s,ip:%s ", d->name, inet_ntoa(((struct sockaddr_in*)a->addr)->sin_addr));
        }
    }
    pcap_freealldevs(alldevs);
#endif
    return true;
}
#else
bool GetOSVersionName(plaform_device_t& dummy)
{
    FILE* fp = fopen("/proc/version", "r");
    if (nullptr == fp)
    {
        return false;
    }
    char buffer[1024] = { 0 };


    fgets(buffer, sizeof(buffer) - 1, fp); // leave out \n

    char* pch = strstr(buffer, "(");
    if (pch)
    {
        *pch = 0;
    }

    dummy._system = buffer;
    dummy._system.pop_back();
    fclose(fp);
    return true;
}

bool GetMemoryInfo(plaform_device_t& dummy)
{
    FILE* fp = fopen("/proc/meminfo", "r");
    if (nullptr == fp)
    {
        return false;
    }
    char mem[1024] = { 0 };

    while (!feof(fp))
    {
        memset(mem, 0, sizeof(mem));
        fgets(mem, sizeof(mem) - 1, fp); // leave out \n

        char* pch = strstr(mem, "MemTotal:");
        if (pch)
        {
            dummy._mem += mem;
            dummy._mem.pop_back();
            dummy._mem += " ";
        }
        

        pch = strstr(mem, "MemAvailable:");

        if (pch)
        {
            dummy._mem += mem;
            dummy._mem.pop_back();
            dummy._mem += " ";
        }

        pch = strstr(mem, "MemFree:");

        if (pch)
        {
            dummy._mem += mem;
            dummy._mem.pop_back();
            dummy._mem += " ";
        }
    }
    fclose(fp);
    return true;
}

void platform_get_memory_info(std::string& info)
{
    FILE* fp = fopen("/proc/self/status", "r");

    if (nullptr == fp)
    {
        return;
    }

    char meminfo[2048] = { 0 };

    while (!feof(fp))
    {
        fgets(meminfo, sizeof(meminfo), fp);

        char* pch = strstr(meminfo, "VmSize:");

        if (pch)
        {
            info += pch;
            info.pop_back();
        }

        pch = strstr(meminfo, "VmRSS:");

        if (pch)
        {
            info += pch;
            info.pop_back();
            break;
        }
    }

    fclose(fp);
}

bool GetCpuInfo(plaform_device_t& dummy)
{
    FILE* fp = fopen("/proc/cpuinfo", "r");
    if (nullptr == fp)
    {
        return false;
    }
    char cpuModel[1024] = { 0 };

    while (!feof(fp))
    {
        memset(cpuModel, 0, sizeof(cpuModel));
        fgets(cpuModel, sizeof(cpuModel) - 1, fp); // leave out \n

        char* pch = strstr(cpuModel, "model name");
        if (pch)
        {
            char* pch2 = strchr(cpuModel, ':');
            if (pch2)
            {
                dummy._cpu = pch2 + 2;
                dummy._cpu.pop_back();
                break;
            }
            else
            {
                fclose(fp);
                return false;
            }
        }
    }
    fclose(fp);
    return true;
}

bool GetNetworkCardInfo(plaform_device_t& dummy)
{
#ifdef USE_PCAP
    pcap_if_t* alldevs;
    pcap_if_t* d;
    int i = 0;
    pcap_addr_t* a;
    char errbuf[PCAP_ERRBUF_SIZE];
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        printf("pcap_findalldevices failed, err:%d\n", errno);
        return false;
    }
    for (d = alldevs; d; d = d->next)
    {
        for (a = d->addresses; a; a = a->next)
        {
             if(a->addr->sa_family != AF_INET)
                 continue;
             dummy._network_card  += str_format("name:%s,ip:%s ", d->name, inet_ntoa(((struct sockaddr_in *)a->addr)->sin_addr));
        }
    }
    
    pcap_freealldevs(alldevs);
#endif
    return true;
}
#endif

bool platform_get_device(plaform_device_t& dummy)
{
    try
    {
        GetOSVersionName(dummy);
        GetMemoryInfo(dummy);
        GetCpuInfo(dummy);
        GetNetworkCardInfo(dummy);
    }
    catch (...)
    {
        return false;
    }

    return true;
}

bool platform_run_one_instance(const std::string& name)
{
#ifdef _WIN32
    HANDLE mutexHandle = CreateMutex(NULL, FALSE, name.c_str());
    if (ERROR_ALREADY_EXISTS == GetLastError())
    {
        return false;
    }

    ;
    return true;
#else
    std::string path = CPlatformFileSystem::GetInstance()->GetProcessDirectory() + "/" + name;
    int fd = open(path.c_str(), O_RDWR | O_CREAT, 0666);
    if (fd < 0)
    {
        return false;
    }
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    int ret = fcntl(fd, F_SETLK, &fl);
    if (ret < 0)
    {
        return false;
    }

    ftruncate(fd, 0);
    char buf[128] = { 0 };
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf));
    return true;
#endif
}
