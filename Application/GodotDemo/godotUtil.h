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
};

void godotInit();

void loadGodotProject(const String& projectDir, GodotContext& context);

void godotProjectSetting();