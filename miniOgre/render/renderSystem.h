#pragma once
#include <functional>
#include "shader.h"
#include "engine_struct.h"
#include "OgreTexture.h"
#include <utils/Allocator.h>
#include <utils/JobSystem.h>
#include <filament/Handle.h>
#include <filament/DriverBase.h>
#include <fg/FrameGraphId.h>
#include <fg/FrameGraphTexture.h>
#include <fg/Allocators.h>
#include <fg/ResourceAllocator.h>


class GraphicsCommandList;
class RenderableData;

using namespace filament::backend;

namespace Ogre
{
    class RenderWindow;
}

using PassCallback = std::function< FrameGraphId<FrameGraphTexture>(FrameGraph& fg)>;

class RenderSystem
{
public:
    RenderSystem();
    ~RenderSystem();
    virtual bool engineInit();
    virtual void frameStart() = 0;
    virtual void frameEnd() = 0;
    virtual void render(PassCallback cb);
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

    uint64_t getFrameNumber()
    {
        return mFrameNumber;
    }


    utils::JobSystem& getJobSystem()
    {
        return mJobSystem;
    }

    virtual void beginRenderPass(
        RenderPassInfo& renderPassInfo);
    virtual void endRenderPass();
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

    virtual Handle<HwBufferObject> createBufferObject(
        BufferObjectBinding bindingType, 
        BufferUsage usage, 
        uint32_t bufferCount);
    virtual void updateBufferObject(
        Handle<HwBufferObject> boh, 
        const char* data, 
        uint32_t size);
private:
    void renderJob(ArenaScope& arena, PassCallback cb);

protected:
	
    uint32_t mBatchCount = 0;
    uint32_t mTriangleCount = 0;
    uint32_t mLoadResCount = 0;
    uint64_t mFrameNumber = 0;


    String mRenderSystemName;
    uint32_t mRenderType;
    
    utils::JobSystem mJobSystem;
    filament::LinearAllocatorArena mPerRenderPassArena;
};
