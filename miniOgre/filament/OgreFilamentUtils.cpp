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
		}

		assert(false);
		return filament::VertexAttribute::POSITION;
	}
}