#pragma once
#include <functional>
#include "filament/Engine.h"
#include "filament/FView.h"
#include <CEGUI/WindowManager.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/System.h>
//#include <CEGUI/ImagesetManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/ImageManager.h>
#include <DefaultWindow.h>
#include <FrameWindow.h>
#include <CEGUIManager.h>

class GameCamera;
class ApplicationWindow;
class SimpleApp
{
    struct RenderTextureInfo
    {
        filament::FView* view;
        Ogre::Camera* cam;
        Ogre::SceneManager* sm;
        uint32_t width;
        uint32_t height;
    };
public:
    using SetupCallback = std::function<void(filament::Engine*)>;
    using CleanupCallback = std::function<void(filament::Engine*)>;
    SimpleApp();
    ~SimpleApp();
    void run(SetupCallback setup, CleanupCallback cleanup);

    std::vector<RenderTextureInfo>& getTextureInfos()
    {
        return mRTInfos;
    }
private:
    
    void example1();
    void example2();
    void example3();
    void example4();
    void example5();
    void example6();
    void update(float delta);
private:
    filament::SwapChain* mSwapChain = nullptr;
    filament::Renderer* mRenderer = nullptr;
    ApplicationWindow* mWindow = nullptr;
    filament::View* mMainView = nullptr;
    bool mClosed = false;

    GameCamera* mGameCamera = nullptr;
    SceneManager* mSceneManager = nullptr;
    AnimationState* mAnimationState = nullptr;
    CEGUI::GUIContext* mGUIContext = nullptr;

    std::vector<RenderTextureInfo> mRTInfos;
};