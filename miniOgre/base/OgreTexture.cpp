#include "OgreHeader.h"
#include "OgreTexture.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreBitwise.h"

namespace Ogre {
	TextureProperty::TextureProperty()
	{
		_texType = TEX_TYPE_2D;
		_pbrType = TextureTypePbr_general;
		_width = 0;
		_height = 0;
		_depth = 1;
		_numMipmaps = 0;
		_tex_format = Ogre::PF_R8G8B8A8;
		_need_mipmap = true;
		_gamma = 1.0f;
		_fsaa = 0;
		_tex_usage = TU_DEFAULT;
		_backgroudColor = ColourValue::Black;
		_tex_addr_mod = Ogre::TAM_WRAP;
		_samplerParams.filterMag = filament::backend::SamplerFilterType::LINEAR;
		_samplerParams.filterMin = filament::backend::SamplerFilterType::LINEAR;
		_samplerParams.mipMapMode = backend::SamplerMipMapMode::MIPMAP_MODE_NEAREST;
		_samplerParams.wrapS = filament::backend::SamplerWrapMode::REPEAT;
		_samplerParams.wrapT = filament::backend::SamplerWrapMode::REPEAT;
		_samplerParams.wrapR = filament::backend::SamplerWrapMode::REPEAT;
		_samplerParams.compareMode = filament::backend::SamplerCompareMode::NONE;
		_samplerParams.compareFunc = filament::backend::SamplerCompareFunc::N;
		_samplerParams.anisotropyLog2 = 0;
		_samplerParams.padding1 = 0;
		_samplerParams.padding2 = 0;
	}

	bool TextureProperty::isRenderTarget()
	{
		if (_tex_usage & Ogre::TextureUsage::COLOR_ATTACHMENT)
		{
			return true;
		}
		if (_tex_usage & Ogre::TextureUsage::DEPTH_ATTACHMENT)
		{
			return true;
		}
		return false;
	}

	OgreTexture::OgreTexture(const String& name, TextureProperty* texProperty)
	{
		mName = name;
		if (texProperty)
		{
			mTextureProperty = *texProperty;
		}

		mUsage = mTextureProperty._tex_usage;
		mFormat = mTextureProperty._tex_format;

		mFace = 1;

		mNumMipmaps = 1;
	}

	OgreTexture::~OgreTexture()
	{

	}

	TextureType OgreTexture::getTextureType()
	{
		return mTextureProperty._texType;
	}

	const HardwarePixelBufferPtr& OgreTexture::getBuffer(size_t face, size_t mipmap)
	{
		size_t idx = face * (mTextureProperty._numMipmaps + 1) + mipmap;
		assert(idx < mSurfaceList.size());
		return mSurfaceList[idx];
	}

	void OgreTexture::createInternalResources()
	{
		if (mInternalResourcesCreated)
			return;
		createInternalResourcesImpl();
		mInternalResourcesCreated = true;
	}

	void OgreTexture::freeInternalResources(void)
	{
		if (mInternalResourcesCreated)
		{
			mSurfaceList.clear();
			freeInternalResourcesImpl();
			mInternalResourcesCreated = false;
		}
	}

	void OgreTexture::preLoad()
	{
		
	}

	void OgreTexture::postLoad()
	{

	}

	void OgreTexture::loadImpl()
	{
		bool cube = isCubeTexture();
		if (cube)
		{
			mFace = 6;
		}

		if (mTextureProperty.isRenderTarget())
		{
			mFormat = mTextureProperty._tex_format;
			createInternalResources();
			return;
		}

		


		


		CImage image;

		image.loadImage(mName, cube);


		/*if (cube)
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
		}*/

		_loadImages({&image});
	}

	bool OgreTexture::load(utils::JobSystem::Job* job)
	{
		if (mLoad)
			return true;
		preLoad();
		loadImpl();
		postLoad();
		mLoad = true;
		return true;
	}

	uint32 OgreTexture::getMaxMipmaps() const
	{
		// see ARB_texture_non_power_of_two
		return Bitwise::mostSignificantBitSet(
			std::max(mTextureProperty._width, 
				std::max(mTextureProperty._height, mTextureProperty._depth)));
	}

	void OgreTexture::loadImage(const CImage& img)
	{
		_loadImages({ &img });
	}

	void OgreTexture::_loadImages(const std::vector<const CImage*>& images)
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

	void OgreTexture::unload()
	{
		assert(false);
	}

	void OgreTexture::loadRawData(DataStreamPtr& stream, ushort uWidth, ushort uHeight, PixelFormat format)
	{
		CImage img;
		img.loadRawData(stream, uWidth, uHeight, format);
		loadImage(img);
	}
}