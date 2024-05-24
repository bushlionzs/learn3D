#include "OgreHeader.h"
#include "OgreRenderable.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include <OgreCamera.h>
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

    void Renderable::updateBuffer(VertexBuffer* vb, IndexBuffer* ib)
    {
        mVertexBuffer = vb;
        mIndexBuffer = ib;

        auto engine = Ogre::Root::getSingleton().getEngine();

        if (!mRenderableObjectHandle)
        {
            mRenderableObjectHandle = engine->getDriverApi().createBufferObject(
                sizeof(ObjectConstantBuffer),
                backend::BufferObjectBinding::UNIFORM,
                backend::BufferUsage::DYNAMIC);
        }

    }

    void Renderable::updateBufferObject(Ogre::Camera* cam)
    {
        const Ogre::Matrix4& view = cam->getViewMatrix();
        const Ogre::Matrix4& proj = cam->getProjectMatrix();
        const Ogre::Matrix4& model = getModelMatrix();


        mObjectBuffer.world = model.transpose();
       // mObjectBuffer.projector = _r->getProjectorMatrix();
        mObjectBuffer.worldViewProj = mObjectBuffer.world * view * proj;

        auto engine = Ogre::Root::getSingleton().getEngine();
        engine->getDriverApi().updateBufferObject(mRenderableObjectHandle, backend::BufferDescriptor(&mObjectBuffer, sizeof(mObjectBuffer)), 0);

        if (RawData* rd = getSkinnedData())
        {
            
            if (!mSkinnObjectHandle)
            {
                mSkinnObjectHandle = engine->getDriverApi().createBufferObject(
                    sizeof(SkinnedConstantBuffer),
                    backend::BufferObjectBinding::UNIFORM,
                    backend::BufferUsage::DYNAMIC);
            }
            engine->getDriverApi().updateBufferObjectUnsynchronized(mSkinnObjectHandle, backend::BufferDescriptor(rd->mData, rd->mDataSize), 0);
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