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

Shader* RenderSystem::createShader(ShaderInfo& sinfo)
{
    return nullptr;
}


Viewport* RenderSystem::_getViewport()
{
    return mViewport;
}

void RenderSystem::_setViewport(ICamera* cam, Viewport* vp)
{

}

void RenderSystem::clearFrameBuffer(uint32 buffers, 
    const ColourValue& colour,
    float depth, uint16 stencil)
{

}

void RenderSystem::attachRenderTarget(RenderTarget& target)
{
    assert(target.getPriority() < OGRE_NUM_RENDERTARGET_GROUPS);

    mRenderTargets.emplace(target.getName(), &target);
    mPrioritisedRenderTargets.emplace(target.getPriority(), &target);
}

void RenderSystem::_updateAllRenderTargets(bool swapBuffers)
{
    for (auto& rt : mPrioritisedRenderTargets)
    {
        if (rt.second->isActive() && rt.second->isAutoUpdated())
            rt.second->update(swapBuffers);
    }
}

void RenderSystem::_swapAllRenderTargetBuffers()
{
    for (auto& rt : mPrioritisedRenderTargets)
    {
        if (rt.second->isActive() && rt.second->isAutoUpdated())
            rt.second->swapBuffers();
    }
}


