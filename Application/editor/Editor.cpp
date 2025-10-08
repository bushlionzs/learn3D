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

//= INCLUDES ====================================
#include "Editor.h"
#include "GeneralWindows.h"
#include "MenuBar.h"
#include "Settings.h"
#include "ImGui/ImGui_Extension.h"
#include "Widgets/AssetBrowser.h"
#include "Widgets/Console.h"
#include "Widgets/Style.h"
#include "Widgets/ProgressDialog.h"
#include "Widgets/Properties.h"
#include "Widgets/EditorViewport.h"
#include "Widgets/WorldViewer.h"
#include "Widgets/ShaderEditor.h"
#include "Widgets/ResourceViewer.h"
#include "Widgets/Profiler.h"
#include "Widgets/TextureViewer.h"
#include "Widgets/RenderOptions.h"
#include "OgreResourceManager.h"
#include "ResourceParserManager.h"
#include "OgreStringConverter.h"
#include "OgreVertexDeclaration.h"
#include <OgreRenderWindow.h>
#include "Profiling/Profiler.h"
#include "game_camera.h"
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include "ImguiPass.h"
#include <windows.h>
//===============================================

//= NAMESPACES =====
using namespace std;
//==================

namespace
{
    float font_size      = 18.0f;
    float font_scale     = 1.0f;
    Widget* widget_world = nullptr;

    void process_event()
    {

    }
}

Editor::Editor(const vector<string>& args)
{
    
}

Editor::~Editor()
{
    if (ImGui::GetCurrentContext())
    {
        ImGui::DestroyContext();
    }


}

void Editor::setup(RenderPipeline* renderPipeline,
    RenderContext& context,
    Ogre::RenderWindow* renderWindow,
    Ogre::SceneManager* sceneManager,
    GameCamera* gameCamera)
{
    GeneralWindows::Initialize(this);

    spartan::Profiler::Initialize();

    auto imguiCallback = [this]()
        {
            logic();
        };
    RenderPassInput input;
    input.color = renderWindow->getColorTarget();
    input.depth = renderWindow->getDepthTarget();
    input.cam = gameCamera->getCamera();
    input.sceneMgr = sceneManager;
    auto imguiPass = new ImGuiPass(input, imguiCallback);
    renderPipeline->addRenderPass(imguiPass);


    IconLoader::Initialize();

    // create all imgui widgets
    m_widgets.emplace_back(make_shared<Style>(this));
    m_widgets.emplace_back(make_shared<ProgressDialog>(this));
    m_widgets.emplace_back(make_shared<Console>(this));
    m_widgets.emplace_back(make_shared<Profiler>(this));
    m_widgets.emplace_back(make_shared<ResourceViewer>(this));
    m_widgets.emplace_back(make_shared<ShaderEditor>(this));
    m_widgets.emplace_back(make_shared<RenderOptions>(this));
    m_widgets.emplace_back(make_shared<TextureViewer>(this));
    m_widgets.emplace_back(make_shared<EditorViewport>(this));
    m_widgets.emplace_back(make_shared<AssetBrowser>(this));
    m_widgets.emplace_back(make_shared<Properties>(this));
    m_widgets.emplace_back(make_shared<WorldViewer>(this));
    widget_world = m_widgets.back().get();
    MenuBar::Initialize(this);
}

void Editor::logic()
{
    BeginWindow();

    for (shared_ptr<Widget>& widget : m_widgets)
    {
        widget->Tick();
    }
    MenuBar::Tick();

    ImGui::End();

    // various windows that don't belong to a certain widget
    GeneralWindows::Tick();

    
}

void Editor::update(float delta)
{

}

void Editor::tick()
{
    
}

void Editor::EditorInit(AppInfo* info)
{
    spartan::Window::Initialize();
    spartan::Display::Initialize();
    uint64_t wndHandle = (uint64_t)spartan::Window::GetHandleRaw();

    info->appWnd = wndHandle;

}


void Editor::BeginWindow()
{
    const auto window_flags =
        ImGuiWindowFlags_MenuBar               |
        ImGuiWindowFlags_NoDocking             |
        ImGuiWindowFlags_NoTitleBar            |
        ImGuiWindowFlags_NoCollapse            |
        ImGuiWindowFlags_NoResize              |
        ImGuiWindowFlags_NoMove                |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;
    
    // set window position and size - this keeps the MenuBar in the right place and at the right size
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y));

    // set window style
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding,   0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,    ImVec2(0.0f, 0.0f));
    
    // begin window
    std::string name = "##main_window";
    bool open = true;
    ImGui::Begin(name.c_str(), &open, window_flags);
    ImGui::PopStyleVar(3);
    
    // begin dock space
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        // dock space
        const auto window_id = ImGui::GetID(name.c_str());
        if (!ImGui::DockBuilderGetNode(window_id))
        {
            // reset current docking state
            ImGui::DockBuilderRemoveNode(window_id);
            ImGui::DockBuilderAddNode(window_id, ImGuiDockNodeFlags_None);
            ImGui::DockBuilderSetNodeSize(window_id, ImGui::GetMainViewport()->Size);
    
            // dockBuilderSplitNode(ImGuiID node_id, ImGuiDir split_dir, float size_ratio_for_node_at_dir, ImGuiID* out_id_dir, ImGuiID* out_id_other);
            ImGuiID dock_main_id       = window_id;
            ImGuiID dock_right_id      = ImGui::DockBuilderSplitNode(dock_main_id,  ImGuiDir_Right, 0.17f, nullptr, &dock_main_id);
            ImGuiID dock_right_down_id = ImGui::DockBuilderSplitNode(dock_right_id, ImGuiDir_Down,  0.6f,  nullptr, &dock_right_id);
            ImGuiID dock_down_id       = ImGui::DockBuilderSplitNode(dock_main_id,  ImGuiDir_Down,  0.22f, nullptr, &dock_main_id);
            ImGuiID dock_down_right_id = ImGui::DockBuilderSplitNode(dock_down_id,  ImGuiDir_Right, 0.3f,  nullptr, &dock_down_id);
    
            // dock windows
            ImGui::DockBuilderDockWindow("World",      dock_right_id);
            ImGui::DockBuilderDockWindow("Properties", dock_right_down_id);
            ImGui::DockBuilderDockWindow("Console",    dock_down_id);
            ImGui::DockBuilderDockWindow("Assets",     dock_down_right_id);
            ImGui::DockBuilderDockWindow("Viewport",   dock_main_id);
    
            ImGui::DockBuilderFinish(dock_main_id);
        }
    
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
        ImGui::DockSpace(window_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::PopStyleVar();
    }
}

