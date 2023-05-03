#include "OgreHeader.h"
#include "OgreSubMesh.h"
#include "OgreHardwareBufferManager.h"
#include "OgreMaterial.h"
#include "OgreMesh.h"
#include "vertex_data.h"
#include "renderSystem.h"
#include "vertex_declaration.h"


namespace Ogre {
    SubMesh::SubMesh(
        Mesh* mesh, 
        bool sharedVertices,
        bool sharedIndex
    )
    {
        mParent = mesh;
        mIndexView.mIndexCount = 0;
        mIndexView.mBaseVertexLocation = 0;
        mIndexView.mIndexLocation = 0;

        mSharedVertices = sharedVertices;
        mSharedIndex = sharedIndex;
        if (!sharedVertices)
        {
            mVertexData = new VertexData;
            
        }
        else
        {
            mVertexData = nullptr;
            
        }

        if (!sharedIndex)
        {
            mIndexData = new IndexData;
        }
        else
        {
            mIndexData = nullptr;
        }

        mPosition = Ogre::Vector3::ZERO;
    }

    SubMesh::~SubMesh()
    {

    }

    VertexData* SubMesh::getVertexData()
    {
        if (mSharedVertices)
        {
            return mParent->getVertexData();
        }
        return mVertexData;
    }

    IndexData* SubMesh::getIndexData()
    {
        if (mSharedIndex)
        {
            return mParent->getIndexData();
        }
        return mIndexData;
    }

    OperationType SubMesh::getOperationType()
    {
        return mOperationType;
    }

    void SubMesh::setOperationType(OperationType ot)
    {
        mOperationType = ot;
    }


    void SubMesh::addIndexs(
        uint32_t drawCount,
        uint32_t indexLocation,
        uint32_t baseVertexLocation)
    {
        mIndexView.mIndexCount = drawCount;
        mIndexView.mIndexLocation = indexLocation;
        mIndexView.mBaseVertexLocation = baseVertexLocation;
    }


    IndexDataView* SubMesh::getIndexView()
    {
        return &mIndexView;
    }

    void SubMesh::setMaterial(std::shared_ptr<Material>& mat)
    {
        mMaterial = mat;
    }

    const std::shared_ptr<Material>& SubMesh::getMaterial()
    {
        return mMaterial;
    }

    void SubMesh::setMaterialName(std::string& name)
    {
        mMatName = name;
    }

    const std::string& SubMesh::getMaterialName()
    {
        return mMatName;
    }

    void SubMesh::addBoneAssignment(const VertexBoneAssignment& vertBoneAssign)
    {
        mVertexData->mBoneAssignments.push_back(vertBoneAssign);
    }

    void SubMesh::buildHardBuffer()
    {
        if (mVertexData && mVertexData->vertexCount > 0)
        {
            mVertexData->buildHardBuffer();
        }
    }


    void SubMesh::setPosition(Ogre::Vector3& pos)
    {
        mPosition = pos;
    }


    const Ogre::Vector3& SubMesh::getPosition()
    {
        return mPosition;
    }
}