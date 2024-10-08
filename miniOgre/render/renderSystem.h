#pragma once
#include <functional>
#include "shader.h"
#include "engine_struct.h"
#include "OgreTexture.h"
#include <DriverEnums.h>
#include <utils/Allocator.h>
#include <utils/JobSystem.h>
#include <filament/Handle.h>
#include <filament/DriverBase.h>
#include <filament/DescriptorSetOffsetArray.h>
#include <fg/FrameGraphId.h>
#include <fg/FrameGraphTexture.h>
#include <fg/Allocators.h>
#include <fg/ResourceAllocator.h>


class GraphicsCommandList;
class RenderableData;
class VertexDeclaration;

using namespace filament::backend;

namespace Ogre
{
    class RenderWindow;
}

using FrameGraphPassCallback = std::function< FrameGraphId<FrameGraphTexture>(FrameGraph& fg)>;

class RenderSystem
{
public:
    RenderSystem();
    ~RenderSystem();
    virtual bool engineInit();
    virtual void frameStart() = 0;
    virtual void frameEnd() = 0;
    virtual void render(FrameGraphPassCallback cb);
    virtual void update(Renderable* r) {}
    virtual void render(Ogre::Renderable* r, RenderListType t) = 0;
    virtual void multiRender(std::vector<Ogre::Renderable*>& objs, bool multithread = true) {}
    virtual Ogre::OgreTexture* createTextureFromFile(
        const std::string& name,
        Ogre::TextureProperty* texProperty);

    virtual Ogre::RenderWindow* createRenderWindow(
        const String& name, unsigned int width, unsigned int height,
        const NameValuePairList* miscParams) = 0;

    virtual Ogre::RenderTarget* createRenderTarget(
        const String& name, 
        uint32_t width, 
        uint32_t height, 
        Ogre::PixelFormat format, 
        uint32_t textureUsage);


    virtual void ready() {}

    virtual RenderableData* createRenderableData(Ogre::Renderable* r) { return nullptr; }

    virtual const String& getRenderSystemName()
    {
        return mRenderSystemName;
    }

    void incrTriangleCount(uint32_t count)
    {
        mTriangleCount += count;
    }
    uint32_t getTriangleCount()
    {
        return mTriangleCount;
    }

    void incrBatchCount(uint32_t count)
    {
        mBatchCount += count;
    }

    uint32_t getBatchCount()
    {
        return mBatchCount;
    }

    utils::JobSystem& getJobSystem()
    {
        return mJobSystem;
    }

    virtual void beginRenderPass(
        RenderPassInfo& renderPassInfo);
    virtual void endRenderPass();

    virtual void beginComputePass(
        ComputePassInfo& computePassInfo);
    virtual void endComputePass();

    virtual void dispatchComputeShader();
    virtual void present();

    virtual void pushGroupMarker(const char* maker) {}
    virtual void popGroupMarker() {}

    virtual Ogre::OgreTexture* generateCubeMap(
        const std::string& name,
        Ogre::OgreTexture* environmentCube,
        Ogre::PixelFormat format,
        int32_t dim,
        CubeType type)
    {
        return nullptr;
    }

    virtual Ogre::OgreTexture* generateBRDFLUT(const std::string& name)
    {
        return nullptr;
    }

    virtual FrameConstantBuffer* getFrameConstantBuffer()
    {
        return nullptr;
    }

    virtual void bindVertexBuffer(Handle<HwBufferObject> bufHandle, uint32_t binding) {}
    virtual void bindIndexBuffer(Handle<HwBufferObject> bufHandle, uint32_t indexSize) {}
    virtual void* lockBuffer(Handle<HwBufferObject> bufHandle, uint32_t offset, uint32_t numBytes) { return nullptr; }
    virtual void unlockBuffer(Handle<HwBufferObject> bufHandle) {}
    virtual Handle<HwBufferObject> createBufferObject(
        BufferObjectBinding bindingType, 
        BufferUsage usage, 
        uint32_t byteCount,
        const char* debugName = nullptr);
    virtual void updateBufferObject(
        Handle<HwBufferObject> boh, 
        const char* data, 
        uint32_t size);
    virtual Handle<HwDescriptorSetLayout> createDescriptorSetLayout(DescriptorSetLayout& info);
    virtual Handle<HwDescriptorSetLayout> getDescriptorSetLayout(Handle<HwProgram> programHandle, uint32_t set);
    virtual Handle<HwDescriptorSet> createDescriptorSet(Handle<HwDescriptorSetLayout> dslh);
    virtual Handle<HwPipelineLayout> createPipelineLayout(std::array<Handle<HwDescriptorSetLayout>, 4>& layouts);
    virtual Handle<HwProgram> createShaderProgram(const ShaderInfo& mShaderInfo, VertexDeclaration* decl);
    virtual Handle<HwDescriptorSetLayout> getDescriptorSetLayout(
        Handle<HwComputeProgram> programHandle, 
        uint32_t set);
    virtual Handle<HwComputeProgram> createComputeProgram(const ShaderInfo& mShaderInfo);
    virtual Handle<HwPipeline> createPipeline(
        backend::RasterState& rasterState,
        Handle<HwProgram>& program);

    virtual void bindDescriptorSet(
        Handle<HwDescriptorSet> dsh,
        uint8_t setIndex,
        backend::DescriptorSetOffsetArray&& offsets);
    virtual void updateDescriptorSetBuffer(
        Handle<HwDescriptorSet> dsh,
        backend::descriptor_binding_t binding,
        backend::BufferObjectHandle boh,
        uint32_t offset,
        uint32_t size);
    virtual void updateDescriptorSetTexture(
        Handle<HwDescriptorSet> dsh,
        backend::descriptor_binding_t binding,
        OgreTexture* tex);
private:
    void renderJob(ArenaScope& arena, FrameGraphPassCallback cb);

protected:
	
    uint32_t mBatchCount = 0;
    uint32_t mTriangleCount = 0;
    uint32_t mLoadResCount = 0;


    String mRenderSystemName;
    uint32_t mRenderType;
    
    utils::JobSystem mJobSystem;
    filament::LinearAllocatorArena mPerRenderPassArena;
};
