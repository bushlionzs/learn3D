#include "OgreHeader.h"
#include "OgreMesh.h"
#include "OgreSubMesh.h"
#include "OgreHardwareBufferManager.h"
#include "OgreMaterial.h"
#include "vertex_data.h"
#include "renderSystem.h"
#include "vertex_declaration.h"
#include "OgreSkeletonManager.h"
#include "OgreSkeleton.h"

namespace Ogre {
    Mesh::Mesh(const std::string& name)
    {
        mName = name;
        mVertexData = new VertexData;
        mIndexData = new IndexData;
        mAABB.setInfinite();
    }

    Mesh::~Mesh()
    {

    }

    SubMesh* Mesh::addSubMesh(bool shareVertices, bool shareIndex)
    {
        SubMesh* sub = new SubMesh(this, shareVertices, shareIndex);
        mSubMeshList.push_back(sub);
        return sub;
    }

    int32_t Mesh::getSubMeshCount()
    {
        return (int32_t)mSubMeshList.size();
    }

    SubMesh* Mesh::getSubMesh(int32_t index)
    {
        return mSubMeshList[index];
    }

    bool Mesh::hasSkeleton()
    {
        return !!mSkeleton;
    }

    std::shared_ptr<Skeleton>& Mesh::getSkeleton()
    {
        return mSkeleton;
    }

    void Mesh::applySkeleton(std::shared_ptr<Skeleton>& skeleton)
    {
        mSkeleton = skeleton;
    }

    void Mesh::setSkeletonName(const std::string& skelName)
    {
        mSkelName = skelName;

        mSkeleton = SkeletonManager::getSingletonPtr()->load(mSkelName);
    }

    void Mesh::_initAnimationState(AnimationStateSet* animSet)
    {
        if (mSkeleton)
        {
            // Delegate to Skeleton
            mSkeleton->_initAnimationState(animSet);

        }

        
    }

    void Mesh::_refreshAnimationState(AnimationStateSet* animSet)
    {
        if (mSkeleton)
        {
            mSkeleton->_refreshAnimationState(animSet);
        }
    }

    VertexData* Mesh::getVertexData()
    {
        return mVertexData;
    }

    IndexData* Mesh::getIndexData()
    {
        return mIndexData;
    }

    void Mesh::addBoneAssignment(const VertexBoneAssignment& vertBoneAssign)
    {
        mVertexData->mBoneAssignments.push_back(vertBoneAssign);
    }

    void Mesh::buildHardBuffer()
    {
        if (mVertexData->vertexCount > 0)
        {
            mVertexData->buildHardBuffer();
        }

        for (auto sub : mSubMeshList)
        {
            sub->buildHardBuffer();
        }
    }

    void Mesh::_setBounds(const AxisAlignedBox& bounds, bool pad)
    {
        mAABB = bounds;
    }

    const AxisAlignedBox& Mesh::getBounds(void) const
    {
        return mAABB;
    }

    const std::string& Mesh::getSkeletonName() const
    {
        return mSkelName;
    }
}
