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

struct ComputePassInput
{
	std::string shaderName;
	PipelineLayout pipelineLayout;
	Handle<HwDescriptorSet> ds;
	Ogre::Vector3i computeGroup;
};

class PassBase
{
public:
	virtual void execute(RenderSystem* rs) = 0;
};

PassBase* createRenderPass(RenderPassInput& input);

PassBase* createComputePass(ComputePassInput& input);
