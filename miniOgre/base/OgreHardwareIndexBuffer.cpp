#include "OgreHeader.h"
#include "OgreHardwareIndexBuffer.h"

HardwareIndexBuffer::HardwareIndexBuffer(
    HardwareBuffer* delegate)
{
    mDelegate.reset(delegate);
    mSizeInBytes = mDelegate->getSizeInBytes();
    mNumVerts = mDelegate->getNumVerts();
    mVertexSize = mDelegate->getVertexSize();
}

HardwareIndexBuffer::~HardwareIndexBuffer()
{

}

void* HardwareIndexBuffer::lockimpl(size_t offset, size_t length, LockOptions options)
{
    return mDelegate->lock(options);
}

void HardwareIndexBuffer::unlock()
{
    mDelegate->unlock();
}

void HardwareIndexBuffer::bind(void* cb)
{
    mDelegate->bind(0, cb);
}

uint32_t HardwareIndexBuffer::getIndexSize()
{
    assert(false);
    return 0;
}

HardwareIndexBuffer::IndexType HardwareIndexBuffer::getType()
{
    if (mDelegate->getVertexSize() == 2)
    {
        return IT_16BIT;
    }
    return IT_32BIT;
}