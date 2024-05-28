#include "OgreHeader.h"
#include "SimpleApp.h"
#include <utils/JobSystem.h>
#include <fg/ResourceAllocator.h>
#include <VulkanPlatform.h>
#include <SwapChain.h>
#include <time_util.h>
#include "application_window.h"
#include "InputManager.h"
#include "game_camera.h"
#include <filament/RendererBase.h>
#include <filament/FView.h>
#include <filament/FTexture.h>
#include <filament/RenderTarget.h>
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
#include <engine_manager.h>
#include <CEGUIManager.h>
#include "PassUtil.h"
#include "role.h"

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
    VulkanPlatform* platform = new VulkanPlatform();
    Engine* engine = Engine::Builder()
        .platform(platform)
        .build();

	utils::JobSystem& js = engine->getJobSystem();

	js.adopt();

	new Ogre::Root(engine);
	Ogre::Root::getSingleton()._initialise();

	new EngineManager;
	EngineManager::getSingleton().initialise();

	mWindow = new ApplicationWindow;
	uint32_t width = 1280;
	uint32_t height = 768;
	mWindow->createWindow(width, height);
	if (!InputManager::getSingletonPtr())
	{
		new InputManager();
	}

	HWND wnd = mWindow->getWnd();
	InputManager::getSingletonPtr()->createInput((size_t)wnd);
 
	mSwapChain = engine->createSwapChain(wnd, filament::SwapChain::CONFIG_HAS_STENCIL_BUFFER);


	mRenderer = engine->createRenderer();

	filament::Renderer::ClearOptions options;
	options.clearColor = { 0.678431f, 0.847058f, 0.901960f, 1.000000000f };
	options.clearStencil = 1.0;
	options.clear = true;
	mRenderer->setClearOptions(options);

	mMainView = engine->createView();
	mMainView->setName("MainView");
	mMainView->setViewport({ 0, 0, width, height });

	mSceneManager = EngineManager::getSingletonPtr()->getSceneManager();

	auto camera = EngineManager::getSingletonPtr()->getMainCamera();

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

	
	example6();
	
	setup(engine);

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
		mRenderer->beginFrame(mSwapChain);

		auto passCallback = [width, height, this](FrameGraph& fg, Engine& engine, FView& view) -> FrameGraphId<FrameGraphTexture> {
				FrameGraphTexture::Descriptor colorBufferDesc = {
				.width = width,
				.height = height,
				.format = backend::TextureFormat::RGB16F
				};

				PassUtil::PassConfig config;

				std::vector<RenderTextureInfo>& textureInfos = this->getTextureInfos();

				for (auto& info : textureInfos)
				{
					config.scene = info.sm;
					config.cam = info.cam;
					config.view = info.view;


					FrameGraphTexture::Descriptor aa = colorBufferDesc;
					aa.width = info.width;
					aa.height = info.height;
					PassUtil::renderTexturePass(fg, "Texture Pass", engine, aa, config);
				}

				config.scene = Ogre::Root::getSingleton().getSceneManager(MAIN_SCENE_MANAGER);

				config.cam = config.scene->getCamera(MAIN_CAMERA);
				auto color = PassUtil::colorPass(fg, "Color Pass", engine, view, colorBufferDesc, config);

				config.scene = Ogre::Root::getSingleton().getSceneManager("cegui");

				config.cam = config.scene->getCamera("cegui_camera");;

			    //auto gui = PassUtil::guiPass(fg, "GUI Pass", engine, view, colorBufferDesc, config);

				
				return color;
			};

		mRenderer->render(mMainView, passCallback);
		mRenderer->endFrame();
		if (!UTILS_HAS_THREADING)
		{
			engine->execute();
		}

		static uint32_t lastfps = 0;
		auto fps = Ogre::Root::getSingleton().getCurrentFPS();

		if (fps != lastfps)
		{
			lastfps = fps;
			char buffer[256];
			snprintf(buffer, sizeof(buffer), "fps:%d", fps);
			::SetWindowText(mWindow->getWnd(), buffer);
		}
	}

	cleanup(engine);
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
		Ogre::Root::getSingleton().getEngine(),
		meshName,
		leftop, leftbottom, righttop, rightbottom, normal);
	Ogre::Entity* rect = mSceneManager->createEntity("rect", meshName);
	SceneNode* rectnode = root->createChildSceneNode("rect");
	rectnode->attachObject(rect);

	mSceneManager->setSkyBox(true, "SkyLan", 50000);

	auto sub = rect->getSubEntity(0);
	auto mat = sub->getMaterial();
	auto tu = mat->getTextureUnit(0);

	//tu->updateTexture(0, "RenderToTexture");
	mGameCamera->setDistance(3.0f);
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
	auto mRole = new Role(sceneMgr);
	mRole->createRoleData();
	auto rolepos = Ogre::Vector3(0.0, -100.0f, 0.0f);
	mRole->setPosition(rolepos);
	mRole->walk();

	CEGUI::Window* backgroud = mSelfEquip->getChildRecursive("background");
	auto w = backgroud->getWidth();
	float width = 206;
	float height = 300;

	TextureProperty texProperty;
	texProperty._tex_usage = TU_RENDERTARGET;
	texProperty._width = width;
	texProperty._height = height;

	//texProperty._backgroudColor = color;
	texProperty._backgroudColor.a = 0.0f;

	FEngine* engine = (FEngine*)Ogre::Root::getSingleton().getEngine();
	if (engine)
	{
		
		filament::Texture::Builder texBuilder;
		texBuilder.width(width);
		texBuilder.height(height);
		texBuilder.levels(0xff);
		texBuilder.format(backend::TextureFormat::RGBA8);
		texBuilder.usage(backend::TextureUsage::COLOR_ATTACHMENT);
		FTexture* texture = (FTexture*)texBuilder.build(*engine);
		texture->setReady(true);

		filament::Texture::Builder depthBuilder;
		depthBuilder.width(width);
		depthBuilder.height(height);
		depthBuilder.levels(0xff);
		depthBuilder.format(backend::TextureFormat::DEPTH32F_STENCIL8);
		depthBuilder.usage(backend::TextureUsage::DEPTH_ATTACHMENT | backend::TextureUsage::STENCIL_ATTACHMENT);
		FTexture* depthTexture = (FTexture*)depthBuilder.build(*engine);
		depthTexture->setReady(true);

		TextureManager::getSingleton().addTexture("RenderToTexture", texture);
	    filament::RenderTarget::Builder rtBuilder;
		rtBuilder.texture(filament::RenderTarget::AttachmentPoint::COLOR0, texture);
		rtBuilder.texture(filament::RenderTarget::AttachmentPoint::DEPTH, depthTexture);
		auto rt = rtBuilder.build(*engine);

		auto view = engine->createView();
		view->setRenderTarget((FRenderTarget*)rt);
		filament::Viewport vp(0, 0, width, height);
		view->setViewport(vp);
		mRTInfos.emplace_back();

		auto& back = mRTInfos.back();
		back.view = view;
		back.cam = cam;
		back.sm = sceneMgr;
		back.width = width;
		back.height = height;
	}
	else
	{
		TexturePtr renderTexture = TextureManager::getSingleton().createManual("RenderToTexture", texProperty);

		Ogre::RenderTarget* textureTarget = renderTexture->getBuffer()->getRenderTarget(0);

		Ogre::Viewport* rv = textureTarget->addViewport(cam);
		rv->setBackgroundColour(texProperty._backgroudColor);
	}

	
	cam->setAspectRatio(width / height);

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
