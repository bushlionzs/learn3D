#pragma once
#include "renderSystem.h"
#include "VulkanTexture.h"
#include "VulkanRenderTarget.h"
#include "VulkanUploadbuffer.h"
#include "VulkanRenderSystemBase.h"
#include "enkiTS/TaskScheduler.h"


class VulkanRayTracingContext;



class VulkanRenderSystem : public VulkanRenderSystemBase
{
public:
    VulkanRenderSystem(HWND wnd);
	~VulkanRenderSystem();

    virtual bool engineInit();
    virtual void frameStart();
    virtual void frameEnd();
    virtual void update(Renderable* r);
    virtual void render(Renderable* r, RenderListType t);
    virtual void multiRender(std::vector<Ogre::Renderable*>& objs, bool multithread);

    void beginRenderPass(RenderPassInfo& renderPassInfo);
    void endRenderPass();
    void present();
    virtual void clearFrameBuffer(uint32 buffers,
        const ColourValue& colour,
        float depth, uint16 stencil);
    virtual Ogre::RenderWindow* createRenderWindow(
        const String& name, unsigned int width, unsigned int height,
        const NameValuePairList* miscParams) override;
    virtual Ogre::RenderTarget* createRenderTarget(
        const String& name, uint32_t width, uint32_t height, Ogre::PixelFormat format, Ogre::TextureUsage usage) override;
private:
    enki::TaskScheduler mTaskScheduler;

    utils::JobSystem::Job* mRootJob;

   
};