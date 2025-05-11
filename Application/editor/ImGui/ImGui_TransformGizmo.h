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

//= INCLUDES =========================
#include "Source/ImGuizmo/ImGuizmo.h"
#include "Source/imgui.h"
#include "World/Entity.h"
#include "World/Components/Camera.h"
#include "Renderer.h"
#include "Engine.h"
//====================================

namespace ImGui::TransformGizmo
{
    const  Ogre::Vector3 snap = Ogre::Vector3(0.1f, 0.1f, 0.1f);

    bool first_use = true;
    Ogre::Vector3 position_previous;
    Ogre::Quaternion rotation_previous;
    Ogre::Vector3 scale_previous;

    void apply_style()
    {
        const ImVec4 inspector_color_x = ImVec4(0.75f, 0.20f, 0.20f, 0.80f);
        const ImVec4 inspector_color_y = ImVec4(0.20f, 0.75f, 0.20f, 0.80f);
        const ImVec4 inspector_color_z = ImVec4(0.20f, 0.20f, 0.75f, 0.80f);

        ImGuizmo::Style& style                            = ImGuizmo::GetStyle();
        style.Colors[ImGuizmo::COLOR::DIRECTION_X]        = ImVec4(inspector_color_x.x, inspector_color_x.y, inspector_color_x.z, 1.0f);
        style.Colors[ImGuizmo::COLOR::DIRECTION_Y]        = ImVec4(inspector_color_y.x, inspector_color_y.y, inspector_color_y.z, 1.0f);
        style.Colors[ImGuizmo::COLOR::DIRECTION_Z]        = ImVec4(inspector_color_z.x, inspector_color_z.y, inspector_color_z.z, 1.0f);
        style.Colors[ImGuizmo::COLOR::PLANE_X]            = inspector_color_x;
        style.Colors[ImGuizmo::COLOR::PLANE_Y]            = inspector_color_y;
        style.Colors[ImGuizmo::COLOR::PLANE_Z]            = inspector_color_z;
        style.Colors[ImGuizmo::COLOR::HATCHED_AXIS_LINES] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

        style.CenterCircleSize           = 5.0f;
        style.TranslationLineThickness   = 4.0f;
        style.TranslationLineArrowSize   = 6.0f;
        style.RotationLineThickness      = 3.0f;
        style.RotationOuterLineThickness = 2.0f;
        style.ScaleLineThickness         = 4.0f;
        style.ScaleLineCircleSize        = 7.0f;
    }

    static void tick()
    {
        assert_invariant(false);
    }

    static bool allow_picking()
    {
        return !ImGuizmo::IsOver() && !ImGuizmo::IsUsing();
    }
}
