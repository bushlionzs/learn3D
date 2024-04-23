#include "OgreHeader.h"
#include "OgreVertexData.h"
#include "OgreHardwareBufferManager.h"
#include "renderSystem.h"
#include "OgreVertexDeclaration.h"


void VertexSlotInfo::createBuffer(uint32_t vertexSize, uint32_t vertexCount)
{
    mVertexSize = vertexSize;
    hardwareVertexBuffer = HardwareBufferManager::getSingletonPtr()->createVertexBuffer(
        vertexSize,
        vertexCount,
        5
    );
}

void VertexSlotInfo::writeData(const char* data, uint32_t size)
{
    void* vdata = hardwareVertexBuffer->lock();
    memcpy(vdata, data, size);
    hardwareVertexBuffer->unlock();
}

VertexData::VertexData()
{
    vertexDeclaration = HardwareBufferManager::getSingletonPtr()->createVertexDeclaration();
}

VertexData::~VertexData()
{

}

void VertexData::buildHardBuffer()
{
    if (!mBoneAssignments.empty())
    {
        vertexSlotInfo.emplace_back();

        int32_t bindIndex = -1;
        for (auto& slotInfo : vertexSlotInfo)
        {
            if (bindIndex < slotInfo.mSlot)
            {
                bindIndex = slotInfo.mSlot;
            }
        }

        bindIndex++;

        VertexSlotInfo& slot = vertexSlotInfo.back();

        

        slot.mSlot = bindIndex;
        slot.mVertexSize = sizeof(SkinnedData);
        slot.createBuffer(sizeof(SkinnedData), vertexCount);

        HardwareBufferLockGuard lockGuard(slot.hardwareVertexBuffer.get());
        SkinnedData* skin = (SkinnedData*)lockGuard.data();
        std::vector<uint32_t> vertexIndex(vertexCount);

        SkinnedData tmp;
        tmp.boneWeight[0] = 0.0f;
        tmp.boneWeight[1] = 0.0f;
        tmp.boneWeight[2] = 0.0f;
        tmp.boneWeight[3] = 0.0f;
        tmp.boneIndices[0] = 0;
        tmp.boneIndices[1] = 0;
        tmp.boneIndices[2] = 0;
        tmp.boneIndices[3] = 0;
        for (int32_t i = 0; i < vertexCount; i++)
        {
            memcpy(&skin[i], &tmp, sizeof(SkinnedData));
        }

        for (auto& assign : mBoneAssignments)
        {
            int32_t i = assign.vertexIndex;
            int32_t wix = vertexIndex[i];
            skin[i].boneWeight[wix] = assign.weight;
            skin[i].boneIndices[wix] = assign.boneIndex;
            vertexIndex[i]++;
        }

        vertexDeclaration->addElement(bindIndex, 0, 0, VET_FLOAT4, VES_BLEND_WEIGHTS);
        vertexDeclaration->addElement(bindIndex, 0, 16, VET_UINT4, VES_BLEND_INDICES);
    }
}


void VertexData::bind(void* cb)
{
    for (auto& slot : vertexSlotInfo)
    {
        slot.hardwareVertexBuffer->bind(slot.mSlot, cb);
    }
}

void VertexData::setBinding(int32_t index, std::shared_ptr<HardwareVertexBuffer>& buf)
{
    for (auto& slot : vertexSlotInfo)
    {
        if (slot.mSlot == index)
        {
            slot.hardwareVertexBuffer = buf;
            break;
        }
    }
}

std::shared_ptr<HardwareVertexBuffer> VertexData::getBuffer(int32_t index) const
{
    for (auto& slot : vertexSlotInfo)
    {
        if (slot.mSlot == index)
        {
            return slot.hardwareVertexBuffer;
        }
    }

    return std::shared_ptr<HardwareVertexBuffer>();
}

