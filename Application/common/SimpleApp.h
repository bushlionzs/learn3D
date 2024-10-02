#pragma once
#include <functional>
#include "filament/Engine.h"
#include <DefaultWindow.h>
#include <FrameWindow.h>
#include <CEGUIManager.h>
#include <engine_struct.h>
#include <renderSystem.h>

class GameCamera;
class ApplicationWindow;
class SimpleApp: public FrameListener
{
public:
    using SetupCallback = std::function<void(RenderSystem*, Ogre::SceneManager*, GameCamera*)>;
    using CleanupCallback = std::function<void()>;
    using UpdateCallback = std::function<void(float)>;
    struct AppInfo
    {
        SetupCallback setup;
        CleanupCallback cleanup;
        UpdateCallback update;
    };
public:
    
    SimpleApp();
    ~SimpleApp();
    void run(AppInfo& info);
    virtual EngineType getEngineType();
private:
    bool frameStarted(const FrameEvent& evt);
private:
    
    void example1();
    void example2();
    void example3();
    void example4();
    void example5();
    void example6();
    void update(float delta);
    void ShowFrameFrequency();
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
    RenderSystem* mRenderSystem;

    Ogre::RenderWindow* mRenderWindow;

    AppInfo* mAppInfo;

    uint64_t mLastFPS = 0;
};