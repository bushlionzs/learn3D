#pragma once 
#include <core/string/ustring.h>
#include <string>
#include <functional>
namespace Ogre
{
    class SceneManager;
};

struct Surface {
    uint32_t width = 0;
    uint32_t height = 0;
    void* renderWnd;
};
using WindowCallback = std::function<Surface(int64_t wnd)>;

struct GodotContext
{
    Ogre::SceneManager* sceneManager;
    std::string brdfTexName;
    std::string prefilteredTexName;
    std::string irradianceTexName;
    WindowCallback wndCallback;
};

void godotInit(GodotContext& context);
void godotLoop();
void loadGodotProject(const String& projectDir, GodotContext& context);


void godotProjectSetting();