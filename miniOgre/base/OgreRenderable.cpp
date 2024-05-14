#include "OgreHeader.h"
#include "OgreRenderable.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include <filament/Engine.h>
#include <filament/DriverApi.h>
namespace Ogre {
    Renderable::Renderable()
    {
        mModel = Ogre::Matrix4::IDENTITY;

        mSortValue = 1000000;
    }

    Renderable::~Renderable()
    {
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

    void Renderable::updateBuffer(FVertexBuffer* vb, FIndexBuffer* ib)
    {
        mVertexBuffer = vb;
        mIndexBuffer = ib;

        if (!mRenderableObjectHandle)
        {
            auto engine = Ogre::Root::getSingleton().getEngine();
            mRenderableObjectHandle = engine->getDriverApi().createBufferObject(
                sizeof(ObjectConstantBuffer),
                backend::BufferObjectBinding::UNIFORM,
                backend::BufferUsage::DYNAMIC);
        }
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
}