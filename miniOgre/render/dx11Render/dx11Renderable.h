#pragma once

#include "OgreRenderable.h"
#include "shader.h"
#include "dx11UploadBuffer.h"
#include "renderHelper.h"

class Dx11Pass;

class Dx11RenderableData: public RenderableData
{
public:
    Dx11RenderableData(Ogre::Renderable* r);
    ~Dx11RenderableData();

    void updateData(Dx11Pass& pass, ICamera* cam);
private:
    void _initialise();
    void updateObject(ICamera* cam);
    ID3D11Buffer* getObjectBuffer(ICamera* cam);
    void applyMaterialTexture(Material* mat);
private:
    
    ObjectConstantBuffer mObjectConstantBuffer;

    std::unordered_map<Ogre::ICamera*, std::shared_ptr<Dx11UploadBuffer<ObjectConstantBuffer>>> mCamaraDataMap;

    MaterialConstantBuffer mMaterialConstantBuffer;
    PbrMaterialConstanceBuffer mPbrMaterialConstanceBuffer;
    std::unique_ptr<Dx11UploadBuffer<MaterialConstantBuffer>> mMaterialCB;
    std::unique_ptr<Dx11UploadBuffer<PbrMaterialConstanceBuffer>> mPbrMaterialCB;
    std::unique_ptr<Dx11UploadBuffer<SkinnedConstantBuffer>> mSkinnedCB;
};