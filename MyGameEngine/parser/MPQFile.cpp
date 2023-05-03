#include "OgreHeader.h"
#include "MPQFile.h"
#include <StormLib.h>
#include <mutex>
#include <filesystem>
#include "myutils.h"
#include "OgreResourceManager.h"

typedef std::pair<std::string, std::unique_ptr<MPQArchive>> ArchiveEntry;
typedef std::list<ArchiveEntry> ArchivesMap;
std::unordered_set<std::string> gListfile;
ArchivesMap _openArchives;
static std::mutex gMPQFileMutex;
static std::mutex gListfileLoadingMutex;


MPQArchive::MPQArchive(const std::string& name, bool doListfile)
{
 
}

bool MPQArchive::hasFile(const std::string& filename) const
{
    return SFileHasFile(_archiveHandle,
        filename.c_str());
}

bool MPQArchive::openFile(const std::string& filename, HANDLE* fileHandle) const
{
    return SFileOpenFileEx(_archiveHandle,
        filename.c_str(), 0, fileHandle);
}

void MPQArchive::loadMPQ(const std::string& filename, bool doListfile)
{
    _openArchives.emplace_back(filename, std::make_unique<MPQArchive>(filename, doListfile));

    MPQArchive* archive = _openArchives.back().second.get();
}

String MPQArchive::getSuffix()
{
    return ".MPQ";
}

void MPQArchive::parseScript(ResourceInfo* res, const String& groupName)
{
    _mpqName = res->_fullname;
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
                res->_fullname = current;
                res->_base = this;
                ResourceManager::getSingleton()._addResource(current, res);
                current.clear();
            }
            else
            {
                current += c;
            }
        }

        if (!current.empty())
        {
            ResourceInfo* res = new ResourceInfo();
            res->_fullname = current;
            res->_base = this;
            ResourceManager::getSingleton()._addResource(current, res);
            current.clear();
        }

        SFileCloseFile(fh);
    }

    finished = true;
}

Real MPQArchive::getLoadingOrder(void) const
{
    return 20.0f;
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