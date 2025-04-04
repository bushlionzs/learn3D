#pragma once

#include <engine_struct.h>
#include "pass.h"
#include "game_camera.h"
#include "DriverBase.h"
#include "sdfUtil.h"

struct UpdateSDFVolumeTextureAtlasConstants
{
	Ogre::Vector3i mSourceAtlasVolumeMinCoord;
	Ogre::Vector3i mSourceDimensionSize;
	Ogre::Vector3i mSourceAtlasVolumeMaxCoord;
};

struct cameraUniformBlock
{
	Ogre::Matrix4 View;
	Ogre::Matrix4 Project;
	Ogre::Matrix4 ViewProject;
	Ogre::Matrix4 InvView;
	Ogre::Matrix4 InvProj;
	Ogre::Matrix4 InvViewProject;
	Ogre::Vector4 mCameraPos;
	float mNear;
	float mFar;
	float mFarNearDiff;
	float mFarNear;
	Ogre::Vector2 mTwoOverRes;
	Ogre::Vector2 mWindowSize;
	Ogre::Vector4 mDeviceZToWorldZ;
};

struct meshSDFUniformBlock
{
	Ogre::Matrix4 mWorldToVolumeMat[SDF_MAX_OBJECT_COUNT];
	Ogre::Vector4 mUVScaleAndVolumeScale[SDF_MAX_OBJECT_COUNT];
	Ogre::Vector4 mLocalPositionExtent[SDF_MAX_OBJECT_COUNT];
	Ogre::Vector4 mUVAddAndSelfShadowBias[SDF_MAX_OBJECT_COUNT];
	Ogre::Vector4 mSDFMAD[SDF_MAX_OBJECT_COUNT];
};

struct PushConstant
{
	uint32_t mNumObjects;
};

struct FrameData
{
	Handle<HwDescriptorSet> zeroSet;

	Handle<HwBufferObject>pBufferSDFVolumeData;
	Handle<HwBufferObject> pBufferUpdateSDFVolumeTextureAtlasConstants;
	Handle<HwDescriptorSet> zeroSetOfSDFVolume;


	Handle<HwBufferObject>pBufferCameraUniform;
	Handle<HwBufferObject>pBufferMeshSDFUniform;
	Handle<HwBufferObject>pBufferPushConstant;
	Handle<HwDescriptorSet> zeroSetOfAtlas;

	
};
#define NUM_SDF_MESHES 3
class BasicApplication
{
public:
	
	BasicApplication();
	~BasicApplication();

	void setup(
		RenderPipeline* renderPipeline,
		RenderSystem* renderSystem,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);

private:
	void base1();
	void initSDFVolumeTextureAtlasData();
	void UpdateMeshSDFConstants();
	void updateCameraUniform();
	void drawSDFMeshVisualizationOnScene(uint32_t frameIndex);
private:

	std::vector<FrameData> mFrameData;
	Ogre::SceneManager* mSceneManager;
	GameCamera* mGameCamera;
	RenderSystem* mRenderSystem;
	Ogre::RenderWindow* mRenderWindow;
	RenderPipeline* mRenderPipeline;

	SDFVolumeTextureAtlas* pSDFVolumeTextureAtlas = nullptr;
	OgreTexture* pTextureSDFVolumeAtlas = nullptr;
	Handle<HwComputeProgram> mUpdateRegion3DTextureHandle;
	Handle<HwComputeProgram> mVisualizeSDFMeshHandle;

	Ogre::RenderTarget* depthTarget;

	Ogre::RenderTarget* outputTarget;

	Handle<HwSampler> clampToEdgeTrillinearSampler;
	Handle<HwSampler> clampToEdgeNearSampler;


	std::vector<SDFVolumeData*> sdfVolumeInstances;

	meshSDFUniformBlock mMeshSDFConstants;
    uint32_t mSDFNumObjects = 0;
};