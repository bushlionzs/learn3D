#pragma once
#include "dx11Common.h"
#include "renderSystem.h"
#include "dx11UploadBuffer.h"

class Dx11RenderWindow;
class Dx11RenderTarget;

class Dx11RenderSystem : public RenderSystem
{
public:
    Dx11RenderSystem(HWND hWnd);
    ~Dx11RenderSystem();
    virtual bool engineInit();
    virtual void update(float delta);
    virtual void frameStart();
    virtual void frameEnd();
    virtual void _setViewport(ICamera* cam, Ogre::Viewport* vp);
    virtual void clearFrameBuffer(uint32 buffers,
        const Ogre::ColourValue& colour,
        float depth, uint16 stencil);
    virtual Ogre::RenderWindow* createRenderWindow(
        const String& name, unsigned int width, unsigned int height,
        const NameValuePairList* miscParams);
    virtual void ready();
    virtual void preRender();
    virtual void render(Renderable* r, RenderListType t);
    virtual void multiRender(std::vector<Ogre::Renderable*>& objs, bool multithread);
    virtual void postRender();
    virtual OgreTexture* createTextureFromFile(const std::string& name, TextureProperty* texProperty);
    virtual RenderableData* createRenderableData(Ogre::Renderable* r);
    EngineType getRenderType();
    ICamera* getCamera()
    {
        return mCamera;
    }
private:
    void updateFrame();
    void renderImpl(Dx11Pass& pass);
private:
    ICamera* mCamera = nullptr;
    Dx11RenderWindow* mRenderWindow;
    Dx11RenderTarget* mActiveRenderTarget;
    Dx11Pass mDx11Pass;

    FrameConstantBuffer mFrameConstantBuffer;
    std::unique_ptr<Dx11UploadBuffer<FrameConstantBuffer>> mFrameCB;

    ID3D11Device* mDx11Device = nullptr;
    ID3D11DeviceContext* mDx11Context = nullptr;
};