#pragma once 
#include <DriverBase.h>
#include <OgreCommon.h>
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
	Ogre::OgreTexture* shadowMap = nullptr;
	Ogre::ICamera* light = nullptr;
	bool shadowPass = false;
};

using RenderPassCallback = std::function< void(RenderPassInfo& info)>;
using ComputePassCallback = std::function< void(ComputePassInfo& info)>;
using UpdatePassCallback = std::function<void(float delta)>;

class PassBase
{
public:
	virtual void execute(RenderSystem* rs) = 0;
	virtual void update(float delta) {}
};


PassBase* createStandardRenderPass(RenderPassInput& input);

PassBase* createUserDefineRenderPass(
	RenderPassCallback renderCallback, 
	UpdatePassCallback updateCallback);

PassBase* createComputePass(ComputePassCallback userCallback);
