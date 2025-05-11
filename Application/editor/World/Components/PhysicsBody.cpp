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

//= INCLUDES =========================================================
#include <OgreHeader.h>
#include "PhysicsBody.h"
#include "Renderable.h"
#include "Terrain.h"
#include "Entity.h"
#include <platform_log.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionShapes/btStaticPlaneShape.h>
#include <BulletCollision/CollisionShapes/btCylinderShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/CollisionShapes/btConeShape.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <BulletCollision/CollisionShapes/btCompoundShape.h>
//====================================================================

//= NAMESPACES ===============
using namespace std;
using namespace spartan::math;
//============================

namespace spartan
{
    namespace
    {
        #define shape      static_cast<btCollisionShape*>(m_shape)
        #define rigid_body static_cast<btRigidBody*>(m_rigid_body)
        #define vehicle    static_cast<btRaycastVehicle*>(m_vehicle)

        btTransform compute_transform(const Ogre::Vector3& position, const Ogre::Quaternion& rotation)
        {
  

            // to transform
            btTransform transform;
        

            return transform;
        }

        bool can_player_fit(Entity* entity, const vector<RHI_Vertex_PosTexNorTan>& vertices, const Ogre::Vector3& scale)
        {
            return true;
        }
    }

    class MotionState : public btMotionState
    {
    public:
        MotionState(PhysicsBody* rigid_body_) { m_rigid_body = rigid_body_; }

        // engine -> bullet
        void getWorldTransform(btTransform& transform) const override
        {
            
        }

        // bullet -> engine
        void setWorldTransform(const btTransform& transform) override
        {
            
        }
    private:
        PhysicsBody* m_rigid_body;
    };

    PhysicsBody::PhysicsBody(Entity* entity) : Component(entity)
    {
        
    }

    PhysicsBody::~PhysicsBody()
    {
        OnRemove();
    }

    void PhysicsBody::OnInitialize()
    {
        Component::OnInitialize();
    }

    void PhysicsBody::OnRemove()
    {
        RemoveBodyFromWorld();

        delete static_cast<btCollisionShape*>(m_shape);
        m_shape = nullptr;
    }

    void PhysicsBody::OnStart()
    {
        Activate();
    }

    void PhysicsBody::OnTick()
    {
        
    }

    void PhysicsBody::Serialize(FileStream* stream)
    {
        
    }

    void PhysicsBody::Deserialize(FileStream* stream)
    {
       
    }

    void PhysicsBody::SetMass(float mass)
    {
        m_mass = max(mass, 0.0f);

        // if the shape doesn't exist, the physics body hasn't been initialized yet
        // so don't do anything and allow the user to set whatever properties they want
        if (shape)
        {
            UpdateShape();
        }
    }

    void PhysicsBody::SetFriction(float friction)
    {
        if (!m_rigid_body || m_friction == friction)
            return;

        m_friction = friction;
        rigid_body->setFriction(friction);
    }

    void PhysicsBody::SetFrictionRolling(float frictionRolling)
    {
        if (!m_rigid_body || m_friction_rolling == frictionRolling)
            return;

        m_friction_rolling = frictionRolling;
        rigid_body->setRollingFriction(frictionRolling);
    }

    void PhysicsBody::SetRestitution(float restitution)
    {
        if (!m_rigid_body || m_restitution == restitution)
            return;

        m_restitution = restitution;
        rigid_body->setRestitution(restitution);
    }

    void PhysicsBody::SetUseGravity(bool gravity)
    {
        if (gravity == m_use_gravity)
            return;

        m_use_gravity = gravity;
        AddBodyToWorld();
    }

    void PhysicsBody::SetGravity(const Ogre::Vector3& gravity)
    {
        if (m_gravity == gravity)
            return;

        m_gravity = gravity;
        AddBodyToWorld();
    }

    void PhysicsBody::SetIsKinematic(bool kinematic)
    {
        if (kinematic == m_is_kinematic)
            return;

        m_is_kinematic = kinematic;
        AddBodyToWorld();
    }

    void PhysicsBody::SetLinearVelocity(const Ogre::Vector3& velocity, const bool activate /*= true*/) const
    {
        if (!m_rigid_body)
            return;

        
    }

    Ogre::Vector3 PhysicsBody::GetLinearVelocity() const
    {
        if (!m_rigid_body)
            return Ogre::Vector3::ZERO;

        return Ogre::Vector3::ZERO;
    }
    
	void PhysicsBody::SetAngularVelocity(const Ogre::Vector3& velocity, const bool activate /*= true*/) const
    {
        if (!m_rigid_body)
            return;


    }

    void PhysicsBody::ApplyForce(const Ogre::Vector3& force, PhysicsForce mode) const
    {
        if (!m_rigid_body)
            return;

       
    }

    void PhysicsBody::ApplyForceAtPosition(
        const Ogre::Vector3& force, const Ogre::Vector3& position, PhysicsForce mode) const
    {
        if (!m_rigid_body)
            return;

       
    }

    void PhysicsBody::ApplyTorque(const Ogre::Vector3& torque, PhysicsForce mode) const
    {
        if (!m_rigid_body)
            return;

       
    }

    void PhysicsBody::SetPositionLock(bool lock)
    {
        SetPositionLock(lock ? Ogre::Vector3::ONE : Ogre::Vector3::ZERO);
    }

    void PhysicsBody::SetPositionLock(const Ogre::Vector3& lock)
    {
        if (!m_rigid_body || m_position_lock == lock)
            return;

        
    }

    void PhysicsBody::SetRotationLock(bool lock)
    {
        SetRotationLock(lock ? Ogre::Vector3::ONE : Ogre::Vector3::ZERO);
    }

    void PhysicsBody::SetRotationLock(const Ogre::Vector3& lock)
    {
        
    }

    void PhysicsBody::SetCenterOfMass(const Ogre::Vector3& center_of_mass)
    {
        m_center_of_mass = center_of_mass;
        SetPosition(GetPosition());
    }

    Ogre::Vector3 PhysicsBody::GetPosition() const
    {
       
        return Ogre::Vector3::ZERO;
    }

    void PhysicsBody::SetPosition(const Ogre::Vector3& position, const bool activate /*= true*/) const
    {
        if (!m_rigid_body)
            return;

        
    }

    Ogre::Quaternion PhysicsBody::GetRotation() const
    {
        return Ogre::Quaternion::IDENTITY;
    }

    void PhysicsBody::SetRotation(const Ogre::Quaternion& rotation, const bool activate /*= true*/) const
    {
        
    }

    void PhysicsBody::ClearForces() const
    {
        if (!m_rigid_body)
            return;

        rigid_body->clearForces();
    }

    void PhysicsBody::Activate() const
    {
        
    }

    void PhysicsBody::Deactivate() const
    {
        
    }

    void PhysicsBody::AddBodyToWorld()
    {
        
    }

    void PhysicsBody::RemoveBodyFromWorld()
    {
        
    }

    void PhysicsBody::SetBoundingBox(const Ogre::Vector3& bounding_box)
    {
        if (m_size == bounding_box)
            return;

        m_size   = bounding_box;
        m_size.x = clamp(m_size.x, std::numeric_limits<float>::min(), std::numeric_limits<float>::infinity());
        m_size.y = clamp(m_size.y, std::numeric_limits<float>::min(), std::numeric_limits<float>::infinity());
        m_size.z = clamp(m_size.z, std::numeric_limits<float>::min(), std::numeric_limits<float>::infinity());
    }

    void PhysicsBody::SetShapeType(PhysicsShape type, const bool replicate_hierarchy)
    {
        if (m_shape_type == type)
            return;

        m_shape_type          = type;
        m_replicate_hierarchy = replicate_hierarchy;

        UpdateShape();
    }

    void PhysicsBody::SetBodyType(const PhysicsBodyType type)
    {
        if (m_body_type == type)
            return;

        m_body_type = type;
    }
    
    bool PhysicsBody::RayTraceIsGrounded() const
    {
       

        return false;
    }

    Ogre::Vector3 PhysicsBody::RayTraceIsNearStairStep(const Ogre::Vector3& forward) const
    {
        return Ogre::Vector3::ZERO;
    }

    float PhysicsBody::GetCapsuleVolume()
	{
        btCapsuleShape* capsule_shape = static_cast<btCapsuleShape*>(m_shape);

        // get the radius of the capsule
        float radius = capsule_shape->getRadius();

        // get the height of the cylindrical part of the capsule
        // for a btCapsuleShape, the height is the distance between the centers of the end caps.
        float cylinder_height = capsule_shape->getHalfHeight() * 2.0f;

        // compute the volume of the cylindrical part
        float cylinder_volume = Ogre::Math::PI * radius * radius * cylinder_height;

        // compute the volume of the hemispherical ends
        float hemisphere_volume = (4.0f / 3.0f) * Ogre::Math::PI * std::pow(radius, 3.0f);

        // total volume is the sum of the cylinder and two hemispheres
        return cylinder_volume + hemisphere_volume;
	}

    float PhysicsBody::GetCapsuleRadius()
    {
        btCapsuleShape* capsule_shape = static_cast<btCapsuleShape*>(m_shape);

        return capsule_shape->getRadius();
    }
    
    void PhysicsBody::UpdateShape()
    {
       
    }
}
