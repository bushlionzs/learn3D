#pragma once
#include "renderSystem.h"
#include "VulkanTexture.h"
#include "VulkanRenderTarget.h"
#include "VulkanUploadbuffer.h"
#include "enkiTS/TaskScheduler.h"

class VulkanGraphicsCommandList;
class VulkanFrame;
class VulkanWindow;
class VulkanRayTracingContext;



class VulkanRenderSystem : public RenderSystem
{
public:
    VulkanRenderSystem(HWND wnd);
	~VulkanRenderSystem();

    virtual bool engineInit();
    virtual void frameStart();
    virtual void frameEnd();
    virtual void preRender(Ogre::Camera* cam);
    virtual void update(Renderable* r);
    virtual void render(Renderable* r, RenderListType t);
    virtual void multiRender(std::vector<Ogre::Renderable*>& objs, bool multithread);
    void rayTracingRender(std::vector<Ogre::Renderable*>& objs);
    virtual void postRender();


    virtual OgreTexture* createTextureFromFile(
        const std::string& name,
        Ogre::TextureProperty* texProperty);

    virtual Shader* createShader(ShaderInfo& sinfo);

    virtual void ready();

    
    virtual RenderableData* createRenderableData(Ogre::Renderable* r);

    void _setViewport(ICamera* cam, Ogre::Viewport* vp);
    EngineType getRenderType();

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
    VulkanFrame* _getCurrentFrame();
    ICamera* _getCamera();
private:
    void updateMainPassCB(ICamera* camera);
    VulkanFrame* getNextFrame();
    void generateIrradianceMap();
    void generatePrefilteredMap();
    virtual Ogre::OgreTexture* generateCubeMap(
        const std::string& name, 
        Ogre::OgreTexture* environmentCube,
        Ogre::PixelFormat format, 
        int32_t dim,
        CubeType type);
    virtual Ogre::OgreTexture*  generateBRDFLUT(const std::string& name);

    virtual FrameConstantBuffer* getFrameConstantBuffer()
    {
        return &mFrameConstantBuffer;
    }

    
private:

    RenderPassInfo mCurrentRenderPassInfo;

    FrameConstantBuffer mFrameConstantBuffer;
    
    VulkanFrame* mCurrentVulkanFrame = nullptr;

    VulkanWindow* mRenderWindow;

    VkImage mCurrentVKImage;

    enki::TaskScheduler mTaskScheduler;

    utils::JobSystem::Job* mRootJob;

    std::vector<Ogre::Renderable*> mRenderList;

    VulkanRayTracingContext* mRayTracingContext;

    uint32_t mFrameIndex = 0;
    uint32_t mImageIndex = 0;
};