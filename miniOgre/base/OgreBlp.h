#pragma once
#include "dds_load.h"

#pragma pack(push,1)
struct BLPHeader
{
	int32_t magix;
	int32_t version;
	uint8_t attr_0_compression;
	uint8_t attr_1_alphadepth;
	uint8_t attr_2_alphatype;
	uint8_t attr_3_mipmaplevels;
	int32_t resx;
	int32_t resy;
	int32_t offsets[16];
	int32_t sizes[16];
};
#pragma pack(pop)
class OgreBlpImage
{
public:
	OgreBlpImage();
	~OgreBlpImage();
	bool load(std::shared_ptr<DataStream>& stream);
	ImageInfo* getImageInfo()
	{
		return &mImageData;
	}

	unsigned char* data()
	{
		return (unsigned char*)mBlpData;
	}
private:
	void loadFromCompressedData(BLPHeader const* lHeader, 
		std::shared_ptr<DataStream>& stream);
	void loadFromUncompressedData(
		BLPHeader const* lHeader, std::shared_ptr<DataStream>& stream);
private:
	ImageInfo mImageData;
	char* mBlpData;
};