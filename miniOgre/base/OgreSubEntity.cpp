#include "OgreHeader.h"
#include "OgreSubEntity.h"
#include "OgreSubMesh.h"
#include "OgreEntity.h"
#include "vertex_data.h"
#include "index_data.h"
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
        VertexData* vd = mSubMesh->getVertexData();
        return vd ? vd : mParentEntity->getVertexData();
    }

    IndexData* SubEntity::getIndexData()
    {
        IndexData* id = mSubMesh->getIndexData();

        return id ? id : mParentEntity->getIndexData();
    }

    IndexDataView* SubEntity::getIndexView()
    {
        return mSubMesh->getIndexView();
    }

    RawData* SubEntity::getShaderConstantData(uint32_t index)
    {
        return mParentEntity->getShaderConstantData(index);
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

    void SubEntity::setPosition(Ogre::Vector3& pos)
    {
        mPosition = pos;
        if (mPosition != Ogre::Vector3::ZERO)
        {
            int kk = 0;
        }
        mLocal.makeTransform(
            pos,
            Ogre::Vector3(1.0f, 1.0f, 1.0f),
            Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f));
    }

    void SubEntity::setMaterialName(const std::string& name)
    {

    }
}