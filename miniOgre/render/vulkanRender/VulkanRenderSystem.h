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
    virtual void beginRenderPass(RenderPassInfo& renderPassInfo) override;
    virtual void endRenderPass(RenderPassInfo& renderPassInfo) override;
    virtual void bindPipeline(
        Handle<HwProgram> programHandle,
        Handle<HwPipeline> pipelineHandle,
        Handle<HwDescriptorSet>* descSets,
        uint32_t setCount) override;
    virtual void draw(uint32_t vertexCount, uint32_t firstVertex) override;
    virtual void drawIndexed(
        uint32_t indexCount,
        uint32_t instanceCount,
        uint32_t firstIndex,
        uint32_t vertexOffset,
        uint32_t firstInstance);
    virtual void drawIndexedIndirect(
        Handle<HwBufferObject> drawBuffer,
        uint32_t offset,
        uint32_t drawCount,
        uint32_t stride
    );
    virtual void beginComputePass(
        ComputePassInfo& computePassInfo) override;
    virtual void endComputePass() override;

    virtual void present() override;

    /// 
private:
    
    VkPipeline mLastPipeline;
};