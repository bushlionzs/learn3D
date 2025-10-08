#include "OgreHeader.h"
#include "OgreTexture.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreResourceBackgroundQueue.h"
#include "OgreBitwise.h"

namespace Ogre {
	TextureProperty::TextureProperty()
	{
		_texType = TEX_TYPE_2D;
		_pbrType = TextureTypePbr_general;
		_width = 0;
		_height = 0;
		_depth = 1;
		_face = 1;
		_numMipmaps = 0;
		_tex_format = Ogre::PF_R8G8B8A8;
		_need_mipmap = true;
		_maxMipLevel = INT_MAX;
		_gamma = 1.0f;
		_fsaa = 0;
		_tex_usage = TEXTURE_USAGE_CAN_COPY_FROM_BIT | TEXTURE_USAGE_CAN_COPY_TO_BIT;
		_backgroudColor = ColourValue::Black;
		_tex_addr_mod = Ogre::TAM_WRAP;
		_samplerParams.filterMag = filament::backend::SamplerFilterType::LINEAR;
		_samplerParams.filterMin = filament::backend::SamplerFilterType::LINEAR;
		_samplerParams.mipMapMode = backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
		_samplerParams.wrapS = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
		_samplerParams.wrapT = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
		_samplerParams.wrapR = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
		_samplerParams.compareMode = filament::backend::SamplerCompareMode::NONE;
		_samplerParams.compareFunc = filament::backend::SamplerCompareFunc::COMPARE_OP_NEVER;
		_samplerParams.anisotropyLog2 = 0;
		_samplerParams.useComparison = 0;
		_samplerParams.maxLod = 0;
		_samplerParams.padding2 = 0;
	}

	bool TextureProperty::isRenderTarget()
	{
		if (_tex_usage.has_flag(TEXTURE_USAGE_COLOR_ATTACHMENT_BIT))
		{
			return true;
		}
		if (_tex_usage.has_flag(TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT))
		{
			return true;
		}

		return false;
	}

	bool TextureProperty::haveImageFile()
	{
		if (_tex_usage.has_flag(TEXTURE_USAGE_COLOR_ATTACHMENT_BIT))
		{
			return false;
		}
		if (_tex_usage.has_flag(TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT))
		{
			return false;
		}

		if (_tex_usage.has_flag(TEXTURE_USAGE_CAN_UPDATE_BIT))
		{
			return false;
		}

		return true;
	}


	void TextureProperty::gltfSampler()
	{
		_samplerParams.filterMag = filament::backend::SamplerFilterType::LINEAR;
		_samplerParams.filterMin = filament::backend::SamplerFilterType::LINEAR;
		_samplerParams.mipMapMode = backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
		_samplerParams.wrapS = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
		_samplerParams.wrapT = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
		_samplerParams.wrapR = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
		_samplerParams.compareMode = filament::backend::SamplerCompareMode::NONE;
		_samplerParams.compareFunc = filament::backend::SamplerCompareFunc::COMPARE_OP_NEVER;
		_samplerParams.anisotropyLog2 = 3;
		_samplerParams.useComparison = 0;
		_samplerParams.maxLod = 0;
		_samplerParams.padding2 = 0;
	}

	OgreTexture::OgreTexture(const String& name, TextureProperty* texProperty)
	{
		mName = name;
		if (texProperty)
		{
			mTextureProperty = *texProperty;
			
		}
		mResourceType = ResourceType_Texture;
	}

	OgreTexture::~OgreTexture()
	{

	}

	TextureType OgreTexture::getTextureType()
	{
		return mTextureProperty._texType;
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
			freeInternalResourcesImpl();
			mInternalResourcesCreated = false;
		}
	}

	void OgreTexture::loadImpl()
	{
		if (!mTextureProperty.haveImageFile())
		{
			createInternalResources();
			return;
		}

		CImage image;
		image.loadImage(mName);
		_loadImages({&image});

		mLoadingState = LOADSTATE_LOADED;
	}

	void OgreTexture::unloadImpl(void)
	{

	}

	bool OgreTexture::isLoaded()
	{
		auto old = mLoadingState.load();
		return old == LOADSTATE_LOADED;
	}

	bool OgreTexture::loadAsync()
	{
		auto old = mLoadingState.load();
		if (old == LOADSTATE_LOADING ||
			old == LOADSTATE_LOADED)
		{
			return false;
		}

		mLoadingState.store(LOADSTATE_LOADING);

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
		mTextureProperty._width = images[0]->getWidth();
		mTextureProperty._height = images[0]->getHeight();
		mTextureProperty._depth = images[0]->getDepth();
		mTextureProperty._tex_format = images[0]->getFormat();
		mTextureProperty._numMipmaps = images[0]->getNumMipmaps();
	
		createInternalResources();

		updateTexture(images);
	}

	void OgreTexture::uploadTextureData(const char* data, uint32_t size, TextureProperty& tp)
	{
		assert_invariant(false);
	}

	void OgreTexture::loadRawData(DataStreamPtr& stream, ushort uWidth, ushort uHeight, PixelFormat format)
	{
		CImage img;
		img.loadRawData(*stream.get(), uWidth, uHeight, format);
		loadImage(img);
	}

	uint32_t OgreTexture::getDataOffset(uint32_t face, uint32_t mip)
	{
		size_t idx = face * (mTextureProperty._numMipmaps + 1) + mip;
		assert_invariant(idx < mOffsetList.size());
		return mOffsetList[idx];
	}
}