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

//= INCLUDES ========================
#include "ShaderEditor.h"
#include <fstream>
#include "../ImGui/ImGui_Extension.h"
//===================================

//= NAMESPACES =========
using namespace std;
using namespace spartan;
//======================

namespace
{
    const float source_pane_vertical_split_percentage = 0.7f;
    const float source_pane_bottom_margin             = 30.0f;
}

ShaderEditor::ShaderEditor(Editor* editor) : Widget(editor)
{
    m_title            = "Shader Editor";
    m_flags           |= ImGuiWindowFlags_NoScrollbar;
    m_visible          = false;
    m_size_initial     = ImVec2(1366, 1000);
    m_alpha            = 1.0f;
    m_index_displayed  = -1;
}

void ShaderEditor::OnTickVisible()
{
    ShowShaderSource();
    ImGui::SameLine();
    ShowShaderList();
    ShowControls();
}

void ShaderEditor::ShowShaderSource()
{
    
}

void ShaderEditor::ShowShaderList()
{
    
}

void ShaderEditor::ShowControls()
{
    
}

void ShaderEditor::GetShaderInstances()
{
   }
