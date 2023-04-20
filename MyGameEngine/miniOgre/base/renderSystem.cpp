#include "OgreHeader.h"
#include "renderSystem.h"
#include "VulkanRenderSystem.h"
#include "dx12RenderSystem.h"
#include "dx11RenderSystem.h"
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
    Ogre::Root::getSingletonPtr()->_initialise();

    return true;
}

ITexture* RenderSystem::createTextureFromFile(
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

void RenderSystem::_setViewport(Viewport* vp)
{
    mViewport = vp;
    RenderTarget* target;
    target = vp->getTarget();

    mActiveRenderTarget = target;


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


