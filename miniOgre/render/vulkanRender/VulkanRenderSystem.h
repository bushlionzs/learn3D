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
    virtual void beginComputePass(
        ComputePassInfo& computePassInfo) override;
    virtual void endComputePass() override;

    virtual void present() override;

    /// 
private:
    
   
};