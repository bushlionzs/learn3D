#pragma once

#define OGRE_SERIALIZER_VALIDATE_CHUNKSIZE 1

namespace Ogre {

    class Serializer
    {
    public:
        const uint16 HEADER_STREAM_ID = 0x1000;
        static const long STREAM_OVERHEAD_SIZE = sizeof(uint16_t) + sizeof(uint32_t);
        enum Endian
        {
            /// Use the platform native endian
            ENDIAN_NATIVE,
            /// Use big endian (0x1000 is serialised as 0x10 0x00)
            ENDIAN_BIG,
            /// Use little endian (0x1000 is serialised as 0x00 0x10)
            ENDIAN_LITTLE
        };
    public:
        Serializer();
        ~Serializer();
    public:
        void flipFromLittleEndian(void* pData, size_t size, size_t count);
        /// Determine the endianness of the incoming stream compared to native
        void determineEndianness(const DataStreamPtr& stream);
        /// Determine the endianness to write with based on option
        void determineEndianness(Endian requestedEndian);
        void readFileHeader(const std::shared_ptr<DataStream>& stream);
        bool skipChunk(const std::shared_ptr<DataStream>& stream);
        uint32_t readChunk(const std::shared_ptr<DataStream>& stream);
        void pushInnerChunk(const std::shared_ptr<DataStream>& stream);
        void popInnerChunk(const std::shared_ptr<DataStream>& stream);
        void backpedalChunkHeader(const std::shared_ptr<DataStream>& stream);

        void readBools(const std::shared_ptr<DataStream>& stream, bool* pDest, size_t count);
        void readFloats(const std::shared_ptr<DataStream>& stream, float* pDest, size_t count);
        void readFloats(const std::shared_ptr<DataStream>& stream, double* pDest, size_t count);
        static void readShorts(const std::shared_ptr<DataStream>& stream, uint16_t* pDest, size_t count);
        void readInts(const std::shared_ptr<DataStream>& stream, uint32_t* pDest, size_t count);

        void readObject(const std::shared_ptr<DataStream>& stream, Ogre::Vector3& v);
        void readObject(const std::shared_ptr<DataStream>& stream, Ogre::Quaternion& v);
        void readData(const std::shared_ptr<DataStream>& stream, void* pDest, size_t size, size_t count);
        String readStringBin(const std::shared_ptr<DataStream>& stream);
       String readString(const std::shared_ptr<DataStream>& stream);
    protected:
        static size_t calcChunkHeaderSize() { return sizeof(uint16) + sizeof(uint32); }
        static size_t calcStringSize(const String& string) { return string.length() + 1; }
    protected:
        uint32_t mCurrentstreamLen;
        String   mVersion;
        String   mFileType;
        String   mCopyRight;
#if OGRE_SERIALIZER_VALIDATE_CHUNKSIZE
        typedef std::vector<size_t> ChunkSizeStack;
        ChunkSizeStack mChunkSizeStack;
        bool mReportChunkErrors;
#endif

        bool mFlipEndian = false;
    };
}