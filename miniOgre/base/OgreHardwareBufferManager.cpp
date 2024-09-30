#include "OgreHeader.h"
#include "OgreHardwareBufferManager.h"
#include "OgreVertexDeclaration.h"
template<> Ogre::HardwareBufferManager* Ogre::Singleton<Ogre::HardwareBufferManager>::msSingleton = 0;

namespace Ogre {

    HardwareBufferManager::HardwareBufferManager()
    {
    }


    HardwareBufferManager::~HardwareBufferManager()
    {

    }

    VertexDeclaration* HardwareBufferManager::createVertexDeclaration()
    {
        return new VertexDeclaration;
    }

    std::shared_ptr<HardwareBuffer> HardwareBufferManager::createBuffer(uint32_t size, HardwareBuffer::Usage usage)
    {
        return std::shared_ptr<HardwareBuffer>();
    }
}