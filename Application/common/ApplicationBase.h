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

struct BasicPass
{
	Ogre::RenderTarget* color = nullptr;
	Ogre::RenderTarget* depth = nullptr;
	SceneManager* sceneMgr = nullptr;
	Ogre::ICamera* cam = nullptr;
	Ogre::OgreTexture* shadowMap = nullptr;
	bool shadowPass = false;
};

using PassCallback = std::function<void(std::vector<BasicPass>&)>;
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



