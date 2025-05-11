#include "OgreHeader.h"
#include "basic.h"
#include "renderSystem.h"
#include "OgreCamera.h"
#include "OgreRenderTarget.h"
#include "OgreRenderWindow.h"
#include "OgreSceneManager.h"

#include "OgreRoot.h"
#include "ImguiPass.h"



BasicApplication::BasicApplication()
{

}

BasicApplication::~BasicApplication()
{

}


void BasicApplication::setup(
	RenderPipeline* renderPipeline,
	RenderSystem* renderSystem,
	Ogre::RenderWindow* renderWindow,
	Ogre::SceneManager* sceneManager,
	GameCamera* gameCamera)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	ogreConfig.reverseDepth = false;
	mSceneManager = sceneManager;
	mGameCamera = gameCamera;
	mRenderWindow = renderWindow;
	mRenderSystem = renderSystem;
	mRenderPipeline = renderPipeline;

	base1();
}

void BasicApplication::update(float delta)
{

}

void BasicApplication::base1()
{
	auto imguiCallback = []()
		{
			float scale = 1.0f;
			bool show_demo_window = true;
			bool show_another_window = false;
			uint32_t counter = 0;
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
			float f = 0.5f;

			static bool displayModels = false;
			static bool displayLogos = false;
			static bool displayBackground = false;
			static bool animateLight = false;
			static float lightSpeed = 0.5f;
			static int selectedStyle = 1;
			ImGui::Begin("Example settings");
			ImGui::Checkbox("Render models", &displayModels);
			ImGui::Checkbox("Display logos", &displayLogos);
			ImGui::Checkbox("Display background", &displayBackground);
			ImGui::Checkbox("Animate light", &animateLight);
			ImGui::SliderFloat("Light speed", &lightSpeed, 0.1f, 1.0f);
			if (ImGui::Combo("UI style", &selectedStyle, "Vulkan\0Classic\0Dark\0Light\0")) {

			}
			ImGui::End();

			ImGui::ShowDemoWindow();
		};
	


	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	auto imguiPass = new ImGuiPass(input, imguiCallback);
	mRenderPipeline->addRenderPass(imguiPass);
}
