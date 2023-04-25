#pragma once
#include <d3d11_1.h>
#include "OgreRenderable.h"
#include "shader.h"
#include "dx11UploadBuffer.h"


class Dx11Pass;

class Dx11RenderableData
{
public:
    Dx11RenderableData();
    ~Dx11RenderableData();

    void updateData(Dx11Pass& pass, ICamera* cam);
private:
    void _initialise();
private:
    
    ObjectConstantBuffer mObjectConstantBuffer;

    std::unique_ptr<Dx11UploadBuffer<ObjectConstantBuffer>> mObjectCB;
    

    MaterialConstantBuffer mMaterialConstantBuffer;
    std::unique_ptr<Dx11UploadBuffer<MaterialConstantBuffer>> mMaterialCB;

    std::unique_ptr<Dx11UploadBuffer<SkinnedConstantBuffer>> mSkinnedCB;
};