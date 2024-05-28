#include "OgreHeader.h"
#include "OgreVertexData.h"
#include "OgreHardwareBufferManager.h"
#include "renderSystem.h"
#include "OgreVertexDeclaration.h"
#include "OgreRoot.h"
#include "OgreMemoryBuffer.h"
#include <filament/FVertexBuffer.h>
#include <filament/FIndexBuffer.h>
#include <filament/OgreFilamentUtils.h>
#include <filament/Engine.h>
#include <filament/DriverApi.h>
#include <filament/FVertexBuffer.h>


void VertexSlotInfo::createBuffer(uint32_t vertexSize, uint32_t vertexCount)
{
    mVertexSize = vertexSize;

    auto engine = Ogre::Root::getSingleton().getEngine();

    if (engine)
    {
        hardwareVertexBuffer = std::make_shared<HardwareVertexBuffer>(vertexSize, vertexCount, new Ogre::MemoryBuffer(vertexSize, vertexCount));
    }
    else
    {
        hardwareVertexBuffer = HardwareBufferManager::getSingleton().createVertexBuffer(
            vertexSize,
            vertexCount,
            5
        );
    }
    
}

void VertexSlotInfo::writeData(const char* data, uint32_t size)
{
    void* vdata = hardwareVertexBuffer->lock();
    memcpy(vdata, data, size);
    hardwareVertexBuffer->unlock();
}


VertexData::VertexData()
{
    vertexDeclaration = new VertexDeclaration;
}

VertexData::~VertexData()
{

}

void VertexData::updateFilamentVertexBuffer(VertexBuffer* vb, VertexData* vd)
{

}

void VertexData::bind(void* cb)
{
    for (auto i = 0; i < vertexSlotInfo.size(); i++)
    {
        auto& slot = vertexSlotInfo[i];
        if (slot.mVertexSize > 0)
        {
            slot.hardwareVertexBuffer->bind(i, cb);
        }
    }
}

HardwareBuffer* VertexData::getBuffer(int32_t index) const
{
    if (vertexSlotInfo[index].mVertexSize > 0)
    {
        return vertexSlotInfo[index].hardwareVertexBuffer.get();
    }
    

    return nullptr;
}

uint32_t VertexData::getBufferCount()
{
    uint32_t count = 0;

    for (auto& slot : vertexSlotInfo)
    {
        if (slot.mVertexSize > 0)
        {
            count++;
        }
    }
    return count;
}

void VertexData::setVertexCount(uint32_t vertexCount)
{
    mVertexCount = vertexCount;
}

uint32_t VertexData::getVertexCount() const
{
    return mVertexCount;
}

uint32_t VertexData::getVertexSize(uint32_t binding) const
{
    return vertexSlotInfo[binding].mVertexSize;
}

void VertexData::removeAllElements()
{
    vertexDeclaration->removeAllElements();
}

const VertexElement& VertexData::addElement(
    int16_t source,
    int16_t index,
    int32_t offset,
    VertexElementType theType,
    VertexElementSemantic semantic)
{
    return vertexDeclaration->addElement(source, index, offset, theType, semantic);
}

int32_t VertexData::addBindBuffer(uint32_t vertexSize, uint32_t vertexCount)
{
    auto binding = getUnusedBinding();
    assert(binding >= 0);
    addBindBuffer(binding, vertexSize, vertexCount);
    return binding;
}

void VertexData::addBindBuffer(uint32_t binding, uint32_t vertexSize, uint32_t vertexCount)
{
    vertexSlotInfo[binding].createBuffer(vertexSize, vertexCount);
}

void VertexData::updateBindBuffer(uint32_t binding, uint32_t vertexCount)
{
    vertexSlotInfo[binding].createBuffer(binding, vertexCount);
}

void VertexData::addBoneInfo(std::vector<VertexBoneAssignment>& assignInfoList)
{
    uint32_t binding = 0;

    for (auto i = 0; i < vertexSlotInfo.size(); i++)
    {
        if (vertexSlotInfo[i].mVertexSize == 0)
        {
            binding = i;
            break;
        }
    }

    auto& slot = vertexSlotInfo[binding];

    slot.mVertexSize = sizeof(SkinnedData);
    slot.createBuffer(sizeof(SkinnedData), mVertexCount);

    vertexSlotInfo[binding].createBuffer(sizeof(SkinnedData), mVertexCount);

    HardwareBufferLockGuard lockGuard(slot.hardwareVertexBuffer.get());
    SkinnedData* skin = (SkinnedData*)lockGuard.data();
    std::vector<uint32_t> vertexIndex(mVertexCount);

    SkinnedData tmp;
    tmp.boneWeight[0] = 0.0f;
    tmp.boneWeight[1] = 0.0f;
    tmp.boneWeight[2] = 0.0f;
    tmp.boneWeight[3] = 0.0f;
    tmp.boneIndices[0] = 0;
    tmp.boneIndices[1] = 0;
    tmp.boneIndices[2] = 0;
    tmp.boneIndices[3] = 0;
    for (int32_t i = 0; i < mVertexCount; i++)
    {
        memcpy(&skin[i], &tmp, sizeof(SkinnedData));
    }

    for (auto& assign : assignInfoList)
    {
        int32_t i = assign.vertexIndex;
        int32_t wix = vertexIndex[i];
        skin[i].boneWeight[wix] = assign.weight;
        skin[i].boneIndices[wix] = assign.boneIndex;
        vertexIndex[i]++;
    }

    vertexDeclaration->addElement(binding, 0, 0, VET_FLOAT4, VES_BLEND_WEIGHTS);
    vertexDeclaration->addElement(binding, 0, 16, VET_UINT4, VES_BLEND_INDICES);

}

void VertexData::writeBindBufferData(uint32_t slot, const char* data, uint32_t size, bool writeGPU)
{
    vertexSlotInfo[slot].writeData(data, size);

    if (writeGPU && mVertexBuffer)
    {
        auto engine = Ogre::Root::getSingleton().getEngine();
        FVertexBuffer* fvb = (FVertexBuffer*)mVertexBuffer;
        auto handle = fvb->getBufferObjectHandle(slot);
        engine->getDriverApi().updateBufferObjectUnsynchronized(handle, backend::BufferDescriptor(data, size), 0);
    }
}

int32_t VertexData::getUnusedBinding()
{
    uint32_t binding = 0;
    for (uint32_t i = 0; i < vertexSlotInfo.size(); i++)
    {
        if (vertexSlotInfo[i].mVertexSize == 0)
        {
            return i;
        }
    }
    return -1;
}

void VertexData::prepare()
{
    auto engine = Ogre::Root::getSingleton().getEngine();
    if (engine && !mVertexBuffer)
    {
        VertexBuffer::Builder vBuilder;

        auto bufferCount = getBufferCount();
        vBuilder.vertexCount(mVertexCount);
        vBuilder.bufferCount(bufferCount);
        //vBuilder.advancedSkinning(true);


        const VertexDeclaration::VertexElementList& elist = vertexDeclaration->getElementList();

        for (auto& e : elist)
        {
            auto bufferIndex = e.getSource();
            auto stride = vertexDeclaration->getVertexSize(bufferIndex);
            auto offset = e.getOffset();
            auto attributeType = filament::mappingOgreVertexType(e.getType());
            auto attribute = filament::mappingOgreVertexAttribute(e.getSemantic(), e.getIndex());
            vBuilder.attribute(attribute, bufferIndex, attributeType, offset, stride);
        }


        auto vb = vBuilder.build(*engine);
        for (auto i = 0; i < bufferCount; i++)
        {
            auto buf = getBuffer(i);
            if (buf)
            {
                void* data = buf->lock();
                auto byteCount = buf->getSizeInBytes();
                Ogre::Vector3* tmp = (Ogre::Vector3*)data;
                vb->setBufferAt(*engine, i, { data, byteCount });
            }
        }

        mVertexBuffer = vb;
    }
}

void VertexData::upload(uint32_t binding, uint32_t vertexCount)
{
    auto engine = Ogre::Root::getSingleton().getEngine();
    if (engine)
    {
        filament::FVertexBuffer* vb = (filament::FVertexBuffer*)mVertexBuffer;

        auto buf = vertexSlotInfo[binding].hardwareVertexBuffer.get();
        const char* data = (const char*)buf->lock();

        auto byteCount = vertexCount * vertexSlotInfo[binding].mVertexSize;
        engine->getDriverApi().updateBufferObjectUnsynchronized(vb->getBufferObjectHandle(binding), { data, byteCount }, 0);
    }
}


