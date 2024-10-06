#pragma once
#include <d3d11_1.h>
#include <d3d11shader.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <engine_struct.h>
#include "LightHelper.h"

class Dx11RenderSystem;
class VertexDeclaration;



class Dx11Shader
{
public:
    typedef std::vector<D3D11_SIGNATURE_PARAMETER_DESC> D3d11ShaderParameters;
public:
    Dx11Shader(
        ShaderInfo& info,
        Dx11RenderSystem* rs);
    // activate the shader


    bool load();
    ID3D11InputLayout* getLayoutEx()
    {
        return mDx11InputLayout2;
    }

    ID3D11VertexShader* getVertexShader()
    {
        return mDx11VertexShader;
    }

    ID3D11PixelShader* getPixelShader()
    {
        return mDx11PixelShader;
    }

    ID3D11Buffer* getConstanctBuffersVS()
    {
        return mConstantBuffersVS;
    }

    const D3d11ShaderParameters& getShaderInputParameters();

    void updateInputDesc(VertexDeclaration* vDeclaration);

    void bind() const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);

private:
    Dx11RenderSystem* mRenderSystem = nullptr;
    ID3DBlob* mDx11BlobOutVS = nullptr;
    ID3DBlob* mDx11BlobOutPS = nullptr;
    ID3D11VertexShader* mDx11VertexShader = nullptr;
    ID3D11PixelShader* mDx11PixelShader = nullptr;

    ID3D11Buffer* mConstantBuffersVS = nullptr;
    ID3D11Buffer* mConstantBuffersPS = nullptr;
    ID3D11InputLayout* mDx11InputLayout2 = nullptr;
    						
    FrameConstantBuffer m_FrameConstantBuffer;						

    D3d11ShaderParameters mD3d11ShaderInputParameters;
    std::vector<std::string*> mSerStrings;

    std::vector<D3D11_INPUT_ELEMENT_DESC> mInputDesc;

    ShaderInfo mShaderInfo;
};
