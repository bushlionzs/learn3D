#include "OgreHeader.h"
#include "SimpleApp.h"
#include <utils/JobSystem.h>
#include <fg/ResourceAllocator.h>
#include <VulkanPlatform.h>
#include <time_util.h>
#include "application_window.h"
#include "InputManager.h"
#include "game_camera.h"
#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreMeshManager.h>
#include <OgreResourceManager.h>
#include <OgreAnimationState.h>
#include <OgreRenderTarget.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>
#include <OgreSubEntity.h>
#include <OgreMaterial.h>
#include <OgreParticleSystem.h>
#include <OgreTextureUnit.h>
#include <OgreTexture.h>
#include <OgreRenderTexture.h>
#include <OgreRenderTarget.h>
#include <ResourceParserManager.h>
#include <CEGUIManager.h>
#include "PassUtil.h"

using namespace filament;
using namespace filament::backend;
SimpleApp::SimpleApp()
{

}

SimpleApp::~SimpleApp()
{

}

void SimpleApp::run(SetupCallback setup, CleanupCallback cleanup)
{
	new Ogre::Root();

	uint32_t width = 1280;
	uint32_t height = 768;
	Ogre::Root::getSingleton().updateMainRect({ 0, 0, (int)width, (int)height });

	Ogre::Root::getSingleton()._initialise();

	mWindow = new ApplicationWindow(nullptr);
	
	mWindow->createWindow(width, height);
	if (!InputManager::getSingletonPtr())
	{
		new InputManager();
	}

	HWND wnd = mWindow->getWnd();
	InputManager::getSingletonPtr()->createInput((size_t)wnd);

	EngineType type = getEngineType();

	mRenderSystem = Ogre::Root::getSingleton().createRenderEngine(wnd, type);
	utils::JobSystem&  js = mRenderSystem->getJobSystem();
	js.adopt();
	Ogre::ColourValue color(0.678431f, 0.847058f, 0.901960f, 1.000000000f);
	Ogre::NameValuePairList params;
	params["externalWindowHandle"] = Ogre::StringConverter::toString((uint64_t)wnd);
	params["backGroundColor"] = Ogre::StringConverter::toString(color);
	mRenderWindow = mRenderSystem->createRenderWindow("", width, height, &params);
	mSceneManager = Ogre::Root::getSingleton().createSceneManger(MAIN_SCENE_MANAGER);

	auto camera = mSceneManager->createCamera(MAIN_CAMERA);

	ResourceParserManager::getSingleton()._initialise();

	mGameCamera = new GameCamera(camera, mSceneManager);
	InputManager::getSingletonPtr()->addListener(mGameCamera);

	ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources"), "sujian", true);
	ResourceManager::getSingletonPtr()->loadAllResource();

	if (true)
	{
		//ShowCursor(FALSE);
		//SetCursor(NULL);
		new CEGUIManager;
		static Ogre::RenderTarget rt;
		CEGUIManager::getSingleton()._initialise(&rt);
	}

	
	example1();
	

	while (!mClosed)
	{
		while (true)
		{
			MSG msg;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (msg.message == WM_QUIT)
				{
					mClosed = true;
					break;
				}
			}
			else
			{
				break;
			}
		}
		InputManager::getSingletonPtr()->captureInput();
		update(0.0f);

		auto passCallback = [width, height, this](FrameGraph& fg) -> FrameGraphId<FrameGraphTexture> {
			FrameGraphTexture::Descriptor colorBufferDesc = {
			.width = width,
			.height = height,
			.format = backend::TextureFormat::RGB16F
			};

			PassUtil::PassConfig config;

			
			config.rs = this->mRenderSystem;
			config.target = this->mRenderWindow;
			config.scene = Ogre::Root::getSingleton().getSceneManager(MAIN_SCENE_MANAGER);

			config.cam = config.scene->getCamera(MAIN_CAMERA);
			auto color = PassUtil::colorPass(fg, "Color Pass", colorBufferDesc, config);

			config.scene = Ogre::Root::getSingleton().getSceneManager("cegui");

			config.cam = config.scene->getCamera("cegui_camera");
			return color;
			};
		mRenderSystem->frameStart();
		mRenderSystem->render(passCallback);
		mRenderSystem->present();
		mRenderSystem->frameEnd();

		static uint32_t lastfps = 0;
		auto fps = Ogre::Root::getSingleton().getCurrentFPS();

		if (fps != lastfps)
		{
			lastfps = fps;
			char buffer[256];
			snprintf(buffer, sizeof(buffer), "fps:%lld", fps);
			::SetWindowText(mWindow->getWnd(), buffer);
		}
	}

}

void SimpleApp::example1()
{
	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	float aa = 1.0f;
	Ogre::Vector3 leftop = Ogre::Vector3(-aa, aa, 0.0f);
	Ogre::Vector3 leftbottom = Ogre::Vector3(-aa, -aa, 0.0f);
	Ogre::Vector3 righttop = Ogre::Vector3(aa, aa, 0.0f);
	Ogre::Vector3 rightbottom = Ogre::Vector3(aa, -aa, 0.0f);
	Ogre::Vector3 normal = Ogre::Vector3(0.0f, 0.0f, 1.0f);

	std::string meshName = "myrect";

	auto mesh = MeshManager::getSingletonPtr()->createRect(
		nullptr,
		meshName,
		leftop, leftbottom, righttop, rightbottom, normal);
	Ogre::Entity* rect = mSceneManager->createEntity("rect", meshName);
	SceneNode* rectnode = root->createChildSceneNode("rect");
	rectnode->attachObject(rect);

	//mSceneManager->setSkyBox(true, "SkyLan", 50000);

	auto sub = rect->getSubEntity(0);
	auto mat = sub->getMaterial();
	auto tu = mat->getTextureUnit(0);

	mGameCamera->updateCamera(Ogre::Vector3(0, 0.0f, -2.5f), Ogre::Vector3::ZERO);

	mGameCamera->setMoveSpeed(5.0f);
}

void SimpleApp::example2()
{
	std::string name = "Êé_·ðÉ½_·¿ÎÝ_13.mesh";
	name = "Â¥À¼ÕÊÅñ04.mesh";
	auto mesh = MeshManager::getSingletonPtr()->load(name);

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* sphere = mSceneManager->createEntity("sphere", name);
	SceneNode* spherenode = root->createChildSceneNode("sphere");

	spherenode->attachObject(sphere);

	mGameCamera->setDistance(2000.0f);
}

void SimpleApp::example3()
{
	std::string meshname = "ÃÉ¹Å¹ó×åÅ®_03.mesh";
	auto mesh = MeshManager::getSingletonPtr()->load(meshname);

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* gltf = mSceneManager->createEntity("gltf", meshname);
	SceneNode* gltfnode = root->createChildSceneNode("gltf");
	gltfnode->updatechildren();
	gltfnode->attachObject(gltf);

	mAnimationState = gltf->getAnimationState(std::string("ÐÝÏÐ04_02"));
	if (mAnimationState)
	{
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
	}

	mGameCamera->setHeight(300.0f);
	mGameCamera->setDistance(500);
	mGameCamera->setMoveSpeed(25.0f);
}

using namespace CEGUI;
void SimpleApp::example4()
{
	mGUIContext = CEGUIManager::getSingleton().getGUIContext();

	auto* root = WindowManager::getSingleton().loadLayoutFromFile("Package.xml");
	FontManager& fontManager(FontManager::getSingleton());
	CEGUI::Font& font(fontManager.createFromFile("simhei24.font"));
	mGUIContext->setDefaultFont(&font);


	mGUIContext->setRootWindow(root);

	CEGUI::String base_name = "DragContainer";

	
	
}

void SimpleApp::example5()
{
	mGUIContext = CEGUIManager::getSingleton().getGUIContext();

	auto mSelfEquip = WindowManager::getSingleton().loadLayoutFromFile("SelfEquip.xml");
	FontManager& fontManager(FontManager::getSingleton());
	CEGUI::Font& font(fontManager.createFromFile("simhei12.font"));

	mGUIContext->setDefaultFont(&font);

	//font.setProperty("TextColor", "FF0000");
	DefaultWindow* aa = (DefaultWindow*)mSelfEquip;
	WindowManager& winMgr = WindowManager::getSingleton();
	auto mRoot = (DefaultWindow*)winMgr.createWindow("DefaultWindow", "Root");
	mGUIContext->setRootWindow(mRoot);
	mRoot->addChild(mSelfEquip);


	

	auto vp = CEGUIManager::getSingleton().getViewport();

	vp->setClearEveryFrame(true);
	Ogre::ColourValue color(0.678431392f, 0.847058892f, 0.901960850f, 1.000000000f);
	vp->setBackgroundColour(color);

	SceneManager* sceneMgr = Ogre::Root::getSingletonPtr()->createSceneManger(std::string("SelfEquip"));
	Ogre::Camera* cam = sceneMgr->createCamera("SelfEquip");
	

	CEGUI::Window* backgroud = mSelfEquip->getChildRecursive("background");
	auto w = backgroud->getWidth();
	float width = 206;
	float height = 300;

	TextureProperty texProperty;
	texProperty._tex_usage = TU_DEFAULT;
	texProperty._width = width;
	texProperty._height = height;

	//texProperty._backgroudColor = color;
	texProperty._backgroudColor.a = 0.0f;

	
	{
		TexturePtr renderTexture = TextureManager::getSingleton().createManual("RenderToTexture", texProperty);

		Ogre::RenderTarget* textureTarget = renderTexture->getBuffer()->getRenderTarget(0);


	}


	auto mUICamera = new GameCamera(cam, sceneMgr);
	mUICamera->setDistance(270);

	mUICamera->update(0.0f);
	//DirectX::XMVECTORF32 mClearColor = DirectX::Colors::Gold;
	



	ImageManager::getSingleton().addRenderTarget("RenderToTexture");
	backgroud->setProperty("Image", "RenderToTexture");
}

void SimpleApp::example6()
{
	Ogre::ParticleSystem* p = mSceneManager->createParticleSystem("Smoke", "Examples/Smoke");
	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");
	SceneNode* node = root->createChildSceneNode(std::string());
	node->attachObject(p);

	mGameCamera->setDistance(500.0f);
	mGameCamera->setMoveSpeed(25.0f);
}

void SimpleApp::update(float delta)
{
	mGameCamera->update(delta);
	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}

	if (mGUIContext)
	{
		mGUIContext->injectTimePulse(delta);
	}

	Ogre::Root::getSingleton()._fireFrameStarted();
	Ogre::TextureManager::getSingleton().updateTextures();
}

EngineType SimpleApp::getEngineType()
{
	return EngineType_Vulkan;
}