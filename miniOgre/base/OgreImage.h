#pragma once
#include "OgrePixelFormat.h"
//#include <filament/DriverEnums.h>
namespace Ogre {
	enum ImageFlags
	{
		IF_COMPRESSED = 0x00000001,
		IF_CUBEMAP = 0x00000002,
		IF_3D_TEXTURE = 0x00000004
	};

	class  ImageInfo
	{
	public:
		ImageInfo() :
			height(0), width(0), depth(1), size(0), face(1),
			num_mipmaps(0), flags(0), format(PF_UNKNOWN)
		{
		}
		uint32_t height;
		uint32_t width;
		uint32_t depth;
		uint32_t face;
		size_t size;
		uint32_t nrComponents;
		int32_t num_mipmaps;
		uint32_t flags;
		char* imageData;
		PixelFormat format;
	};
	class CImage
	{
	public:
		CImage();
		virtual ~CImage();
		static Ogre::ImageType getImageType(const std::string& name);
		static bool loadImageInfo(
			const uint8_t* data, 
			uint32_t byteCount, 
			ImageInfo& imageInfo,
			Ogre::ImageType type);
		/*static bool loadImageInfo(
			const std::string& name,
			ImageInfo& imageInfo,
			bool cube);*/
		static void freeImageData(void* data);
		bool loadImage(const std::string& name);
		bool loadImage(const uint8_t* data, uint32_t byteCount, Ogre::ImageType type);
		bool loadImage(DataStream& stream, Ogre::ImageType type);
		bool loadRawData(DataStream& stream, ushort uWidth, ushort uHeight, PixelFormat format);
		unsigned char* getImageData();
		uint32_t getSize();
		uint32_t getRowSpan();
		int getHeight() const;
		int getWidth() const;
		int getDepth() const;
		int getNumFaces() const;
		int getNumMipmaps() const;

		const ImageInfo& getImageInfo()
		{
			return mImageInfo;
		}
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

		static size_t calculateSize(Ogre::ImageInfo& info);
		static size_t calculateFaceSize(Ogre::ImageInfo& info);

		void save(const String& filename);
	private:
		const uchar* getData(uint32 x = 0, uint32 y = 0, uint32 z = 0) const;
		void convertRawData(void* from, void* to, size_t _size, int _format);
		void freeMemory();

		bool loadDDS(DataStream& stream, ImageInfo& imageInfo);
		bool loadSTB(DataStream& stream, ImageInfo& imageInfo);
		bool loadKTX(DataStream& stream, ImageInfo& imageInfo);
		bool loadBLP(DataStream& stream, ImageInfo& imageInfo);
		bool loadTIF(DataStream& stream, ImageInfo& imageInfo);
	private:
		ImageInfo mImageInfo;
		int32_t mFlags;
		char* mImageData;
		uint32_t mPixelSize;
		uint32_t mImageDataSize;
		/// A bool to determine if we delete the buffer or the calling app does
		bool mAutoDelete;
		using LoadPicFunc = std::function< bool(DataStream& stream, ImageInfo& imageInfo)>;
		std::unordered_map<Ogre::ImageType, LoadPicFunc> mLoadPicMap;
	};
}
