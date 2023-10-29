#include "OgreHeader.h"
#include "dx11Shader.h"
#include "dx11RenderSystem.h"
#include "vertex_declaration.h"
#include "myutils.h"
#include <d3dcompiler.h>
#include "shaderManager.h"
#include "dx11Helper.h"
#include "OgreResourceManager.h"

#define SAFE_RELEASE(p) { if ((p)) { (p)->Release(); (p) = nullptr; } }

Dx11Shader::Dx11Shader(ShaderInfo& info, Dx11RenderSystem* rs)
{
    mShaderInfo = info;
    mRenderSystem = rs;
    
}


bool Dx11Shader::load()
{
    Ogre::ShaderPrivateInfo* privateInfo = 
        ShaderManager::getSingleton().getShader(mShaderInfo.shaderName, EngineType_Dx11);

    const D3D_SHADER_MACRO* macro = nullptr;

    std::vector<D3D_SHADER_MACRO> macros;
    if (!mShaderInfo.shaderMacros.empty())
    {
        for (auto& o : mShaderInfo.shaderMacros)
        {
            macros.emplace_back();
            macros.back().Name = o.first.c_str();
            macros.back().Definition = o.second.c_str();
        }

        macros.emplace_back();
        macros.back().Name = NULL;
        macros.back().Definition = NULL;
    }

    macro = macros.data();

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // 设置 D3DCOMPILE_DEBUG 标志用于获取着色器调试信息。该标志可以提升调试体验，
    // 但仍然允许着色器进行优化操作
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // 在Debug环境下禁用优化以避免出现一些不合理的情况
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
    ID3DBlob* errorBlob = nullptr;
    
    String* content = ShaderManager::getSingleton().getShaderContent(privateInfo->vertexShaderName);
    auto res = ResourceManager::getSingleton().getResource(privateInfo->vertexShaderName);
    HRESULT hr = D3DCompile2(content->c_str(), content->size(), res->_fullname.c_str(), macro,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, privateInfo->vertexShaderEntryPoint.c_str(), "vs_5_0",
        dwShaderFlags, 0, 0, nullptr, 0, &mDx11BlobOutVS, &errorBlob);
    if (FAILED(hr))
    {
        if (errorBlob != nullptr)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
        }
        SAFE_RELEASE(errorBlob);
    }

    auto device = DX11Helper::getSingleton().getDevice();
    device->CreateVertexShader(mDx11BlobOutVS->GetBufferPointer(), mDx11BlobOutVS->GetBufferSize(),
        nullptr, &mDx11VertexShader);


    ID3D11ShaderReflection* shaderReflection = nullptr;

    hr = D3DReflect((void*)mDx11BlobOutVS->GetBufferPointer(), mDx11BlobOutVS->GetBufferSize(),
        IID_ID3D11ShaderReflection, (void**)&shaderReflection);

    D3D11_SHADER_DESC shaderDesc;
    hr = shaderReflection->GetDesc(&shaderDesc);

    mD3d11ShaderInputParameters.resize(shaderDesc.InputParameters);
    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC& curParam = mD3d11ShaderInputParameters[i];
        shaderReflection->GetInputParameterDesc(i, &curParam);
        std::string* name = new std::string(curParam.SemanticName);
        mSerStrings.push_back(name);
        curParam.SemanticName = &(*name)[0];
    }
    ReleaseCOM(shaderReflection);
    errorBlob = nullptr;

    content = ShaderManager::getSingleton().getShaderContent(privateInfo->fragShaderName);
    res = ResourceManager::getSingleton().getResource(privateInfo->fragShaderName);
    hr = D3DCompile2(content->c_str(), content->size(), res->_fullname.c_str(), macro,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, privateInfo->fragShaderEntryPoint.c_str(), "ps_5_0",
        dwShaderFlags, 0, 0, nullptr, 0, &mDx11BlobOutPS, &errorBlob);
    if (FAILED(hr))
    {
        if (errorBlob != nullptr)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
        }
        SAFE_RELEASE(errorBlob);
    }

    device->CreatePixelShader(mDx11BlobOutPS->GetBufferPointer(), mDx11BlobOutPS->GetBufferSize(),
        nullptr, &mDx11PixelShader);
    ReleaseCOM(mDx11BlobOutPS);

    

    return true;
}

void Dx11Shader::bind() const
{
    ID3D11DeviceContext* dx11Context = DX11Helper::getSingleton().getDeviceContext();
    dx11Context->VSSetShader(mDx11VertexShader, nullptr, 0);
    // VS常量缓冲区对应HLSL寄存于b0的常量缓冲区
    dx11Context->VSSetConstantBuffers(0, 1, &mConstantBuffersVS);
    // PS常量缓冲区对应HLSL寄存于b1的常量缓冲区
    dx11Context->PSSetConstantBuffers(1, 1, &mConstantBuffersPS);
    dx11Context->PSSetShader(mDx11PixelShader, nullptr, 0);
}

const Dx11Shader::D3d11ShaderParameters& Dx11Shader::getShaderInputParameters()
{
    return mD3d11ShaderInputParameters;
}


static LPCSTR dx11GetSemanticName(VertexElementSemantic sem)
{
    // todo - add to ogre - POSITIONT and PSIZE ("Transformed vertex position" and "Point size")
    switch (sem)
    {
    case VES_BLEND_INDICES:
        return "BLENDINDICES";
    case VES_BLEND_WEIGHTS:
        return "BLENDWEIGHT";
    case VES_DIFFUSE:
        return "COLOR"; // NB index will differentiate
    case VES_SPECULAR:
        return "COLOR"; // NB index will differentiate
    case VES_NORMAL:
        return "NORMAL";
    case VES_POSITION:
        return "POSITION";
    case VES_TEXTURE_COORDINATES:
        return "TEXCOORD";
    case VES_BINORMAL:
        return "BINORMAL";
    case VES_TANGENT:
        return "TANGENT";
    }
    // to keep compiler happy
    return "";
}


DXGI_FORMAT dx11GetType(VertexElementType vType)
{
    switch (vType)
    {
        // Float32
    case VET_FLOAT1:
        return DXGI_FORMAT_R32_FLOAT;
    case VET_FLOAT2:
        return DXGI_FORMAT_R32G32_FLOAT;
    case VET_FLOAT3:
        return DXGI_FORMAT_R32G32B32_FLOAT;
    case VET_FLOAT4:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;

        // Signed short
    case VET_SHORT1:
        return DXGI_FORMAT_R16_SINT;
    case VET_SHORT2:
        return DXGI_FORMAT_R16G16_SINT;
    case VET_SHORT4:
        return DXGI_FORMAT_R16G16B16A16_SINT;
    case VET_SHORT2_NORM:
        return DXGI_FORMAT_R16G16_SNORM;
    case VET_SHORT4_NORM:
        return DXGI_FORMAT_R16G16B16A16_SNORM;

        // Unsigned short
    case VET_USHORT1:
        return DXGI_FORMAT_R16_UINT;
    case VET_USHORT2:
        return DXGI_FORMAT_R16G16_UINT;
    case VET_USHORT4:
        return DXGI_FORMAT_R16G16B16A16_UINT;
    case VET_USHORT2_NORM:
        return DXGI_FORMAT_R16G16_UNORM;
    case VET_USHORT4_NORM:
        return DXGI_FORMAT_R16G16B16A16_UNORM;

        // Signed int
    case VET_INT1:
        return DXGI_FORMAT_R32_SINT;
    case VET_INT2:
        return DXGI_FORMAT_R32G32_SINT;
    case VET_INT3:
        return DXGI_FORMAT_R32G32B32_SINT;
    case VET_INT4:
        return DXGI_FORMAT_R32G32B32A32_SINT;

        // Unsigned int
    case VET_UINT1:
        return DXGI_FORMAT_R32_UINT;
    case VET_UINT2:
        return DXGI_FORMAT_R32G32_UINT;
    case VET_UINT3:
        return DXGI_FORMAT_R32G32B32_UINT;
    case VET_UINT4:
        return DXGI_FORMAT_R32G32B32A32_UINT;

    case VET_BYTE4:
        return DXGI_FORMAT_R8G8B8A8_SINT;
    case VET_BYTE4_NORM:
        return DXGI_FORMAT_R8G8B8A8_SNORM;
    case VET_UBYTE4:
        return DXGI_FORMAT_R8G8B8A8_UINT;
    case VET_UBYTE4_NORM:
        return DXGI_FORMAT_R8G8B8A8_UNORM;
    }
    // to keep compiler happy
    return DXGI_FORMAT_R32G32B32_FLOAT;
}

void Dx11Shader::updateInputDesc(VertexDeclaration* vDeclaration)
{
    if (!mInputDesc.empty())
    {
        return;
    }

    const VertexDeclaration::VertexElementList& elementList = vDeclaration->getElementList();

    std::vector<D3D11_INPUT_ELEMENT_DESC> D3delems;

    for (auto& it : mD3d11ShaderInputParameters)
    {
        D3D11_INPUT_ELEMENT_DESC elem = {};
        for (const auto& e : elementList)
        {
            LPCSTR semanticName = dx11GetSemanticName(e.getSemantic());
            if (strcmp(semanticName, it.SemanticName) == 0 && e.getIndex() == it.SemanticIndex)
            {
                elem.Format = dx11GetType(e.getType());
                elem.InputSlot = e.getSource();
                elem.AlignedByteOffset = static_cast<WORD>(e.getOffset());
                break;
            }
        }

        if (elem.Format == DXGI_FORMAT_UNKNOWN)
        {
            std::throw_with_nested("No VertexElement for semantic");
        }

        elem.SemanticName = it.SemanticName;
        elem.SemanticIndex = it.SemanticIndex;
        elem.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elem.InstanceDataStepRate = 0;

        D3delems.push_back(elem);
    }
    
    D3delems.swap(mInputDesc);

    int32_t size = mInputDesc.size();
    DX11Helper::getSingleton().getDevice()->CreateInputLayout(mInputDesc.data(), size,
        mDx11BlobOutVS->GetBufferPointer(), mDx11BlobOutVS->GetBufferSize(), &mDx11InputLayout2);
 
}

void Dx11Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    
}