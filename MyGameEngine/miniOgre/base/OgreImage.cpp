// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "OgreHeader.h"
#include "OgreImage.h"
#include "myutils.h"
#include "stb_image.h"
#include "dds_load.h"
#include "OgreResourceManager.h"

namespace Ogre {

    CImage::CImage()
    {
        mWidth = 0;
        mHeight = 0;
        mFormat = Ogre::PF_UNKNOWN;
        mImageData = nullptr;
        mDepth = 1;
        mFace = 1;
        mPixelSize = 0;
        mNumMipmaps = 0;
    }

    CImage::~CImage()
    {
        freeMemory();
    }

    bool CImage::loadImage(const std::string& name)
    {
        const char* suffix = getSuffix(name);

        bool dds = false;

        if (strcmp(suffix, ".dds") == 0)
        {
            dds = true;
        }

        std::shared_ptr<DataStream> stream 
            = ResourceManager::getSingleton().openResource(name);

        if (!stream)
        {
            return false;
        }
        uint32_t nrComponents = 0;

        unsigned char* data = nullptr;
        if (dds)
        {
            DDSImage ddsload;
            if (ddsload.load(stream))
            {
                data = ddsload.data();
                nrComponents = 4;

                ImageData* imageData = ddsload.getImageInfo();

                mWidth = imageData->width;
                mHeight = imageData->height;
                mDepth = imageData->depth;
                mFace = imageData->face;
                mNumMipmaps = imageData->num_mipmaps;
                mFormat = imageData->format;
            }
        }
        else
        {
            mFace = 1;
            const stbi_uc* stream_data = (const stbi_uc*)stream->getStreamData();
            uint32_t size = stream->getStreamLength();
            data = stbi_load_from_memory(stream_data, size,
                (int*)&mWidth, (int*)&mHeight, (int*)&nrComponents, 0);

            mPixelSize = nrComponents;
            if (nrComponents == 3)
            {
                mFormat = Ogre::PF_BYTE_RGB;
            }
            else if (nrComponents == 4)
            {
                mFormat = Ogre::PF_BYTE_RGBA;
            }
            else if (nrComponents == 2)
            {
                mFormat = Ogre::PF_BYTE_LA;
            }
            else if (nrComponents == 1)
            {
                mFormat = Ogre::PF_L8;
            }
        }


       // mNumMipmaps = 0;
        mImageData = data;

        mImageDataSize = calculateSize(
            mNumMipmaps, mFace, mWidth, mHeight, mDepth, mFormat);
        

        return true;
    }

    int CImage::getWidth() const
    {
        return mWidth;
    }

    int CImage::getHeight() const
    {
        return mHeight;
    }

    Ogre::PixelFormat CImage::getFormat() const
    {
        return mFormat;
    }

    int CImage::getDepth() const
    {
        return mDepth;
    }

    int CImage::getNumFaces() const
    {
        return mFace;
    }

    int CImage::getNumMipmaps() const
    {
        return mNumMipmaps;
    }

    unsigned char* CImage::getImageData()
    {
        return mImageData;
    }

    uint32_t CImage::getSize()
    {
        return mImageDataSize;
    }

    Ogre::PixelBox CImage::getPixelBox(uint32 face, uint32 mipmap) const
    {
        uint8* offset = mImageData;
        uint32 width = mWidth, height = mHeight, depth = mDepth;
        uint32 numMips = mNumMipmaps;

        size_t fullFaceSize = 0;
        size_t finalFaceSize = 0;
        uint32 finalWidth = 0, finalHeight = 0, finalDepth = 0;
        for (uint32 mip = 0; mip <= mNumMipmaps; ++mip)
        {
            if (mip == mipmap)
            {
                finalFaceSize = fullFaceSize;
                finalWidth = width;
                finalHeight = height;
                finalDepth = depth;
            }
            fullFaceSize += PixelUtil::getMemorySize(width, height, depth, getFormat());

            /// Half size in each dimension
            if (width != 1) width /= 2;
            if (height != 1) height /= 2;
            if (depth != 1) depth /= 2;
        }
        // Advance pointer by number of full faces, plus mip offset into
        offset += face * fullFaceSize;
        offset += finalFaceSize;
        // Return subface as pixelbox
        PixelBox src(finalWidth, finalHeight, finalDepth, getFormat(), offset);
        return src;
    }


    const uchar* CImage::getData(uint32 x, uint32 y, uint32 z) const
    {
        assert(mImageData);
        assert(x < mWidth&& y < mHeight&& z < mDepth);
        return mImageData + mPixelSize * (z * mWidth * mHeight + mWidth * y + x);
    }

    void CImage::convertRawData(void* from, void* to, size_t _size, int _format)
    {

    }

    void CImage::CImage::freeMemory()
    {
        if (mImageData)
        {
            delete mImageData;
            mImageData = nullptr;
        }
    }

    Ogre::ColourValue CImage::getColourAt(uint32 x, uint32 y, uint32 z) const
    {
        Ogre::ColourValue rval;
        Ogre::PixelUtil::unpackColour(&rval, mFormat, getData(x, y, z));
        return rval;
    }

    CImage& CImage::loadDynamicImage(
        uchar* data, 
        uint32 width, 
        uint32 height, 
        uint32 depth, 
        PixelFormat format,
        bool autoDelete, 
        uint32 numFaces, 
        uint32 numMipMaps)
    {
        freeMemory();
        // Set image metadata
        mWidth = width;
        mHeight = height;
        mDepth = depth;
        mFormat = format;
        mPixelSize = static_cast<uchar>(PixelUtil::getNumElemBytes(mFormat));
        mNumMipmaps = numMipMaps;
        mFlags = 0;
        // Set flags
        if (PixelUtil::isCompressed(format))
            mFlags |= IF_COMPRESSED;
        if (mDepth != 1)
            mFlags |= IF_3D_TEXTURE;
        if (numFaces == 6)
            mFlags |= IF_CUBEMAP;
        OgreAssert(numFaces == 6 || numFaces == 1, "Invalid number of faces");

        mImageDataSize = calculateSize(numMipMaps, numFaces, width, height, depth, format);
        mImageData = data;
        mAutoDelete = autoDelete;

        return *this;
    }

    //-----------------------------------------------------------------------------
    size_t CImage::calculateSize(
        uint32 mipmaps, 
        uint32 faces, 
        uint32 width, 
        uint32 height, 
        uint32 depth,
        PixelFormat format)
    {
        size_t size = 0;
        for (uint32 mip = 0; mip <= mipmaps; ++mip)
        {
            size += PixelUtil::getMemorySize(width, height, depth, format) * faces;
            if (width != 1) width /= 2;
            if (height != 1) height /= 2;
            if (depth != 1) depth /= 2;
        }
        return size;
    }

    void CImage::save(const String& filename)
    {

    }
}