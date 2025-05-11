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

//= INCLUDES ============================
#include <OgreHeader.h>
#include "Renderable.h"
#include "Camera.h"
#include "../Entity.h"

//=======================================

//= NAMESPACES ===============
using namespace std;

//============================

namespace spartan
{
    namespace grid_partitioning
    {
        // this namespace organizes 3D objects into a grid layout, grouping instances into grid cells
        // it enables optimized rendering by allowing culling of non-visible chunks
    
        const uint32_t cell_size = 64; // meters
    
        struct GridKey
        {
            int32_t x, y, z;
        
            bool operator==(const GridKey& other) const
            {
                return x == other.x && y == other.y && z == other.z;
            }
        };
    
        struct GridKeyHash
        {
            size_t operator()(const GridKey& k) const
            {
                size_t result = 0;
                uint32_t ux = static_cast<uint32_t>(k.x);
                uint32_t uy = static_cast<uint32_t>(k.y);
                uint32_t uz = static_cast<uint32_t>(k.z);
                for (uint32_t i = 0; i < (sizeof(uint32_t) * 8); i++)
                {
                    result |= ((ux & (1u << i)) << (2 * i)) |
                              ((uy & (1u << i)) << (2 * i + 1)) |
                              ((uz & (1u << i)) << (2 * i + 2));
                }
                return result;
            }
    
            static GridKey get_key(const Ogre::Vector3& position)
            {
                return
                {
                    static_cast<int32_t>(floor(position.x / static_cast<float>(cell_size))),
                    static_cast<int32_t>(floor(position.y / static_cast<float>(cell_size))),
                    static_cast<int32_t>(floor(position.z / static_cast<float>(cell_size)))
                };
            }
        };
    
       
    }

    Renderable::Renderable(Entity* entity) : Component(entity)
    {
        SP_REGISTER_ATTRIBUTE_VALUE_VALUE(m_material_default, bool);
        SP_REGISTER_ATTRIBUTE_VALUE_VALUE(m_material,         Material*);
        SP_REGISTER_ATTRIBUTE_VALUE_VALUE(m_flags,            uint32_t);
        SP_REGISTER_ATTRIBUTE_VALUE_VALUE(m_mesh,             Mesh*);

    }

    Renderable::~Renderable()
    {
        m_mesh = nullptr;
    }

    void Renderable::Serialize(FileStream* stream)
    {
       
    }

    void Renderable::Deserialize(FileStream* stream)
    {
       
    }

    void Renderable::OnTick()
    {
       
    }

    void Renderable::SetMesh(Mesh* mesh, const uint32_t sub_mesh_index)
    {
        
    }

    

   
    
    void Renderable::SetMaterial(const shared_ptr<Material>& material)
    {
       
    }

    void Renderable::SetMaterial(const string& file_path)
    {
       
    }

    void Renderable::SetDefaultMaterial()
    {
       
    }

    string Renderable::GetMaterialName() const
    {
        return "";
    }

    uint32_t Renderable::GetIndexOffset(const uint32_t lod) const
    {
        return 0;
    }

    uint32_t Renderable::GetIndexCount(const uint32_t lod) const
    {
        return 0;
    }

    uint32_t Renderable::GetVertexOffset(const uint32_t lod) const
    {
        return 0;
    }

    uint32_t Renderable::GetVertexCount(const uint32_t lod) const
    {
        return 0;
    }

    RHI_Buffer* Renderable::GetIndexBuffer() const
	{
        if (!m_mesh)
            return nullptr;

        return nullptr;
	}

    RHI_Buffer* Renderable::GetVertexBuffer() const
    {
        if (!m_mesh)
            return nullptr;

        return nullptr;
    }

    const string& Renderable::GetMeshName() const
    {
        static string no_mesh = "N/A";
        if (!m_mesh)
            return no_mesh;

        return no_mesh;
    }

    bool Renderable::IsSolid() const
    {
        return true;
    }

    uint32_t Renderable::GetInstanceGroupStartIndex(uint32_t group_index) const
    {
        return group_index == 0 ? 0 : m_instance_group_end_indices[group_index - 1];
    }
    
    uint32_t Renderable::GetInstanceGroupCount(uint32_t group_index) const
    {
        uint32_t start_index = GetInstanceGroupStartIndex(group_index);
        uint32_t end_index   = m_instance_group_end_indices[group_index];

        return end_index - start_index;
    }



    uint32_t Renderable::GetLodCount() const
    {
        return 1;
    }

    void Renderable::SetFlag(const RenderableFlags flag, const bool enable /*= true*/)
    {
        bool enabled      = false;
        bool disabled     = false;
        bool flag_present = m_flags & flag;

        if (enable && !flag_present)
        {
            m_flags |= static_cast<uint32_t>(flag);
            enabled  = true;

        }
        else if (!enable && flag_present)
        {
            m_flags  &= ~static_cast<uint32_t>(flag);
            disabled  = true;
        }
    }

    void Renderable::UpdateFrustumAndDistanceCulling()
    {
       
    }

    void Renderable::UpdateLodIndices()
    {
       
    }
}
