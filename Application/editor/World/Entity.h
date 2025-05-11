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

//= INCLUDES ====================
#include <atomic>
#include <array>
#include <mutex>
#include "World.h"
#include "Component.h"
//===============================

namespace spartan
{
    class FileStream;
    class Renderable;
    
    class Entity : public SpartanObject
    {
    public:
        Entity();
        ~Entity();

        void Initialize();
        std::shared_ptr<Entity> Clone();

        // core
        void OnStart(); // runs once, before the simulation ends
        void OnStop();  // runs once, after the simulation ends
        void Tick();    // runs every frame

        // io
        void Serialize(FileStream* stream);
        void Deserialize(FileStream* stream, std::shared_ptr<Entity> parent);

        // active
        bool IsActive() const;
        void SetActive(const bool active) { m_is_active = active; }

        // adds a component of type T
        template <class T>
        T* AddComponent()
        {
            const ComponentType type = Component::TypeToEnum<T>();

            // early exit if the component exists
            if (T* component = GetComponent<T>())
                return component;

            // create a new component
            std::shared_ptr<T> component = std::make_shared<T>(this);

            // save new component
            m_components[static_cast<uint32_t>(type)] = std::static_pointer_cast<Component>(component);

            // initialize component
            component->SetType(type);
            component->OnInitialize();

            World::Resolve();

            return component.get();
        }

        // adds a component of ComponentType 
        Component* AddComponent(ComponentType type);

        // returns a component of type T
        template <class T>
        T* GetComponent()
        {
            const ComponentType component_type = Component::TypeToEnum<T>();
            return static_cast<T*>(m_components[static_cast<uint32_t>(component_type)].get());
        }

        // removes a component
        template <class T>
        void RemoveComponent()
        {
            const ComponentType component_type = Component::TypeToEnum<T>();
            m_components[static_cast<uint32_t>(component_type)] = nullptr;

            World::Resolve();
        }

        void RemoveComponentById(uint64_t id);
        const auto& GetAllComponents() const { return m_components; }

        //= POSITION ======================================================================
        Ogre::Vector3 GetPosition()             const { return m_matrix.getTrans(); }
        const Ogre::Vector3& GetPositionLocal() const { return m_position_local; }
        void SetPosition(const Ogre::Vector3& position);
        void SetPositionLocal(const Ogre::Vector3& position);
        //=================================================================================

        //= ROTATION ======================================================================
        Ogre::Quaternion GetRotation()             const { return m_matrix.extractQuaternion(); }
        const Ogre::Quaternion& GetRotationLocal() const { return m_rotation_local; }
        void SetRotation(const Ogre::Quaternion& rotation);
        void SetRotationLocal(const Ogre::Quaternion& rotation);
        //=================================================================================

        //= SCALE ================================================================
        Ogre::Vector3 GetScale()             const 
        { 
            assert_invariant(false);
            return m_matrix.getTrans();
        }
        const Ogre::Vector3& GetScaleLocal() const { return m_scale_local; }
        void SetScale(const Ogre::Vector3& scale);
        void SetScaleLocal(const Ogre::Vector3& scale);
        //========================================================================

        //= TRANSLATION/ROTATION ==================
        void Translate(const Ogre::Vector3& delta);
        void Rotate(const Ogre::Quaternion& delta);
        //=========================================

        //= DIRECTIONS ================================================
        const Ogre::Vector3& GetUp() const       { return m_up; }
        const Ogre::Vector3& GetDown() const     { return m_down; }
        const Ogre::Vector3& GetForward() const  { return m_forward; }
        const Ogre::Vector3& GetBackward() const { return m_backward; }
        const Ogre::Vector3& GetRight() const    { return m_right; }
        const Ogre::Vector3& GetLeft() const     { return m_left; }
        //=============================================================

        //= HIERARCHY ===================================================================================
        void SetParent(std::weak_ptr<Entity> new_parent);
        Entity* GetChildByIndex(uint32_t index);
        Entity* GetChildByName(const std::string& name);
        void AcquireChildren();
        void RemoveChild(Entity* child, bool update_child_with_null_parent = true);
        void AddChild(Entity* child);
        bool IsDescendantOf(Entity* transform) const;
        void GetDescendants(std::vector<Entity*>* descendants);
        Entity* GetDescendantByName(const std::string& name);
        bool HasParent() const                    { return !m_parent.expired(); }
        bool HasChildren() const                  { return GetChildrenCount() > 0 ? true : false; }
        uint32_t GetChildrenCount() const         { return static_cast<uint32_t>(m_children.size()); }
        Entity* GetRoot()                         { return HasParent() ? GetParent()->GetRoot() : this; }
        std::shared_ptr<Entity> GetParent() const { return m_parent.lock(); }
        std::vector<Entity*>& GetChildren()       { return m_children; }
        //===============================================================================================

        const Ogre::Matrix4& GetMatrix() const              { return m_matrix; }
        const Ogre::Matrix4& GetLocalMatrix() const         { return m_matrix_local; }
        const Ogre::Matrix4& GetMatrixPrevious() const      { return m_matrix_previous; }
        void SetMatrixPrevious(const Ogre::Matrix4& matrix) { m_matrix_previous = matrix; }
        float GetTimeSinceLastTransform() const            { return m_time_since_last_transform_sec; }

    private:
        std::atomic<bool> m_is_active = true;
        std::array<std::shared_ptr<Component>, 13> m_components;

        void UpdateTransform();
        Ogre::Matrix4 GetParentTransformMatrix() const;

        // local
        Ogre::Vector3 m_position_local    = Ogre::Vector3::ZERO;
        Ogre::Quaternion m_rotation_local = Ogre::Quaternion::IDENTITY;
        Ogre::Vector3 m_scale_local       = Ogre::Vector3::UNIT_SCALE;

        Ogre::Matrix4 m_matrix          = Ogre::Matrix4::IDENTITY;
        Ogre::Matrix4 m_matrix_previous = Ogre::Matrix4::IDENTITY;
        Ogre::Matrix4 m_matrix_local    = Ogre::Matrix4::IDENTITY;

        // computed during UpdateTransform() and cached for performance
        Ogre::Vector3 m_forward  = Ogre::Vector3::ZERO;
        Ogre::Vector3 m_backward = Ogre::Vector3::ZERO;
        Ogre::Vector3 m_up       = Ogre::Vector3::ZERO;
        Ogre::Vector3 m_down = Ogre::Vector3::ZERO;
        Ogre::Vector3 m_right    = Ogre::Vector3::ZERO;
        Ogre::Vector3 m_left     = Ogre::Vector3::ZERO;

        std::weak_ptr<Entity> m_parent;  // the parent of this entity
        std::vector<Entity*> m_children; // the children of this entity

        // misc
        std::mutex m_mutex_children;
        std::mutex m_mutex_parent;
        float m_time_since_last_transform_sec = 0.0f;
    };
}
