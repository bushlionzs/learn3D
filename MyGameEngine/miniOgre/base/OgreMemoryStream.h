#pragma once

#include "OgreDataStream.h"
class ResourceInfo;
namespace Ogre {

    class MemoryDataStream : public Ogre::DataStream
    {
    public:
        MemoryDataStream(ResourceInfo* res);
        ~MemoryDataStream();

        virtual void seek(int64_t pos);
        virtual void seekRelative(int64_t pos);
        virtual int64_t tell(void) const;
        virtual bool eof(void) const;
        virtual size_t read(void* buf, int64_t count);
        virtual void skip(int64_t count);
        virtual String getLine(bool trimAfter);
        virtual const char* getStreamData();
        virtual const char* getCurrentStreamData();
    private:
        std::string mMem;

        const char* mFirst;
        const char* mEnd;
        const char* mCurrent;
    };
}