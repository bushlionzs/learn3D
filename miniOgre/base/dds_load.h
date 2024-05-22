#pragma once

#include "OgrePixelFormat.h"


class DDSImage
{
public:
    DDSImage();
    ~DDSImage();

    static bool load_simple_info(
        const char* data,
        uint32_t size,
        ImageInfo& info);
    bool load(DataStream* stream);

    unsigned char* data()
    {
        return (unsigned char*)mDDSData;
    }

    
    ImageInfo* getImageInfo()
    {
        return mImageData;
    }
private:
    ImageInfo* mImageData;

    char* mDDSData;
};