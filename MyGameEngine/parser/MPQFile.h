#pragma once

#include "OgreScriptLoader.h"

class MPQFile
{
    bool eof;
    std::vector<char> buffer;
    size_t pointer;


    bool External;
    std::string _disk_path;
    std::string _mpq_path;
    
    
public:
    explicit MPQFile(const std::string& pFilename);  // filenames are not case sensitive, the are if u dont use a filesystem which is kinda shitty...

    MPQFile() = delete;
    ~MPQFile();
    MPQFile(MPQFile const&) = delete;
    MPQFile(MPQFile&&) = delete;
    MPQFile& operator=(MPQFile const&) = delete;
    MPQFile& operator=(MPQFile&&) = delete;

    size_t read(void* dest, size_t bytes);
    size_t getSize() const;
    size_t getPos() const;
    char const* getBuffer() const;
    char const* getPointer() const;
    bool isEof() const;
    void seek(size_t offset);
    void seekRelative(size_t offset);
    void close();
    bool isExternal() const
    {
        return External;
    }

    template<typename T>
    const T* get(size_t offset) const
    {
        return reinterpret_cast<T const*>(buffer.data() + offset);
    }

    void setBuffer(std::vector<char> const& vec)
    {
        buffer = vec;
    }

    void SaveFile();

    static bool exists(std::string const& filename);
    static bool existsOnDisk(std::string const& filename);
};

class MPQArchive : public Ogre::ScriptLoader, public PackFileBase
{
public:
    MPQArchive(const std::string& name, bool doListfile);
    bool hasFile(const std::string& filename) const;
    bool openFile(const std::string& filename, HANDLE* fileHandle) const;
    void finishLoading();
    static void loadMPQ(const std::string& filename, bool doListfile = false);

    virtual String getSuffix();
    virtual void parseScript(DataStreamPtr& stream, const String& groupName);
    virtual Real getLoadingOrder(void) const;

    Ogre::StreamContent* getPackfile(
        const String& name, const String& group);
private:
    HANDLE _archiveHandle;
    std::atomic<bool> finished = false;
    std::string _mpqName;
};