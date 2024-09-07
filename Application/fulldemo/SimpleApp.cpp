#include "OgreHeader.h"
#include "SimpleApp.h"
#include <utils/JobSystem.h>
#include <fg/ResourceAllocator.h>
#include <vulkan/VulkanPlatform.h>
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
#include "GameWorld.h"

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

	mWindow = new ApplicationWindow(nullptr);
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

	
	loadResource();
	
	setup(engine);

	uint32_t fps = 0;

	uint32_t last_time = get_tick_count();
	Timer mTimer;

	auto last = mTimer.getMicrosecondsCPU();
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
		auto current = mTimer.getMicrosecondsCPU();
		float delta = (current - last) / 1000000.0f;
		last = current;
		
		update(delta);
		
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
		
		fps++;

		uint32_t this_time = get_tick_count();

		if (this_time >= last_time + 1000)
		{
			char buffer[128];
			snprintf(buffer, sizeof(buffer), "fps:%d", fps);
			::SetWindowText(wnd, buffer);
			last_time = this_time;
			fps = 0;
		}
	}

	cleanup(engine);
}

void SimpleApp::loadResource()
{
	mGameCamera->getCamera()->setNearClipDistance(100.0f);
	mGameWorld = new GameWorld(mGameCamera);
	mGameWorld->gameWorldInit();
}

void SimpleApp::update(float delta)
{
	mGameCamera->update(delta);
	mGameWorld->update(delta);

	if (mGUIContext)
	{
		mGUIContext->injectTimePulse(delta);
	}
	
	Ogre::Root::getSingleton()._fireFrameStarted();
	Ogre::TextureManager::getSingleton().updateTextures();
}
