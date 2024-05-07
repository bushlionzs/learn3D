#pragma once

#include "OgreSceneNode.h"
#include "OgreIndexData.h"
class VertexData;
class IndexData;



enum OperationType : uint8_t {
    /// A list of points, 1 vertex per point
    OT_POINT_LIST = 1,
    /// A list of lines, 2 vertices per line
    OT_LINE_LIST = 2,
    /// A strip of connected lines, 1 vertex per line plus 1 start vertex
    OT_LINE_STRIP = 3,
    /// A list of triangles, 3 vertices per triangle
    OT_TRIANGLE_LIST = 4,
    /// A strip of triangles, 3 vertices for the first triangle, and 1 per triangle after that
    OT_TRIANGLE_STRIP = 5,
    /// A fan of triangles, 3 vertices for the first triangle, and 1 per triangle after that
    OT_TRIANGLE_FAN = 6,
    /// Patch control point operations, used with tessellation stages
    OT_PATCH_1_CONTROL_POINT = 7,
    OT_PATCH_2_CONTROL_POINT = 8,
    OT_PATCH_3_CONTROL_POINT = 9,
    OT_PATCH_4_CONTROL_POINT = 10,
    OT_PATCH_5_CONTROL_POINT = 11,
    OT_PATCH_6_CONTROL_POINT = 12,
    OT_PATCH_7_CONTROL_POINT = 13,
    OT_PATCH_8_CONTROL_POINT = 14,
    OT_PATCH_9_CONTROL_POINT = 15,
    OT_PATCH_10_CONTROL_POINT = 16,
    OT_PATCH_11_CONTROL_POINT = 17,
    OT_PATCH_12_CONTROL_POINT = 18,
    OT_PATCH_13_CONTROL_POINT = 19,
    OT_PATCH_14_CONTROL_POINT = 20,
    OT_PATCH_15_CONTROL_POINT = 21,
    OT_PATCH_16_CONTROL_POINT = 22,
    OT_PATCH_17_CONTROL_POINT = 23,
    OT_PATCH_18_CONTROL_POINT = 24,
    OT_PATCH_19_CONTROL_POINT = 25,
    OT_PATCH_20_CONTROL_POINT = 26,
    OT_PATCH_21_CONTROL_POINT = 27,
    OT_PATCH_22_CONTROL_POINT = 28,
    OT_PATCH_23_CONTROL_POINT = 29,
    OT_PATCH_24_CONTROL_POINT = 30,
    OT_PATCH_25_CONTROL_POINT = 31,
    OT_PATCH_26_CONTROL_POINT = 32,
    OT_PATCH_27_CONTROL_POINT = 33,
    OT_PATCH_28_CONTROL_POINT = 34,
    OT_PATCH_29_CONTROL_POINT = 35,
    OT_PATCH_30_CONTROL_POINT = 36,
    OT_PATCH_31_CONTROL_POINT = 37,
    OT_PATCH_32_CONTROL_POINT = 38,
    // max valid base OT_ = (1 << 6) - 1
    /// Mark that the index buffer contains adjacency information
    OT_DETAIL_ADJACENCY_BIT = 1 << 6,
    /// like OT_POINT_LIST but with adjacency information for the geometry shader
    OT_LINE_LIST_ADJ = OT_LINE_LIST | OT_DETAIL_ADJACENCY_BIT,
    /// like OT_LINE_STRIP but with adjacency information for the geometry shader
    OT_LINE_STRIP_ADJ = OT_LINE_STRIP | OT_DETAIL_ADJACENCY_BIT,
    /// like OT_TRIANGLE_LIST but with adjacency information for the geometry shader
    OT_TRIANGLE_LIST_ADJ = OT_TRIANGLE_LIST | OT_DETAIL_ADJACENCY_BIT,
    /// like OT_TRIANGLE_STRIP but with adjacency information for the geometry shader
    OT_TRIANGLE_STRIP_ADJ = OT_TRIANGLE_STRIP | OT_DETAIL_ADJACENCY_BIT,
};

class VertexDeclaration;


namespace Ogre {
    class SubMesh
    {
        friend class Mesh;
    public:
        SubMesh(
            Mesh* mesh,
            bool sharedVertices = false,
            bool sharedIndex = false);
        ~SubMesh();

        VertexData* getVertexData();
        IndexData* getIndexData();
        OperationType getOperationType();
        void setOperationType(OperationType ot);

        void addIndexs(uint32_t drawCount, uint32_t indexLocation, uint32_t baseVertexLocation);

        IndexDataView* getIndexView();

        void setMaterial(std::shared_ptr<Material>& mat);
        const std::shared_ptr<Material>& getMaterial();

        void setMaterialName(std::string& name);
        const std::string& getMaterialName();

        VertexDeclaration* getVertexDeclaration()
        {
            return mVetexDeclaration;
        }

        void addBoneAssignment(const VertexBoneAssignment& vertBoneAssign);
        void buildHardBuffer();

        void setPosition(Ogre::Vector3& pos);
        const Ogre::Vector3& getPosition();

        bool useSharedVertices()
        {
            return mSharedVertices;
        }

        Mesh* getParent()
        {
            return mParent;
        }

        void updateBuffer(VertexBuffer* vb, IndexBuffer* ib)
        {
            mVertexBuffer = vb;
            mIndexBuffer = ib;
        }

    private:
        VertexDeclaration* mVetexDeclaration;
        VertexData* mVertexData;
        IndexData* mIndexData;
        Mesh* mParent = nullptr;

        IndexDataView mIndexView;

        std::shared_ptr<Material> mMaterial;
        std::string mMatName;

        OperationType mOperationType = OT_TRIANGLE_LIST;

        Ogre::Vector3 mPosition;

        bool mSharedVertices = false;
        bool mSharedIndex = false;

        VertexBuffer* mVertexBuffer = nullptr;
        IndexBuffer* mIndexBuffer = nullptr;
    };
}