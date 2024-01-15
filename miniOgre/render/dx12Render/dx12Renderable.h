#pragma once
#include <d3dutil.h>
#include "shader.h"
#include "UploadBuffer.h"
#include "OgreTexture.h"
#include "renderHelper.h"
class Dx12RenderSystem;
class Dx12Shader;
class RawData;
class Dx12Pass;

class FrameRenderableData
{
private:
    std::unordered_map<Ogre::ICamera*, std::shared_ptr<UploadBuffer<ObjectConstantBuffer>>> mCamaraDataMap;
    std::unique_ptr<UploadBuffer<MaterialConstantBuffer>> mMaterialCB;
    std::unique_ptr<UploadBuffer<PbrMaterialConstanceBuffer>> mPBrMaterialCB;
    std::unique_ptr<UploadBuffer<SkinnedConstantBuffer>> mSkinnedCB;
    
public:
    void _initialise();
    void updateObjectCB(ICamera* cam, ObjectConstantBuffer& cb);
    void updateMaterialCB(MaterialConstantBuffer& cb);
    void updateSkinnedCB(RawData* rd);

    D3D12_GPU_VIRTUAL_ADDRESS getObjectAddress(ICamera* cam);
    D3D12_GPU_VIRTUAL_ADDRESS getMaterialAddress();
    D3D12_GPU_VIRTUAL_ADDRESS getSkinnedAddress();
};

class Dx12RenderableData: public RenderableData
{
public:
    Dx12RenderableData(Dx12RenderSystem* engine, Ogre::Renderable* r);

    D3D12_GPU_VIRTUAL_ADDRESS getObjectAddress();

    D3D12_GPU_VIRTUAL_ADDRESS getMaterialAddress();

    D3D12_GPU_VIRTUAL_ADDRESS getSkinedAddress();

    void buildMaterial(Ogre::Material* mat);
    void updateCurrentFrame(int32_t index);
    void updateData(Dx12Pass* pass, Ogre::ICamera* cam);
    int32_t getTexStartIndex();
    int32_t getCubeTexStartIndex();

    void updateSkinedConstanctBuffer(RawData* rd);
private:
    void updateObjectConstantBuffer(Ogre::ICamera* cam);

    void updateMaterialConstantBuffer(Ogre::ICamera* cam);

    void updatePbrMaterialConstantBuffer(Ogre::ICamera* cam);

    
    void buildPbrMaterial(Ogre::Material* mat);
    void buildCommonMaterial(Ogre::Material* mat);
    void updatePbrTextureIndex(Ogre::TextureProperty* texProperty, uint32_t index);
private:
    std::vector<FrameRenderableData> mFrameRenderableDatas;
    FrameRenderableData* mCurrentFrameData;
    Dx12RenderSystem* mEngine;
    int32_t mTexCount = 0;
    int32_t mTexStartIndex = -1;
    int32_t mCubeTexCount = 0;
    int32_t mCubeTexStartIndex = -1;

    ObjectConstantBuffer mObjectConstantBuffer;
    MaterialConstantBuffer mMaterialConstantBuffer;
    PbrMaterialConstanceBuffer mPbrMaterialConstanceBuffer;

    ICamera* mCurrentCamera;
};