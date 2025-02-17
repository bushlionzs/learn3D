#pragma once 
#include <core/string/ustring.h>
struct GodotContext
{
    Ogre::SceneManager* sceneManager;
    std::string brdfTexName;
    std::string prefilteredTexName;
    std::string irradianceTexName;
};

void loadGodotProject(const String& projectDir, GodotContext& context);