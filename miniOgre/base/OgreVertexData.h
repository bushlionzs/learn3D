#pragma once
#include "engine_struct.h"
#include "OgreHardwareVertexBuffer.h"
class VertexDeclaration;
class GraphicsCommandList;

class VertexSlotInfo
{
public:
    int32_t mSlot = -1;
    uint32_t mVertexSize = 0;
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
    static void updateFilamentVertexBuffer(VertexBuffer* vb, VertexData* vd);
    void bind(void* cb);
    bool empty()
    {
        return mVertexCount == 0;
    }
    HardwareBuffer* getBuffer(int32_t index) const;

    uint32_t getBufferCount();

    void setVertexCount(uint32_t vertexCount);

    uint32_t getVertexCount() const;

    void setVertexStart(uint32_t vertexStart)
    {
        mVertexStart = vertexStart;
    }

    uint32_t getVertexStart() const
    {
        return mVertexStart;
    }

    uint32_t getVertexSize(uint32_t binding) const;
    

    void removeAllElements();
    const VertexElement& addElement(
        int16_t source, 
        int16_t index, 
        int32_t offset, 
        VertexElementType theType,
        VertexElementSemantic semantic);

    VertexDeclaration* getVertexDeclaration() const
    {
        return vertexDeclaration;
    }

    int32_t addBindBuffer(uint32_t vertexSize, uint32_t vertexCount);
    void addBindBuffer(uint32_t binding, uint32_t vertexSize, uint32_t vertexCount);
    void updateBindBuffer(uint32_t binding, uint32_t vertexCount);
    void addBoneInfo(std::vector<VertexBoneAssignment>& assignInfoList);
    void writeBindBufferData(uint32_t binding, const char* data, uint32_t size, bool writeGPU = false);

    int32_t getUnusedBinding();

    void prepare();
    
    VertexBuffer* getVertexBuffer()
    {
        return mVertexBuffer;
    }

private:
    uint32_t mVertexStart = 0;
    uint32_t mVertexCount = 0;
    VertexDeclaration* vertexDeclaration = nullptr;
    std::array<VertexSlotInfo, 5> vertexSlotInfo;
    VertexBuffer* mVertexBuffer = nullptr;
};