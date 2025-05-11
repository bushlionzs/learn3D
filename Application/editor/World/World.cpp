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

//= INCLUDES =======================
#include <OgreHeader.h>
#include "World.h"
#include "Entity.h"
#include "../Profiling/Profiler.h"
#include "Components/Renderable.h"
#include "Components/Camera.h"
#include "Components/Light.h"
#include "Components/AudioSource.h"
#include "ProgressTracker.h"
//==================================

//= NAMESPACES ===============
using namespace std;

//============================

namespace spartan
{
    namespace
    {
        vector<shared_ptr<Entity>> entities;
        vector<shared_ptr<Entity>> entities_lights; // entities subset that contains only lights
        string name;
        string file_path;
        mutex entity_access_mutex;
        bool resolve                = false;
        bool was_in_editor_mode     = false;
        Ogre::OrientedBoundingBox;
        shared_ptr<Entity> camera   = nullptr;
        shared_ptr<Entity> light    = nullptr;
        uint32_t audio_source_count = 0;

        void compute_bounding_box()
        {
            for (shared_ptr<Entity>& entity : entities)
            {
                if (entity->IsActive())
                {
                    if (Renderable* renderable = entity->GetComponent<Renderable>())
                    {
                        
                    }
                }
            }
        }
    }

    namespace day_night_cycle
    {
        float current_time = 0.25f;  // start at 6 am
        float time_scale   = 200.0f; // 200x real time

        void tick()
        {
            
        }
    }

    void World::Initialize()
    {

    }

    void World::Shutdown()
    {
       
    }

    void World::Tick()
    {
        // loading can happen in the background
       
    }

    void World::Clear()
    {
       
    }

    bool World::SaveToFile(const string& file_path_in)
    {
        

        return true;
    }

    bool World::LoadFromFile(const string& file_path_)
    {
        

        return true;
    }

    void World::Resolve()
    {
        resolve = true;
    }

    shared_ptr<Entity> World::CreateEntity()
    {
        lock_guard lock(entity_access_mutex);

        shared_ptr<Entity> entity = make_shared<Entity>();
        entity->Initialize();
        entities.push_back(entity);

        return entity;
    }

    bool World::EntityExists(Entity* entity)
    {
        assert_invariant(entity != nullptr);
        return GetEntityById(entity->GetObjectId()) != nullptr;
    }

    void World::RemoveEntity(Entity* entity_to_remove)
    {
        assert_invariant(entity_to_remove != nullptr);

        lock_guard<mutex> lock(entity_access_mutex);

        // remove the entity and all of its children
        {
            // get the root entity and its descendants
            vector<Entity*> entities_to_remove;
            entities_to_remove.push_back(entity_to_remove);        // add the root entity
            entity_to_remove->GetDescendants(&entities_to_remove); // get descendants

            // create a set containing the object ids of entities to remove
            set<uint64_t> ids_to_remove;
            for (Entity* entity : entities_to_remove)
            {
                ids_to_remove.insert(entity->GetObjectId());
            }

            // remove entities using a single loop
            for (auto it = entities.begin(); it != entities.end(); )
            {
                if (ids_to_remove.count((*it)->GetObjectId()) > 0)
                {
                    it = entities.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            // if there was a parent, update it
            if (shared_ptr<Entity> parent = entity_to_remove->GetParent())
            {
                parent->AcquireChildren();
            }
        }

        resolve      = true;

    }

    vector<shared_ptr<Entity>> World::GetRootEntities()
    {
        lock_guard<mutex> lock(entity_access_mutex);

        vector<shared_ptr<Entity>> root_entities;

        for (shared_ptr<Entity>& entity : entities)
        {
            if (!entity->HasParent())
            {
                root_entities.emplace_back(entity);
            }
        }

        return root_entities;
    }

    const shared_ptr<Entity>& World::GetEntityById(const uint64_t id)
    {
        lock_guard<mutex> lock(entity_access_mutex);
    
        for (const auto& entity : entities)
        {
            if (entity && entity->GetObjectId() == id)
                return entity;
        }
    
        static shared_ptr<Entity> empty;
        return empty;
    }
    
    const vector<shared_ptr<Entity>>& World::GetEntities()
    {
        return entities;
    }

    const vector<shared_ptr<Entity>>& World::GetEntitiesLights()
    {
        return entities_lights;
    }

    const string World::GetName()
    {
        return name;
    }

    const string& World::GetFilePath()
    {
        return file_path;
    }

    Ogre::OrientedBoundingBox& World::GetBoundingBox()
    {
        static Ogre::OrientedBoundingBox bounding_box;

        return bounding_box;
    }

    Camera* World::GetCamera()
    {
        return camera ? camera->GetComponent<Camera>() : nullptr;
    }

    Light* World::GetDirectionalLight()
    {
        return light ? light->GetComponent<Light>() : nullptr;
    }

    uint32_t World::GetLightCount()
    {
        return static_cast<uint32_t>(entities_lights.size());
    }

    uint32_t World::GetAudioSourceCount()
    {
        return audio_source_count;
    }

    bool World::IsLoading()
    {
        return ProgressTracker::IsLoading();
    }

    float World::GetTimeOfDay()
    {
        return day_night_cycle::current_time;
    }
}
