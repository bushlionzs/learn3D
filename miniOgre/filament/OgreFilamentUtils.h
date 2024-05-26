#pragma once
#include <filament/DriverEnums.h>
#include <filament/MaterialEnums.h>
#include <OgreHardwareVertexBuffer.h>
#include <OgrePixelFormat.h>
namespace filament {


	backend::ElementType mappingOgreVertexType(VertexElementType type);

	filament::VertexAttribute mappingOgreVertexAttribute(VertexElementSemantic semantic);

	backend::TextureFormat mappingOgreTextureFormat(Ogre::PixelFormat format);
}