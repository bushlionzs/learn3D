#pragma once
#include "engine_struct.h"
class VertexDeclaration;
class GraphicsCommandList;

class VertexSlotInfo
{
public:
    int32_t mSlot;
    uint32_t mVertexSize;
    std::shared_ptr<Ogre::HardwareVertexBuffer> hardwareVertexBuffer;
    void createBuffer(uint32_t vertexSize, uint32_t vertexCount);
    void writeData(const char* data, uint32_t size);
};

class VertexData
{
public:
    typedef std::vector<VertexBoneAssignment> VertexBoneAssignmentList;
public:
    VertexData();
    ~VertexData();

    void buildHardBuffer();
    void bind();

    void setBinding(int32_t index, std::shared_ptr<Ogre::HardwareVertexBuffer>& buf);

    std::shared_ptr<Ogre::HardwareVertexBuffer> getBuffer(int32_t index) const;
public:
    uint32_t vertexStart = 0;
    uint32_t vertexCount = 0;
    VertexDeclaration* vertexDeclaration = nullptr;
    std::vector<VertexSlotInfo> vertexSlotInfo;
    VertexBoneAssignmentList mBoneAssignments;
};