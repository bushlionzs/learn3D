#ifndef __PLATFORM_FILE_SYSTEM_H__
#define __PLATFORM_FILE_SYSTEM_H__
#include <string>
namespace CommonUtils
{ 
class PlatformFileSystem
{
public:
	static PlatformFileSystem* GetInstance();
private:
	PlatformFileSystem();
public:
	bool InitFileSystem();
	const std::string& getProcessDirectory();
	const std::string& getWorkDirectory();
    const std::string& getProjectDirectory();
    const std::string& getProcessName();
    std::string getFullPath(const std::string& dir);
    
	
private:
	std::string mProcessDirectory;
	std::string mWorkDirectory;
    std::string mProcessName;
    std::string mProjectDirectory;
};
}
#endif// __PLATFORM_FILE_SYSTEM_H__