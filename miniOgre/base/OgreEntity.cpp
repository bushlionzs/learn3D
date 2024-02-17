#include "OgreHeader.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreSubMesh.h"
#include "OgreMesh.h"
#include "vertex_data.h"
#include "index_data.h"
#include "OgreHardwareBufferManager.h"
#include "renderSystem.h"
#include "OgreSkeletonInstance.h"
#include "OgreMaterial.h"
#include "OgreMeshManager.h"
#include "OgreAnimationState.h"
#include "OgreRoot.h"

namespace Ogre {
    Entity::Entity()
        :MoveObject(std::string(""))
    {
        mSharedSkeletonEntities = nullptr;
        mAnimationState = nullptr;
    }
    Entity::Entity(const std::string& name, const std::shared_ptr<Mesh>& mesh)
        :MoveObject(name)
    {
        mMesh = mesh;
        mSharedSkeletonEntities = nullptr;
        mAnimationState = nullptr;
        mAABB.setNull();
        if (mMesh)
            buildSubEntityList(mMesh, &mSubEntityList);
    }

    Entity::~Entity()
    {

    }

    const std::vector<Renderable*>& Entity::getRenderableList()
    {
        /*static std::vector<Renderable*> aa;
        aa.clear();
        for (int32_t i = 0; i < mSubEntityList.size(); i++)
        {
            if ( i == 7)
            aa.push_back(mSubEntityList[i]);
        }*/
        return mSubEntityList;
    }

    bool Entity::isTransparent() const
    {
        return mTransparent;
    }

    SubEntity* Entity::createSubEntity(SubMesh* sub)
    {
        return new SubEntity(this, sub);
    }

    bool Entity::setMaterial(uint32_t index, std::shared_ptr<Material>& mat)
    {
        if (index >= mSubEntityList.size())
        {
            return false;
        }

        mat->load();
        mSubEntityList[index]->setMaterial(mat);

        return true;
    }

    void Entity::setTransparent(float alpha)
    {
        mTransparent = true;
    }

    void Entity::setMirror(bool mirror)
    {
        mMirror = mirror;
    }

    void Entity::update(float delta)
    {
        if (mSkeletonInstance)
        {
            mSkeletonInstance->setAnimationState(*mAnimationState);
        }
    }

    RawData* Entity::getShaderConstantData(uint32_t index)
    {
        if (!mSkeletonInstance)
        {
            return nullptr;
        }

        return mSkeletonInstance->getShaderConstantData(index);
    }

    VertexData* Entity::getVertexData()
    {
        return mMesh->getVertexData();
    }

    IndexData* Entity::getIndexData()
    {
        return mMesh->getIndexData();
    }

    Ogre::Vector3 Entity::getPosition()
    {
        return Ogre::Vector3(0.0f, 0.0f, 0.0f);
    }

    AnimationStateSet* Entity::getAllAnimationStates(void) const
    {
        return mAnimationState;
    }

    AnimationState* Entity::getAnimationState(const String& name)
    {
        if (!mAnimationState)
        {
            return nullptr;
        }
        return mAnimationState->getAnimationState(name);
    }

    const AxisAlignedBox& Entity::getBoundingBox(void) const
    {
        if (mMesh)
        {
            mAABB = mMesh->getBounds();
        }
        return mAABB;
    }


    TagPoint* Entity::attachObjectToBone(const String& boneName,
        MoveObject* pMovable,
        const Quaternion& offsetOrientation,
        const Vector3& offsetPosition)
    {
        return nullptr;
    }

    int32_t Entity::getNumSubEntities() const
    {
        return mSubEntityList.size();
    }

    SubEntity* Entity::getSubEntity(int32_t index) const
    {
        return (SubEntity*)mSubEntityList[index];
    }

    bool Entity::hasSkeleton() const
    {
        return !!mSkeletonInstance;
    }

    SkeletonInstance* Entity::getSkeleton(void) const
    {
        return mSkeletonInstance.get();
    }

    Real Entity::getBoundingRadius(void) const
    {
        return 0.0f;
    }


    void Entity::setMaterialName(const std::string& name)
    {

    }

    const Entity::ChildObjectList& Entity::getAttachedObjects() const
    {
        static Entity::ChildObjectList aa;
        return aa;
    }

    void Entity::shareSkeletonInstanceWith(Entity* entity)
    {
        if (mSharedSkeletonEntities != nullptr)
        {
            entity->shareSkeletonInstanceWith(this);
        }
        else
        {
            if (mAnimationState)
            {
                delete mAnimationState;
            }
            mSkeletonInstance = entity->mSkeletonInstance;

            if (entity->mSharedSkeletonEntities == nullptr)
            {
                entity->mSharedSkeletonEntities = OGRE_NEW_T(EntitySet, MEMCATEGORY_ANIMATION)();
                entity->mSharedSkeletonEntities->insert(entity);
            }
            mSharedSkeletonEntities = entity->mSharedSkeletonEntities;
            mSharedSkeletonEntities->insert(this);

            mAnimationState = entity->mAnimationState;
        }
    }

    void Entity::refreshAvailableAnimationState(void)
    {
        mMesh->_refreshAnimationState(mAnimationState);
    }

    void Entity::buildSubEntityList(
        std::shared_ptr<Mesh>& mesh, 
        std::vector<Renderable*>* sublist)
    {
        int32_t numSubMeshes = mesh->getSubMeshCount();
        for (int32_t i = 0; i < numSubMeshes; ++i)
        {
            SubMesh* subMesh = mesh->getSubMesh(i);
            const std::string& name = subMesh->getMaterialName();

            /*if (name != "RomanBath/Default_Grey")
                continue;*/
            SubEntity* subEnt = createSubEntity(subMesh);

            Ogre::Vector3 position = subMesh->getPosition();

            subEnt->setPosition(position);

            sublist->push_back(subEnt);
        }

        //skeleton

        if (mesh->hasSkeleton())
        {
            std::shared_ptr<Skeleton> skeleton = mesh->getSkeleton();
            mSkeletonInstance = std::make_shared<SkeletonInstance>(skeleton);

            mAnimationState = OGRE_NEW AnimationStateSet();
            mesh->_initAnimationState(mAnimationState);
        }
        else
        {
            int kk = 0;
        }
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    String EntityFactory::FACTORY_TYPE_NAME = "Entity";
    //-----------------------------------------------------------------------
    const String& EntityFactory::getType(void) const
    {
        return FACTORY_TYPE_NAME;
    }
    //-----------------------------------------------------------------------
    MoveObject* EntityFactory::createInstanceImpl(const String& name,
        const NameValuePairList* params)
    {
        // must have mesh parameter
        MeshPtr pMesh;
        if (params != 0)
        {
            NameValuePairList::const_iterator ni;

            ni = params->find("mesh");
            if (ni != params->end())
            {
                // Get mesh (load if required)
                pMesh = MeshManager::getSingleton().load(ni->second);
            }

        }
        if (!pMesh)
        {
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
                "'mesh' parameter required when constructing an Entity.",
                "EntityFactory::createInstance");
        }

        return OGRE_NEW Entity(name, pMesh);

    }
}
