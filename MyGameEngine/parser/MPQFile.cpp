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


bool existsInMPQ(std::string const& filename)
{
    return std::any_of(_openArchives.begin(), _openArchives.end()
        , [&](ArchiveEntry const& archive)
    {
        return archive.second->hasFile(filename);
    }
    );
}

MPQFile::MPQFile(std::string const& filename)
    : eof(true)
    , pointer(0)
    , External(false)
{
    if (filename.empty())
        throw std::runtime_error("MPQFile: filename empty");

    std::unique_lock<std::mutex> lock(gMPQFileMutex);

    std::ifstream input(_disk_path, std::ios_base::binary | std::ios_base::in);
    if (input.is_open())
    {
        External = true;
        eof = false;

        input.seekg(0, std::ios::end);
        buffer.resize(input.tellg());
        input.seekg(0, std::ios::beg);

        input.read(buffer.data(), buffer.size());

        input.close();
        return;
    }

    for (ArchivesMap::reverse_iterator i = _openArchives.rbegin(); i != _openArchives.rend(); ++i)
    {
        HANDLE fileHandle;

        if (!i->second->openFile(filename, &fileHandle))
            continue;

        eof = false;
        buffer.resize(SFileGetFileSize(fileHandle, nullptr));
        SFileReadFile(fileHandle, buffer.data(), buffer.size(), nullptr, nullptr); //last nullptrs for newer version of StormLib
        SFileCloseFile(fileHandle);

        return;
    }

    throw std::invalid_argument("File '" + filename + "' does not exist.");
}

MPQFile::~MPQFile()
{
    close();
}

bool MPQFile::exists(std::string const& filename)
{
    return existsOnDisk(filename) || existsInMPQ(filename);
}
bool MPQFile::existsOnDisk(std::string const& filename)
{
    return std::filesystem::exists(filename);
}

size_t MPQFile::read(void* dest, size_t bytes)
{
    if (eof || !bytes)
        return 0;

    size_t rpos = pointer + bytes;
    if (rpos > buffer.size()) {
        bytes = buffer.size() - pointer;
        eof = true;
    }

    memcpy(dest, &(buffer[pointer]), bytes);

    pointer = rpos;

    return bytes;
}

bool MPQFile::isEof() const
{
    return eof;
}

void MPQFile::seek(size_t offset)
{
    pointer = offset;
    eof = (pointer >= buffer.size());
}

void MPQFile::seekRelative(size_t offset)
{
    pointer += offset;
    eof = (pointer >= buffer.size());
}

void MPQFile::close()
{
    eof = true;
}

size_t MPQFile::getSize() const
{
    return buffer.size();
}

size_t MPQFile::getPos() const
{
    return pointer;
}

char const* MPQFile::getBuffer() const
{
    return buffer.data();
}

char const* MPQFile::getPointer() const
{
    return buffer.data() + pointer;
}

void MPQFile::SaveFile()
{
}


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
    archive->finishLoading();
}

String MPQArchive::getSuffix()
{
    return ".MPQ";
}

void MPQArchive::parseScript(DataStreamPtr& stream, const String& groupName)
{
    _mpqName = stream->getName();
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