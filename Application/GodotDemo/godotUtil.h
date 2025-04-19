#pragma once 
#include <core/string/ustring.h>
#include <string>
namespace Ogre
{
    class SceneManager;
};

struct GodotContext
{
    Ogre::SceneManager* sceneManager;
    std::string brdfTexName;
    std::string prefilteredTexName;
    std::string irradianceTexName;
    int64_t godotWnd;
};

void godotInit(GodotContext& context);
void godotLoop();
void loadGodotProject(const String& projectDir, GodotContext& context);


void godotProjectSetting();