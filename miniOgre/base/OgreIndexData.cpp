#include "OgreHeader.h"
#include "OgreIndexData.h"
#include "OgreHardwareBuffer.h"
#include "OgreHardwareBufferManager.h"
#include "OgreHardwareIndexBuffer.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "OgreMemoryBuffer.h"

IndexData::IndexData()
{

}

IndexData::~IndexData()
{

}

void IndexData::createBuffer(uint32_t indexSize, uint32_t indexCount)
{
    auto engine = Ogre::Root::getSingleton().getEngine();
    if (engine)
    {
        mIndexBuffer = std::make_shared<HardwareIndexBuffer>(new Ogre::MemoryBuffer(indexSize, indexCount));
    }
    else
    {
        mIndexBuffer = HardwareBufferManager::getSingletonPtr()->createIndexBuffer(
            indexSize,
            indexCount,
            5
        );
    }
   
}

void IndexData::writeData(const char* data, uint32_t size)
{
    void* indexdata = mIndexBuffer->lock();
    memcpy(indexdata, data, size);
    mIndexBuffer->unlock();
}