#pragma once

#include "shader.h"
#include "engine_struct.h"
#include "texture.h"

class GraphicsCommandList;

namespace Ogre
{
    class RenderWindow;
}


typedef std::map< String, Ogre::RenderTarget* > RenderTargetMap;
typedef std::multimap<uchar, Ogre::RenderTarget* > RenderTargetPriorityMap;

class RenderSystem
{
public:
    class  Listener
    {
    public:
        Listener() {}
        virtual ~Listener() {}

        /** A rendersystem-specific event occurred.
        @param eventName The name of the event which has occurred
        @param parameters A list of parameters that may belong to this event,
        may be null if there are no parameters
        */
        virtual void eventOccurred(const String& eventName,
            const NameValuePairList* parameters = 0) = 0;
    };
public:
    RenderSystem();
    ~RenderSystem();

    virtual bool engineInit();
    virtual void frameStart() = 0;
    virtual void frameEnd() = 0;
    virtual void render(Ogre::Renderable* r, RenderListType t) = 0;

    virtual Ogre::ITexture* createTextureFromFile(
        const std::string& name,
        Ogre::TextureProperty* texProperty);

    virtual Ogre::RenderWindow* createRenderWindow(
        const String& name, unsigned int width, unsigned int height,
        const NameValuePairList* miscParams) = 0;

    virtual Shader* createShader(ShaderInfo& sinfo);

    virtual void ready() {}

    virtual void* createRenderableData() { return nullptr; }

    virtual EngineType getRenderType() = 0;
    virtual const String& getRenderSystemName()
    {
        return mRenderSystemName;
    }
    uint32_t getTriangleCount()
    {
        return mTriangleCount;
    }

    uint64_t getNextFrame()
    {
        return mNextFrame;
    }


    Ogre::Viewport* _getViewport();
    virtual void _setViewport(Ogre::Viewport* vp);

    virtual void clearFrameBuffer(uint32 buffers, const Ogre::ColourValue& colour = Ogre::ColourValue::Black,
        float depth = 1.0f, uint16 stencil = 0);

    virtual void _convertProjectionMatrix(const Ogre::Matrix4& matrix,
        Ogre::Matrix4& dest, bool forGpuProgram = false) {}

    void attachRenderTarget(Ogre::RenderTarget& target);

   virtual void _updateAllRenderTargets(bool swapBuffers = true);

    virtual void _swapAllRenderTargetBuffers();

    virtual void _resourceLoaded() {}
protected:
	
    uint32_t mBatchCount = 0;
    uint32_t mTriangleCount = 0;
    uint32_t mLoadResCount = 0;
    uint64_t mNextFrame = 0;
    Ogre::Viewport* mViewport = nullptr;


    /** The render targets. */
    RenderTargetMap mRenderTargets;
    /** The render targets, ordered by priority. */
    RenderTargetPriorityMap mPrioritisedRenderTargets;
    /** The Active render target. */
    Ogre::RenderTarget* mActiveRenderTarget;

    String mRenderSystemName;
};
