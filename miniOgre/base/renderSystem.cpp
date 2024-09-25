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
    const String& name, 
    uint32_t width, 
    uint32_t height, 
    Ogre::PixelFormat format, 
    uint32_t textureUsage)
{
    return nullptr;
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



