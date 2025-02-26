// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "OgreHeader.h"
#include "OgreImage.h"
#include "myutils.h"
#include "stb_image.h"
#include "dds_load.h"
#include "OgreResourceManager.h"
#include "OgreMemoryStream.h"
#include "OgreBlp.h"
#include <gli/gli.hpp>
#include <platform_file.h>
#include <compressonator.h>

namespace Ogre {

    CImage::CImage()
    {
        mImageData = nullptr;
        mPixelSize = 0;
    }

    CImage::~CImage()
    {
        freeMemory();
    }

    Ogre::ImageType CImage::getImageType(const std::string& name)
    {
        std::string suffix = getSuffix(name);
        if (suffix == ".dds")
        {
            return Ogre::ImageType_DDS;
        }
        else if (suffix == ".ktx")
        {
            return Ogre::ImageType_KTX;
        }
        else if (suffix == ".blp")
        {
            return Ogre::ImageType_BLP;
        }
        else if (suffix == ".png")
        {
            return Ogre::ImageType_PNG;
        }
        else if (suffix == ".jpg")
        {
            return Ogre::ImageType_JPG;
        }
        else
        {
            return Ogre::ImageType_UnSupported;
        }
    }

    PixelFormat getClosestSupportedPF(PixelFormat ogrePF)
    {
        switch (ogrePF)
        {
        case PF_R8G8B8:
            return PF_X8R8G8B8;
        case PF_FLOAT16_RGB:
            return PF_FLOAT16_RGBA;
        case PF_FLOAT32_RGB:
            return PF_FLOAT32_RGBA;
        case PF_DEPTH16:
            return PF_L16;
        case PF_DEPTH24_STENCIL8:
        case PF_DEPTH32:
        case PF_DEPTH32F:
            return PF_FLOAT32_R;
        default:
            return ogrePF;
        }
    }

    bool CImage::loadImageInfo(
        const uint8_t* data, 
        uint32_t byteCount, 
        ImageInfo& imageInfo,
        Ogre::ImageType type)
    {
        switch (type)
        {
        case Ogre::ImageType::ImageType_PNG:
        case Ogre::ImageType::ImageType_JPG:
        {
            int width;
            int height;
            int numComponents;
            stbi_info_from_memory(data, byteCount, &width, &height, &numComponents);
            imageInfo.width = width;
            imageInfo.height = height;
            if (numComponents == 3)
            {
                imageInfo.format = Ogre::PF_BYTE_RGB;
            }
            else if (numComponents == 4)
            {
                imageInfo.format = Ogre::PF_BYTE_RGBA;
            }
            else if (numComponents == 2)
            {
                imageInfo.format = Ogre::PF_BYTE_LA;
            }
            else if (numComponents == 1)
            {
                imageInfo.format = Ogre::PF_L8;
            }
            
            return true;
        }
            
        case Ogre::ImageType::ImageType_DDS:
            return DDSImage::load_simple_info((const char*)data, byteCount, imageInfo);
        default:
            assert_invariant(false);
            return false;
            break;
        }
        
    }

    Ogre::PixelFormat translateKtxFormat(gli::texture::format_type format)
    {
        switch (format)
        {
        case gli::FORMAT_RGBA16_SFLOAT_PACK16:
            return Ogre::PF_FLOAT16_RGBA;
        case gli::FORMAT_RGBA8_UNORM_PACK8:
            return Ogre::PF_A8B8G8R8;
        default:
            assert_invariant(false);
        }
        return Ogre::PF_FLOAT16_RGBA;
    }
    bool CImage::loadImageInfo(
        const std::string& name,
        ImageInfo& imageInfo,
        bool cube)
    {
        ResourceInfo* res = nullptr;
        Ogre::ImageType type = CImage::getImageType(name);
        if (cube)
        {
            if (type == Ogre::ImageType::ImageType_DDS ||
                type == Ogre::ImageType::ImageType_KTX)
            {
                res = ResourceManager::getSingleton().getResourceInfo(name);
            }
            else
            {
                std::string suffix = getSuffix(name);
                std::string basename = removeSuffix(name);
                std::string current = basename + "_rt" + suffix;
                res = ResourceManager::getSingleton().getResourceInfo(current);
            }
            
        }
        else
        {
            res = ResourceManager::getSingleton().getResourceInfo(name);
        }
        

        std::string content;
        get_file_content(res->_fullname.c_str(), content, 2048);

        const char* data = content.c_str();
        uint32_t byteCount = content.size();
        
        return CImage::loadImageInfo((const uint8_t*)data, byteCount, imageInfo, type);
    }

    void CImage::freeImageData(void* data)
    {
        stbi_image_free(data);
    }

    bool CImage::loadImage(const std::string& name, bool cube)
    {
        auto type = getImageType(name);
        uint32_t nrComponents = 0;

        unsigned char* data = nullptr;
        if (type == Ogre::ImageType::ImageType_DDS)
        {
            std::shared_ptr<DataStream> stream
                = ResourceManager::getSingleton().openResource(name);
            DDSImage ddsload;
            if (ddsload.load(stream.get()))
            {
                data = ddsload.data();
                nrComponents = 4;

                ImageInfo* imageData = ddsload.getImageInfo();
                mImageInfo = *imageData;
            }
        }
        else if (type == Ogre::ImageType::ImageType_KTX)
        {
            auto resInfo = ResourceManager::getSingleton().getResourceInfo(name);
            gli::texture tmp = gli::load(resInfo->_fullname.c_str());

            mImageInfo.width = static_cast<uint32_t>(tmp.extent().x);
            mImageInfo.height = static_cast<uint32_t>(tmp.extent().y);
            mImageInfo.num_mipmaps = static_cast<uint32_t>(tmp.levels()) - 1;
            mImageInfo.face = tmp.faces();
            mImageInfo.size = tmp.size();
            auto ktxFormat = tmp.format();
            mImageInfo.format = translateKtxFormat(ktxFormat);
            data = new unsigned char[mImageInfo.size];
            memcpy(data, tmp.data(), mImageInfo.size);
            int kk = 0;
        }
        else if (type == Ogre::ImageType::ImageType_BLP)
        {
            std::shared_ptr<DataStream> stream
                = ResourceManager::getSingleton().openResource(name);
            OgreBlpImage blpImage;
            blpImage.load(stream);
            data = blpImage.data();
            ImageInfo* imageData = blpImage.getImageInfo();

            mImageInfo = *imageData;
        }
        else
        {
            mImageInfo.face = 1;
            PixelFormat format[4] = { Ogre::PF_L8, Ogre::PF_BYTE_LA, Ogre::PF_BYTE_RGB, Ogre::PF_BYTE_RGBA };
            {
                std::shared_ptr<DataStream> stream
                    = ResourceManager::getSingleton().openResource(name);

                const stbi_uc* stream_data = (const stbi_uc*)stream->getStreamData();
                uint32_t size = stream->getStreamLength();
                data = stbi_load_from_memory(stream_data, size,
                    (int*)&mImageInfo.width, (int*)&mImageInfo.height, (int*)&nrComponents, 0);
                mImageInfo.format = format[nrComponents - 1];
            }
         
            mPixelSize = nrComponents;   
        }

        mImageData = data;

        mImageDataSize = calculateSize(mImageInfo);
        bool compress = true;
        if (compress)
        {
            //compressonator lib crash in multi-thread, so add a mutex
            static std::mutex _mutex;
            std::unique_lock<std::mutex> lock(_mutex);
            if (mImageInfo.format == Ogre::PF_BYTE_RGBA)
            {
                CMP_MipSet mipSet = {};
                uint32_t width = mImageInfo.width;
                uint32_t height = mImageInfo.height;
                mipSet.m_nWidth = width;
                mipSet.m_nHeight = height;
                mipSet.m_nDepth = 1;
                mipSet.m_format = CMP_FORMAT_RGBA_8888;
                mipSet.m_nMipLevels = 1;

                
                uint32_t maxMipLevels = static_cast<uint32_t>(floor(log2(std::max(width, height))) + 1.0);
                mipSet.m_nMaxMipLevels = maxMipLevels;
                CMP_MipLevel dummy[20];
                mipSet.m_pMipLevelTable = (CMP_MipLevelTable*)malloc(sizeof(CMP_MipLevel*)* maxMipLevels);
                for (uint32_t i = 0; i < maxMipLevels; i++)
                {
                    mipSet.m_pMipLevelTable[i] = &dummy[i];
                }
                CMP_MipLevel* mipLevel = mipSet.m_pMipLevelTable[0];
                mipLevel->m_nWidth = width;
                mipLevel->m_nHeight = height;
                mipLevel->m_dwLinearSize = mImageDataSize;
                mipLevel->m_pbData = (CMP_BYTE*)malloc(mImageDataSize);
                memcpy(mipLevel->m_pbData, data, mImageDataSize);

                CMP_INT result = CMP_GenerateMIPLevels(&mipSet, 1);
                if (result != CMP_OK)
                {
                    assert_invariant(false);
                }

                

                delete mImageData;
                mImageInfo.format = PF_BC7_UNORM;
                mImageInfo.num_mipmaps  = maxMipLevels - 1;
                mImageDataSize = calculateSize(mImageInfo);
                mImageData = (unsigned char*)malloc(mImageDataSize);
                

                uint32_t offset = 0;
                for (uint32_t i = 0; i < maxMipLevels; i++)
                {
                    CMP_MipLevel* level = mipSet.m_pMipLevelTable[i];
                    CMP_Texture srcTexture = { 0 };
                    srcTexture.dwSize = sizeof(CMP_Texture);
                    srcTexture.dwWidth = width;
                    srcTexture.dwHeight = height;
                    srcTexture.format = CMP_FORMAT_RGBA_8888;
                    srcTexture.dwDataSize = level->m_dwLinearSize;
                    srcTexture.pData = (CMP_BYTE*)level->m_pbData;

                    CMP_Texture dstTexture = { 0 };
                    dstTexture.dwSize = sizeof(CMP_Texture);
                    dstTexture.dwWidth = width;
                    dstTexture.dwHeight = height;
                    dstTexture.format = CMP_FORMAT_BC7;
                    dstTexture.pData = mImageData + offset;
                    dstTexture.dwDataSize = CMP_CalculateBufferSize(&dstTexture);
                    
                    offset += dstTexture.dwDataSize;

                    CMP_CompressOptions options = { 0 };
                    options.dwSize = sizeof(CMP_CompressOptions);
                    options.nCompressionSpeed = CMP_Speed_Normal;


                    result = CMP_ConvertTexture(&srcTexture, &dstTexture, &options, nullptr);
                    if (result != CMP_OK)
                    {
                        assert_invariant(false);
                    }

                    if(width > 1)width >>= 1;
                    if(height > 1)height >>= 1;
                }

                
                for (uint32_t i = 0; i < maxMipLevels; i++)
                {
                    CMP_MipLevel* level = mipSet.m_pMipLevelTable[i];
                    free(level->m_pbData);
                }
                free(mipSet.m_pMipLevelTable);
            }
        }
        

        return true;
    }

    bool CImage::loadImage(DataStreamPtr& stream)
    {
        const uint8_t* data = (const uint8_t*)stream->getStreamData();
        uint32_t size = stream->getStreamLength();
        return loadImage(data, size, Ogre::ImageType::ImageType_PNG);
    }

    bool CImage::loadImage(const uint8_t* data, uint32_t byteCount, Ogre::ImageType type)
    {
        switch (type)
        {
        case Ogre::ImageType::ImageType_PNG:
        case Ogre::ImageType::ImageType_JPG:
        {
            mImageInfo.face = 1;
            uint32_t nrComponents = 0;
            auto imagedata = stbi_load_from_memory(data, byteCount,
                (int*)&mImageInfo.width, (int*)&mImageInfo.height, (int*)&nrComponents, 0);

            if (nullptr == imagedata)
            {
                return false;
            }

            mPixelSize = nrComponents;
            if (nrComponents == 3)
            {
                mImageInfo.format = Ogre::PF_BYTE_RGB;
            }
            else if (nrComponents == 4)
            {
                mImageInfo.format = Ogre::PF_BYTE_RGBA;
            }
            else if (nrComponents == 2)
            {
                mImageInfo.format = Ogre::PF_BYTE_LA;
            }
            else if (nrComponents == 1)
            {
                mImageInfo.format = Ogre::PF_L8;
            }

            // mNumMipmaps = 0;
            mImageData = (unsigned char*)imagedata;

            mImageDataSize = calculateSize(mImageInfo);

            return true;
        }
        case Ogre::ImageType::ImageType_DDS:
        {
            DDSImage ddsload;
            MemoryDataStream sm((const char*)data, byteCount);
            if (ddsload.load(&sm))
            {
                data = ddsload.data();

                ImageInfo* imageData = ddsload.getImageInfo();

                mImageInfo = *imageData;

                mImageData = (unsigned char*)data;

                mImageDataSize = calculateSize(mImageInfo);
            }
            return true;
        }
        default:
            assert_invariant(false);
            return false;
        }
        
    }

    bool CImage::loadRawData(DataStreamPtr& stream, ushort uWidth, ushort uHeight, PixelFormat format)
    {
        const char* data = stream->getStreamData();
        uint32_t size = stream->getStreamLength();

        mImageData = (unsigned char*)malloc(size);
        memcpy(mImageData, data, size);
        mImageInfo.format = format;

        mImageInfo.width = uWidth;
        mImageInfo.height = uHeight;
        mImageInfo.depth = 1;
        mImageInfo.num_mipmaps = 1;

        return true;
    }

    int CImage::getWidth() const
    {
        return mImageInfo.width;
    }

    int CImage::getHeight() const
    {
        return mImageInfo.height;
    }

    Ogre::PixelFormat CImage::getFormat() const
    {
        return mImageInfo.format;
    }

    int CImage::getDepth() const
    {
        return mImageInfo.depth;
    }

    int CImage::getNumFaces() const
    {
        return mImageInfo.face;
    }

    int CImage::getNumMipmaps() const
    {
        return mImageInfo.num_mipmaps;
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
        uint32 width = mImageInfo.width, height = mImageInfo.height, depth = mImageInfo.depth;
        uint32 numMips = mImageInfo.num_mipmaps;

        size_t fullFaceSize = 0;
        size_t finalFaceSize = 0;
        uint32 finalWidth = 0, finalHeight = 0, finalDepth = 0;
        for (uint32 mip = 0; mip <= numMips; ++mip)
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
        assert_invariant(mImageData);
        assert_invariant(x < mImageInfo.width&& y < mImageInfo.height&& z < mImageInfo.depth);
        return mImageData + mPixelSize * (z * mImageInfo.width * mImageInfo.height + mImageInfo.width * y + x);
    }

    void CImage::convertRawData(void* from, void* to, size_t _size, int _format)
    {

    }

    void CImage::CImage::freeMemory()
    {
    }

    Ogre::ColourValue CImage::getColourAt(uint32 x, uint32 y, uint32 z) const
    {
        Ogre::ColourValue rval;
        Ogre::PixelUtil::unpackColour(&rval, mImageInfo.format, getData(x, y, z));
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
        mImageInfo.width = width;
        mImageInfo.height = height;
        mImageInfo.depth = depth;
        mImageInfo.format = format;
        mPixelSize = static_cast<uchar>(PixelUtil::getNumElemBytes(format));
        mImageInfo.num_mipmaps = numMipMaps;
        mFlags = 0;
        // Set flags
        if (PixelUtil::isCompressed(format))
            mFlags |= IF_COMPRESSED;
        if (mImageInfo.depth != 1)
            mFlags |= IF_3D_TEXTURE;
        if (mImageInfo.face == 6)
            mFlags |= IF_CUBEMAP;
        OgreAssert(numFaces == 6 || numFaces == 1, "Invalid number of faces");

        mImageDataSize = calculateSize(mImageInfo);
        mImageData = data;
        mAutoDelete = autoDelete;

        return *this;
    }

    //-----------------------------------------------------------------------------
    size_t CImage::calculateSize(
        Ogre::ImageInfo& info)
    {
        size_t size = 0;
        auto width = info.width;
        auto height = info.height;
        auto depth = info.depth;
        for (uint32 mip = 0; mip <= info.num_mipmaps; ++mip)
        {
            size += PixelUtil::getMemorySize(width, height, info.depth, info.format) * info.face;
            if (width != 1) width /= 2;
            if (height != 1) height /= 2;
            if (depth != 1) depth /= 2;
        }
        return size;
    }

    size_t CImage::calculateFaceSize(Ogre::ImageInfo& info)
    {
        return PixelUtil::getMemorySize(info.width, info.height, info.depth, info.format);
    }

    void CImage::save(const String& filename)
    {

    }
}