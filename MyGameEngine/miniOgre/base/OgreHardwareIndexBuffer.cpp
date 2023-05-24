#include "OgreHeader.h"
#include "OgreHardwareIndexBuffer.h"

HardwareIndexBuffer::HardwareIndexBuffer(
    HardwareBuffer* delegate)
{
    mDelegate.reset(delegate);

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

void HardwareIndexBuffer::bind()
{
    mDelegate->bind(0);
}

uint32_t HardwareIndexBuffer::getIndexSize()
{
    assert(false);
    return 0;
}

HardwareIndexBuffer::IndexType HardwareIndexBuffer::getType()
{
    return IT_16BIT;
}