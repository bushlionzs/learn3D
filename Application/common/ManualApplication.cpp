#include "OgreHeader.h"
#include "ManualApplication.h"
#include "application_window.h"
#include "InputManager.h"
#include "renderSystem.h"
#include "OgreResourceManager.h"
#include "OgreStringConverter.h"
#include "OgreMaterialManager.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"
#include "OgreRenderable.h"
#include "GameTableManager.h"
#include "OgreTextureManager.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include <ResourceParserManager.h>
#include "renderUtil.h"
#include "pass.h"
//#include "CEGUIManager.h"


ManualApplication::ManualApplication()
{
}

ManualApplication::~ManualApplication()
{

}
void ManualApplication::appInit()
{
	new Ogre::Root();
	Ogre::Root::getSingleton()._initialise();

	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	ogreConfig.width = 1600;
	ogreConfig.height = 900;
	ogreConfig.enableRaytracing = mAppInfo->enableRayTracing;

	mRenderSystem = Ogre::Root::getSingleton().createRenderEngine(mAppInfo->engineType);
	assert_invariant(mRenderSystem);

	Ogre::ResourceParserManager::getSingleton()._initialise();
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources\\cegui"), "", true);
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources\\gltf"), "", true);
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources\\ogre"), "", true);
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources\\shader"), "", true);
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources\\textures"), "", true);
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources\\forge"), "", true);
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources\\scene"), "", true);
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources\\fbx"), "", true);
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources\\obj"), "", true);
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources\\editor"), "", true);
	Ogre::ResourceManager::getSingletonPtr()->loadAllResource();

	mSceneManager = Ogre::Root::getSingleton().createSceneManger(MAIN_SCENE_MANAGER);

	mCamera = mSceneManager->createCamera(MAIN_CAMERA);

	mCamera->setNearClipDistance(1.0f);
	mGameCamera = new GameCamera(mCamera, mSceneManager);

	

	Ogre::Root::getSingleton().addFrameListener(this);

	if (isUseCEGUI())
	{
		/*ShowCursor(FALSE);
		SetCursor(NULL);*/
		//new CEGUIManager;
		//CEGUIManager::getSingleton()._initialise(mRenderWindow);
	}

	Ogre::TextureManager::getSingleton().load("white1x1.dds", nullptr);

	utils::JobSystem& js = Ogre::ResourceManager::getSingleton().getJobSystem();

	js.adopt();
}

Ogre::RenderWindow* ManualApplication::wndInit(int64_t appWnd)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	HWND wnd;
	wnd = (HWND)appWnd;

	if (!InputManager::getSingletonPtr())
	{
		new InputManager();
		InputManager::getSingletonPtr()->createInput((size_t)wnd);
		InputManager::getSingletonPtr()->addListener(mGameCamera);
	}
	

	Ogre::ColourValue color(0.678431f, 0.847058f, 0.901960f, 1.000000000f);

	RECT rt;
	::GetWindowRect(wnd, &rt);
	Ogre::CreateWindowDesc desc;
	desc.width = rt.right - rt.left;
	desc.height = rt.bottom - rt.top;
	desc.srgb = mAppInfo->useSRGB;
	std::string wndString = Ogre::StringConverter::toString((uint64_t)wnd);
	strncpy(desc.windowHandle, wndString.c_str(), sizeof(desc.windowHandle));
	Ogre::RenderWindow* renderWindow =  mRenderSystem->createRenderWindow(desc);
	if (!mRenderWindow)
	{
		mRenderWindow = renderWindow;
	}
	return renderWindow;
}

bool ManualApplication::frameStarted(const Ogre::FrameEvent& evt)
{
	InputManager::getSingletonPtr()->captureInput();
	mGameCamera->update(evt.timeSinceLastFrame);
	mAppInfo->update(evt.timeSinceLastFrame);
	for (auto pass : mPassList)
	{
		pass->update(evt.timeSinceLastFrame);
	}
	return true;
}






void ManualApplication::run(AppInfo* info)
{
	mWidth = 0;
	mHeight = 0;
	mAppInfo = info;
	mUseCEGUI = mAppInfo->useCEGUI;

	appInit();

	if (info->userRunCallback)
	{
		info->userRunCallback(mAppInfo);
	}
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	{
		uint64_t wndHandle;
		if (info->appWnd)
		{
			wndHandle = info->appWnd;
		}
		else
		{
			mApplicationWindow = new ApplicationWindow();
			mApplicationWindow->createWindow(ogreConfig.width, ogreConfig.height);
			wndHandle = (uint64_t)mApplicationWindow->getWnd();
		}
		
		wndInit(wndHandle);

		ogreConfig.reverseDepth = info->reverseDepth;
		
		mSwapChainHandle = mRenderSystem->createSwapChain(mRenderWindow);		
	}
	context.cqh = mRenderSystem->createCommandQueue(Ogre::QUEUE_TYPE_GRAPHICS, 0);
	if (mWidth != ogreConfig.width || mHeight != ogreConfig.height)
	{
		mRenderSystem->swapChainResize(context.cqh, mSwapChainHandle);
		mWidth = ogreConfig.width;
		mHeight = ogreConfig.height;
	}

	
	info->setup(context, mRenderWindow, mSceneManager, mGameCamera);
	mRenderSystem->ready();
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	


	if (info->loopback)
	{
		info->loopback();
	}
	else
	{
		loop();
	}	
}

filament::backend::Handle<filament::backend::HwCommandBuffer> ManualApplication::getCurrentCommandBuffer()
{
	return frameContextList[mImageIndex].cbh;
}

void ManualApplication::loop()
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();

	
	mFrameLast = 0;
	mFrameCurrent = 0;
	MSG msg;
	
	context.rs = Ogre::Root::getSingleton().getRenderSystem();
	context.sch = mSwapChainHandle;

	
	frameContextList.resize(3);
	for (uint32_t i = 0; i < 3; i++)
	{
		FrameContext* frameContext = &frameContextList[i];
		frameContext->cbh = mRenderSystem->createCommandBuffer(Ogre::QUEUE_TYPE_GRAPHICS);
		frameContext->fh = mRenderSystem->createFence(true);
		frameContext->sph = mRenderSystem->createSemaphore();
	}

	mRenderSystem->flushCmd(context.cqh, true);
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			if (msg.message == WM_SIZE)
			{
				int kk = 0;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			
			mRenderSystem->frameStart();
			Ogre::Root::getSingleton()._fireFrameStarted();
			Ogre::Root::getSingleton().getWorkQueue()->processMainThreadTasks();
			mRenderSystem->swapChainAcquire(context.cqh, context.sch, context.scInfo);
			mImageIndex = context.scInfo.imageIndex;
			FrameContext* frameContext = &frameContextList[context.scInfo.imageIndex];
			
			mRenderSystem->waitFence(frameContext->fh);
			context.frameContext = frameContext;

			mFrameCurrent = mTimer.getMicrosecondsCPU();
			float delta = (mFrameCurrent - mFrameLast) / 1000000.0f;

			mGameCamera->update(delta);
			mAppInfo->update(delta);
			context.delta = delta;

			for (auto pass : mPassList)
			{
				pass->update(context);
			}


			mRenderSystem->flushCmd(context.cqh, true);

			mRenderSystem->beginCommandBuffer(frameContext->cbh);

			for (auto pass : mPassList)
			{
				pass->execute(context);
			}
			
			mRenderSystem->endCommandBuffer(frameContext->cbh);
			mRenderSystem->executeAndPresent(context.cqh, nullptr, 0,
				&frameContext->cbh, 1, &frameContext->sph, 1,
				frameContext->fh, &context.sch, 1);

			ShowFrameFrequency();
		}
	}
}

void ManualApplication::loop2()
{
	mFrameLast = 0;
	mFrameCurrent = 0;
	MSG msg;
	RenderContext context;
	context.cqh = mRenderSystem->createCommandQueue(Ogre::QUEUE_TYPE_GRAPHICS, 0);
	context.sch = mSwapChainHandle; 

	std::vector<FrameContext> frameContextList;
	frameContextList.resize(3);
	for (uint32_t i = 0; i < 3; i++)
	{
		FrameContext* frameContext = &frameContextList[i];
		frameContext->cbh = mRenderSystem->createCommandBuffer(Ogre::QUEUE_TYPE_GRAPHICS);
		frameContext->fh = mRenderSystem->createFence(true);
		frameContext->sph = mRenderSystem->createSemaphore();
	}

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			Ogre::Root::getSingleton()._fireFrameStarted();
			mRenderSystem->swapChainAcquire(context.cqh, context.sch, context.scInfo);
			FrameContext* frameContext = &frameContextList[context.scInfo.imageIndex];
			mRenderSystem->waitFence(frameContext->fh);
			context.frameContext = frameContext;
			{
				mFrameCurrent = mTimer.getMicrosecondsCPU();
				float delta = (mFrameCurrent - mFrameLast) / 1000000.0f;
				InputManager::getSingletonPtr()->captureInput();
				mGameCamera->update(delta);
				mAppInfo->update(delta);
				context.delta = delta;
				
				for (auto pass : mPassList)
				{
					pass->update(context);
				}
				
				mRenderSystem->flushCmd(context.cqh, true);
				
			}
			
			mRenderSystem->beginCommandBuffer(frameContext->cbh);

			for (auto pass : mPassList)
			{
				pass->execute(context);
			}

			mRenderSystem->endCommandBuffer(frameContext->cbh);
			mRenderSystem->executeAndPresent(context.cqh, nullptr, 0, 
				&frameContext->cbh, 1, &frameContext->sph, 1,
				frameContext->fh, &context.sch, 1);

			ShowFrameFrequency();
		}
	}
}

void ManualApplication::ShowFrameFrequency()
{
	if (mLastFPS != Ogre::Root::getSingletonPtr()->getCurrentFPS())
	{
		mLastFPS = Ogre::Root::getSingletonPtr()->getCurrentFPS();


		char buffer[1024];
		std::string str = mGameCamera->getCameraString();
		snprintf(buffer, sizeof(buffer), "render:%s, fps:%lld, triangle:%d,batch:%d, %s", 
			mRenderSystem->getRenderSystemName().c_str(),
			mLastFPS, mRenderSystem->getTriangleCount(), 
			mRenderSystem->getBatchCount(),
			str.c_str());

		
		::SetWindowText(mApplicationWindow->getWnd(), buffer);
	}
}

void ManualApplication::OnSize(uint32_t width, uint32_t height)
{
	if (mRenderWindow)
	{
		auto w = mRenderWindow->getWidth();
		auto h = mRenderWindow->getHeight();
		if (w != width || h != height)
		{
			mRenderWindow->resize(width, height);
		}
	}
}

void ManualApplication::addRenderPass(PassBase* pass)
{
	mPassList.push_back(pass);
}

void updateFrameData(
	Ogre::ICamera* camera,
	FrameConstantBuffer& frameConstantBuffer,
	filament::backend::Handle<filament::backend::HwBufferObject> frameHandle)
{
	RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
	const Ogre::Matrix4& view = camera->getViewMatrix();
	const Ogre::Matrix4& proj = camera->getProjectMatrix();
	const Ogre::Vector3& camepos = camera->getDerivedPosition();
	Ogre::Matrix4 invView = view.inverse();
	Ogre::Matrix4 viewProj = proj * view;
	Ogre::Matrix4 invProj = proj.inverse();
	Ogre::Matrix4 invViewProj = viewProj.inverse();

	frameConstantBuffer.View = view.transpose();
	frameConstantBuffer.InvView = invView.transpose();
	frameConstantBuffer.Proj = proj.transpose();
	frameConstantBuffer.InvProj = invProj.transpose();
	frameConstantBuffer.ViewProj = viewProj.transpose();
	frameConstantBuffer.InvViewProj = invViewProj.transpose();

	frameConstantBuffer.EyePosW = camepos;

	
	frameConstantBuffer.Shadow = 0;
	frameConstantBuffer.directionLights[0].Direction = Ogre::Vector3(0, -1, 0.0f);
	frameConstantBuffer.directionLights[0].Direction.normalise();
	


	frameConstantBuffer.TotalTime += Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;
	frameConstantBuffer.DeltaTime = Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;

	
	rs->updateBufferObject(frameHandle,
		(const char*)&frameConstantBuffer, sizeof(frameConstantBuffer));
}
void ManualApplication::addUIPass()
{
	return;
	/*CEGUIManager* ceguiManager = CEGUIManager::getSingletonPtr();
	Ogre::Camera*  cam = ceguiManager->getCamera();
	Ogre::SceneManager* sceneManager = ceguiManager->getSceneManager();
	FrameConstantBuffer frameConstantBuffer;
	auto* rs = mRenderSystem;
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	Ogre::BufferDesc desc{};
	desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
	desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = 0;
	desc.mSize = sizeof(frameConstantBuffer);
	filament::backend::Handle<filament::backend::HwBufferObject> frameHandle =
		rs->createBufferObject(desc);

	updateFrameData(cam, frameConstantBuffer, frameHandle);

	static UserDefineShader userDefineShader;
	userDefineShader.initCallback = initFrameResource;

	userDefineShader.initCallback = initFrameResource;

	RenderableBindCallback bindCallback = [=](uint32_t frameIndex, Ogre::Renderable* r) {
		Ogre::DescriptorData descriptorData;
		for (auto i = 0; i < ogreConfig.swapBufferCount; i++)
		{
			descriptorData.mCount = 1;
			descriptorData.pName = "cbPass";
			descriptorData.ppBuffers = &frameHandle;
			FrameResourceInfo* resourceInfo = (FrameResourceInfo*)r->getFrameResourceInfo(frameIndex);
			auto* rs = Ogre::Root::getSingleton().getRenderSystem();
			rs->updateDescriptorSet(resourceInfo->zeroSet, 1, &descriptorData);
		}
		};
	userDefineShader.bindCallback = bindCallback;

	RenderableDrawCallback drawCallback = [=](uint32_t frameIndex, Ogre::Renderable* r) {
		void* frameData = r->getFrameResourceInfo(frameIndex);
		FrameResourceInfo* resourceInfo = (FrameResourceInfo*)frameData;
		Ogre::Material* mat = r->getMaterial().get();

		auto programHandle = mat->getProgram();
		auto piplineHandle = mat->getPipeline();
		filament::backend::Handle<filament::backend::HwDescriptorSet> descriptorSet[2];
		descriptorSet[0] = resourceInfo->zeroSet;
		descriptorSet[1] = resourceInfo->firstSet;
		rs->bindPipeline(piplineHandle, descriptorSet, 2);


		VertexData* vertexData = r->getVertexData();
		IndexData* indexData = r->getIndexData();
		vertexData->bind(nullptr);
		indexData->bind();
		IndexDataView* view = r->getIndexView();
		rs->drawIndexed(view->mIndexCount, 1,
			view->mIndexLocation, view->mBaseVertexLocation, 0);
		};
	userDefineShader.drawCallback = drawCallback;
	
	RenderPassCallback guiCallback = [=](RenderPassInfo& info) {		
		
		info.renderTargetCount = 1;
		info.renderTargets[0].renderTarget = mRenderWindow->getColorTarget();
		info.renderLoadAction = LOAD_ACTION_LOAD;
		info.renderStoreAction = STORE_ACTION_STORE;
		info.renderTargets[0].clearColour = { 0.0f, 0.847058f, 0.901960f, 1.000000000f };
		info.depthTarget.depthStencil = nullptr;
		auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
		const std::vector<Ogre::Renderable*>& renderList = ceguiManager->getRenderableList();
		
		renderScene(cam, renderList, info, &userDefineShader);
		};
	UpdatePassCallback updateCallback = [](float delta) {
		};
	auto guiPass = createUserDefineRenderPass(guiCallback, updateCallback);
	addRenderPass(guiPass);*/
}
