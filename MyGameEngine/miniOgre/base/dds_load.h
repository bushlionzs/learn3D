#pragma once

#include "OgrePixelFormat.h"
class  ImageData
{
public:
    ImageData() :
        height(0), width(0), depth(1), size(0),
        num_mipmaps(0), flags(0), format(PF_UNKNOWN)
    {
    }
    uint32_t height;
    uint32_t width;
    uint32_t depth;
    uint32_t face;
    size_t size;

    uint32_t num_mipmaps;
    uint32_t flags;

    PixelFormat format;
};

class DDSImage
{
public:
    DDSImage();
    ~DDSImage();

    bool load(std::shared_ptr<DataStream>& stream);

    unsigned char* data()
    {
        return (unsigned char*)mDDSData;
    }

    
    ImageData* getImageInfo()
    {
        return mImageData;
    }
private:
    ImageData* mImageData;

    char* mDDSData;
};