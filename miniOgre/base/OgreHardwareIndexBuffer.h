#pragma once

#include "OgreHardwareBuffer.h"

class HardwareIndexBuffer: public Ogre::HardwareBuffer
{
public:
    enum IndexType : uint8_t 
    {
        IT_16BIT,
        IT_32BIT
    };
public:
    HardwareIndexBuffer(
        HardwareBuffer* delegate);
    virtual ~HardwareIndexBuffer();

    virtual void* lockimpl(size_t offset, size_t length, LockOptions options);
    virtual void unlock();

    virtual void bind();

    uint32_t getIndexSize();

    IndexType getType();

private:
    std::unique_ptr<HardwareBuffer> mDelegate;
};