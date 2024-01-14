/***********************************************************************
    created:    Tue Feb 17 2009
    author:     Paul D Turner
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2013 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#include <OgreHeader.h>
#include "CEGUI/RendererModules/Ogre/Renderer.h"
#include "CEGUI/RendererModules/Ogre/GeometryBuffer.h"
#include "CEGUI/RendererModules/Ogre/TextureTarget.h"
#include "CEGUI/RendererModules/Ogre/Texture.h"
#include "CEGUI/RendererModules/Ogre/WindowTarget.h"
#include "CEGUI/GUIContext.h"
#include "CEGUI/Exceptions.h"
#include "CEGUI/System.h"
#include "CEGUI/RendererModules/Ogre/ResourceProvider.h"
#include "CEGUI/RendererModules/Ogre/ImageCodec.h"
#include "CEGUI/Logger.h"

#include <OgreRoot.h>
#include <RenderSystem.h>
#include <OgreRenderWindow.h>

#include <OgreFrameListener.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <CEGUIManager.h>


#ifdef CEGUI_USE_OGRE_HLMS
#include <OgreHlmsManager.h>
#include <OgreHlmsDatablock.h>
#endif

// Start of CEGUI namespace section
namespace CEGUI
{
//----------------------------------------------------------------------------//
// shader source code strings
static Ogre::String S_hlsl_vs_source(
    "uniform float4x4 worldViewProjMatrix;"
    "struct VS_OUT {"
    "   float4 position : POSITION;"
    "   float2 uv : TEXCOORD0;"
    "   float4 colour : COLOR;"
    "};"
    "VS_OUT main(float4 position : POSITION,"
    "            float2 uv : TEXCOORD0,"
    "            float4 colour : COLOR)"
    "{"
    "    VS_OUT o;"
    "    o.uv = uv;"
    "    o.colour = colour;"
    "    o.position = mul(worldViewProjMatrix, position);"
    "    return o;"
    "}"
);

static Ogre::String S_hlsl_ps_source(
    "float4 main(float4 colour : COLOR,"
    "            float2 texCoord : TEXCOORD0,"
    "            uniform sampler2D texture0 : TEXUNIT0) : COLOR"
    "{"
    "    return tex2D(texture0, texCoord) * colour;"
    "}"
);

#ifdef CEGUI_USE_OGRE_HLMS
static Ogre::String S_hlsl_d3d11_vs_source(
    "cbuffer MatrixBuffer\n"
    "{\n"
	"    matrix worldViewProjMatrix;\n"
    "};\n"
    "\n"
    "struct VertOut\n"
    "{\n"
    "	float4 pos : SV_Position;\n"
    "	float4 colour : COLOR;\n"
    "	float2 texcoord0 : TEXCOORD;\n"
    "};\n"
    "\n"
    "// Vertex shader\n"
    "VertOut main(float3 inPos : POSITION, float4 inColour : COLOR, float2 inTexCoord0 : TEXCOORD)\n"
    "{\n"
    "	VertOut output;\n"
    "\n"
    "   output.pos = mul(worldViewProjMatrix, float4(inPos, 1.0));\n"
    "   output.texcoord0 = inTexCoord0;\n"
    "	output.colour = inColour;\n"
    "\n"
    "	return output;\n"
    "}\n"
);

static Ogre::String S_hlsl_d3d11_ps_source(
    "Texture2D texture0 : register(t0);\n"
    "SamplerState textureSamplerState : register(s0);\n"
    "\n"
    "struct VertOut\n"
    "{\n"
    "	float4 pos : SV_Position;\n"
    "	float4 colour : COLOR;\n"
    "	float2 texcoord0 : TEXCOORD;\n"
    "};\n"
    "\n"
    "float4 main(VertOut input) : SV_Target\n"
    "{\n"
    "	float4 colour = texture0.Sample(textureSamplerState, input.texcoord0) * input.colour;\n"
    "	return colour;\n"
    "}\n"
    "\n"
);
#endif

static Ogre::String S_glsl_compat_vs_source(
    "void main(void)"
    "{"
    "    gl_TexCoord[0] = gl_MultiTexCoord0;"
    "    gl_FrontColor = gl_Color;"
    "    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
    "}"
);
static Ogre::String S_glsl_compat_ps_source(
    "uniform sampler2D texture0;"
    "void main(void)"
    "{"
    "    gl_FragColor = texture2D(texture0, gl_TexCoord[0].st) * gl_Color;"
    "}"
);

static Ogre::String S_glsl_core_vs_source(
    "#version 150 core \n"

    "uniform mat4 modelViewPerspMatrix;"

    "in vec4 vertex;"
    "in vec2 uv0;"
    "in vec4 colour;"

    "out vec2 exTexCoord;"
    "out vec4 exColour;"

    "void main(void)"
    "{"
    "   exTexCoord = uv0;"
    "   exColour = colour;"

    "   gl_Position = modelViewPerspMatrix * vertex;"
    "}"
);

static Ogre::String S_glsl_core_ps_source(
    "#version 150 core \n"

    "uniform sampler2D texture0;"

    "in vec2 exTexCoord;"
    "in vec4 exColour;"

    "out vec4 fragColour;"

    "void main(void)"
    "{"
    "   fragColour = texture(texture0, exTexCoord) * exColour;"
    "}"
);

//----------------------------------------------------------------------------//
#ifdef CEGUI_USE_OGRE_COMPOSITOR2
// The new method will be used
// Internal Ogre::RenderQueueListener. This is how the renderer gets notified
// of workspaces that need rendering
static class OgreGUIRenderQueueListener
{
public:
    OgreGUIRenderQueueListener();

    void setCEGUIRenderEnabled(bool enabled);
    bool isCEGUIRenderEnabled() const;

private:
    bool d_enabled;

} S_frameListener;


#else // Use the old method
// Internal Ogre::FrameListener based class.  This is how we noew hook into the
// rendering process (as opposed to render queues previously)
static class OgreGUIFrameListener : public Ogre::FrameListener
{
public:
    OgreGUIFrameListener();

    void setCEGUIRenderEnabled(bool enabled);
    bool isCEGUIRenderEnabled() const;

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
    bool d_enabled;

} S_frameListener;

#endif    
//----------------------------------------------------------------------------//
//! container type used to hold TextureTargets we create.
typedef std::vector<TextureTarget*> TextureTargetList;
//! container type used to hold GeometryBuffers we create.
typedef std::vector<OgreGeometryBuffer*> GeometryBufferList;
//! container type used to hold Textures we create.
typedef std::map<String, OgreTexture*, StringFastLessCompare
                 CEGUI_MAP_ALLOC(String, OgreTexture*)> TextureMap;

//----------------------------------------------------------------------------//
// Implementation data for the OgreRenderer
struct OgreRenderer_impl :
    public AllocatedObject<OgreRenderer_impl>
{
    OgreRenderer_impl() :
        d_displayDPI(96, 96),
        // TODO: should be set to correct value
        d_maxTextureSize(2048),
        d_ogreRoot(Ogre::Root::getSingletonPtr()),
#if !defined(CEGUI_USE_OGRE_COMPOSITOR2)
        d_previousVP(0),
#endif
#ifdef CEGUI_USE_OGRE_HLMS
        d_renderTarget(0),
        d_hlmsMacroblock(0),
        d_hlmsBlendblock(0),
        d_hlmsSamplerblock(0),
#endif
        d_activeBlendMode(BM_INVALID),
        d_makeFrameControlCalls(true),
        d_useShaders(false),
        d_useGLSL(false),
        d_useGLSLCore(false),
        d_worldMatrix(Ogre::Matrix4::IDENTITY),
        d_viewMatrix(Ogre::Matrix4::IDENTITY),
        d_projectionMatrix(Ogre::Matrix4::IDENTITY),
        d_worldViewProjMatrix(Ogre::Matrix4::IDENTITY),
        d_combinedMatrixValid(true)
        {}

    //! String holding the renderer identification text.
    static String d_rendererID;
    //! What the renderer considers to be the current display size.
    Sizef d_displaySize;
    //! What the renderer considers to be the current display DPI resolution.
    Vector2f d_displayDPI;
    //! The default RenderTarget
    OgreWindowTarget* d_defaultTarget;
    //! Container used to track texture targets.
    TextureTargetList d_textureTargets;
    //! Container used to track geometry buffers.
    GeometryBufferList d_geometryBuffers;
    //! Container used to track textures.
    TextureMap d_textures;
    //! What the renderer thinks the max texture size is.
    uint d_maxTextureSize;
    //! OGRE root object ptr
    Ogre::Root* d_ogreRoot;
    //! Pointer to the render system for Ogre.
    RenderSystem* d_renderSystem;
#if !defined(CEGUI_USE_OGRE_COMPOSITOR2)
    //! Pointer to the previous viewport set in render system.
    Ogre::Viewport* d_previousVP;
    //! Previous projection matrix set on render system.
    Ogre::Matrix4 d_previousProjMatrix;
#endif
#ifdef CEGUI_USE_OGRE_HLMS
    //! OGRE render target
    Ogre::RenderTarget* d_renderTarget;
    //! HLMS block used to set macro parameters
    const Ogre::HlmsMacroblock* d_hlmsMacroblock;
    //! HLMS block used to set blending parameters
    const Ogre::HlmsBlendblock* d_hlmsBlendblock;
    //! HLMS block used to set sampling parameters
    const Ogre::HlmsSamplerblock* d_hlmsSamplerblock;
#endif
    //! What we think is the current blend mode to use
    BlendMode d_activeBlendMode;
    //! Whether _beginFrame and _endFrame will be called.
    bool d_makeFrameControlCalls;
    //! Whether shaders will be used for basic rendering
    bool d_useShaders;
    //! Whether shaders are glsl or hlsl
    bool d_useGLSL;
    //! Whether we use the ARB glsl shaders or the OpenGL 3.2 Core shader profile (140 core)
    bool d_useGLSLCore;


    Ogre::Matrix4 d_worldMatrix;
    Ogre::Matrix4 d_viewMatrix;
    Ogre::Matrix4 d_projectionMatrix;
    Ogre::Matrix4 d_worldViewProjMatrix;
    bool d_combinedMatrixValid;
};

//----------------------------------------------------------------------------//
String OgreRenderer_impl::d_rendererID(
"CEGUI::OgreRenderer - Official OGRE based 2nd generation renderer module.");

//----------------------------------------------------------------------------//
#if !defined(CEGUI_USE_OGRE_COMPOSITOR2)
OgreRenderer& OgreRenderer::bootstrapSystem(const int abi)
{
    System::performVersionTest(CEGUI_VERSION_ABI, abi, CEGUI_FUNCTION_NAME);

    if (System::getSingletonPtr())
        CEGUI_THROW(InvalidRequestException(
            "CEGUI::System object is already initialised."));

    OgreRenderer& renderer = create();
    OgreResourceProvider& rp = createOgreResourceProvider();
    OgreImageCodec& ic = createOgreImageCodec();
    System::create(renderer, &rp, static_cast<XMLParser*>(0), &ic);

    return renderer;
}
#endif
//----------------------------------------------------------------------------//
OgreRenderer& OgreRenderer::bootstrapSystem(Ogre::RenderTarget& target,
                                            const int abi)
{
    System::performVersionTest(CEGUI_VERSION_ABI, abi, CEGUI_FUNCTION_NAME);

    if (System::getSingletonPtr())
        CEGUI_THROW(InvalidRequestException(
            "CEGUI::System object is already initialised."));

    OgreRenderer& renderer = OgreRenderer::create(target);
    OgreResourceProvider& rp = createOgreResourceProvider();
    OgreImageCodec& ic = createOgreImageCodec();
    System::create(renderer, &rp, static_cast<XMLParser*>(0), &ic);

    return renderer;
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroySystem()
{
    System* sys;
    if (!(sys = System::getSingletonPtr()))
        CEGUI_THROW(InvalidRequestException(
            "CEGUI::System object is not created or was already destroyed."));

    OgreRenderer* renderer = static_cast<OgreRenderer*>(sys->getRenderer());
    OgreResourceProvider* rp =
        static_cast<OgreResourceProvider*>(sys->getResourceProvider());

    OgreImageCodec* ic = &static_cast<OgreImageCodec&>(sys->getImageCodec());

    System::destroy();
    destroyOgreImageCodec(*ic);
    destroyOgreResourceProvider(*rp);
    destroy(*renderer);
}

//----------------------------------------------------------------------------//
#if !defined(CEGUI_USE_OGRE_COMPOSITOR2)
OgreRenderer& OgreRenderer::create(const int abi)
{
    System::performVersionTest(CEGUI_VERSION_ABI, abi, CEGUI_FUNCTION_NAME);

    return *CEGUI_NEW_AO OgreRenderer();
}
#endif
//----------------------------------------------------------------------------//
OgreRenderer& OgreRenderer::create(Ogre::RenderTarget& target,
                                   const int abi)
{
    System::performVersionTest(CEGUI_VERSION_ABI, abi, CEGUI_FUNCTION_NAME);

    return *CEGUI_NEW_AO OgreRenderer(target);
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroy(OgreRenderer& renderer)
{
    CEGUI_DELETE_AO &renderer;
}

//----------------------------------------------------------------------------//
OgreResourceProvider& OgreRenderer::createOgreResourceProvider()
{
    return *CEGUI_NEW_AO OgreResourceProvider();
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroyOgreResourceProvider(OgreResourceProvider& rp)
{
    CEGUI_DELETE_AO &rp;
}

//----------------------------------------------------------------------------//
OgreImageCodec& OgreRenderer::createOgreImageCodec()
{
    return *CEGUI_NEW_AO OgreImageCodec();
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroyOgreImageCodec(OgreImageCodec& ic)
{
    CEGUI_DELETE_AO &ic;
}

//----------------------------------------------------------------------------//
void OgreRenderer::setRenderingEnabled(const bool enabled)
{
    S_frameListener.setCEGUIRenderEnabled(enabled);
}

//----------------------------------------------------------------------------//
bool OgreRenderer::isRenderingEnabled() const
{
    return S_frameListener.isCEGUIRenderEnabled();
}

//----------------------------------------------------------------------------//
RenderTarget& OgreRenderer::getDefaultRenderTarget()
{
    return *d_pimpl->d_defaultTarget;
}

//----------------------------------------------------------------------------//
GeometryBuffer& OgreRenderer::createGeometryBuffer()
{
    OgreGeometryBuffer* gb =
        CEGUI_NEW_AO OgreGeometryBuffer(*this, *d_pimpl->d_renderSystem);

    d_pimpl->d_geometryBuffers.push_back(gb);
    return *gb;
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroyGeometryBuffer(const GeometryBuffer& buffer)
{
    GeometryBufferList::iterator i = std::find(d_pimpl->d_geometryBuffers.begin(),
                                               d_pimpl->d_geometryBuffers.end(),
                                               &buffer);

    if (d_pimpl->d_geometryBuffers.end() != i)
    {
        d_pimpl->d_geometryBuffers.erase(i);
        CEGUI_DELETE_AO &buffer;
    }
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroyAllGeometryBuffers()
{
    while (!d_pimpl->d_geometryBuffers.empty())
        destroyGeometryBuffer(**d_pimpl->d_geometryBuffers.begin());
}

//----------------------------------------------------------------------------//
TextureTarget* OgreRenderer::createTextureTarget()
{
    TextureTarget* tt = CEGUI_NEW_AO OgreTextureTarget(*this, *d_pimpl->d_renderSystem);
    d_pimpl->d_textureTargets.push_back(tt);
    return tt;
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroyTextureTarget(TextureTarget* target)
{
    TextureTargetList::iterator i = std::find(d_pimpl->d_textureTargets.begin(),
                                              d_pimpl->d_textureTargets.end(),
                                              target);

    if (d_pimpl->d_textureTargets.end() != i)
    {
        d_pimpl->d_textureTargets.erase(i);
        CEGUI_DELETE_AO target;
    }
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroyAllTextureTargets()
{
    while (!d_pimpl->d_textureTargets.empty())
        destroyTextureTarget(*d_pimpl->d_textureTargets.begin());
}

//----------------------------------------------------------------------------//
Texture& OgreRenderer::createTexture(const String& name)
{
    throwIfNameExists(name);

    OgreTexture* t = CEGUI_NEW_AO OgreTexture(name);
    d_pimpl->d_textures[name] = t;

    logTextureCreation(name);

    return *t;
}

//----------------------------------------------------------------------------//
Texture& OgreRenderer::createTexture(const String& name, const String& filename,
                                     const String& resourceGroup)
{
    throwIfNameExists(name);

    OgreTexture* t = CEGUI_NEW_AO OgreTexture(name, filename, resourceGroup);
    d_pimpl->d_textures[name] = t;

    logTextureCreation(name);

    return *t;
}

//----------------------------------------------------------------------------//
Texture& OgreRenderer::createTexture(const String& name, const Sizef& size)
{
    throwIfNameExists(name);

    OgreTexture* t = CEGUI_NEW_AO OgreTexture(name, size);
    d_pimpl->d_textures[name] = t;

    logTextureCreation(name);

    return *t;
}

//----------------------------------------------------------------------------//
Texture& OgreRenderer::createTexture(const String& name, Ogre::TexturePtr& tex,
                                     bool take_ownership)
{
    throwIfNameExists(name);

    OgreTexture* t = CEGUI_NEW_AO OgreTexture(name, tex, take_ownership);
    d_pimpl->d_textures[name] = t;

    logTextureCreation(name);

    return *t;
}

//----------------------------------------------------------------------------//
void OgreRenderer::throwIfNameExists(const String& name) const
{
    if (d_pimpl->d_textures.find(name) != d_pimpl->d_textures.end())
        CEGUI_THROW(AlreadyExistsException(
            "[OgreRenderer] Texture already exists: " + name));
}

//----------------------------------------------------------------------------//
void OgreRenderer::logTextureCreation(const String& name)
{
    Logger* logger = Logger::getSingletonPtr();
    if (logger)
        logger->logEvent("[OgreRenderer] Created texture: " + name);
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroyTexture(Texture& texture)
{
    destroyTexture(texture.getName());
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroyTexture(const String& name)
{
    TextureMap::iterator i = d_pimpl->d_textures.find(name);

    if (d_pimpl->d_textures.end() != i)
    {
        logTextureDestruction(name);
        CEGUI_DELETE_AO i->second;
        d_pimpl->d_textures.erase(i);
    }
}

//----------------------------------------------------------------------------//
void OgreRenderer::logTextureDestruction(const String& name)
{
    Logger* logger = Logger::getSingletonPtr();
    if (logger)
        logger->logEvent("[OgreRenderer] Destroyed texture: " + name);
}

//----------------------------------------------------------------------------//
void OgreRenderer::destroyAllTextures()
{
    while (!d_pimpl->d_textures.empty())
        destroyTexture(d_pimpl->d_textures.begin()->first);
}

//----------------------------------------------------------------------------//
Texture& OgreRenderer::getTexture(const String& name) const
{
    TextureMap::const_iterator i = d_pimpl->d_textures.find(name);
    
    if (i == d_pimpl->d_textures.end())
        CEGUI_THROW(UnknownObjectException("Texture does not exist: " + name));

    return *i->second;
}

//----------------------------------------------------------------------------//
bool OgreRenderer::isTextureDefined(const String& name) const
{
    return d_pimpl->d_textures.find(name) != d_pimpl->d_textures.end();
}

//----------------------------------------------------------------------------//
void OgreRenderer::beginRendering()
{

}

//----------------------------------------------------------------------------//
void OgreRenderer::endRendering()
{
    
}

//----------------------------------------------------------------------------//
const Sizef& OgreRenderer::getDisplaySize() const
{
    return d_pimpl->d_displaySize;
}

//----------------------------------------------------------------------------//
const Vector2f& OgreRenderer::getDisplayDPI() const
{
    return d_pimpl->d_displayDPI;
}

//----------------------------------------------------------------------------//
uint OgreRenderer::getMaxTextureSize() const
{
    return d_pimpl->d_maxTextureSize;
}

//----------------------------------------------------------------------------//
const String& OgreRenderer::getIdentifierString() const
{
    return d_pimpl->d_rendererID;
}

//----------------------------------------------------------------------------//
#if !defined(CEGUI_USE_OGRE_COMPOSITOR2)
OgreRenderer::OgreRenderer() :
    d_pimpl(CEGUI_NEW_AO OgreRenderer_impl())
{
    checkOgreInitialised();

    // get auto created window
    Ogre::RenderWindow* rwnd = CEGUIManager::getSingleton().getRenderWindows();
    if (!rwnd)
        CEGUI_THROW(RendererException(
            "Ogre was not initialised to automatically create a window, you "
            "should therefore be explicitly specifying a Ogre::RenderTarget in "
            "the OgreRenderer::create function."));

    constructor_impl(*rwnd);
}
#endif

//----------------------------------------------------------------------------//
OgreRenderer::OgreRenderer(Ogre::RenderTarget& target) :
    d_pimpl(CEGUI_NEW_AO OgreRenderer_impl())
{
    checkOgreInitialised();

    constructor_impl(target);
}

//----------------------------------------------------------------------------//
OgreRenderer::~OgreRenderer()
{
#if !defined(CEGUI_USE_OGRE_COMPOSITOR2)
    d_pimpl->d_ogreRoot->removeFrameListener(&S_frameListener);
#endif    

    cleanupShaders();

    destroyAllGeometryBuffers();
    destroyAllTextureTargets();
    destroyAllTextures();

    CEGUI_DELETE_AO d_pimpl->d_defaultTarget;
    CEGUI_DELETE_AO d_pimpl;
}

//----------------------------------------------------------------------------//
void OgreRenderer::checkOgreInitialised()
{
 
}

//----------------------------------------------------------------------------//
void OgreRenderer::constructor_impl(Ogre::RenderTarget& target)
{
    d_pimpl->d_renderSystem = d_pimpl->d_ogreRoot->getRenderSystem();

    d_pimpl->d_displaySize.d_width  = target.getWidth();
    d_pimpl->d_displaySize.d_height = target.getHeight();

    // create default target & rendering root (surface) that uses it
    d_pimpl->d_defaultTarget =
        CEGUI_NEW_AO OgreWindowTarget(*this, *d_pimpl->d_renderSystem, target);

#ifdef CEGUI_USE_OGRE_HLMS
    d_pimpl->d_renderTarget = &target;
#endif

#if OGRE_VERSION >= 0x10800
    #ifdef CEGUI_USE_OGRE_HLMS
        bool isFixedFunctionEnabled = false;
    // Check if built with RT Shader System and if it is: Check if fixed function pipeline is enabled
    #else
        #if defined RTSHADER_SYSTEM_BUILD_CORE_SHADERS
            bool isFixedFunctionEnabled = d_pimpl->d_renderSystem->getFixedPipelineEnabled();
        #else
            bool isFixedFunctionEnabled = true;
        #endif

        #ifndef RTSHADER_SYSTEM_BUILD_CORE_SHADERS
            if (d_pimpl->d_useGLSLCore)
                CEGUI_THROW(RendererException("RT Shader System not available but trying to render using OpenGL 3.X+ Core."
                "When GLSL shaders are necessary, the RT Shader System component of Ogre is required for rendering CEGUI."));
        #endif
    #endif

    // Default to using shaders when that is the sane thing to do.
    // We check for use of the OpenGL 3+ Renderer in which case we always wanna (because we have to) use shaders
    if (!isFixedFunctionEnabled || d_pimpl->d_useGLSLCore)
        setUsingShaders(true);
#endif

    // hook into the rendering process
#if !defined(CEGUI_USE_OGRE_COMPOSITOR2)
    d_pimpl->d_ogreRoot->addFrameListener(&S_frameListener);
#endif

}

//----------------------------------------------------------------------------//
void OgreRenderer::initialiseShaders()
{

}

//----------------------------------------------------------------------------//
void OgreRenderer::cleanupShaders()
{


}

//----------------------------------------------------------------------------//
void OgreRenderer::setDisplaySize(const Sizef& sz)
{
    if (sz != d_pimpl->d_displaySize)
    {
        d_pimpl->d_displaySize = sz;

        // FIXME: This is probably not the right thing to do in all cases.
        Rectf area(d_pimpl->d_defaultTarget->getArea());
        area.setSize(sz);
        d_pimpl->d_defaultTarget->setArea(area);
    }

}

//----------------------------------------------------------------------------//
void OgreRenderer::setupRenderingBlendMode(const BlendMode mode,
                                           const bool force)
{
  
}


//----------------------------------------------------------------------------//
void OgreRenderer::setFrameControlExecutionEnabled(const bool enabled)
{
    d_pimpl->d_makeFrameControlCalls = enabled;

    // default rendering requires _beginFrame and _endFrame calls be made,
    // so if we're disabling those we must also disable default rendering.
    if (!d_pimpl->d_makeFrameControlCalls)
        setRenderingEnabled(false);
}

//----------------------------------------------------------------------------//
bool OgreRenderer::isFrameControlExecutionEnabled() const
{
    return d_pimpl->d_makeFrameControlCalls;
}

//----------------------------------------------------------------------------//
void OgreRenderer::initialiseRenderStateSettings()
{
    using namespace Ogre;



    bindShaders();

    // set alpha blending to known state
    setupRenderingBlendMode(BM_NORMAL, true);
}

//----------------------------------------------------------------------------//
void OgreRenderer::setDefaultRootRenderTarget(Ogre::RenderTarget& target)
{
    d_pimpl->d_defaultTarget->setOgreRenderTarget(target);
}

//----------------------------------------------------------------------------//
void OgreRenderer::bindShaders()
{
    
}

//----------------------------------------------------------------------------//
bool OgreRenderer::isUsingShaders() const
{
    return d_pimpl->d_useShaders;
}

//----------------------------------------------------------------------------//
void OgreRenderer::setUsingShaders(const bool use_shaders)
{
    if (d_pimpl->d_useShaders == use_shaders)
        return;

    if (use_shaders)
        initialiseShaders();
    else
        cleanupShaders();

    d_pimpl->d_useShaders = use_shaders;
}

//----------------------------------------------------------------------------//
void OgreRenderer::updateShaderParams() const
{
   
}

//----------------------------------------------------------------------------//
const Ogre::Matrix4& OgreRenderer::getWorldViewProjMatrix() const
{
    if (!d_pimpl->d_combinedMatrixValid)
    {
        Ogre::Matrix4 final_prj(d_pimpl->d_projectionMatrix);

#ifdef CEGUI_USE_OGRE_HLMS
        if (d_pimpl->d_renderTarget->requiresTextureFlipping())
#else
        if (d_pimpl->d_renderSystem->_getViewport()->getTarget()->
            requiresTextureFlipping())
#endif
        {
            final_prj[1][0] = -final_prj[1][0];
            final_prj[1][1] = -final_prj[1][1];
            final_prj[1][2] = -final_prj[1][2];
            final_prj[1][3] = -final_prj[1][3];
        }

        d_pimpl->d_worldViewProjMatrix =
            final_prj * d_pimpl->d_viewMatrix * d_pimpl->d_worldMatrix;

        d_pimpl->d_combinedMatrixValid = true;
    }

    return d_pimpl->d_worldViewProjMatrix;
}

//----------------------------------------------------------------------------//
const Ogre::Matrix4& OgreRenderer::getWorldMatrix() const
{
    return d_pimpl->d_worldMatrix;
}

//----------------------------------------------------------------------------//
const Ogre::Matrix4& OgreRenderer::getViewMatrix() const
{
    return d_pimpl->d_viewMatrix;
}

//----------------------------------------------------------------------------//
const Ogre::Matrix4& OgreRenderer::getProjectionMatrix() const
{
    return d_pimpl->d_projectionMatrix;
}

//----------------------------------------------------------------------------//
void OgreRenderer::setWorldMatrix(const Ogre::Matrix4& m)
{
    //d_pimpl->d_renderSystem->_setWorldMatrix(m);zhousha

    d_pimpl->d_worldMatrix = m;
    d_pimpl->d_combinedMatrixValid = false;
}

//----------------------------------------------------------------------------//
void OgreRenderer::setViewMatrix(const Ogre::Matrix4& m)
{
    //d_pimpl->d_renderSystem->_setViewMatrix(m);zhousha

    d_pimpl->d_viewMatrix = m;
    d_pimpl->d_combinedMatrixValid = false;
}

//----------------------------------------------------------------------------//
void OgreRenderer::setProjectionMatrix(const Ogre::Matrix4& m)
{
    //d_pimpl->d_renderSystem->_setProjectionMatrix(m);zhousha

    d_pimpl->d_projectionMatrix = m;
    d_pimpl->d_combinedMatrixValid = false;
}

//----------------------------------------------------------------------------//
#ifdef CEGUI_USE_OGRE_HLMS
Ogre::RenderTarget* OgreRenderer::getOgreRenderTarget()
{
    return d_pimpl->d_renderTarget;
}

//----------------------------------------------------------------------------//
const Ogre::HlmsSamplerblock* OgreRenderer::getHlmsSamplerblock()
{
    return d_pimpl->d_hlmsSamplerblock;
}
#endif

//----------------------------------------------------------------------------//
#ifdef CEGUI_USE_OGRE_COMPOSITOR2
OgreGUIRenderQueueListener::OgreGUIRenderQueueListener() : d_enabled(true)
{

}

//----------------------------------------------------------------------------//
void OgreGUIRenderQueueListener::setCEGUIRenderEnabled(bool enabled)
{
    d_enabled = enabled;
}

//----------------------------------------------------------------------------//
bool OgreGUIRenderQueueListener::isCEGUIRenderEnabled() const
{
    return d_enabled;
}

//----------------------------------------------------------------------------//

#else
OgreGUIFrameListener::OgreGUIFrameListener() :
    d_enabled(true)
{
}

//----------------------------------------------------------------------------//
void OgreGUIFrameListener::setCEGUIRenderEnabled(bool enabled)
{
    d_enabled = enabled;
}

//----------------------------------------------------------------------------//
bool OgreGUIFrameListener::isCEGUIRenderEnabled() const
{
    return d_enabled;
}

//----------------------------------------------------------------------------//
bool OgreGUIFrameListener::frameRenderingQueued(const Ogre::FrameEvent&)
{
    if (d_enabled)
        System::getSingleton().renderAllGUIContexts();

    return true;
}
#endif    

} // End of  CEGUI namespace section
