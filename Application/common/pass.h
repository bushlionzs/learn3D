#pragma once 
#include <DriverBase.h>
#include <OgreCommon.h>
#include <engine_struct.h>
class GameCamera;
class RenderSystem;

namespace Ogre
{
	class RenderWindow;
	class SceneManager;
	class ICamera;
	class OgreTexture;
	class RenderTarget;
}

struct RenderPassInput
{
	Ogre::RenderTarget* color = nullptr;
	Ogre::RenderTarget* depth = nullptr;
	Ogre::SceneManager* sceneMgr = nullptr;
	Ogre::ICamera* cam = nullptr;
	Ogre::Light* light = nullptr;
	Ogre::RenderTarget* shadowMapTarget = nullptr;
	cascadeInfo* cascadeMatrices = nullptr;
	bool flipY = true;
};


struct FrameContext
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh;
	filament::backend::Handle<filament::backend::HwFence> fh;
	filament::backend::Handle<filament::backend::HwSemaphore> sph;
};
struct RenderContext
{
	filament::backend::Handle<filament::backend::HwCommandQueue> cqh;
	filament::backend::Handle<filament::backend::HwSwapChain> sch;
	FrameContext* frameContext;
	RenderSystem* rs;
	Ogre::SwapChainInfo scInfo;
	float delta;
};


using RenderPassCallback = std::function< void(RenderContext& context, RenderPassInfo& info)>;
using ComputePassCallback = std::function< void(RenderContext& context)>;
using UpdatePassCallback = std::function<void(float delta)>;

class PassBase
{
public:
	
	virtual bool initialize() { return true; }
	virtual void execute(RenderContext& context) {}
	virtual void update(float delta) {}
	virtual void update(RenderContext& context) {}
};

class RenderPipeline
{
public:
	virtual void addRenderPass(PassBase* pass) = 0;
	virtual filament::backend::Handle<filament::backend::HwCommandBuffer> getCurrentCommandBuffer()
	{
		return filament::backend::Handle<filament::backend::HwCommandBuffer>();
	}
};

PassBase* createStandardRenderPass(RenderPassInput& input);

PassBase* createSceneRenderPass(RenderPassInput& input);

PassBase* createUserDefineRenderPass(
	RenderPassCallback renderCallback, 
	UpdatePassCallback updateCallback);

PassBase* createComputePass(
	ComputePassCallback userCallback,
	UpdatePassCallback updateCallback);

PassBase* createPresentPass(
	Ogre::RenderTarget* sourceTarget, 
	Ogre::RenderWindow* renderWindow,
	const char* shaderName = nullptr);
