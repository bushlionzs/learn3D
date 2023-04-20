#pragma once
#include <string>

namespace Ogre {
    class StreamContent
    {
    public:
        const char* _data;
        uint64_t _size;
    };
    class DataStream
    {
    public:
#define STRING_STREAM_TEMP_SIZE 128
    public:
        DataStream(const std::string& name);
        ~DataStream();

        virtual void seek(int64_t pos) = 0;
        virtual int64_t tell(void) const = 0;
        virtual bool eof(void) const = 0;
        virtual size_t read(void* buf, int64_t count) = 0;
        virtual void skip(int64_t count) = 0;
        virtual uint32_t getStreamLength();
        virtual String getLine(bool trimAfter);
        virtual const char* getStreamData();
        std::string getBaseDir();

        const std::string& getName()
        {
            return mStreamName;
        }

        String getAsString(void);
    protected:
        std::string mStreamName;
        int64_t mSize;
    };
}