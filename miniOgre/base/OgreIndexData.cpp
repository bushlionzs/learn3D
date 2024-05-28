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

void IndexData::prepare()
{
    auto engine = Ogre::Root::getSingleton().getEngine();
    if (engine && !mFIndexBuffer)
    {
        auto buf = getIndexBuffer();

        auto indexCount = buf->getNumVerts();
        auto indexType = IndexBuffer::IndexType::USHORT;
        if (buf->getType() == HardwareIndexBuffer::IndexType::IT_32BIT)
        {
            indexType = IndexBuffer::IndexType::UINT;
        };

        mFIndexBuffer = IndexBuffer::Builder()
            .indexCount(indexCount)
            .bufferType(indexType)
            .build(*engine);

        mFIndexBuffer->setBuffer(*engine, { buf->lock(), buf->getSizeInBytes() });
    }
    
}