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
#include <OgreHeader.h>
#include "Camera.h"
#include "Renderable.h"
#include "SDLWindow.h"
#include "PhysicsBody.h"
#include "../Entity.h"
#include "../World.h"
#include "Renderer.h"
#include "Display.h"
//===================================

//= NAMESPACES ===============
using namespace spartan::math;
using namespace std;
//============================

namespace spartan
{
    Camera::Camera(Entity* entity) : Component(entity)
    {
        m_entity_ptr->SetPosition(Ogre::Vector3(0.0f, 3.0f, -5.0f));
        SetFlag(CameraFlags::CanBeControlled, true);
    }

    void Camera::OnInitialize()
    {
        Component::OnInitialize();
        ComputeMatrices();
    }

    void Camera::OnTick()
    {
       
    }

    void Camera::Serialize(FileStream* stream)
    {
       
    }

    void Camera::Deserialize(FileStream* stream)
    {
       
    }

    void Camera::SetNearPlane(const float near_plane)
    {
        float near_plane_limited = max(near_plane, 0.01f);

        if (m_near_plane != near_plane_limited)
        {
            m_near_plane = near_plane_limited;
            SetFlag(CameraFlags::IsDirty, true);
        }
    }

    void Camera::SetFarPlane(const float far_plane)
    {
        m_far_plane = far_plane;
        SetFlag(CameraFlags::IsDirty, true);
    }

    void Camera::SetProjection(const ProjectionType projection)
    {
        m_projection_type = projection;
        SetFlag(CameraFlags::IsDirty, true);
    }

    float Camera::GetFovHorizontalDeg() const
    {
        return m_fov_horizontal_rad * Ogre::Math::fRad2Deg;
    }

    float Camera::GetFovVerticalRad() const
    {
        return 0.0f;
    }

    void Camera::SetFovHorizontalDeg(const float fov)
    {
      
    }

    float Camera::GetAspectRatio() const
    {
        return 0.0f;
    }

   

    bool Camera::IsInViewFrustum(shared_ptr<Renderable> renderable) const
    {
        return false;
    }

    const Ogre::Ray Camera::ComputePickingRay()
    {
        return Ogre::Ray();
    }
    
    void Camera::Pick()
    {
       
    }

    void Camera::WorldToScreenCoordinates(const Ogre::Vector3& position_world, Ogre::Vector2& position_screen) const
    {
       
    }

    Ogre::RealRect Camera::WorldToScreenCoordinates(const Ogre::OrientedBoundingBox& bounding_box) const
    {
        return Ogre::RealRect();
    }

    Ogre::Vector3 Camera::ScreenToWorldCoordinates(const Ogre::Vector2& position_screen, const float z) const
    {
        return Ogre::Vector3::ZERO;
    }

    void Camera::ComputeMatrices()
    {
        if (!GetFlag(CameraFlags::IsDirty))
            return;

        m_view                          = ComputeViewMatrix();
        m_projection                    = ComputeProjection(m_far_plane, m_near_plane);
        m_projection_non_reverse_z      = ComputeProjection(m_near_plane, m_far_plane);
        m_view_projection               = m_view * m_projection;
        m_view_projection_non_reverse_z = m_view * m_projection_non_reverse_z;

        SetFlag(CameraFlags::IsDirty, false);
    }

    void Camera::ProcessInput()
    {
        if (GetFlag(CameraFlags::CanBeControlled))
        {
            Input_FpsControl();
        }

        // shortcuts
        {
            Input_LerpToEntity(); // f
        }
    }

    void Camera::Input_FpsControl()
    {
       
    }

    void Camera::Input_LerpToEntity()
    {
        
    }

    void Camera::FocusOnSelectedEntity()
    {
       
    }

    void Camera::SetFlag(const CameraFlags flag, const bool enable)
    {
        bool flag_present = m_flags & flag;

        if (enable && !flag_present)
        {
            m_flags |= static_cast<uint32_t>(flag);
        }
        else if (!enable && flag_present)
        {
            m_flags  &= ~static_cast<uint32_t>(flag);
        }
    }

    void Camera::SetPhysicsBodyToControl(PhysicsBody* physics_body)
    {
        m_physics_body_to_control = physics_body;
    }

    bool Camera::IsWalking()
    {
        return true;
    }

    Ogre::Matrix4 Camera::ComputeViewMatrix() const
    {
        return Ogre::Matrix4::IDENTITY;
    }

    Ogre::Matrix4 Camera::ComputeProjection(const float near_plane, const float far_plane)
    {
        return Ogre::Matrix4::IDENTITY;
    }
}
