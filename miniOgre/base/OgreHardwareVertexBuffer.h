#pragma once

#include <memory>
#include "OgreHardwareBuffer.h"
#include "OgreColourValue.h"

enum VertexElementType
{
    VET_FLOAT1 = 0,
    VET_FLOAT2 = 1,
    VET_FLOAT3 = 2,
    VET_FLOAT4 = 3,

    VET_SHORT1 = 5,  ///< @deprecated (see #VertexElementType note)
    VET_SHORT2 = 6,
    VET_SHORT3 = 7,  ///< @deprecated (see #VertexElementType note)
    VET_SHORT4 = 8,
    VET_UBYTE4 = 9,
    _DETAIL_SWAP_RB = 10,

    // the following are not universally supported on all hardware:
    VET_DOUBLE1 = 12,
    VET_DOUBLE2 = 13,
    VET_DOUBLE3 = 14,
    VET_DOUBLE4 = 15,
    VET_USHORT1 = 16,  ///< @deprecated (see #VertexElementType note)
    VET_USHORT2 = 17,
    VET_USHORT3 = 18,  ///< @deprecated (see #VertexElementType note)
    VET_USHORT4 = 19,
    VET_INT1 = 20,
    VET_INT2 = 21,
    VET_INT3 = 22,
    VET_INT4 = 23,
    VET_UINT1 = 24,
    VET_UINT2 = 25,
    VET_UINT3 = 26,
    VET_UINT4 = 27,
    VET_BYTE4 = 28,  ///< signed bytes
    VET_BYTE4_NORM = 29,   ///< signed bytes (normalized to -1..1)
    VET_UBYTE4_NORM = 30,  ///< unsigned bytes (normalized to 0..1)
    VET_SHORT2_NORM = 31,  ///< signed shorts (normalized to -1..1)
    VET_SHORT4_NORM = 32,
    VET_USHORT2_NORM = 33, ///< unsigned shorts (normalized to 0..1)
    VET_USHORT4_NORM = 34,
    VET_INT_10_10_10_2_NORM = 35, ///< signed int (normalized to 0..1)
    VET_COLOUR = VET_UBYTE4_NORM,  ///< @deprecated use VET_UBYTE4_NORM
    VET_COLOUR_ARGB = VET_UBYTE4_NORM,  ///< @deprecated use VET_UBYTE4_NORM
    VET_COLOUR_ABGR = VET_UBYTE4_NORM,  ///< @deprecated use VET_UBYTE4_NORM
};

enum VertexElementSemantic {
    /// Position, typically VET_FLOAT3
    VES_POSITION = 1,
    /// Blending weights
    VES_BLEND_WEIGHTS = 2,
    /// Blending indices
    VES_BLEND_INDICES = 3,
    /// Normal, typically VET_FLOAT3
    VES_NORMAL = 4,
    /// Colour, typically VET_UBYTE4
    VES_COLOUR = 5,
    /// Secondary colour. Generally free for custom data. Means specular with OpenGL FFP.
    VES_COLOUR2 = 6,
    /// Texture coordinates, typically VET_FLOAT2
    VES_TEXTURE_COORDINATES = 7,
    /// Binormal (Y axis if normal is Z)
    VES_BINORMAL = 8,
    /// Tangent (X axis if normal is Z)
    VES_TANGENT = 9,
    /// The  number of VertexElementSemantic elements (note - the first value VES_POSITION is 1) 
    VES_COUNT = 9,
    /// @deprecated use VES_COLOUR
    VES_DIFFUSE = VES_COLOUR,
    /// @deprecated use VES_COLOUR2
    VES_SPECULAR = VES_COLOUR2
};

class VertexElement
{
public:
    VertexElement(int16_t source, int16_t index, int32_t offset, VertexElementType type, VertexElementSemantic semantic)
    {
        mSource         = source;
        mIndex          = index;
        mOffset         = offset;
        mType           = type;
        mSemantic       = semantic;
    }

    VertexElementSemantic  getSemantic() const
    {
        return mSemantic;
    }

    int16_t getSource() const
    {
        return mSource;
    }

    int16_t getIndex() const
    {
        return mIndex;
    }

    int16_t getOffset() const
    {
        return mOffset;
    }

    VertexElementType getType() const
    {
        return mType;
    }

    uint32_t getSize(void) const;

    inline void baseVertexPointerToElement(void* pBase, float** pElem) const
    {
        *pElem = static_cast<float*>(
            static_cast<void*>(
                static_cast<unsigned char*>(pBase) + mOffset));
    }

    template<typename T>
    void baseVertexPointerToElement(void* pBase, T** pElem) const
    {
        // The only way we can do this is to cast to char* in order to use byte offset
        // then cast back to T*.
        *pElem = reinterpret_cast<T*>(static_cast<char*>(pBase) + mOffset);
    }

    static uint32_t getTypeSize(VertexElementType etype);

    static uint32_t convertColourValue(const Ogre::ColourValue& src,
        VertexElementType dst);
private:
    int32_t mOffset;
    int16_t mSource;
    int16_t mIndex;
    VertexElementType mType;
    VertexElementSemantic mSemantic;
};


namespace Ogre {

    class HardwareVertexBuffer : public HardwareBuffer
    {
    public:
        HardwareVertexBuffer(size_t vertexSize, size_t numVerts,
            HardwareBuffer* delegate);
        ~HardwareVertexBuffer();


        virtual void* lockimpl(size_t offset, size_t length, LockOptions options);
        virtual void unlock();
        virtual void bind(int32_t slot, void* cb);

        

        int32_t getVertexSize()
        {
            return mVertexSize;
        }

        HardwareBuffer* getHardwareBuffer()
        {
            return mDelegate.get();
        }
    private:
        std::unique_ptr<HardwareBuffer> mDelegate;
        
    };
}