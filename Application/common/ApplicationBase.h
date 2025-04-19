#pragma once
#include <functional>
#include <filament/Engine.h>
#include <fg/FrameGraphTexture.h>
#include <fg/FrameGraphId.h>
#include <fg/FrameGraph.h>
#include <renderSystem.h>
class GameCamera;
class RenderSystem;
namespace Ogre
{
    class RenderWindow;
    class SceneManager;
}



class PassBase;
struct AppInfo;
using PreInitCallback = std::function<void(AppInfo* appInfo)>;
using SetupCallback = std::function<void(RenderSystem*, Ogre::RenderWindow*, Ogre::SceneManager*, GameCamera*)>;
using CleanupCallback = std::function<void()>;
using UpdateCallback = std::function<void(float)>;
using LoopCallback = std::function<void()>;
struct AppInfo
{
    PreInitCallback preInit = nullptr;
    SetupCallback setup = nullptr;
    CleanupCallback cleanup = nullptr;
    UpdateCallback update = nullptr;
    LoopCallback loopback = nullptr;
    EngineType engineType = EngineType_Vulkan;
    bool enableRayTracing = false;
    bool useCEGUI = false;
    bool useSRGB = false;
    int64_t appWnd = 0;
};



