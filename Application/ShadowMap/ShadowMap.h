#pragma once
#include "ApplicationBase.h"
#include "forgeCommon.h"
class GameCamera;
class RenderSystem;
class Ogre::RenderWindow;
class Ogre::SceneManager;

#define NUM_CULLING_VIEWPORTS 5
#define NUM_GEOMETRY_SETS 2

struct FrameData
{
    //在compute shader中，保存索引对应的batchMeshIndex
	Handle<HwBufferObject> indirectDataBuffer;
	PerFrameVBConstants    perFrameVBConstants;
	Handle<HwBufferObject> perFrameConstantsBuffer;
	ObjectUniformBlock   meshUniformBlock;
	Handle<HwBufferObject> objectUniformBlockHandle;

	//for filter angles pass
	//set=0的描述符
	Handle <HwDescriptorSet> defaultDescSet;
	//set=1的描述符
	Handle <HwDescriptorSet> frameDescSet;

	//for visibility pass

	Handle <HwDescriptorSet> defaultDescriptorSetOfVisibilityPass;
	Handle <HwDescriptorSet> drawDescriptorSetOfVisibilityPass;
};

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();
	void setup(
		RenderSystem* renderSystem,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);
	void updatePass(std::vector<PassBase*>& passlist);
	FrameGraphId<FrameGraphTexture> fgPass(FrameGraph& fg);

	FrameData* getFrameData(uint32_t frameIndex)
	{
		return &mFrameData[frameIndex];
	}
private:
	void base1();
	void base2();
private:
	AnimationState* mAnimationState = nullptr;

	SceneNode* mLightNode = nullptr;

	Ogre::Light* light = nullptr;

	Ogre::SceneManager* mSceneManager;
	GameCamera* mGameCamera;
	RenderSystem* mRenderSystem;
	RenderWindow* mRenderWindow;
	std::vector<PassBase*> mPassList;

	std::vector<FrameData> mFrameData;
	Handle<HwComputeProgram> clearBufferProgramHandle;
	Handle<HwComputeProgram> filterTrianglesProgramHandle;

	Handle<HwBufferObject> filteredIndexBuffer[NUM_CULLING_VIEWPORTS];

	
	Handle<HwBufferObject> indirectDrawArgBuffer;

	Handle<HwBufferObject> vbConstantsBuffer;

	Handle<HwBufferObject> meshConstantsBuffer;

	VBConstants vbConstants[NUM_GEOMETRY_SETS];

};