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

//= INCLUDES =============================
#include <OgreHeader.h>
#include "EditorViewport.h"
#include "AssetBrowser.h"
#include "WorldViewer.h"
#include "../ImGui/ImGui_Extension.h"
#include "../ImGui/ImGui_TransformGizmo.h"
#include "Settings.h"
#include "OgreTextureManager.h"
//========================================

//= NAMESPACES =========
using namespace std;
using namespace spartan;
//======================

namespace
{
    bool first_frame         = true;
    uint32_t width_previous  = 0;
    uint32_t height_previous = 0;
}

EditorViewport::EditorViewport(Editor* editor) : Widget(editor)
{
    m_title         = "Viewport";
    m_size_initial  = Ogre::Vector2(400, 250);
    m_flags        |= ImGuiWindowFlags_NoScrollbar;
    m_padding       = Ogre::Vector2(2.0f);

    mEditorTarget = Ogre::TextureManager::getSingleton().load("bricks.dds", nullptr);
}

void EditorViewport::OnTickVisible()
{
    uint32_t width = static_cast<uint32_t>(ImGui::GetContentRegionAvail().x);
    uint32_t height = static_cast<uint32_t>(ImGui::GetContentRegionAvail().y);
    ImGuiSp::image(mEditorTarget.get(), ImVec2(static_cast<float>(width), static_cast<float>(height)));
}
