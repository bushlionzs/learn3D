#pragma once

class HardwareIndexBuffer;

class IndexData
{
public:
    IndexData();
    ~IndexData();
    

    filament::backend::Handle<filament::backend::HwBufferObject> getHandle() const
    {
        return mIndexBufferHandle;
    }
    void bind();
    void bind(filament::backend::Handle<filament::backend::HwCommandBuffer>);
    void createBuffer(uint32_t indexSize, uint32_t indexCount);
    void writeData(const char* data, uint32_t size);

    uint32_t getIndexCount() const
    {
        return mIndexCount;
    }

    uint32_t getIndexSize() const
    {
        return mIndexSize;
    }

    void updateIndexCount(uint32_t indexCount)
    {
        mIndexCount = indexCount;
    }
private:
    uint32_t mIndexStart = 0;
    uint32_t mIndexCount = 0;
    uint32_t mIndexSize = 0;
    filament::backend::Handle<filament::backend::HwBufferObject> mIndexBufferHandle;
};