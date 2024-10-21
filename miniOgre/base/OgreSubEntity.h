#pragma once

#include "OgreRenderable.h"

class IndexDataView;

namespace Ogre {
    class SubMesh;
    class SubEntity : public Renderable
    {
    public:
        SubEntity(Entity* entity, SubMesh* subMesh);
        ~SubEntity();

        virtual VertexData* getVertexData();

        virtual IndexData* getIndexData();

        virtual IndexDataView* getIndexView();

        virtual RawData* getSkinnedData(uint32_t dummy);

        virtual std::shared_ptr<Material>& getMaterial();

        virtual const Ogre::Matrix4& getModelMatrix();

        void setLocalMatrix(const Ogre::Vector3& pos, const Ogre::Vector3& scale, const Ogre::Quaternion& q);

        void setMaterialName(const std::string& name);

        bool isVisible() const
        {
            return mVisible;
        }

        SubMesh* getSubMesh()
        {
            return mSubMesh;
        }

    protected:
        Entity* mParentEntity;

        SubMesh* mSubMesh;

        Ogre::Matrix4 mWorld;
        Ogre::Matrix4 mLocal;
        //Ogre::Vector3 mPosition;

        bool mVisible = true;
    };
}