//#include "stdafx.h"
#include "basic.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreAnimationState.h"
#include "renderSystem.h"
#include "OgreCamera.h"
#include "OgreRenderTarget.h"
#include "OgreRenderWindow.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreRoot.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreTextureManager.h"
#include "godotUtil.h"
#include "pbrUtil.h"

BasicApplication::BasicApplication(ManualApplication* app)
{
	mApplication = app;
}

BasicApplication::~BasicApplication()
{

}


void BasicApplication::setup(
	RenderPipeline* renderPipeline,
	RenderContext& context,
	Ogre::RenderWindow* renderWindow,
	Ogre::SceneManager* sceneManager,
	GameCamera* gameCamera)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	ogreConfig.reverseDepth = false;
	mSceneManager = sceneManager;
	mGameCamera = gameCamera;
	mRenderWindow = renderWindow;
	mRenderPipeline = renderPipeline;
	
	base2(context);
}

void BasicApplication::update(float delta)
{
	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}
}

void BasicApplication::addCustomDirectory()
{
	//ResourceManager::getSingletonPtr()->addDirectory(std::string("D:\\wow3.3.5\\Data"), "wow", true);
}

void BasicApplication::ibl_init(RenderContext& context)
{
	Ogre::TextureProperty tp;
	tp._need_mipmap = false;
	tp._texType = Ogre::TEX_TYPE_CUBE_MAP;
	tp._tex_addr_mod = Ogre::TAM_CLAMP;
	tp._samplerParams.filterMag = filament::backend::SamplerFilterType::LINEAR;
	tp._samplerParams.filterMin = filament::backend::SamplerFilterType::LINEAR;
	tp._samplerParams.mipMapMode = filament::backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
	tp._samplerParams.wrapS = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	tp._samplerParams.wrapT = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	tp._samplerParams.wrapR = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	tp._samplerParams.anisotropyLog2 = 0;

	TextureLoadDesc textureLoadDesc;
	textureLoadDesc.tp = &tp;
	textureLoadDesc.pFileName = "papermill.ktx";
	Ogre::ResourceManager::getSingletonPtr()->addResource(&textureLoadDesc, nullptr);
	auto cbh = context.rs->createCommandBuffer(Ogre::QUEUE_TYPE_GRAPHICS);
	auto environmentCube = textureLoadDesc.pTexture;
	{
		std::string brdfLutName = "brdflut";
		brdfTarget = Ogre::generateBRDFLUT(context.cqh, cbh, brdfLutName);
		Ogre::TextureManager::getSingleton().addTexture(brdfLutName, brdfTarget->getTarget());
		tp._pbrType = Ogre::TextureTypePbr_BRDF_LUT;
	}

	{
		std::string prefilteredenvName = "prefilteredMap";
		prefilteredTarget = generateCubeMap(context.cqh, cbh, prefilteredenvName, environmentCube,
			Ogre::PF_FLOAT32_RGBA, 512, Ogre::CubeType_Prefiltered);
		Ogre::TextureManager::getSingleton().addTexture(prefilteredenvName, prefilteredTarget->getTarget());
		tp._pbrType = Ogre::TextureTypePbr_IBL_Specular;

	}

	{
		std::string irradianceName = "IrradianceMap";
		irradianceTarget = generateCubeMap(context.cqh, cbh, irradianceName, environmentCube,
			Ogre::PF_FLOAT32_RGBA, 64, Ogre::CubeType_Irradiance);
		Ogre::TextureManager::getSingleton().addTexture(irradianceName, irradianceTarget->getTarget());
		tp._pbrType = Ogre::TextureTypePbr_IBL_Diffuse;

	}
}
void BasicApplication::base1(RenderContext& context)
{
	ibl_init(context);
	std::string projectDir = "D:\\godotProject\\Abandoned-Spaceship-Godot-Demo";
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(projectDir);

	String UProjectDir = projectDir.c_str();
	GodotContext godotContext;
	godotContext.sceneManager = mSceneManager;
	godotContext.brdfTexName = "brdflut";
	godotContext.prefilteredTexName = "prefilteredMap";
	godotContext.irradianceTexName = "IrradianceMap";

	loadGodotProject(UProjectDir, godotContext);
	
	mGameCamera->lookAt(Ogre::Vector3(-0.2, 5.28, 8.14), Ogre::Vector3(-0.2, 5.28, 0.0));
	mGameCamera->setCameraType(Ogre::CameraMoveType_FirstPerson);
	mGameCamera->setMoveSpeed(5);
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	Ogre::Matrix4 m;
	if (ogreConfig.reverseDepth)
	{
		float aspectInverse = ogreConfig.height / (float)ogreConfig.width;
		m = Ogre::Math::makePerspectiveMatrixReverseZ(
			Ogre::Math::PI / 3.0f, aspectInverse, 0.1, 6000);
	}
	else
	{
		float aspect = ogreConfig.width / (float)ogreConfig.height;
		m = Ogre::Math::makePerspectiveMatrix(
			Ogre::Math::PI / 3.0f, aspect, 0.1, 6000);

	}
	mGameCamera->getCamera()->updateProjectMatrix(m);

	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	auto mainPass = createStandardRenderPass(input);
	mRenderPipeline->addRenderPass(mainPass);
}

Surface BasicApplication::godotWndCallback(AppInfo* appInfo, int64_t wnd)
{
	appInfo->appWnd = wnd;
	appInfo->loopback = godotLoop;
	

	Surface surface;
	surface.renderWnd = mApplication->wndInit(wnd);
	return surface;
}

void BasicApplication::userInit(AppInfo* appInfo)
{
	auto cb = std::bind(&BasicApplication::godotWndCallback, this, appInfo, std::placeholders::_1);
	GodotContext context; 
	context.wndCallback = cb;
	godotInit(context);
	
	
}

void BasicApplication::base2(RenderContext& context)
{
	godotProjectSetting();
}

