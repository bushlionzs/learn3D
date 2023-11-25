#pragma once
#include "renderSystem.h"
#include "VulkanTexture.h"
#include "VulkanUploadbuffer.h"

class VulkanGraphicsCommandList;
class VulkanFrame;
class VulkanWindow;
class VulkanRenderTarget;

class VulkanRenderSystem : public RenderSystem
{
public:
    VulkanRenderSystem(HWND wnd);
	~VulkanRenderSystem();

    virtual bool engineInit();
    virtual void frameStart();
    virtual void frameEnd();
    virtual void preRender(Ogre::Camera* cam);
    virtual void render(Renderable* r, RenderListType t);
    virtual void postRender();


    virtual ITexture* createTextureFromFile(
        const std::string& name,
        Ogre::TextureProperty* texProperty);

    virtual Shader* createShader(ShaderInfo& sinfo);

    virtual void ready();

    
    virtual RenderableData* createRenderableData(Ogre::Renderable* r);

    void _setViewport(ICamera* cam, Ogre::Viewport* vp);
    EngineType getRenderType();

    virtual void clearFrameBuffer(uint32 buffers,
        const ColourValue& colour,
        float depth, uint16 stencil);
    virtual Ogre::RenderWindow* createRenderWindow(
        const String& name, unsigned int width, unsigned int height,
        const NameValuePairList* miscParams);
    VulkanFrame* _getCurrentFrame();
    ICamera* _getCamera();
private:
    void updateMainPassCB(ICamera* camera);
private:
    bool mEnableValidationLayers;

    ICamera* mCamera = nullptr;

    FrameConstantBuffer mFrameConstantBuffer;
    
    VulkanFrame* mCurrentVulkanFrame;

    VulkanWindow* mRenderWindow;

    VulkanRenderTarget* mActiveVulkanRenderTarget;
};