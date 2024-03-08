#include "platform_file_system.h"
#include <stdio.h>
#include <string.h>
#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#include <fileapi.h>
bool get_executable_dir(char* fullname, size_t len)
{
	::GetModuleFileNameA(NULL, fullname, static_cast<DWORD>(len - 1));
	return true;
}

bool get_executable_name(char* fullname, size_t len)
{
	char* path_end;
	::GetModuleFileNameA(NULL, fullname, static_cast<DWORD>(len - 1));
	path_end = strrchr(fullname, '\\');
	*path_end = '\0';
	memmove(fullname, path_end + 1, len - (path_end + 1 - fullname));
	return true;
}
#elif __APPLE__
#include <libproc.h>
#include <unistd.h>

bool get_executable_dir(char* fullname, size_t len)
{
    pid_t pid = getpid();
    int ret = proc_pidpath(pid, fullname, len);

    if (ret <= 0)
        return false;

    char*path_end = strrchr(fullname, '/');
    *path_end = '\0';
    return true;
}

bool get_executable_name(char* fullname, size_t len)
{
    pid_t pid = getpid();
    int ret = proc_pidpath(pid, fullname, len);

    if (ret <= 0)
        return false;

    char* path_end = strrchr(fullname, '/');
    *path_end = '\0';
    memmove(fullname, path_end + 1, len - (path_end + 1 - fullname));
}

#else
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>

bool get_executable_dir(char* fullname,size_t len)
{
    char* path_end;
    if(readlink("/proc/self/exe", fullname,len) <=0)
            return false;
    path_end = strrchr(fullname,  '/');
    *path_end = '\0';
    return true;
}

bool get_executable_name(char* fullname,size_t len)
{
    char* path_end;
    if(readlink("/proc/self/exe", fullname,len) <=0)
            return false;
    path_end = strrchr(fullname,  '/');
    *path_end = '\0';
    memmove(fullname, path_end + 1, len - (path_end + 1 - fullname));
    return true;
}

#endif

CPlatformFileSystem* CPlatformFileSystem::GetInstance()
{
	static CPlatformFileSystem __instance;
	return &__instance;
}

CPlatformFileSystem::CPlatformFileSystem()
{
	InitFileSystem();
}

bool CPlatformFileSystem::InitFileSystem()
{
    if (!m_strProcessDirectory.empty())
        return true;
    char buffer[2048]={0};
    std::string procName;

    get_executable_dir(buffer, sizeof(buffer)-1);
    procName = buffer;
    procName += "/";
	std::string find;
#ifdef _WIN32
	find = "\\";
#else
	find = "/";
#endif
	size_t position = procName.find_last_of(find);


	if (position > 0)
	{
		m_strProcessDirectory = procName.substr(0, position);
        
        position = m_strProcessDirectory.find_last_of("/");
        if (position > 0)
        {
            m_strWorkDirectory = m_strProcessDirectory.substr(0, position);
        }
        
        get_executable_name(buffer, sizeof(buffer) - 1);
    
        m_strProcessName = buffer;

       // printf("bin dir:%s, process name:%s\n", m_strProcessDirectory.c_str(), m_strProcessName.c_str());
		
        return true;
	}
	return false;
}

const std::string& CPlatformFileSystem::GetProcessDirectory()
{
	return m_strProcessDirectory;
}

const std::string& CPlatformFileSystem::GetWorkDirectory()
{
	return m_strWorkDirectory;
}


std::string CPlatformFileSystem::getFullPath(const std::string& dir)
{
    std::filesystem::path myPath(dir);
    if (myPath.is_relative())
    {
        std::string workdir =
            CPlatformFileSystem::GetInstance()->GetWorkDirectory();
        workdir += "\\";
        workdir += dir;
        return workdir;
    }
    return dir;
}

// static 
bool CPlatformFileSystem::exists(const char *path)
{
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path);
    return (attr != INVALID_FILE_ATTRIBUTES);
#else
    return -1 != access(path, F_OK);
#endif
}

// static 
bool CPlatformFileSystem::make_dir(const char *path)
{
#ifdef _WIN32
    return !!CreateDirectoryA(path, NULL);
#else
    return -1 != mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
}

#define DY_NETWORK_PATH_MAX 512
#define MKDIR_DEPTH_LIMIT 100

// static 
bool CPlatformFileSystem::mkdir_full(const char *path)
{
    // assert(path);
    char buf[DY_NETWORK_PATH_MAX];
    uint32_t depth = 0;

    for (size_t i = 0; i < sizeof(buf) && depth < MKDIR_DEPTH_LIMIT; ++i)
    {
        char c = path[i];
        if ('\0' == c)
        {
            return true;
        }

        if ('/' == c || '\\' == c)
        {
            buf[i] = 0;
            if (i > 0 && !exists(buf))
            {
                if (!make_dir(buf))
                {
                    return false;
                }
            }

            depth++;
        }
  
        buf[i] = c;
    }

    return false;
}

// static 
bool CPlatformFileSystem::rename_file(const char *path, const char *to)
{
#ifdef _WIN32
    return !!::MoveFileExA(path, to, MOVEFILE_REPLACE_EXISTING);
#else
    return 0 == ::rename(path, to);
#endif
}

// static
bool CPlatformFileSystem::remove_file(const char *path)
{
#ifdef _WIN32
    return !!::DeleteFileA(path);
#else
    return 0 == ::unlink(path);
#endif
}

std::string CPlatformFileSystem::get_filename(const char* fullname, bool erase_postfix)
{
    std::string full = fullname;

    std::string name;
    auto npos = full.find_last_of("\\");
    if (npos != std::string::npos)
    {
        name = full.substr(npos + 1, full.size());
    }
    else
    {
        npos = full.find_last_of("/");

        if (npos != std::string::npos)
        {
            name = full.substr(npos + 1, full.size());
        }
    }

    if (!name.empty())
    {
        if (erase_postfix)
        {
            npos = name.find_last_of(".");
            if (npos != std::string::npos)
            {
                name.erase(npos);
            }
        }
        return name;
    }
    return full;
}