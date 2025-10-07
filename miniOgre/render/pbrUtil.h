#pragma once
#include "OgreCommon.h"
#include "OgrePixelFormat.h"

namespace Ogre
{
    Ogre::RenderTarget* generateCubeMap(
        filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
        const std::string& name,
        Ogre::OgreTexture* environmentCube,
        Ogre::PixelFormat format,
        int32_t dim,
        CubeType type);
   Ogre::RenderTarget* generateBRDFLUT(
       filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
       const std::string& name);
}