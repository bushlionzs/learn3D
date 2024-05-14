#pragma once


#include "engine_struct.h"
#include <filament/Handle.h>

class RenderSystem;
class VertexData;
class IndexData;
class IndexDataView;
class RenderableData;

namespace filament
{
    class FVertexBuffer;
    class FIndexBuffer;
}

using namespace filament;

namespace Ogre {
    class Renderable
    {
    public:
        Renderable();
        ~Renderable();
        virtual bool buildRenderable(RenderSystem* engine, SceneNode* node) { return false; }
        virtual void render(RenderSystem* engine) {}
        virtual void addTexture(OgreTexture* tex) {}
        void setMaterial(std::shared_ptr<Material> mat)
        {
            mMaterial = mat;
        }

        virtual const std::shared_ptr<Material>& getMaterial()
        {
            return mMaterial;
        }

        virtual VertexData* getVertexData()
        {
            return nullptr;
        }

        virtual IndexData* getIndexData()
        {
            return nullptr;
        }

        virtual IndexDataView* getIndexView()
        {
            return nullptr;
        }

        virtual RawDataView* getRawDataView()
        {
            return nullptr;
        }

        virtual RawData* getSkinnedData(uint32_t dummy = 0)
        {
            return nullptr;
        }

        virtual const Ogre::Matrix4& getProjectorMatrix()
        {
            return Ogre::Matrix4::IDENTITY;
        }

        virtual uint64_t getSortValue();

        virtual const Ogre::Matrix4& getModelMatrix();

        RenderableData* getRenderableData();

        void updateBuffer(FVertexBuffer* vb, FIndexBuffer* ib);

        FVertexBuffer* getVertexBuffer()
        {
            return mVertexBuffer;
        }

        FIndexBuffer* getIndexBuffer()
        {
            return mIndexBuffer;
        }

        backend::VertexBufferInfoHandle getVertexBufferInfoHandle()
        {
            return mVertexBufferInfoHandle;
        }

        backend::BufferObjectHandle getBufferObjectHandle()
        {
            return mRenderableObjectHandle;
        }

    protected:
        std::shared_ptr<Material> mMaterial;
        RenderableData* mRenderableData = nullptr;

        FVertexBuffer* mVertexBuffer = nullptr;
        FIndexBuffer* mIndexBuffer = nullptr;
        backend::VertexBufferInfoHandle mVertexBufferInfoHandle;
        backend::BufferObjectHandle mRenderableObjectHandle;
        Ogre::Matrix4 mModel;

        uint64_t mSortValue;


    };
}