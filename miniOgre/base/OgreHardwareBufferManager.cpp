#include "OgreHeader.h"
#include "OgreHardwareBufferManager.h"
#include "OgreVertexDeclaration.h"
template<> Ogre::HardwareBufferManager* Ogre::Singleton<Ogre::HardwareBufferManager>::msSingleton = 0;

namespace Ogre {

    HardwareBufferManager::HardwareBufferManager(RenderSystem* rs)
    {
        mRenderSystem = rs;
    }


    HardwareBufferManager::~HardwareBufferManager()
    {

    }

    VertexDeclaration* HardwareBufferManager::createVertexDeclaration()
    {
        return new VertexDeclaration;
    }
}