#include "OgreHeader.h"
#include "OgreRenderable.h"
#include "renderSystem.h"
#include "OgreRoot.h"
namespace Ogre {
    Renderable::Renderable()
    {
        mWorld = Ogre::Matrix4::IDENTITY;
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

    const Ogre::Matrix4& Renderable::getModelMatrix()
    {
        return mWorld;
    }
}