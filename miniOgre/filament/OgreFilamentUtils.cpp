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

	filament::VertexAttribute mappingOgreVertexAttribute(VertexElementSemantic semantic)
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
			return filament::VertexAttribute::UV0;
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
		default:
			assert(false);
			return filament::backend::TextureFormat::RGBA8;
		}
	}
}