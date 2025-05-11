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

//= INCLUDES ======================
#include "Component.h"
#include <memory>

//=================================

namespace spartan
{
    class Entity;
    class Renderable;
    class Renderer;
    class PhysicsBody;

    enum ProjectionType
    {
        Projection_Perspective,
        Projection_Orthographic,
    };

    enum CameraFlags : uint32_t
    {
        // fps camera controls
        // x-axis movement: w, a, s, d
        // y-axis movement: q, e
        // mouse look: hold right click to enable
        CanBeControlled      = 1U << 0,
        IsActivelyControlled = 1U << 1,
        WantsCursorHidden    = 1U << 2,
        IsDirty              = 1U << 3
    };

    class Camera : public Component
    {
    public:
        Camera(Entity* entity);
        ~Camera() = default;

        // component
        void OnInitialize() override;
        void OnTick() override;
        void Serialize(FileStream* stream) override;
        void Deserialize(FileStream* stream) override;

        // matrices
        const Ogre::Matrix4& GetViewMatrix() const           { return m_view; }
        const Ogre::Matrix4& GetProjectionMatrix() const     { return m_projection; }
        const Ogre::Matrix4& GetViewProjectionMatrix() const { return m_view_projection; }

        // ray casting
        const Ogre::Ray ComputePickingRay();

        // picks the nearest entity under the mouse cursor
        void Pick();

        // converts a world point to a screen point
        void WorldToScreenCoordinates(const Ogre::Vector3& position_world, Ogre::Vector2& position_screen) const;

        // converts a world bounding box to a screen rectangle
       
        Ogre::RealRect WorldToScreenCoordinates(const Ogre::OrientedBoundingBox& bounding_box) const;

        // converts a screen point to a world point. Z can be 0.0f to 1.0f and it will lerp between the near and far plane
        Ogre::Vector3 ScreenToWorldCoordinates(const Ogre::Vector2& position_screen, const float z) const;

        // aperture
        float GetAperture() const              { return m_aperture; }
        void SetAperture(const float aperture) { m_aperture = aperture; }

        // shutter speed
        float GetShutterSpeed() const                   { return m_shutter_speed; }
        void SetShutterSpeed(const float shutter_speed) { m_shutter_speed = shutter_speed; }

        // iso
        float GetIso() const         { return m_iso; }
        void SetIso(const float iso) { m_iso = iso; }

        // exposure
        float GetExposure() const
        {
            // computed ev (using squared aperture for photometric accuracy)
            float ev100 = std::log2((m_aperture * m_aperture) / m_shutter_speed * 100.0f / m_iso);

            // base exposure from ev
            float base_exposure = 1.0f / (std::pow(2.0f, ev100));

            // the base exposure is very low for bright conditions
            // so we apply an aristic bias here, to make it look right
            float exposure_bias = 600.0f;

            return base_exposure * exposure_bias;
        }

        // planes/projection
        void SetNearPlane(float near_plane);
        void SetFarPlane(float far_plane);
        void SetProjection(ProjectionType projection);
        float GetNearPlane()               const { return m_near_plane; }
        float GetFarPlane()                const { return m_far_plane; }
        ProjectionType GetProjectionType() const { return m_projection_type; }

        // fov
        float GetFovHorizontalRad() const { return m_fov_horizontal_rad; }
        float GetFovVerticalRad()   const;
        float GetFovHorizontalDeg() const;
        void SetFovHorizontalDeg(float fov);
        float GetAspectRatio() const;
  
        // frustum
        bool IsInViewFrustum(const Ogre::OrientedBoundingBox& bounding_box) const;
        bool IsInViewFrustum(std::shared_ptr<Renderable> renderable) const;

        // flags
        bool GetFlag(const CameraFlags flag) { return m_flags & flag; }
        void SetFlag(const CameraFlags flag, const bool enable = true);

        // misc
        void SetPhysicsBodyToControl(PhysicsBody* physics_body);
        bool IsWalking();
        void SetSelectedEntity(std::shared_ptr<Entity> entity) { m_selected_entity = entity; }
        std::shared_ptr<Entity> GetSelectedEntity()            { return m_selected_entity.lock(); }

        Ogre::Matrix4 ComputeViewMatrix() const;
        Ogre::Matrix4 ComputeProjection(const float near_plane, const float far_plane);
        void FocusOnSelectedEntity();

    private:
        void ComputeMatrices();
        void ProcessInput();
        void Input_FpsControl();
        void Input_LerpToEntity();

        uint32_t m_flags                             = 0;
        float m_aperture                             = 5.6f;          // aperture value in f-stop. Controls the amount of light, depth of field and chromatic aberration
        float m_shutter_speed                        = 1.0f / 125.0f; // length of time for which the camera shutter is open (sec). Also controls the amount of motion blur
        float m_iso                                  = 200.0f;        // sensitivity to light
        float m_fov_horizontal_rad = 90.0f * Ogre::Math::fDeg2Rad;
        float m_near_plane                           = 0.1f;
        float m_far_plane                            = 4000.0f;
        ProjectionType m_projection_type             = Projection_Perspective;
        Ogre::Matrix4 m_view                          = Ogre::Matrix4::IDENTITY;
        Ogre::Matrix4 m_projection                    = Ogre::Matrix4::IDENTITY;
        Ogre::Matrix4 m_projection_non_reverse_z      = Ogre::Matrix4::IDENTITY;
        Ogre::Matrix4 m_view_projection               = Ogre::Matrix4::IDENTITY;
        Ogre::Matrix4 m_view_projection_non_reverse_z = Ogre::Matrix4::IDENTITY;
        Ogre::Vector3 m_position                     = Ogre::Vector3::ZERO;
        Ogre::Quaternion m_rotation                  = Ogre::Quaternion::IDENTITY;
        Ogre::Vector2 m_mouse_last_position          = Ogre::Vector2::ZERO;
        Ogre::Vector3 m_movement_speed               = Ogre::Vector3::ZERO;
        float m_movement_scroll_accumulator          = 0.0f;
        Ogre::Vector2 m_mouse_smoothed               = Ogre::Vector2::ZERO;
        Ogre::Vector2 m_first_person_rotation        = Ogre::Vector2::ZERO;
        float m_mouse_sensitivity                    = 0.2f;
        float m_mouse_smoothing                      = 0.5f;
        bool m_lerp_to_target_p                      = false;
        bool m_lerp_to_target_r                      = false;
        float m_lerp_to_target_alpha                 = 0.0f;
        float m_lerp_to_target_distance              = 0.0f;
        Ogre::Vector3 m_lerp_to_target_position      = Ogre::Vector3::ZERO;
        Ogre::Quaternion m_lerp_to_target_rotation   = Ogre::Quaternion::IDENTITY;
        PhysicsBody* m_physics_body_to_control       = nullptr;
        Ogre::Frustum m_frustum;
        std::weak_ptr<spartan::Entity> m_selected_entity;
    };
}
