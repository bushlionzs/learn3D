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

void IndexData::bind()
{
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    rs->bindIndexBuffer(mIndexBufferHandle, mIndexSize);
}

void IndexData::createBuffer(uint32_t indexSize, uint32_t indexCount)
{
    mIndexSize = indexSize;
    mIndexCount = indexCount;
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    mIndexBufferHandle = rs->createBufferObject(
        BufferObjectBinding::SHADER_STORAGE,
        BufferUsage::DYNAMIC,
        indexSize * indexCount,
        "IndexBuffer");
    
}

void IndexData::writeData(const char* data, uint32_t size)
{
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    rs->updateBufferObject(mIndexBufferHandle, data, size);
}
