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

#pragma once

//= INCLUDES ==============
#include <vector>
#include <memory>
#include "Widgets/Widget.h"
#include <OgreHeader.h>
#include <ApplicationBase.h>
#include "pass.h"
//=========================

class Editor
{
public:
    struct ImGuiFrameData
    {
        filament::backend::Handle<filament::backend::HwDescriptorSet> descriptorSet;
        filament::backend::Handle<filament::backend::HwBufferObject> cbPassHandle;
    };
    Editor(const std::vector<std::string>& args);
    ~Editor();
    void EditorInit(AppInfo* info);
    void setup(RenderPipeline* renderPipeline,
        RenderSystem* renderSystem,
        Ogre::RenderWindow* renderWindow,
        Ogre::SceneManager* sceneManager,
        GameCamera* gameCamera);
    void update(float delta);
    void tick();

    void logic();
    template<typename T>
    T* GetWidget()
    {
        for (const auto& widget : m_widgets)
        {
            if (T* widget_t = dynamic_cast<T*>(widget.get()))
            {
                return widget_t;
            }
        }

        return nullptr;
    }

    inline static ImFont* font_normal = nullptr;
    inline static ImFont* font_bold   = nullptr;

private:
    
    void BeginWindow();

    Ogre::RenderWindow* renderWindow;

    std::vector<std::shared_ptr<Widget>> m_widgets;

    uint32_t mWidth;
    uint32_t mHeight;

    uint32_t mVertexCount = 0;
    uint32_t mIndexCount = 0;

    filament::backend::Handle<filament::backend::HwProgram> mProgramHandle;
    filament::backend::Handle<filament::backend::HwPipeline> mPipelineHandle;
    filament::backend::Handle<filament::backend::HwDescriptorSet> mDescriptorSet[2];

    filament::backend::Handle<filament::backend::HwBufferObject> mVertexBufferHandle;
    filament::backend::Handle<filament::backend::HwBufferObject> mIndexBufferHandle;

    std::vector<ImGuiFrameData> mFrameDataList;


    Ogre::OgreTexture* mFontTexture;

};
