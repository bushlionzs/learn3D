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
    virtual void update(float delta);
    virtual void frameStart();
    virtual void frameEnd();
    virtual void render(Ogre::Renderable* r, RenderListType t);
    virtual void postRender();
    virtual Ogre::Camera* getCurrentCamera();
    virtual Ogre::ITexture* createTextureFromFile(const std::string& name, Ogre::TextureProperty* texProperty);
    virtual Shader* createShader(ShaderInfo& sinfo);
    void* createRenderableData();
    ID3D12GraphicsCommandList* getCommandList();
    virtual void _setViewport(Ogre::Viewport* vp);
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
private:
    bool initDirect3D();
    void buildRootSignature();
    void renderImpl(Dx12Pass* pass);
    void UpdateMainPassCB(Ogre::Camera* camera);
    void UpdateShadowTransform(float delta);
    void updateShadowPassCB();
    void CreateRtvAndDsvDescriptorHeaps();
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

    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;

    Ogre::Camera* mCamera = nullptr;

    Dx12Pass mCurrentPass;
    Dx12Frame* mCurrentFrame;
    std::vector< Dx12Frame*> mFrameList;
    uint32_t mCurrFrameResourceIndex = 0;
    Dx12RenderTarget* mActiveDx12RenderTarget;

    FrameConstantBuffer  mFrameConstantBuffer;

    Dx12ShadowMap* mDx12ShadowMap = nullptr;
    uint32_t mShadowSize = 2048;
    Dx12TextureHandleManager* mDx12TextureHandleManager = nullptr;


    float mLightNearZ = 0.0f;
    float mLightFarZ = 0.0f;
    Ogre::Vector3 mLightPosW;
    Ogre::Matrix4 mLightView = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 mLightProj = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 mShadowTransform = Ogre::Matrix4::IDENTITY;

    float mLightRotationAngle = 0.0f;
    Ogre::Vector3 mBaseLightDirections[3] = {
        Ogre::Vector3(0.57735f, -0.57735f, 0.57735f),
        Ogre::Vector3(-0.57735f, -0.57735f, 0.57735f),
        Ogre::Vector3(0.0f, -0.707f, -0.707f)
    };
    Ogre::Vector3 mRotatedLightDirections[3];
    Ogre::Sphere mSceneBounds;

    CD3DX12_GPU_DESCRIPTOR_HANDLE mNullSrv;
    CD3DX12_GPU_DESCRIPTOR_HANDLE mNullCubeSrv;

    DirectX::XMVECTORF32 mClearColor = DirectX::Colors::Black;
};