#pragma once
#include "OgrePixelFormat.h"

namespace Ogre {
	enum ImageFlags
	{
		IF_COMPRESSED = 0x00000001,
		IF_CUBEMAP = 0x00000002,
		IF_3D_TEXTURE = 0x00000004
	};

	class CImage
	{
	public:
		CImage();
		virtual ~CImage();
		bool loadImage(const std::string& name);
		unsigned char* getImageData();
		uint32_t getSize();
		int getHeight() const;
		int getWidth() const;
		int getDepth() const;
		int getNumFaces() const;
		int getNumMipmaps() const;
		bool hasAlpha();
		Ogre::PixelFormat getFormat() const;
		Ogre::PixelBox getPixelBox(uint32 face = 0, uint32 mipmap = 0) const;
		Ogre::ColourValue getColourAt(uint32 x, uint32 y, uint32 z) const;

		CImage& loadDynamicImage(uchar* data, uint32 width, uint32 height, uint32 depth, PixelFormat format,
			bool autoDelete = false, uint32 numFaces = 1, uint32 numMipMaps = 0);

		/// @overload
		CImage& loadDynamicImage(uchar* data, uint32 width, uint32 height, PixelFormat format)
		{
			return loadDynamicImage(data, width, height, 1, format);
		}

		size_t calculateSize(
			uint32 mipmaps,
			uint32 faces,
			uint32 width,
			uint32 height,
			uint32 depth,
			PixelFormat format);

		void save(const String& filename);
	private:
		const uchar* getData(uint32 x = 0, uint32 y = 0, uint32 z = 0) const;
		void convertRawData(void* from, void* to, size_t _size, int _format);
		void freeMemory();
	private:

		uint32_t mWidth;
		uint32_t mHeight;
		uint32_t mDepth;
		uint32_t mNumMipmaps;
		uint32_t mFace;
		int32_t mFlags;
		Ogre::PixelFormat mFormat;
		unsigned char* mImageData;
		uint32_t mPixelSize;
		uint32_t mImageDataSize;
		/// A bool to determine if we delete the buffer or the calling app does
		bool mAutoDelete;
	};
}
