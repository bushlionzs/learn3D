#pragma once

class HardwareIndexBuffer;


class IndexData
{
public:
    IndexData();
    ~IndexData();
    
    const std::shared_ptr<HardwareIndexBuffer>& getIndexBuffer()
    {
        return mIndexBuffer;
    }

    void createBuffer(uint32_t vertexSize, uint32_t indexCount);
    void writeData(const char* data, uint32_t size);

public:
    size_t mIndexStart = 0;
    size_t mIndexCount = 0;
    std::shared_ptr<HardwareIndexBuffer> mIndexBuffer;
};