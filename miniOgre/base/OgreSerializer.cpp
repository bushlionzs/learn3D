#include "OgreHeader.h"
#include "OgreSerializer.h"
#include "OgreDataStream.h"
#include "OgreBitwise.h"

static const long STREAM_OVERHEAD_SIZE = sizeof(uint16_t) + sizeof(uint32_t);
namespace Ogre {

    Serializer::Serializer()
    {
        mVersion = "[Serializer_v1.00]";
    }

    Serializer::~Serializer()
    {

    }

    void Serializer::readFileHeader(const std::shared_ptr<DataStream>& stream)
    {
        unsigned short headerID;

        // Read header ID
        readShorts(stream, &headerID, 1);

        if (headerID == HEADER_STREAM_ID)
        {
            // Read version
            String ver = readString(stream);
            if (ver != mVersion)
            {
                OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR,
                    "Invalid file: version incompatible, file reports " + String(ver) +
                    " Serializer is version " + mVersion,
                    "Serializer::readFileHeader");
            }
        }
        else
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "Invalid file: no header",
                "Serializer::readFileHeader");
        }
    }

    void Serializer::flipFromLittleEndian(void* pData, size_t size, size_t count)
    {
        if (mFlipEndian)
        {
            Ogre::Bitwise::bswapChunks(pData, size, count);
        }
    }

    void Serializer::determineEndianness(const DataStreamPtr& stream)
    {

    }
    /// Determine the endianness to write with based on option
    void Serializer::determineEndianness(Endian requestedEndian)
    {

    }

    bool    Serializer::skipChunk(const std::shared_ptr<DataStream>& stream)
    {
        stream->skip(mCurrentstreamLen - STREAM_OVERHEAD_SIZE);
        return true;
    }

    uint32_t Serializer::readChunk(const std::shared_ptr<DataStream>& stream)
    {
#if OGRE_SERIALIZER_VALIDATE_CHUNKSIZE
        size_t pos = stream->tell();
#endif
        unsigned short id;
        readShorts(stream, &id, 1);

        readInts(stream, &mCurrentstreamLen, 1);
#if OGRE_SERIALIZER_VALIDATE_CHUNKSIZE
        if (!mChunkSizeStack.empty() && !stream->eof()) {
            if (pos != static_cast<size_t>(mChunkSizeStack.back())) {
                OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "chunk stack exception");
            }
            mChunkSizeStack.back() = pos + mCurrentstreamLen;
        }
#endif
        return id;
    }

    void Serializer::pushInnerChunk(const std::shared_ptr<DataStream>& stream)
    {
#if OGRE_SERIALIZER_VALIDATE_CHUNKSIZE
        mChunkSizeStack.push_back(stream->tell());
#endif
    }

    void Serializer::popInnerChunk(const std::shared_ptr<DataStream>& stream)
    {
#if OGRE_SERIALIZER_VALIDATE_CHUNKSIZE
        if (!mChunkSizeStack.empty()) {
            size_t pos = stream->tell();
            if (pos != static_cast<size_t>(mChunkSizeStack.back()) && !stream->eof() && mReportChunkErrors) {
                OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "chunk stack exception");
            }

            mChunkSizeStack.pop_back();
        }
#endif
    }

    void Serializer::backpedalChunkHeader(const std::shared_ptr<DataStream>& stream)
    {
        if (!stream->eof()) {
            stream->skip(-(int)calcChunkHeaderSize());
        }
#if OGRE_SERIALIZER_VALIDATE_CHUNKSIZE
        mChunkSizeStack.back() = stream->tell();
#endif
    }

    void Serializer::readBools(const std::shared_ptr<DataStream>& stream, bool* pDest, size_t count)
    {
        stream->read(pDest, sizeof(bool) * count);
    }

    void Serializer::readFloats(const std::shared_ptr<DataStream>& stream, float* pDest, size_t count)
    {
        stream->read(pDest, sizeof(float) * count);
    }

    void Serializer::readFloats(const std::shared_ptr<DataStream>& stream, double* pDest, size_t count)
    {
        stream->read(pDest, sizeof(double) * count);
    }

    void Serializer::readShorts(const std::shared_ptr<DataStream>& stream, uint16_t* pDest, size_t count)
    {
        stream->read(pDest, sizeof(uint16_t) * count);
    }

    void Serializer::readInts(const std::shared_ptr<DataStream>& stream, uint32_t* pDest, size_t count)
    {
        stream->read(pDest, sizeof(uint32_t) * count);
    }

    void Serializer::readObject(const std::shared_ptr<DataStream>& stream, Ogre::Vector3& v)
    {
        float tmp[3];
        readFloats(stream, tmp, 3);

        v.x = tmp[0];
        v.y = tmp[1];
        v.z = tmp[2];
    }

    void Serializer::readObject(const std::shared_ptr<DataStream>& stream, Ogre::Quaternion& v)
    {
        float tmp[4];
        readFloats(stream, tmp, 4);
        v.x = tmp[0];
        v.y = tmp[1];
        v.z = tmp[2];
        v.w = tmp[3];
    }

    void Serializer::readData(const std::shared_ptr<DataStream>& stream, void* pDest, size_t size, size_t count)
    {
        stream->read(pDest, size * count);
        flipFromLittleEndian(pDest, size, count);
    }

    String Serializer::readStringBin(const std::shared_ptr<DataStream>& stream)
    {
        String string;
        if (!stream->eof())
        {
            unsigned int length = 0;
            stream->read(&length, sizeof(unsigned int));
            string.resize(length);
            stream->read(string.data(), length);
            string.pop_back();
        }
        return string;
    }

    String Serializer::readString(const std::shared_ptr<DataStream>& stream)
    {
        return stream->getLine(false);
    }
}