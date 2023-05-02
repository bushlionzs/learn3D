#include "OgreHeader.h"
#include "OgreBlp.h"
#include "OgreDataStream.h"
#include "OgrePixelFormat.h"



OgreBlpImage::OgreBlpImage()
{

}

OgreBlpImage::~OgreBlpImage()
{

}

bool OgreBlpImage::load(std::shared_ptr<DataStream>& stream)
{
	BLPHeader header;
	stream->read(&header, sizeof(header));

	mImageData.width = header.resx;
	mImageData.height = header.resy;
	mImageData.face = 1;
	mImageData.depth = 1;
	if (header.attr_0_compression == 1)
	{
		loadFromUncompressedData(&header, stream);
	}
	if (header.attr_0_compression == 2)
	{
		loadFromCompressedData(&header, stream);
	}
	else
	{
		return false;
	}

	return true;
}

extern size_t calculateSize(uint32 mipmaps, uint32 faces, uint32 width, uint32 height, uint32 depth,
	PixelFormat format);
void OgreBlpImage::loadFromCompressedData(BLPHeader const* lHeader, std::shared_ptr<DataStream>& stream)
{
	const PixelFormat alphatypes[] = {
		PF_DXT1,
		PF_DXT3,
		PF_UNKNOWN,
		PF_DXT5 };
	const int blocksizes[] = { 8, 16, 0, 16 };

	int alpha_type = lHeader->attr_2_alphatype & 3;
	mImageData.format = alphatypes[alpha_type];

	int width = mImageData.width, height = mImageData.height;
	mImageData.num_mipmaps = -1;
	for (int i = 0; i < 16; i++)
	{
		if (lHeader->sizes[i] <= 0 || lHeader->offsets[i] <= 0)
		{
			break;
		}

		int size = std::floor((width + 3) / 4) * std::floor((height + 3) / 4) * blocksizes[alpha_type];

		if (size < lHeader->sizes[i])
		{
			break;
		}
		mImageData.num_mipmaps++;
	}

	if (mImageData.num_mipmaps < 0)
	{
		return;
	}

	mImageData.size = calculateSize(mImageData.num_mipmaps, mImageData.face,
		mImageData.width, mImageData.height, mImageData.depth, mImageData.format);
	mBlpData = new char[mImageData.size];
	uint32_t offset = 0;
	char const* lData = stream->getStreamData();
	for (int i = 0; i <= mImageData.num_mipmaps; i++)
	{
		char const* start = lData + lHeader->offsets[i];
		std::copy(start, start + lHeader->sizes[i], mBlpData + offset);

		offset += lHeader->sizes[i];
		width = std::max(width >> 1, 1);
		height = std::max(height >> 1, 1);
	}
}

void OgreBlpImage::loadFromUncompressedData(
	BLPHeader const* lHeader, std::shared_ptr<DataStream>& stream)
{
	

	int alphabits = lHeader->attr_1_alphadepth;
	bool hasalpha = alphabits != 0;
	
	mImageData.format = PF_BYTE_RGBA;


	int width = mImageData.width, height = mImageData.height;
	mImageData.num_mipmaps = -1;
	for (int i = 0; i < 16; i++)
	{
		if (lHeader->sizes[i] <= 0 || lHeader->offsets[i] <= 0)
		{
			break;
		}

		mImageData.num_mipmaps++;
	}

	if (mImageData.num_mipmaps < 0)
	{
		return;
	}

	mImageData.size = calculateSize(mImageData.num_mipmaps, mImageData.face,
		mImageData.width, mImageData.height, mImageData.depth, mImageData.format);
	mBlpData = new char[mImageData.size];

	char const* lData = stream->getStreamData();

	unsigned int const* pal = reinterpret_cast<unsigned int const*>(stream->getStreamData() + sizeof(BLPHeader));
	uint32_t streamLength = stream->getStreamLength();
	uint32_t offset = 0;
	unsigned char const* buf;
	unsigned int* p;
	unsigned char const* c;
	unsigned char const* a;
	for (int i = 0; i <= mImageData.num_mipmaps; ++i)
	{
		p = (unsigned int*)(mBlpData + offset);
		buf = (unsigned char const*)(lData + lHeader->offsets[i]);
		c = buf;
		a = buf + width * height;
		int alpha = 0;
		int cnt = 0;
		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {
				unsigned int k = pal[*c++];

				k = ((k & 0x00FF0000) >> 16) | ((k & 0x0000FF00)) | ((k & 0x000000FF) << 16);

				if (hasalpha) {
					if (alphabits == 8) {
						alpha = (*a++);
					}
					else if (alphabits == 4) {
						alpha = (*a & (0xf << cnt++)) * 0x11;
						if (cnt == 2) {
							cnt = 0;
							a++;
						}
					}
					else if (alphabits == 1) {
						//alpha = (*a & (128 >> cnt++)) ? 0xff : 0;
						alpha = (*a & (1 << cnt++)) ? 0xff : 0;
						if (cnt == 8) {
							cnt = 0;
							a++;
						}
					}
				}
				else alpha = 0xff;

				k |= alpha << 24;
				*p++ = k;
			}
		}

		offset += width * height * 4;

		width = std::max(width >> 1, 1);
		height = std::max(height >> 1, 1);
	}
}