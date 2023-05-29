#pragma once
#include "OgreDataStream.h"
class FileDataStream: public Ogre::DataStream
{
public:
    FileDataStream(const std::string& name);
    ~FileDataStream();

    virtual void seek(int64_t pos);
    virtual int64_t tell(void) const;
    virtual bool eof(void) const;
    virtual size_t read(void* buf, int64_t count);
    virtual void skip(int64_t count);
private:
    void _init();
private:
    FILE* mFile;
    uint64_t mCurrentPos;
};