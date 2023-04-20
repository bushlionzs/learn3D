#include "OgreHeader.h"
#include "dx12Shader.h"
#include "dx12RenderSystem.h"
#include "vertex_declaration.h"
#include "myutils.h"
#include "d3dutil.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "OgreMaterial.h"
#include "dx12Common.h"
#include "D3D12Mappings.h"
#include "shaderManager.h"
#include "OgreResourceManager.h"
#include "dx12Helper.h"


Dx12Shader::Dx12Shader(ShaderInfo& info)
{
    mShaderInfo = info;
}

Dx12Shader::~Dx12Shader()
{

}

bool Dx12Shader::load()
{
    Ogre::ShaderPrivateInfo* privateInfo =
        ShaderManager::getSingleton().getShader(mShaderInfo.shaderName, EngineType_Dx12);

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

    auto res = ResourceManager::getSingleton().getResource(privateInfo->vertexShaderName);

    String* vertexContent = ShaderManager::getSingleton().getShaderContent(privateInfo->vertexShaderName);
    mvsByteCode = d3dUtil::CompileShader(
        *vertexContent, 
        macro, 
        privateInfo->vertexShaderEntryPoint.c_str(), 
        "vs_5_0",
        res->_fullname);

    String* fragContent = ShaderManager::getSingleton().getShaderContent(privateInfo->fragShaderName);

    res = ResourceManager::getSingleton().getResource(privateInfo->fragShaderName);
    mpsByteCode = d3dUtil::CompileShader(
        *fragContent, 
        macro, 
        privateInfo->fragShaderEntryPoint.c_str(), 
        "ps_5_0",
        res->_fullname);

    ID3D12ShaderReflection* shaderReflection = nullptr;

    HRESULT hr = D3DReflect((void*)mvsByteCode->GetBufferPointer(), mvsByteCode->GetBufferSize(),
        IID_ID3D11ShaderReflection, (void**)&shaderReflection);

    D3D12_SHADER_DESC shaderDesc;
    hr = shaderReflection->GetDesc(&shaderDesc);

    mD3d12ShaderInputParameters.resize(shaderDesc.InputParameters);
    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D12_SIGNATURE_PARAMETER_DESC& curParam = mD3d12ShaderInputParameters[i];
        shaderReflection->GetInputParameterDesc(i, &curParam);
        std::string* name = new std::string(curParam.SemanticName);
        mSerStrings.push_back(name);
        curParam.SemanticName = &(*name)[0];
    }
    ReleaseCOM(shaderReflection);
    return true;
}

DXGI_FORMAT dx12GetType(VertexElementType vType)
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

void Dx12Shader::updateInputDesc(VertexDeclaration* vDeclaration)
{
    if (!mInputDesc.empty())
    {
        return;
    }
    const VertexDeclaration::VertexElementList& elementList = vDeclaration->getElementList();

    std::vector<D3D12_INPUT_ELEMENT_DESC> D3delems;

    for (auto& it : mD3d12ShaderInputParameters)
    {
        D3D12_INPUT_ELEMENT_DESC elem = {};
        for (const auto& e : elementList)
        {
            LPCSTR semanticName = D3D12Mappings::getSemanticName(e.getSemantic());
            if (strcmp(semanticName, it.SemanticName) == 0 && e.getIndex() == it.SemanticIndex)
            {
                elem.Format = dx12GetType(e.getType());
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
        elem.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
        elem.InstanceDataStepRate = 0;

        D3delems.push_back(elem);
    }

    D3delems.swap(mInputDesc);
}


ID3D12PipelineState* Dx12Shader::BuildPSO(Dx12Pass* pass)
{
    return BuildNormalPSO(pass);
}

ID3D12PipelineState* Dx12Shader::BuildNormalPSO(Dx12Pass* pass)
{
    if (!mPSO)
    {
        ID3D12Device* device = DX12Helper::getSingleton().getDevice();
        ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));

        auto desc = getInputDesc();
        psoDesc.InputLayout = { desc.data(), (UINT)desc.size() };
        psoDesc.pRootSignature = pass->mRootSignature;

        ID3DBlob* vsblob = getVsBlob();
        psoDesc.VS =
        {
            reinterpret_cast<BYTE*>(vsblob->GetBufferPointer()),
            vsblob->GetBufferSize()
        };

        ID3DBlob* psblob = getPsBlob();
        psoDesc.PS =
        {
            reinterpret_cast<BYTE*>(psblob->GetBufferPointer()),
            psblob->GetBufferSize()
        };
        psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
        //psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
        
        psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
        psoDesc.RasterizerState.FrontCounterClockwise = true;
        psoDesc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON;
        psoDesc.RasterizerState.MultisampleEnable = true;
        psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.SampleDesc.Count = DX12Helper::getSingleton().hasMsaa()?4:1;
        psoDesc.SampleDesc.Quality = 0;
        psoDesc.DSVFormat = DX12Helper::getSingleton().getDepthStencilFormat();

        if (!pass->mMaterial->isWriteDepth())
        {
            D3D12_DEPTH_STENCIL_DESC depthDSS;
            depthDSS.DepthEnable = true;
            depthDSS.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
            depthDSS.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
            depthDSS.StencilEnable = false;
            psoDesc.DepthStencilState = depthDSS;
        }

        auto blendState = pass->mMaterial->getBlendState();
        if (blendState.blendingEnabled())
        {
            D3D12_RENDER_TARGET_BLEND_DESC transparencyBlendDesc;

            transparencyBlendDesc.BlendEnable = true;
            transparencyBlendDesc.LogicOpEnable = false;
            transparencyBlendDesc.SrcBlend = D3D12Mappings::get(blendState.sourceFactor, false);
            transparencyBlendDesc.DestBlend = D3D12Mappings::get(blendState.destFactor, false);
            transparencyBlendDesc.BlendOp = D3D12Mappings::get(blendState.operation);
            transparencyBlendDesc.SrcBlendAlpha = D3D12Mappings::get(blendState.sourceFactorAlpha, true);
            transparencyBlendDesc.DestBlendAlpha = D3D12Mappings::get(blendState.destFactorAlpha, true);
            transparencyBlendDesc.BlendOpAlpha = D3D12Mappings::get(blendState.alphaOperation);
            transparencyBlendDesc.LogicOp = D3D12_LOGIC_OP_NOOP;
            transparencyBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

            psoDesc.BlendState.RenderTarget[0] = transparencyBlendDesc;
        }

        if (psoDesc.RasterizerState.FillMode == D3D12_FILL_MODE_WIREFRAME)
        {
            int kk = 0;
        }
        ThrowIfFailed(device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPSO)));
    }

    
    return mPSO.Get();
}
