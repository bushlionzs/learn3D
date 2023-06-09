#include "OgreHeader.h"
#include "index_data.h"
#include "OgreHardwareBuffer.h"
#include "OgreHardwareBufferManager.h"
#include "OgreHardwareIndexBuffer.h"
#include "renderSystem.h"

IndexData::IndexData()
{

}

IndexData::~IndexData()
{

}

void IndexData::createBuffer(uint32_t indexSize, uint32_t indexCount)
{
    mIndexBuffer = HardwareBufferManager::getSingletonPtr()->createIndexBuffer(
        indexSize,
        indexCount,
        5
    );
}

void IndexData::writeData(const char* data, uint32_t size)
{
    void* indexdata = mIndexBuffer->lock();
    memcpy(indexdata, data, size);
    mIndexBuffer->unlock();
}