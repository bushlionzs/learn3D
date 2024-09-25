#pragma once

#include "VulkanRenderSystemBase.h"
#include "enkiTS/TaskScheduler.h"


class VulkanRenderSystem : public VulkanRenderSystemBase
{
public:
    VulkanRenderSystem(HWND wnd);
	~VulkanRenderSystem();

    virtual bool engineInit() override;
    virtual void frameStart() override;
    virtual void frameEnd() override;
    virtual void update(Renderable* r) override;
    virtual void render(Renderable* r, RenderListType t) override;
    virtual void multiRender(
        std::vector<Ogre::Renderable*>& objs, bool multithread) override;

    virtual void beginRenderPass(RenderPassInfo& renderPassInfo) override;
    virtual void endRenderPass() override;
    virtual void present() override;
    virtual Ogre::RenderWindow* createRenderWindow(
        const String& name, unsigned int width, unsigned int height,
        const NameValuePairList* miscParams) override;
    virtual Ogre::RenderTarget* createRenderTarget(
        const String& name, uint32_t width, uint32_t height, 
        Ogre::PixelFormat format, uint32_t textureUsage) override;
private:
    enki::TaskScheduler mTaskScheduler;

    utils::JobSystem::Job* mRootJob;

   
};