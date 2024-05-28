#include <OgreHeader.h>

#include "OgreFilamentUtils.h"

namespace filament {

	backend::ElementType mappingOgreVertexType(VertexElementType type)
	{
		switch (type)
		{
		case VET_FLOAT3:
			return backend::ElementType::FLOAT3;
		case VET_FLOAT2:
			return backend::ElementType::FLOAT2;
		case VET_FLOAT4:
			return backend::ElementType::FLOAT4;
		case VET_UINT4:
			return backend::ElementType::UINT4;
		case VET_UBYTE4_NORM:
			return backend::ElementType::UBYTE4;
			break;
		}

		assert(false);
		return backend::ElementType::FLOAT3;
	}

	filament::VertexAttribute mappingOgreVertexAttribute(VertexElementSemantic semantic, uint32_t index)
	{
		switch (semantic)
		{
		case VES_POSITION:
			return filament::VertexAttribute::POSITION;
		case VES_NORMAL:
			return filament::VertexAttribute::TANGENTS;
		case VES_COLOUR:
			return filament::VertexAttribute::COLOR;
		case VES_TEXTURE_COORDINATES:
		{
			if (index == 0)
			{
				return filament::VertexAttribute::UV0;
			}
			else if (index == 1)
			{
				return filament::VertexAttribute::UV1;
			}
			else
			{
				return filament::VertexAttribute::CUSTOM0;
			}
		}
			
		case VES_BLEND_WEIGHTS:
			return filament::VertexAttribute::BONE_WEIGHTS;
		case VES_BLEND_INDICES:
			return filament::VertexAttribute::BONE_INDICES;
		}

		assert(false);
		return filament::VertexAttribute::POSITION;
	}

	backend::TextureFormat mappingOgreTextureFormat(Ogre::PixelFormat format)
	{
		switch (format)
		{
		case Ogre::PF_BYTE_RGBA:
			return filament::backend::TextureFormat::RGBA8;
		case Ogre::PF_DXT1:
			return filament::backend::TextureFormat::DXT1_RGBA;
		case Ogre::PF_DXT3:
			return filament::backend::TextureFormat::DXT3_RGBA;
		case Ogre::PF_DXT5:
			return filament::backend::TextureFormat::DXT5_RGBA;
		case Ogre::PF_BYTE_LA:
			return filament::backend::TextureFormat::BYTE_LA;
		case Ogre::PF_L8:
			return filament::backend::TextureFormat::R8;
		case Ogre::PF_BYTE_RGB:
			return filament::backend::TextureFormat::RGB8;
		case Ogre::PF_A8R8G8B8:
			return filament::backend::TextureFormat::RGBA8;
		default:
			assert(false);
			return filament::backend::TextureFormat::RGBA8;
		}
	}
	backend::BlendFunction mappingOgreBlendFactor(Ogre::SceneBlendFactor factor, bool forAlpha)
	{
		switch (factor)
		{
		case SBF_ONE:
			return backend::BlendFunction::ONE;
		case SBF_ZERO:
			return backend::BlendFunction::ZERO;
		case SBF_DEST_COLOUR:
			return forAlpha ? backend::BlendFunction::DST_ALPHA : backend::BlendFunction::DST_COLOR;
		case SBF_SOURCE_COLOUR:
			return forAlpha ? backend::BlendFunction::SRC_ALPHA : backend::BlendFunction::SRC_COLOR;
		case SBF_ONE_MINUS_DEST_COLOUR:
			return forAlpha ? backend::BlendFunction::ONE_MINUS_DST_ALPHA : backend::BlendFunction::ONE_MINUS_DST_COLOR;
		case SBF_ONE_MINUS_SOURCE_COLOUR:
			return forAlpha ? backend::BlendFunction::ONE_MINUS_SRC_ALPHA : backend::BlendFunction::ONE_MINUS_SRC_COLOR;
		case SBF_DEST_ALPHA:
			return backend::BlendFunction::DST_ALPHA;
		case SBF_SOURCE_ALPHA:
			return backend::BlendFunction::SRC_ALPHA;
		case SBF_ONE_MINUS_DEST_ALPHA:
			return backend::BlendFunction::ONE_MINUS_DST_ALPHA;
		case SBF_ONE_MINUS_SOURCE_ALPHA:
			return backend::BlendFunction::ONE_MINUS_SRC_ALPHA;
		}
		return backend::BlendFunction::ONE;
	}

	backend::BlendEquation mappingOgreBlendOperation(Ogre::SceneBlendOperation operation)
	{
		switch (operation)
		{
		case Ogre::SBO_ADD:
			return backend::BlendEquation::ADD;
		case Ogre::SBO_SUBTRACT:
			return backend::BlendEquation::SUBTRACT;
		case Ogre::SBO_REVERSE_SUBTRACT:
			return backend::BlendEquation::REVERSE_SUBTRACT;
		case Ogre::SBO_MIN:
			return backend::BlendEquation::MIN;
		case Ogre::SBO_MAX:
			return backend::BlendEquation::MAX;
		}
		return backend::BlendEquation::ADD;
	}
}