#pragma once

#include "renderSystem.h"
#include "d3dutil.h"
#include "UploadBuffer.h"
#include "dx12Common.h"

class Dx12GraphicsCommandList;
class Dx12RenderTarget;
class Dx12TextureHandleManager;
class Dx12ShadowMap;
class Dx12RenderWindow;

class Dx12RenderSystem : public RenderSystem
{
public:
    Dx12RenderSystem(HWND wnd);
    ~Dx12RenderSystem();
    virtual bool engineInit();
    virtual void ready();
    virtual void _resourceLoaded();
    virtual void frameStart();
    virtual void frameEnd();
    virtual void render(Ogre::Renderable* r, RenderListType t);
    virtual void multiRender(std::vector<Ogre::Renderable*>& objs, bool multithread);
    virtual Ogre::ITexture* createTextureFromFile(const std::string& name, Ogre::TextureProperty* texProperty);
    virtual Shader* createShader(ShaderInfo& sinfo);
    RenderableData* createRenderableData(Ogre::Renderable* r);
    ID3D12GraphicsCommandList* getCommandList();
    virtual void _setViewport(ICamera* cam, Ogre::Viewport* vp);
    EngineType getRenderType();
    void clearFrameBuffer(uint32 buffers,
        const Ogre::ColourValue& colour,
        float depth, uint16 stencil);
    Ogre::RenderWindow* createRenderWindow(
        const String& name, unsigned int width, unsigned int height,
        const NameValuePairList* miscParams);

    Dx12TextureHandleManager* getTextureHandleManager()
    {
        return mDx12TextureHandleManager;
    }

    Dx12Frame* getCurrentFrame()
    {
        return mCurrentFrame;
    }

    ICamera* getCamera()
    {
        return mCamera;
    }
private:
    void buildRootSignature();
    void renderImpl(Dx12Pass* pass);
    void updateMainPassCB(Ogre::ICamera* camera);

    void updateMainPassCBForTest(Ogre::ICamera* camera);
    void UpdateShadowPassCBForTest(Ogre::ICamera* camera);
    void createFrameResource();
private:
    Dx12RenderWindow* mRenderWindow = nullptr;    
    Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

    uint64_t mCurrentFence = 0;
    uint32_t mCubeMapIndex = 0;
    uint32_t mShadowMapIndex = 1;
    uint32_t mTextureArrayIndex = 2;
    uint32_t mMainConstantIndex = 4;
    uint32_t mObjectConstantIndex = 3;
    uint32_t mMatConstantIndex = 5;
    uint32_t mSkinedConstantIndex = 6;

    Dx12Shader* mShadowShader;
    Ogre::ICamera* mCamera = nullptr;

    Dx12Pass mCurrentPass;
    Dx12Frame* mCurrentFrame;
    std::vector< Dx12Frame*> mFrameList;
    uint32_t mCurrFrameResourceIndex = 0;
    Dx12RenderTarget* mActiveDx12RenderTarget;

    FrameConstantBuffer  mFrameConstantBuffer;

    Dx12TextureHandleManager* mDx12TextureHandleManager = nullptr;
};