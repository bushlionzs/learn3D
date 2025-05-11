/*
Copyright(c) 2016-2025 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//= INCLUDES ======================
#include <OgreHeader.h>
#include <OgreResourceManager.h>
#include <OgreTextureManager.h>
#include "IconLoader.h"
#include "ThreadPool.h"

//=================================

//= NAMESPACES =========
using namespace std;
//======================

namespace
{
    vector<shared_ptr<Icon>> icons;
    Icon no_icon;
    mutex icon_mutex;

    void destroy_rhi_resources()
    {
        icons.clear();
    }

    Icon* get_icon_by_type(IconType type)
    {
        for (auto& icon : icons)
        {
            if (icon->GetType() == type)
                return icon.get();
        }

        return &no_icon;
    }
}

Icon::Icon(IconType type, const string& file_path)
{
    m_type = type;

    m_texture = Ogre::TextureManager::getSingleton().load(file_path, nullptr, false);
    
    m_texture->loadAsync();
}

Ogre::OgreTexture* Icon::GetTexture() const
{
    if (m_texture)
    {
        return m_texture.get();
    }

    return nullptr;
}

void Icon::SetTexture(shared_ptr<Ogre::OgreTexture> texture)
{
    m_texture = texture;
}

string Icon::GetFilePath() const
{
    if (!m_texture)
        return "";
    const String& name = m_texture->getName();
    ResourceInfo* resInfo = Ogre::ResourceManager::getSingleton().getResourceInfo(name);
    return resInfo->_fullname;
}

void IconLoader::Initialize()
{
    IconLoader::LoadFromFile("component_audioListener.png"         , IconType::Component_AudioListener);
    IconLoader::LoadFromFile("component_audioSource.png"           , IconType::Component_AudioSource);
    IconLoader::LoadFromFile("component_camera.png"                , IconType::Component_Camera);
    IconLoader::LoadFromFile("component_light.png"                 , IconType::Component_Light);
    IconLoader::LoadFromFile("component_material.png"              , IconType::Component_Material);
    IconLoader::LoadFromFile("component_material_removeTexture.png", IconType::Component_Material_RemoveTexture);
    IconLoader::LoadFromFile("component_meshCollider.png"          , IconType::Component_MeshCollider);
    IconLoader::LoadFromFile("component_renderable.png"            , IconType::Component_Renderable);
    IconLoader::LoadFromFile("component_rigidBody.png"             , IconType::Component_PhysicsBody);
    IconLoader::LoadFromFile("component_softBody.png"              , IconType::Component_SoftBody);
    IconLoader::LoadFromFile("component_transform.png"             , IconType::Component_Transform);
    IconLoader::LoadFromFile("component_terrain.png"               , IconType::Component_Terrain);
    IconLoader::LoadFromFile("component_environment.png"           , IconType::Component_Environment);
    IconLoader::LoadFromFile("console.png"                         , IconType::Console);
    IconLoader::LoadFromFile("file.png"                            , IconType::Directory_File_Default);
    IconLoader::LoadFromFile("folder.png"                          , IconType::Directory_Folder);
    IconLoader::LoadFromFile("audio.png"                           , IconType::Directory_File_Audio);
    IconLoader::LoadFromFile("model.png"                           , IconType::Directory_File_Model);
    IconLoader::LoadFromFile("world.png"                           , IconType::Directory_File_World);
    IconLoader::LoadFromFile("material.png"                        , IconType::Directory_File_Material);
    IconLoader::LoadFromFile("shader.png"                          , IconType::Directory_File_Shader);
    IconLoader::LoadFromFile("xml.png"                             , IconType::Directory_File_Xml);
    IconLoader::LoadFromFile("dll.png"                             , IconType::Directory_File_Dll);
    IconLoader::LoadFromFile("txt.png"                             , IconType::Directory_File_Txt);
    IconLoader::LoadFromFile("ini.png"                             , IconType::Directory_File_Ini);
    IconLoader::LoadFromFile("exe.png"                             , IconType::Directory_File_Exe);
    IconLoader::LoadFromFile("font.png"                            , IconType::Directory_File_Font);
    IconLoader::LoadFromFile("screenshot.png"                      , IconType::Screenshot);
    IconLoader::LoadFromFile("settings.png"                        , IconType::Component_Options);
    IconLoader::LoadFromFile("play.png"                            , IconType::Button_Play);
    IconLoader::LoadFromFile("timer.png"                           , IconType::Button_Profiler);
    IconLoader::LoadFromFile("resource_viewer.png"                 , IconType::Button_ResourceCache);
    IconLoader::LoadFromFile("capture.png"                         , IconType::Button_RenderDoc);
    IconLoader::LoadFromFile("code.png"                            , IconType::Button_Shader);
    IconLoader::LoadFromFile("texture.png"                         , IconType::Directory_File_Texture);
    IconLoader::LoadFromFile("window_minimise.png"                 , IconType::Window_Minimize);
    IconLoader::LoadFromFile("window_maximise.png"                 , IconType::Window_Maximize);
    IconLoader::LoadFromFile("window_close.png"                    , IconType::Window_Close);
}

Ogre::OgreTexture* IconLoader::GetTextureByType(IconType type)
{
    return LoadFromFile("", type)->GetTexture();
}

Icon* IconLoader::LoadFromFile(const string& file_path, IconType type /*Undefined*/)
{
    // check if the texture is already loaded, and return that
    bool search_by_type = type != IconType::Undefined;
    for (auto& icon : icons)
    {
        if (search_by_type)
        {
            if (icon->GetType() == type)
                return icon.get();
        }
        else if (icon->GetFilePath() == file_path)
        {
            return icon.get();
        }
    }

    // the texture is new so load it
    {
        lock_guard<mutex> guard(icon_mutex);

        // add a new icon
        icons.push_back(make_shared<Icon>(type, file_path));
        return icons.back().get();
    }
        
    return get_icon_by_type(IconType::Directory_File_Default);
}
