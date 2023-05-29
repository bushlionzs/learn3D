#pragma once
#include <d3d12.h>
#include <d3d12shader.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "shader.h"
#include "UploadBuffer.h"
#include "engine_struct.h"

class Dx12RenderSystem;
class VertexDeclaration;
class Dx12Pass;

class Dx12Shader:public Shader
{
public:
    typedef std::vector<D3D12_SIGNATURE_PARAMETER_DESC> D3d12ShaderParameters;
public:
    Dx12Shader(ShaderInfo& info, bool shadow = false);
    // activate the shader

    ~Dx12Shader();

    bool load();

    ID3DBlob* getVsBlob()
    {
        return mvsByteCode.Get();
    }

    ID3DBlob* getPsBlob()
    {
        return mpsByteCode.Get();
    }
    
    const std::vector<D3D12_INPUT_ELEMENT_DESC>& getInputDesc()
    {
        return mInputDesc;
    }

    

    void updateInputDesc(VertexDeclaration* vDeclaration);
    

    ID3D12PipelineState* BuildPSO(
        Dx12Pass* pass);
private:
    ID3D12PipelineState* BuildNormalPSO(Dx12Pass* pass);
private:
    std::vector<std::string*> mSerStrings;

    std::vector<D3D12_INPUT_ELEMENT_DESC> mInputDesc;

    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

    Microsoft::WRL::ComPtr<ID3DBlob> mvsByteCode = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> mpsByteCode = nullptr;


    uint32_t mObjectCBSize = 0;

    Microsoft::WRL::ComPtr<ID3D12PipelineState> mPSO;
    D3d12ShaderParameters mD3d12ShaderInputParameters;

    ShaderInfo mShaderInfo;

    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;

    bool mShadow;
};
