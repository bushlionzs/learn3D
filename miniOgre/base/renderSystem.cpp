#include "OgreHeader.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreRenderTarget.h"
#include "OgreViewport.h"


RenderSystem::RenderSystem()
{
    
}

RenderSystem::~RenderSystem()
{

}

bool RenderSystem::engineInit()
{

    return true;
}

OgreTexture* RenderSystem::createTextureFromFile(
    const std::string& name,
    Ogre::TextureProperty* texProperty)
{
    return nullptr;
}

Ogre::RenderTarget* RenderSystem::createRenderTarget(
    const String& name, uint32_t width, uint32_t height, Ogre::PixelFormat format, Ogre::TextureUsage usage)
{
    return nullptr;
}

Viewport* RenderSystem::_getViewport()
{
    return nullptr;
    return mViewport;
}

void RenderSystem::_setViewport(ICamera* cam, Viewport* vp)
{

}

void RenderSystem::beginRenderPass(RenderPassInfo& renderPassInfo)
{

}

void RenderSystem::endRenderPass()
{

}

void RenderSystem::present()
{

}

void RenderSystem::clearFrameBuffer(uint32 buffers, 
    const ColourValue& colour,
    float depth, uint16 stencil)
{

}

void RenderSystem::_updateAllRenderTargets(bool swapBuffers)
{
   
}

void RenderSystem::_swapAllRenderTargetBuffers()
{
    
}


