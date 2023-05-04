#include "OgreHeader.h"
#include "MPQFile.h"
#include <StormLib.h>
#include <mutex>
#include <filesystem>
#include "myutils.h"
#include "OgreResourceManager.h"


MPQArchive::MPQArchive(const String& name)
{
    _mpqName = name;
}



void MPQArchive::load()
{

    if (!SFileOpenArchive(_mpqName.c_str(), 0, 
        MPQ_OPEN_NO_LISTFILE | STREAM_FLAG_READ_ONLY, &_archiveHandle))
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to open mpq!");
    }

    HANDLE fh;


    if (SFileOpenFileEx(_archiveHandle, "(listfile)", 0, &fh))
    {
        size_t filesize = SFileGetFileSize(fh, nullptr); //last nullptr for newer version of StormLib

        std::vector<char> readbuffer(filesize);
        SFileReadFile(fh, readbuffer.data(), filesize, nullptr, nullptr); //last nullptrs for newer version of StormLib
        SFileCloseFile(fh);

        std::string current;
        for (char c : readbuffer)
        {
            if (c == '\r')
            {
                continue;
            }
            if (c == '\n')
            {
                stringToUpper(current);
                ResourceInfo* res = new ResourceInfo();
                const char* aa = getSuffix(current);
                if (aa && strcmp(aa, ".ANIM") == 0)
                {
                    int kk = 0;
                }
                res->_fullname = current;
                res->_base = this;
                bool add = ResourceManager::getSingleton()._addResource(current, res);
                if (!add)
                {
                    delete res;
                }
                current.clear();
            }
            else
            {
                current += c;
            }
        }

        if (!current.empty())
        {
            stringToUpper(current);
            ResourceInfo* res = new ResourceInfo();
            res->_fullname = current;
            res->_base = this;
            if (current == "CREATURE\\AKAMA\\AKAMA.M2")
            {
                int kk = 0;
            }
            ResourceManager::getSingleton()._addResource(current, res);
            current.clear();
        }

        SFileCloseFile(fh);
    }

    finished = true;
}

Ogre::StreamContent* MPQArchive::getPackfile(
    const String& name, const String& group)
{
    HANDLE h;
    if (!SFileOpenFileEx(_archiveHandle, name.c_str(), 0, &h))
    {
        return nullptr;
    }

    uint32_t size = SFileGetFileSize(h, nullptr);

    Ogre::StreamContent* content = new Ogre::StreamContent;
    content->_size = SFileGetFileSize(h, nullptr);
    content->_data = new char[content->_size];

    SFileReadFile(h, (void*)content->_data, content->_size, nullptr, nullptr);
    SFileCloseFile(h);
    content->_needDel = true;
    return content;
}