#pragma once
#include "OgrePixelFormat.h"
#include <filament/DriverEnums.h>
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
		static backend::ImageType getImageType(const std::string& name);
		static bool loadImageInfo(
			const uint8_t* data, 
			uint32_t byteCount, 
			ImageInfo& imageInfo,
			backend::ImageType type);
		static void freeImageData(void* data);
		bool loadImage(const std::string& name);
		bool loadImage(const uint8_t* data, uint32_t byteCount, backend::ImageType type);
		bool loadImage(DataStreamPtr& stream);
		bool loadRawData(DataStreamPtr& stream, ushort uWidth, ushort uHeight, PixelFormat format);
		unsigned char* getImageData();
		uint32_t getSize();
		uint32_t getRowSpan();
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

		static size_t calculateSize(
			Ogre::ImageInfo& info);

		void save(const String& filename);
	private:
		const uchar* getData(uint32 x = 0, uint32 y = 0, uint32 z = 0) const;
		void convertRawData(void* from, void* to, size_t _size, int _format);
		void freeMemory();
	private:
		ImageInfo mImageInfo;
		int32_t mFlags;
		unsigned char* mImageData;
		uint32_t mPixelSize;
		uint32_t mImageDataSize;
		/// A bool to determine if we delete the buffer or the calling app does
		bool mAutoDelete;
	};
}
