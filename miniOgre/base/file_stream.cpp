#include "OgreHeader.h"
#include "file_stream.h"
#include "OgreResourceManager.h"
#include <exception>
#include <stdexcept>

FileDataStream::FileDataStream(const std::string& name)
    :DataStream(name)
{
    mFile = nullptr;
    mCurrentPos = mSize = 0;
    _init();
}

FileDataStream::~FileDataStream()
{
    if (mFile != nullptr)
    {
        fclose(mFile);
    }
}

void FileDataStream::seek(int64_t pos)
{
    fseek(mFile, pos, SEEK_SET);
}

int64_t FileDataStream::tell(void) const
{
    return mCurrentPos;
}

bool FileDataStream::eof(void) const
{
    return mCurrentPos == mSize;
}

size_t FileDataStream::read(void* buf, int64_t count)
{
    size_t r = fread(buf, 1, count, mFile);
    mCurrentPos += r;
    return r;
}

void FileDataStream::skip(int64_t count)
{
    fseek(mFile, count, SEEK_CUR);
}

void FileDataStream::_init()
{
    if (mFile != nullptr)
    {
        fclose(mFile);
    }

    mFile = fopen(mStreamName.c_str(), "rb");

    if (mFile == nullptr)
    {
        std::throw_with_nested(std::runtime_error("Couldn't open " + mStreamName));
        return;
    }

    fseek(mFile, 0, SEEK_END);

    mSize = ftell(mFile);

    fseek(mFile, 0, SEEK_SET);

}
