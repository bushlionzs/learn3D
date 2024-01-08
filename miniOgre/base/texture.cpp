#include "OgreHeader.h"
#include "texture.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreBitwise.h"

namespace Ogre {
	ITexture::ITexture(const String& name, TextureProperty* texProperty)
	{
		mName = name;
		if (texProperty)
		{
			mTextureProperty = *texProperty;
		}

		mUsage = mTextureProperty._tex_usage;
		mFormat = mTextureProperty._tex_format;

		mFace = 1;

		mNumMipmaps = 100;
	}

	ITexture::~ITexture()
	{

	}

	TextureType ITexture::getTextureType()
	{
		return mTextureProperty._texType;
	}

	const HardwarePixelBufferPtr& ITexture::getBuffer(size_t face, size_t mipmap)
	{
		size_t idx = face * (mTextureProperty._numMipmaps + 1) + mipmap;
		assert(idx < mSurfaceList.size());
		return mSurfaceList[idx];
	}

	void ITexture::createInternalResources()
	{
		if (mInternalResourcesCreated)
			return;
		createInternalResourcesImpl();
		mInternalResourcesCreated = true;
	}

	void ITexture::freeInternalResources(void)
	{
		if (mInternalResourcesCreated)
		{
			mSurfaceList.clear();
			freeInternalResourcesImpl();
			mInternalResourcesCreated = false;
		}
	}

	void ITexture::preLoad()
	{
		
	}

	void ITexture::postLoad()
	{

	}

	void ITexture::loadImpl()
	{
		if ((mUsage & TU_RENDERTARGET) || mUsage == TU_DYNAMIC_WRITE_ONLY)
		{
			mFormat = mTextureProperty._tex_format;
			createInternalResources();
			return;
		}

		


		bool cube = isCubeTexture();
		if (cube)
		{
			mFace = 6;
		}


		std::vector<std::string> names;
		std::vector<CImage> images;
		names.reserve(mFace);

		if (cube)
		{
			std::string suffix = getSuffix(mName);
			if (ResourceManager::getSingletonPtr()->hasResource(mName, BLANKSTRING))
			{
				names.push_back(mName);
				images.emplace_back();
			}
			else
			{
				std::string basename = removeSuffix(mName);
				std::string currname;
				const char* CUBEMAP_SUFFIXES[] = { "_rt", "_lf", "_up", "_dn", "_fr", "_bk" };
				const char* CUBEMAP_SUFFIXES_ALT[] = { "_px", "_nx", "_py", "_ny", "_pz", "_nz" };
				for (int32_t i = 0; i < 6; i++)
				{
					currname = basename + CUBEMAP_SUFFIXES[i] + suffix;
					if (ResourceManager::getSingletonPtr()->hasResource(currname, BLANKSTRING))
					{
						names.push_back(currname);
					}
					else
					{
						currname = basename + CUBEMAP_SUFFIXES_ALT[i] + suffix;
						names.push_back(currname);
					}
				}
			}

		}
		else
		{
			names.push_back(mName);
		}

		images.resize(names.size());

		bool b = true;
		for (int32_t i = 0; i < names.size(); i++)
		{
			if (!images[i].loadImage(names[i]))
			{
				b = false;
			}
		}

		if (!b)
		{
			return;
		}

		std::vector<const CImage*> imagePtrs;
		imagePtrs.resize(images.size());

		for (int32_t i = 0; i < images.size(); i++)
		{
			imagePtrs[i] = &images[i];
		}
		_loadImages(imagePtrs);
	}

	bool ITexture::load()
	{
		if (mLoad)
			return true;
		preLoad();
		loadImpl();
		postLoad();
		mLoad = true;
		return true;
	}

	uint32 ITexture::getMaxMipmaps() const
	{
		// see ARB_texture_non_power_of_two
		return Bitwise::mostSignificantBitSet(
			std::max(mTextureProperty._width, 
				std::max(mTextureProperty._height, mTextureProperty._depth)));
	}

	void ITexture::loadImage(const CImage& img)
	{
		_loadImages({ &img });
	}

	void ITexture::_loadImages(const std::vector<const CImage*>& images)
	{
		mSrcWidth = images[0]->getWidth();
		mSrcHeight = images[0]->getHeight();
		mSrcDepth = images[0]->getDepth();
		mSrcFormat = images[0]->getFormat();

		mTextureProperty._width = mSrcWidth;
		mTextureProperty._height = mSrcHeight;
		mTextureProperty._depth = mSrcDepth;
		mTextureProperty._tex_format = mSrcFormat;
		mTextureProperty._numMipmaps = images[0]->getNumMipmaps();
		mNumMipmaps = mTextureProperty._numMipmaps;

		if (PixelUtil::isCompressed(mSrcFormat) && mNumMipmaps > 0)
		{
			mNumMipmaps = std::max((uint32_t)1, mNumMipmaps);
			mTextureProperty._numMipmaps = mNumMipmaps;
		}

		mFormat = PixelUtil::getFormatForBitDepths(mSrcFormat, 0, 0);
		mFace = 1;
		if (isCubeTexture())
		{
			mFace = 6;
		}
		createInternalResources();


		uint32 faces;
		bool multiImage; // Load from multiple images?
		if (images.size() > 1)
		{
			faces = uint32(images.size());
			multiImage = true;
		}
		else
		{
			faces = images[0]->getNumFaces();
			multiImage = false;
		}

		
		int32_t mip = 0;
		int32_t depth = 1;
		for (uint32 mip = 0; mip <= std::min(mNumMipmaps, mTextureProperty._numMipmaps); ++mip)
		{
			for (uint32 i = 0; i < mFace; ++i)
			{
				PixelBox src;
				size_t face = (depth == 1) ? i : 0; // depth = 1, then cubemap face else 3d/ array layer

				auto buffer = getBuffer(face, mip);
				Box dst(0, 0, 0, buffer->getWidth(), buffer->getHeight(), buffer->getDepth());

				if (multiImage)
				{
					// Load from multiple images
					src = images[i]->getPixelBox(0, mip);
					// set dst layer
					if (depth > 1)
					{
						dst.front = i;
						dst.back = i + 1;
					}
				}
				else
				{
					// Load from faces of images[0]
					src = images[0]->getPixelBox(i, mip);
				}

				if (mTextureProperty._gamma != 1.0f) {
					assert(false);
					//// Apply gamma correction
					//// Do not overwrite original image but do gamma correction in temporary buffer
					//Image tmp(src.format, src.getWidth(), getHeight(), src.getDepth());
					//PixelBox corrected = tmp.getPixelBox();
					//PixelUtil::bulkPixelConversion(src, corrected);

					//Image::applyGamma(corrected.data, mGamma, tmp.getSize(), tmp.getBPP());

					//// Destination: entire texture. blitFromMemory does the scaling to
					//// a power of two for us when needed
					//buffer->blitFromMemory(corrected, dst);
				}
				else
				{
					// Destination: entire texture. blitFromMemory does the scaling to
					// a power of two for us when needed
					buffer->blitFromMemory(src, dst);
				}
			}
		}
	}

	void ITexture::unload()
	{
		assert(false);
	}

	void ITexture::loadRawData(DataStreamPtr& stream, ushort uWidth, ushort uHeight, PixelFormat format)
	{
		CImage img;
		img.loadRawData(stream, uWidth, uHeight, format);
		loadImage(img);
	}
}