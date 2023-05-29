#pragma once


#include "engine_struct.h"

class RenderSystem;
class VertexData;
class IndexData;
class IndexDataView;
namespace Ogre {
    class Renderable
    {
    public:
        Renderable();
        ~Renderable();
        virtual bool buildRenderable(RenderSystem* engine, SceneNode* node) { return false; }
        virtual void render(RenderSystem* engine) {}
        virtual void addTexture(ITexture* tex) {}
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

        virtual RawData* getShaderConstantData(uint32_t index)
        {
            return nullptr;
        }

        virtual const Ogre::Matrix4& getProjectorMatrix()
        {
            return Ogre::Matrix4::IDENTITY;
        }

        virtual uint64_t getSortValue()
        {
            return 0;
        }
        virtual const Ogre::Matrix4& getModelMatrix();
        virtual Ogre::Vector3 getPosition() { return Ogre::Vector3(0.0f, 0.0f, 0.0f); }

        void* getRenderableData();
    protected:
        std::shared_ptr<Material> mMaterial;
        void* mRenderableData = nullptr;

        Ogre::Matrix4 mWorld;
    };
}