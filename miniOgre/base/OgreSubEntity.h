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

        virtual const std::shared_ptr<Material>& getMaterial();

        virtual const Ogre::Matrix4& getModelMatrix();

        void setPosition(Ogre::Vector3& pos);

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
        Ogre::Vector3 mPosition;

        bool mVisible = true;
    };
}