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
using namespace filament::backend;
using namespace filament;


class PassBase;
using PassCallback = std::function<void(std::vector<PassBase*>&)>;
using SetupCallback = std::function<void(RenderSystem*, Ogre::RenderWindow*, Ogre::SceneManager*, GameCamera*)>;
using CleanupCallback = std::function<void()>;
using UpdateCallback = std::function<void(float)>;

struct AppInfo
{
    SetupCallback setup;
	PassCallback pass;
	FrameGraphPassCallback  fgpass;
    CleanupCallback cleanup;
    UpdateCallback update;
};



