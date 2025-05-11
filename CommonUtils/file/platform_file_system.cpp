#include "platform_file_system.h"
#include <stdio.h>
#include <string.h>
#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#include <fileapi.h>

namespace CommonUtils
{
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

    char* path_end = strrchr(fullname, '/');
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

bool get_executable_dir(char* fullname, size_t len)
{
    char* path_end;
    if (readlink("/proc/self/exe", fullname, len) <= 0)
        return false;
    path_end = strrchr(fullname, '/');
    *path_end = '\0';
    return true;
}

bool get_executable_name(char* fullname, size_t len)
{
    char* path_end;
    if (readlink("/proc/self/exe", fullname, len) <= 0)
        return false;
    path_end = strrchr(fullname, '/');
    *path_end = '\0';
    memmove(fullname, path_end + 1, len - (path_end + 1 - fullname));
    return true;
}

#endif

PlatformFileSystem* PlatformFileSystem::GetInstance()
{
    static PlatformFileSystem __instance;
    return &__instance;
}

PlatformFileSystem::PlatformFileSystem()
{
    InitFileSystem();
}

bool PlatformFileSystem::InitFileSystem()
{
    if (!mProcessDirectory.empty())
        return true;
    char buffer[2048] = { 0 };
    std::string procName;

    get_executable_dir(buffer, sizeof(buffer) - 1);
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
        mProcessDirectory = procName.substr(0, position);

        position = mProcessDirectory.find_last_of("/");
        if (position > 0)
        {
            mWorkDirectory = mProcessDirectory.substr(0, position);
        }

        get_executable_name(buffer, sizeof(buffer) - 1);

        mProcessDirectory = buffer;
        return true;
    }
    return false;
}

const std::string& PlatformFileSystem::getProcessDirectory()
{
    return mProcessDirectory;
}

const std::string& PlatformFileSystem::getWorkDirectory()
{
    return mWorkDirectory;
}

const std::string& PlatformFileSystem::getProcessName()
{
    return mProcessName;
}

const std::string& PlatformFileSystem::getProjectDirectory()
{
    return mProjectDirectory;
}

std::string PlatformFileSystem::getFullPath(const std::string& dir)
{
    std::filesystem::path myPath(dir);
    if (myPath.is_relative())
    {
        std::string workdir =
            PlatformFileSystem::GetInstance()->getWorkDirectory();
        workdir += "\\";
        workdir += dir;
        return workdir;
    }
    return dir;
}

}