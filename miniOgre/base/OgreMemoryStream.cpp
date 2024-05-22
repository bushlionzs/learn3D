#include "OgreHeader.h"
#include "OgreMemoryStream.h"
#include "OgreResourceManager.h"
#include "myutils.h"
#include "platform_file.h"
namespace Ogre {

    MemoryDataStream::MemoryDataStream(ResourceInfo* res)
        :DataStream(res->_fullname)
    {
        if (res->_base)
        {
            auto content = res->_base->getPackfile(res->_fullname);
            if (content)
            {
                mSize = content->_size;
                mFirst = content->_data;
                mEnd = mFirst + mSize;
                mCurrent = mFirst;
            }
            else
            {
                assert(false);
                mSize = 0;
                mFirst = nullptr;
                mEnd = nullptr;
                mCurrent = nullptr;
            }
        }
        else
        {
            get_file_content(res->_fullname.c_str(), mMem);
            mSize = mMem.size();
            mFirst = mMem.data();
            mEnd = mFirst + mSize;
            mCurrent = mFirst;
        }
    }

    MemoryDataStream::MemoryDataStream(const char* data, uint32_t size)
        :DataStream("")
    {
        mMem.assign(data, size);
        mSize = size;
        mFirst = mMem.data();
        mEnd = mFirst + mSize;
        mCurrent = mFirst;
    }

    MemoryDataStream::~MemoryDataStream()
    {

    }

    void MemoryDataStream::seek(int64_t pos)
    {
        mCurrent = mFirst + pos;
    }

    void MemoryDataStream::seekRelative(int64_t pos)
    {
        mCurrent += pos;
    }

    int64_t MemoryDataStream::tell(void) const
    {
        return mCurrent - mFirst;
    }

    bool MemoryDataStream::eof(void) const
    {
        return mCurrent == mEnd;
    }

    size_t MemoryDataStream::read(void* buf, int64_t count)
    {
        int64_t left = mEnd - mCurrent;

        int64_t r = std::min(left, count);

        memcpy(buf, mCurrent, r);

        mCurrent += r;

        return r;
    }

    void MemoryDataStream::skip(int64_t count)
    {
        mCurrent += count;

        if (mCurrent >= mEnd)
        {
            mCurrent = mEnd;
        }
    }

    String MemoryDataStream::getLine(bool trimAfter)
    {
        char tmpBuf[STRING_STREAM_TEMP_SIZE];
        String retString;
        size_t readCount;
        // Keep looping while not hitting delimiter
        while ((readCount = read(tmpBuf, STRING_STREAM_TEMP_SIZE - 1)) != 0)
        {
            // Terminate string
            tmpBuf[readCount] = '\0';

            char* p = strchr(tmpBuf, '\n');
            if (p != 0)
            {
                // Reposition backwards
                skip((long)(p + 1 - tmpBuf - readCount));
                *p = '\0';
            }

            retString += tmpBuf;

            if (p != 0)
            {
                // Trim off trailing CR if this was a CR/LF entry
                if (retString.length() && retString[retString.length() - 1] == '\r')
                {
                    retString.erase(retString.length() - 1, 1);
                }

                // Found terminator, break out
                break;
            }
        }

        if (trimAfter)
        {
            StringUtil::trim(retString);
        }

        return retString;
    }

    const char* MemoryDataStream::getStreamData()
    {
        return mFirst;
    }

    const char* MemoryDataStream::getCurrentStreamData()
    {
        return mCurrent;
    }
}