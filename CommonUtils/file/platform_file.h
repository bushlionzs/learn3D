#ifndef __PLATFORM_FILE_H__
#define __PLATFORM_FILE_H__
#include <string>
#include <stdint.h>
#include <vector>

namespace CommonUtils
{
    bool get_file_content(const char* filename, std::string& content, uint32_t part = 0);
    bool get_file_content(const char* filename, std::wstring& content, uint32_t part = 0);
    uint32_t get_file_size(FILE* fp);
    bool save_file_content(const char* filename, const std::string& content);
    bool save_file_content(const char* filename, const char* data, uint32_t size);

    bool delete_file(const char* filename);
    void traverse_dir(const char* path, std::vector<std::string>& filelist, uint32_t day);
    void traverse_dir(const char* path, std::vector<std::string>& filelist);
    std::vector<std::string> traverse_dir_for_dir(const char* path);

    bool platform_copy_file(const char* srcname, const char* dstname);

    bool exists(const char* path);
    bool make_dir(const char* path);
    bool mkdir_full(const char* path);
    bool rename_file(const char* path, const char* to);
    bool remove_file(const char* path);
    bool IsDirectory(const char* path);

    bool IsSupportedModelFile(const std::string& name);
    bool IsSupportedImageFile(const std::string& name);
    bool IsSupportedAudioFile(const std::string& name);
    bool IsEngineMaterialFile(const std::string& name);
    bool IsEngineTextureFile(const std::string& name);
    bool IsEngineModelFile(const std::string& name);
    std::vector<std::string> getSupportedSceneFilesInDirectory(const std::string& dir);
    std::vector<std::string> getSupportedModelFilesInDirectory(const std::string& dir);
    
}


#endif //__PLATFORM_FILE_H__
