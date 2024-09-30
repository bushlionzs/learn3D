#pragma once

#include "OgreSingleton.h"
#include "OgreHardwareVertexBuffer.h"
#include "OgreHardwareIndexBuffer.h"
class RenderSystem;
class VertexDeclaration;

namespace Ogre {
    class HardwareBufferManager : public Ogre::Singleton<HardwareBufferManager>
    {
    public:
        HardwareBufferManager();
        ~HardwareBufferManager();


        virtual VertexDeclaration* createVertexDeclaration();


        virtual std::shared_ptr<HardwareVertexBuffer>
            createVertexBuffer(size_t vertexSize, size_t numVerts, HardwareBuffer::Usage usage) = 0;

        virtual std::shared_ptr<HardwareIndexBuffer>
            createIndexBuffer(
                size_t vertexSize,
                size_t numIndexes,
                HardwareBuffer::Usage usage) = 0;

        virtual std::shared_ptr<HardwareBuffer> createBuffer(uint32_t size, HardwareBuffer::Usage usage);

    protected:
    };
}