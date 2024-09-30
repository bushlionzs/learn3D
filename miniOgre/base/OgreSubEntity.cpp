#include "OgreHeader.h"
#include "OgreSubEntity.h"
#include "OgreSubMesh.h"
#include "OgreEntity.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreHardwareBufferManager.h"
#include "renderSystem.h"
namespace Ogre {
    SubEntity::SubEntity(Entity* entity, SubMesh* subMesh)
    {
        mParentEntity = entity;
        mSubMesh = subMesh;
        mLocal = Ogre::Matrix4::IDENTITY;
    }

    SubEntity::~SubEntity()
    {

    }

    VertexData* SubEntity::getVertexData()
    {
        return mSubMesh->getVertexData();
    }

    IndexData* SubEntity::getIndexData()
    {
        return mSubMesh->getIndexData();
    }

    IndexDataView* SubEntity::getIndexView()
    {
        return mSubMesh->getIndexView();
    }

    RawData* SubEntity::getSkinnedData(uint32_t dummy)
    {
        return mParentEntity->getSkinnedData(dummy);
    }

    const std::shared_ptr<Material>& SubEntity::getMaterial()
    {
        if (mMaterial)
            return mMaterial;
        return mSubMesh->getMaterial();
    }

    const Ogre::Matrix4& SubEntity::getModelMatrix()
    {
        mWorld = mParentEntity->getModelMatrix() * mLocal;

        return mWorld;
    }

    void SubEntity::setLocalMatrix(
        const Ogre::Vector3& pos, 
        const Ogre::Vector3& scale, 
        const Ogre::Quaternion& q)
    {
        mLocal.makeTransform(pos, scale, q);
    }

    void SubEntity::setMaterialName(const std::string& name)
    {
        assert(false);
    }
}