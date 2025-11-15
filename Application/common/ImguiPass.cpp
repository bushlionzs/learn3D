#include <OgreHeader.h>
#include "ImguiPass.h"
#include "imgui.h"
#include "OgreVertexDeclaration.h"
#include "OgreResourceManager.h"
#include <windows.h>

ImGuiPass::ImGuiPass(RenderPassInput& input, ImGuiPassCallback cb)
{
    mRenderPassInput = input;
    mCallback = cb;
    init();
}

ImGuiPass::~ImGuiPass()
{

}



void ImGuiPass::execute(RenderContext& context)
{
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    newFrame();
    updateBuffers(context);
    RenderPassInfo renderPassInfo;
    renderPassInfo.renderTargetCount = 1;
    renderPassInfo.renderTargets[0].target.renderTarget = mRenderPassInput.color;
    renderPassInfo.depthTarget.target.depthStencil = mRenderPassInput.depth;
    renderPassInfo.depthTarget.depthIndex = 0;
    renderPassInfo.renderTargets[0].clearColour = { 0.0, 0.0, 0.0, 1.000000000f };
    renderPassInfo.viewport = false;
    {
        Ogre::RenderTargetBarrier rtBarriers[] =
        {
            {
                mRenderPassInput.color,
                Ogre::RESOURCE_STATE_PRESENT,
                Ogre::RESOURCE_STATE_RENDER_TARGET
            }
        };
        rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers, &context.frameContext->cbh);
    }
    rs->beginRenderPass(renderPassInfo);
    ImDrawData* imDrawData = ImGui::GetDrawData();
    int32_t vertexOffset = 0;
    int32_t indexOffset = 0;
    if (imDrawData->CmdListsCount > 0) {
        uint32_t frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
        ImGuiFrameData& frameData = mFrameDataList[frameIndex];
        rs->bindPipeline(context.frameContext->cbh, mPipelineHandle);

        rs->bindVertexBuffer(context.frameContext->cbh, 0, &mVertexBufferHandle, nullptr);
        rs->bindIndexBuffer(context.frameContext->cbh, mIndexBufferHandle, 2, 0);
        
        rs->setViewport(0, 0, mWidth, mHeight, 0.0, 1.0, &context.frameContext->cbh);
        
        for (int32_t i = 0; i < imDrawData->CmdListsCount; i++)
        {
            const ImDrawList* cmd_list = imDrawData->CmdLists[i];
            for (int32_t j = 0; j < cmd_list->CmdBuffer.Size; j++)
            {
                const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[j];
                Ogre::OgreTexture* texture = reinterpret_cast<Ogre::OgreTexture*>(pcmd->TextureId);

                filament::backend::Handle<filament::backend::HwDescriptorSet> descSet = getDescriptorSet(texture);
               
                 rs->bindDescriptorSet(context.frameContext->cbh, mProgramHandle, descSet);
                
                uint32_t x = std::max((int32_t)(pcmd->ClipRect.x), 0);
                uint32_t y = std::max((int32_t)(pcmd->ClipRect.y), 0);
                uint32_t width = (uint32_t)(pcmd->ClipRect.z - pcmd->ClipRect.x);
                uint32_t height = (uint32_t)(pcmd->ClipRect.w - pcmd->ClipRect.y);

                rs->setScissor(x, y, width, height, &context.frameContext->cbh);
                rs->drawIndexed(pcmd->ElemCount, 1, indexOffset, vertexOffset, 0, &context.frameContext->cbh);
                indexOffset += pcmd->ElemCount;
            }
            vertexOffset += cmd_list->VtxBuffer.Size;
        }
    }

    rs->endRenderPass(renderPassInfo);

    {
        Ogre::RenderTargetBarrier rtBarriers[] =
        {
            {
                mRenderPassInput.color,
                Ogre::RESOURCE_STATE_RENDER_TARGET,
                Ogre::RESOURCE_STATE_PRESENT
            }
        };
        rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers, nullptr);
    }

    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
}

void ImGuiPass::update(float delta)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)mWidth, (float)mHeight);
    io.DeltaTime = delta;

    io.MousePos = ImVec2(mMousePosition.x, mMousePosition.y);
    io.MouseDown[0] = left;
    io.MouseDown[1] = right;
    io.MouseDown[2] = middle;
}

void ImGuiPass::injectMouseMove(int _absx, int _absy, int _absz)
{
    mMousePosition.x = _absx;
    mMousePosition.y = _absy;
}

void ImGuiPass::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
    if (_id == OIS::MB_Left)
    {
        left = true;
    }
    else if (_id == OIS::MB_Right)
    {
        right = true;
    }
    else if (_id == OIS::MB_Middle)
    {
        middle = true;
    }
}

void ImGuiPass::injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id)
{
    if (_id == OIS::MB_Left)
    {
        left = false;
    }
    else if (_id == OIS::MB_Right)
    {
        right = false;
    }
    else if (_id == OIS::MB_Middle)
    {
        middle = false;
    }
}

void ImGuiPass::injectKeyPress(KeyCode _key, uint32_t _text)
{

}

void ImGuiPass::injectKeyRelease(KeyCode _key)
{

}

void ImGuiPass::injectMouseCursor()
{

}

void ImGuiPass::init()
{
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    ShaderInfo shaderInfo;
    auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();

    mWidth = ogreConfig.width;
    mHeight = ogreConfig.height;

    shaderInfo.shaderName = "imgui";
    VertexDeclaration decl;
    decl.addElement(0, 0, 0, Ogre::VET_FLOAT2, Ogre::VES_POSITION);
    decl.addElement(0, 0, 8, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
    decl.addElement(0, 0, 16, Ogre::VET_UBYTE4_NORM, Ogre::VES_COLOUR);
    mProgramHandle = rs->createShaderProgram(shaderInfo, &decl);
    filament::backend::RasterState rasterState;
    rasterState.blendEquationRGB = filament::backend::BlendEquation::ADD;
    rasterState.blendEquationAlpha = filament::backend::BlendEquation::ADD;
    rasterState.blendFunctionSrcRGB = filament::backend::BlendFunction::SRC_ALPHA;
    rasterState.blendFunctionDstRGB = filament::backend::BlendFunction::ONE_MINUS_SRC_ALPHA;
    rasterState.blendFunctionSrcAlpha = filament::backend::BlendFunction::ONE_MINUS_SRC_ALPHA; 
    rasterState.blendFunctionDstAlpha = filament::backend::BlendFunction::ZERO;
    rasterState.depthWrite = true;
    rasterState.depthTest = false;
    rasterState.depthFunc = filament::backend::SamplerCompareFunc::COMPARE_OP_LESS_OR_EQUAL;
    rasterState.colorWrite = true;
    rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_UNKNOWN;
    rasterState.renderTargetCount = 1;
    rasterState.depthBiasConstantFactor = 1.25f;
    rasterState.depthBiasSlopeFactor = 1.75f;

    mPipelineHandle = rs->createPipeline(rasterState, mProgramHandle);

    float left = 0.0f;
    float top = 0.0f;
    float right = mWidth;
    float bottom = mHeight;
    mProjectionMatrix =
        Ogre::Math::makeOrthoLH(left, right, bottom, top, 0.1, 1000.0f);
    mViewMatrix = Ogre::Matrix4::IDENTITY;

    
    imguiInit();
    bindReresource();

    InputManager::getSingleton().addListener(this);
}

void ImGuiPass::imguiInit()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.FontGlobalScale = 1.0f;
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(1.0f);

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    io.ConfigWindowsResizeFromEdges = true;

    ImGui::StyleColorsClassic();
    float font_size = 18.0f;
    float font_scale = 1.0f;
    ResourceInfo* resInfo = Ogre::ResourceManager::getSingleton().getResourceInfo("OpenSans-Medium.ttf");
    ImFont* font_normal = io.Fonts->AddFontFromFileTTF(resInfo->_fullname.c_str(), font_size * font_scale);
    resInfo = Ogre::ResourceManager::getSingleton().getResourceInfo("OpenSans-Bold.ttf");
    ImFont* font_bold = io.Fonts->AddFontFromFileTTF(resInfo->_fullname.c_str(), font_size * font_scale);
    io.FontGlobalScale = font_scale;

    io.DisplaySize = ImVec2(mWidth, mHeight);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    //io.KeyMap[ImGuiKey_Tab] = VK_TAB;
    //io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
    //io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
    //io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
    //io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
    //io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
    //io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
    //io.KeyMap[ImGuiKey_Space] = VK_SPACE;
    //io.KeyMap[ImGuiKey_Delete] = VK_DELETE;


    unsigned char* fontData;
    int texWidth = 0;
    int texHeight = 0;
    int bpp = 0;
    io.Fonts->GetTexDataAsRGBA32(&fontData, &texWidth, &texHeight, &bpp);
    uint32_t uploadSize = texWidth * texHeight * bpp;


    auto* rs = Ogre::Root::getSingleton().getRenderSystem();

    Ogre::TextureProperty tp;
    tp._width = texWidth;
    tp._height = texHeight;
    tp._need_mipmap = false;
    tp._tex_usage = Ogre::TEXTURE_USAGE_SAMPLING_BIT |
        Ogre::TEXTURE_USAGE_CAN_COPY_TO_BIT;
    mFontTexture = rs->createManualTexture("imguiImage", &tp);

    mFontTexture->uploadTextureData((const char*)fontData, uploadSize, tp);
}

void ImGuiPass::newFrame()
{
    ImGui::NewFrame();

    mCallback();

    ImGui::Render();
}

void ImGuiPass::updateBuffers(RenderContext& context)
{
    ImDrawData* imDrawData = ImGui::GetDrawData();

    if (imDrawData->TotalVtxCount == 0)
    {
        return;
    }

    uint64_t vertexBufferSize = imDrawData->TotalVtxCount * sizeof(ImDrawVert);
    uint64_t indexBufferSize = imDrawData->TotalIdxCount * sizeof(ImDrawIdx);

    auto* rs = Ogre::Root::getSingleton().getRenderSystem();

    if (mVertexCount < imDrawData->TotalVtxCount)
    {
        if (mVertexBufferHandle)
        {
            rs->destroyBufferObject(mVertexBufferHandle);
        }
        Ogre::BufferDesc desc{};
        desc.mBindingType = Ogre::BufferObjectBinding_Vertex;
        desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
        desc.bufferCreationFlags = 0;
        desc.mSize = vertexBufferSize;
        mVertexBufferHandle = rs->createBufferObject(desc);

        mVertexCount = imDrawData->TotalVtxCount;
    }

    if (mIndexCount < imDrawData->TotalIdxCount)
    {
        if (mIndexBufferHandle)
        {
            rs->destroyBufferObject(mIndexBufferHandle);
        }
        Ogre::BufferDesc desc{};
        desc.mBindingType = Ogre::BufferObjectBinding_Index;
        desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
        desc.bufferCreationFlags = 0;
        desc.mSize = indexBufferSize;
        mIndexBufferHandle = rs->createBufferObject(desc);

        mIndexCount = imDrawData->TotalIdxCount;
    }

    ImDrawVert* vtxDst = (ImDrawVert*)rs->bufferMap(mVertexBufferHandle);
    ImDrawIdx* idxDst = (ImDrawIdx*)rs->bufferMap(mIndexBufferHandle);

    for (int n = 0; n < imDrawData->CmdListsCount; n++) {
        const ImDrawList* cmd_list = imDrawData->CmdLists[n];
        memcpy(vtxDst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
        memcpy(idxDst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
        vtxDst += cmd_list->VtxBuffer.Size;
        idxDst += cmd_list->IdxBuffer.Size;
    }

    rs->bufferUnmap(mVertexBufferHandle, context.frameContext->cbh);
    rs->bufferUnmap(mIndexBufferHandle, context.frameContext->cbh);


    ImGuiUniform uniform;

    ImGuiIO& io = ImGui::GetIO();
    uniform.scale = Ogre::Vector2(2.0f / io.DisplaySize.x, 2.0f / io.DisplaySize.y);
    uniform.translate = Ogre::Vector2(-1.0f);

    auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();

    rs->updateBufferObject(mFrameDataList[frameIndex].cbPassHandle,
        (const char*)&uniform, sizeof(ImGuiUniform));
}


void ImGuiPass::bindReresource()
{
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();

    mFrameDataList.resize(2);

    filament::backend::SamplerParams params{};
    params.filterMag = filament::backend::SamplerFilterType::LINEAR;
    params.filterMin = filament::backend::SamplerFilterType::LINEAR;
    params.mipMapMode = filament::backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
    params.wrapS = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
    params.wrapT = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
    params.wrapR = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
    params.compareMode = filament::backend::SamplerCompareMode::COMPARE_TO_TEXTURE;
    params.compareFunc = filament::backend::SamplerCompareFunc::COMPARE_OP_LESS_OR_EQUAL;
    params.anisotropyLog2 = 0;
    params.useComparison = 0;
    params.maxLod = 0;
    params.padding2 = 0;
    mSamplerHandle =  rs->createTextureSampler(params);

    Ogre::DescriptorData descriptorData[16];
    for (uint32_t i = 0; i < 2; i++)
    {
        Ogre::BufferDesc desc{};
        desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
        desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
        desc.bufferCreationFlags = 0;
        desc.mSize = sizeof(ImGuiUniform);
        mFrameDataList[i].cbPassHandle = rs->createBufferObject(desc);
    }
}

filament::backend::Handle<filament::backend::HwDescriptorSet> ImGuiPass::getDescriptorSet(
    Ogre::OgreTexture* source)
{
    uint32_t frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();

    ImGuiFrameData& frameData = mFrameDataList[frameIndex];
    Ogre::OgreTexture* tex = source;
    if (tex == nullptr)
    {
        tex = mFontTexture;
    }
    auto itor = frameData.mDescriptorSetMap.find(tex);
    if (itor != frameData.mDescriptorSetMap.end())
    {
        return itor->second;
    }
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    auto descSet = rs->createDescriptorSet(mProgramHandle, 0);
    Ogre::DescriptorData descriptorData[16];
    descriptorData[0].mCount = 1;
    descriptorData[0].pName = "cbPass";
    descriptorData[0].descriptorType = Ogre::DESCRIPTOR_TYPE_BUFFER;
    descriptorData[0].ppBuffers = &frameData.cbPassHandle;

    descriptorData[1].mCount = 1;
    descriptorData[1].pName = "first";
    descriptorData[1].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[1].ppTextures = (const Ogre::OgreTexture**)&tex;

    descriptorData[2].mCount = 1;
    descriptorData[2].pName = "firstSampler";
    descriptorData[2].descriptorType = Ogre::DESCRIPTOR_TYPE_SAMPLER;
    descriptorData[2].ppSamplers = &mSamplerHandle;

    rs->updateDescriptorSet(descSet, 3, descriptorData);

    frameData.mDescriptorSetMap[tex] = descSet;
    return descSet;
}
