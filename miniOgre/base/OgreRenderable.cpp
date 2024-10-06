#include "OgreHeader.h"
#include "OgreRenderable.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include <OgreCamera.h>
#include <OgreVertexData.h>
#include <OgreIndexData.h>
#include <OgreMaterial.h>

namespace Ogre {
    Renderable::Renderable()
    {
        mModel = Ogre::Matrix4::IDENTITY;

        mSortValue = 1000000;
    }

    Renderable::~Renderable()
    {
    }

    void Renderable::setMaterial(std::shared_ptr<Material> mat)
    {
        mMaterial = mat;

        VertexData* vd = getVertexData();
        VertexDeclaration* decl = vd->getVertexDeclaration();
        mMaterial->updateVertexDeclaration(decl);
    }

    RenderableData* Renderable::getRenderableData()
    {
        if (!mRenderableData)
        {
            auto rs = Ogre::Root::getSingleton().getRenderSystem();
            mRenderableData = rs->createRenderableData(this);
        }
        return mRenderableData;
    }

    uint64_t Renderable::getSortValue()
    {
        return 0;
    }

    const Ogre::Matrix4& Renderable::getModelMatrix()
    {
        return mModel;
    }

    Ogre::Vector3 getPosition()
    {
        return Ogre::Vector3(0.0f, 0.0f, 0.0f);
    }

    Ogre::OperationType Renderable::getPrimitiveTopology()
    {
        return OT_TRIANGLE_LIST;
    }

    void Renderable::prepare(VertexData* vd, IndexData* id)
    {
        
    }
}