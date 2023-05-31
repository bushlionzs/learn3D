#include "platform_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "time_util.h"
#ifdef WIN32
#include <tchar.h>
#include <WinSock2.h>
#include <Windows.h>
#endif
bool get_file_content(const char* filename, std::string& content)
{
    FILE* fp = fopen(filename, "rb");
    if (NULL == fp)
    {
        return false;
    }

    fseek(fp, 0, SEEK_END);
    uint32_t size = ftell(fp);
    if (size > 1024 * 1024 * 100)
    {
        fclose(fp);
        return false;
    }
    fseek(fp, 0, SEEK_SET);
    char* mem = (char*)malloc(size);
    fread(mem, 1, size, fp);
    content.assign(mem, size);
    free(mem);
    fclose(fp);
    return true;
}


#ifdef _WINDOWS_

typedef struct _dirdesc {
    int     dd_fd;      /** file descriptor associated with directory */
    long    dd_loc;     /** offset in current buffer */
    long    dd_size;    /** amount of data returned by getdirentries */
    char    *dd_buf;    /** data buffer */
    int     dd_len;     /** size of data buffer */
    long    dd_seek;    /** magic cookie returned by getdirentries */
    HANDLE  w_handle;
} DIR;

# define __dirfd(dp)    ((dp)->dd_fd)

DIR *opendir(const wchar_t *);
struct dirent *readdir(DIR *);
void rewinddir(DIR *);
int closedir(DIR *);
struct dirent
{
    long d_ino;              /* inode number*/
    off_t d_off;             /* offset to this dirent*/
    unsigned short d_reclen; /* length of this d_name*/
    unsigned char d_type;    /* the type of d_name*/
    wchar_t d_name[MAX_PATH];          /* file name (null-terminated)*/
};

std::wstring utf8_to_unicode(const std::string& utf8string);

std::wstring acsi_to_widebyte(const char* name)
{
    int widesize = MultiByteToWideChar(CP_ACP, 0, name, -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)
    {
        return std::wstring();
    }
    if (widesize == 0)
    {
        return std::wstring();
    }

    std::vector<wchar_t> resultstring(widesize);
    int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)name, -1, &resultstring[0], widesize);


    if (convresult != widesize)
    {
        return std::wstring();
    }

    return std::wstring(&resultstring[0]);
}

std::wstring utf8_to_unicode(const std::string& utf8string)
{
    int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)
    {
        return std::wstring();
    }
    if (widesize == 0)
    {
        return std::wstring();
    }

    std::vector<wchar_t> resultstring(widesize);

    int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);

    if (convresult != widesize)
    {
        return std::wstring();
    }

    return std::wstring(&resultstring[0]);
}

std::string utf8_to_ansi(const std::string& utf8string)
{
    std::wstring strunicode = utf8_to_unicode(utf8string);
    return unicode_to_acsi(strunicode.c_str());
}

std::string unicode_to_acsi(const wchar_t* name)
{
    int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, name, -1, NULL, 0, NULL, NULL);
    if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
    {
        return std::string();
    }
    if (asciisize == 0)
    {
        return std::string();
    }
    std::vector<char> resultstring(asciisize);
    int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, name, -1, &resultstring[0], asciisize, NULL, NULL);

    if (convresult != asciisize)
    {
        return std::string();;
    }

    return std::string(&resultstring[0]);
}

std::string unicode_to_utf8(const std::wstring& strUnicode)
{
    int nUtf8Length = WideCharToMultiByte(CP_UTF8,
        0,
        strUnicode.c_str(),
        -1,
        NULL,
        0,
        NULL,
        NULL);

    char* pUtf8 = new char[nUtf8Length + 1];
    memset((void*)pUtf8, 0, sizeof(char) * (nUtf8Length + 1));

    ::WideCharToMultiByte(CP_UTF8,
        0,
        strUnicode.c_str(),
        -1,
        pUtf8,
        nUtf8Length,
        NULL,
        NULL);

    std::string strUtf8;
    strUtf8 = pUtf8;
    delete[] pUtf8;

    return strUtf8;
}

bool is_str_utf8(const char* str)
{
    unsigned int nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节  
    unsigned char chr = *str;
    bool bAllAscii = true;

    for (unsigned int i = 0; str[i] != '\0'; ++i) {
        chr = *(str + i);
        //判断是否ASCII编码,如果不是,说明有可能是UTF8,ASCII用7位编码,最高位标记为0,0xxxxxxx 
        if (nBytes == 0 && (chr & 0x80) != 0) {
            bAllAscii = false;
        }

        if (nBytes == 0) {
            //如果不是ASCII码,应该是多字节符,计算字节数  
            if (chr >= 0x80) {

                if (chr >= 0xFC && chr <= 0xFD) {
                    nBytes = 6;
                }
                else if (chr >= 0xF8) {
                    nBytes = 5;
                }
                else if (chr >= 0xF0) {
                    nBytes = 4;
                }
                else if (chr >= 0xE0) {
                    nBytes = 3;
                }
                else if (chr >= 0xC0) {
                    nBytes = 2;
                }
                else {
                    return false;
                }

                nBytes--;
            }
        }
        else {
            //多字节符的非首字节,应为 10xxxxxx 
            if ((chr & 0xC0) != 0x80) {
                return false;
            }
            //减到为零为止
            nBytes--;
        }
    }

    //违返UTF8编码规则 
    if (nBytes != 0) {
        return false;
    }

    if (bAllAscii) { //如果全部都是ASCII, 也是UTF8
        return true;
    }

    return true;
}

bool is_str_gbk(const char* str)
{
    unsigned int nBytes = 0;//GBK可用1-2个字节编码,中文两个 ,英文一个 
    unsigned char chr = *str;
    bool bAllAscii = true; //如果全部都是ASCII,  

    for (unsigned int i = 0; str[i] != '\0'; ++i) {
        chr = *(str + i);
        if ((chr & 0x80) != 0 && nBytes == 0) {// 判断是否ASCII编码,如果不是,说明有可能是GBK
            bAllAscii = false;
        }

        if (nBytes == 0) {
            if (chr >= 0x80) {
                if (chr >= 0x81 && chr <= 0xFE) {
                    nBytes = +2;
                }
                else {
                    return false;
                }

                nBytes--;
            }
        }
        else {
            if (chr < 0x40 || chr>0xFE) {
                return false;
            }
            nBytes--;
        }//else end
    }

    if (nBytes != 0) {		//违返规则 
        return false;
    }

    if (bAllAscii) { //如果全部都是ASCII, 也是GBK
        return true;
    }

    return true;
}

DIR *opendir(const char *name)
{
    DIR *dir;
    WIN32_FIND_DATAA FindData;
    char namebuf[1024];

    dir = (DIR *)malloc(sizeof(DIR));
    if (!dir)
    {
        return 0;
    }
    memset(dir, 0, sizeof(DIR));
    dir->dd_fd = 0;

    dir->w_handle = INVALID_HANDLE_VALUE;
    sprintf(namebuf, "%s\\*.*", name);

    dir->w_handle = FindFirstFileA(namebuf, &FindData);
    if (dir->w_handle == INVALID_HANDLE_VALUE)
    {
        free(dir);
        return 0;
    }

    return dir;
}

struct dirent *readdir(DIR *d)
{
    BOOL bf;
    WIN32_FIND_DATAW FileData;
    if (!d)
    {
        return 0;
    }

    bf = FindNextFileW(d->w_handle, &FileData);
    //fail or end  
    if (!bf)
    {
        return 0;
    }

    struct dirent *dir = (struct dirent *)malloc(sizeof(struct dirent));

    wcscpy(dir->d_name, FileData.cFileName);

    dir->d_reclen = wcslen(dir->d_name);

    //check there is file or directory  
    if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        dir->d_type = 2;
    }
    else
    {
        dir->d_type = 1;
    }

    return dir;
}
int closedir(DIR *d)
{
    if (!d)
        return -1;
    ::FindClose(d->w_handle);
    free(d);
    return 0;
}

#define S_ISDIR(mode) (mode & _S_IFDIR)
#endif


void trave_dir(const char* path, std::vector<std::string>& filelist, uint32_t day)
{
    DIR *d = NULL;
    struct dirent *dp = NULL;
    struct stat st;
    char p[1024] = { 0 };


    uint32_t size = strlen(path);
#ifdef _WIN32
    std::string apath = utf8_to_ansi(path);
#else
    std::string apath = path;
#endif
    if (stat(apath.c_str(), &st) < 0 )
    {
        return;
    }

    if (!(d = opendir(apath.c_str())))
    {
        return;
    }
    std::wstring fullpath;
    while ((dp = readdir(d)) != NULL)
    {
        if (dp->d_name[0] != '.')
      {

        #ifdef _WIN32
        snprintf(p, sizeof(p), "%s%s", apath.c_str(), unicode_to_acsi(dp->d_name).c_str());
        #else
        snprintf(p, sizeof(p), "%s%s", apath.c_str(), dp->d_name);
        #endif
        stat(p, &st);
        if (!S_ISDIR(st.st_mode))
        {
            uint32_t lasttime = get_seconds() - day * 3600 * 24;
            if (st.st_mtime < lasttime)
            {
                filelist.push_back(p);
            }
        }
      }
#ifdef _WIN32
      free(dp);
#endif
    }
    closedir(d);

    return;
}
