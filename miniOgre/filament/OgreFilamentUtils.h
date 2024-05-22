#pragma once
#include <filament/DriverEnums.h>
#include <filament/MaterialEnums.h>
#include <OgreHardwareVertexBuffer.h>
namespace filament {


	backend::ElementType mappingOgreVertexType(VertexElementType type);

	filament::VertexAttribute mappingOgreVertexAttribute(VertexElementSemantic semantic);
}