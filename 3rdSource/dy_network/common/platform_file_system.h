#ifndef __PLATFORM_FILE_SYSTEM_H__
#define __PLATFORM_FILE_SYSTEM_H__
#include <string>
class CPlatformFileSystem
{
public:
	static CPlatformFileSystem* GetInstance();
private:
	CPlatformFileSystem();
public:
	bool InitFileSystem();
	const std::string& GetProcessDirectory();
	const std::string& GetWorkDirectory();
    std::string getFullPath(const std::string& dir);
    static std::string get_filename(const char* fullname, bool erase_postfix);
    const std::string& GetProcessName()
    {
        return m_strProcessName;
    }

    static bool exists(const char *path);
    static bool make_dir(const char *path);
    static bool mkdir_full(const char *path);
    static bool rename_file(const char *path, const char *to);
    static bool remove_file(const char *path);
private:
	std::string m_strProcessDirectory;
	std::string m_strWorkDirectory;
    std::string m_strProcessName;
};
#endif// __PLATFORM_FILE_SYSTEM_H__