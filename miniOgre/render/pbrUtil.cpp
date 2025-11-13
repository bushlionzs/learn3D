#include <OgreHeader.h>
#include "pbrUtil.h"
#include "OgreTexture.h"
#include "OgreRoot.h"
#include "renderSystem.h"
#include "OgreTextureManager.h"
#include "OgreMeshManager.h"
#include "OgreVertexData.h"
#include "OgreRenderTarget.h"

namespace Ogre
{
    Ogre::RenderTarget* generateCubeMap(
        filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
        Handle<HwCommandBuffer> cbh,
        const std::string& name,
        Ogre::OgreTexture* environmentCube,
        Ogre::PixelFormat format,
        int32_t dim,
        CubeType type)
    {
        Ogre::TextureProperty texProperty;
        texProperty._tex_usage = TEXTURE_USAGE_CAN_UPDATE_BIT | TEXTURE_USAGE_STORAGE_BIT;
        texProperty._texType = TEX_TYPE_CUBE_MAP;

        RenderSystem* rs = Root::getSingleton().getRenderSystem();
        texProperty._width = dim;
        texProperty._height = dim;
        texProperty._face = 6;
        texProperty._tex_format = format;
        Ogre::RenderTarget* rt = rs->createRenderTarget(name, texProperty);
        OgreTexture* cubeTexture = rt->getTarget();
        struct PushBlockIrradiance {
            Ogre::Matrix4 mvp;
            float deltaPhi = (2.0f * float(Ogre::Math::PI)) / 180.0f;
            float deltaTheta = (0.5f * float(Ogre::Math::PI)) / 64.0f;
        } pushBlockIrradiance;

        struct PushBlockPrefilterEnv {
            Ogre::Matrix4 mvp;
            float roughness;
            uint32_t numSamples = 32u;
        } pushBlockPrefilterEnv;

        ShaderInfo shaderInfo;

        uint32 pushBlockSize;
        if (type == CubeType_Irradiance)
        {
            pushBlockSize = sizeof(PushBlockIrradiance);
            shaderInfo.shaderName = "irradianceMap";
        }
        else
        {
            pushBlockSize = sizeof(PushBlockPrefilterEnv);
            shaderInfo.shaderName = "prefilteredMap";
        }
        std::string meshName = "box.mesh";
        auto mesh = MeshManager::getSingleton().createBox(meshName, 256, "SkyLan");
        auto* subMesh = mesh->getSubMesh(0);
        IndexData* indexData = subMesh->getIndexData();
        VertexData* vertexData = subMesh->getVertexData();
        VertexDeclaration* decl = vertexData->getVertexDeclaration();
        Handle<HwProgram> programHandle = rs->createShaderProgram(shaderInfo, decl);

        
        filament::backend::RasterState rasterState{};
        rasterState.colorWrite = true;
        rasterState.renderTargetCount = 1;
        rasterState.depthWrite = false;
        rasterState.depthTest = false;
        rasterState.pixelFormat[0] = format;

        Handle<HwPipeline> pipelineHandle = rs->createPipeline(rasterState, programHandle);
        BufferDesc desc{};
        desc.mBindingType = BufferObjectBinding_Uniform;
        desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
        desc.bufferCreationFlags = 0;
        desc.mSize = pushBlockSize;
        Handle<HwBufferObject> pushBlockHandle = rs->createBufferObject(desc);
        auto zeroDescSet = rs->createDescriptorSet(programHandle, 0);
        DescriptorData descriptorData[2];

        descriptorData[0].pName = "samplerEnv";
        descriptorData[0].mCount = 1;
        descriptorData[0].descriptorType = DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
        descriptorData[0].ppTextures = (const OgreTexture**) & environmentCube;

        descriptorData[1].pName = "pushConsts";
        descriptorData[1].mCount = 1;
        descriptorData[1].descriptorType = DESCRIPTOR_TYPE_BUFFER;
        descriptorData[1].ppBuffers = &pushBlockHandle;

        rs->updateDescriptorSet(zeroDescSet, 2, descriptorData);
        
        std::vector<Ogre::Matrix4> matrices = {
            Ogre::Math::makeRotateMatrix(Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, 90.0f, Ogre::Vector3(0.0f, 1.0f, 0.0f)), 180.0f, Ogre::Vector3(1.0f, 0.0f, 0.0f)),
            Ogre::Math::makeRotateMatrix(Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, -90.0f, Ogre::Vector3(0.0f, 1.0f, 0.0f)), 180.0f, Ogre::Vector3(1.0f, 0.0f, 0.0f)),
            Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, -90.0f, Ogre::Vector3(1.0f, 0.0f, 0.0f)),
            Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, 90.0f, Ogre::Vector3(1.0f, 0.0f, 0.0f)),
            Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, 180.0f, Ogre::Vector3(1.0f, 0.0f, 0.0f)),
            Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, 180.0f, Ogre::Vector3(0.0f, 0.0f, 1.0f)),
        };
       
        texProperty._width = dim;
        texProperty._height = dim;
        texProperty._tex_usage = TEXTURE_USAGE_COLOR_ATTACHMENT_BIT;
        texProperty._tex_format = format;
        texProperty._texType = TEX_TYPE_2D;
        texProperty._backgroudColor = ColourValue(0.678431f, 0.847058f, 0.901960f, 1.000000000f);
        texProperty._need_mipmap = false;
        texProperty._initState = RESOURCE_STATE_SHADER_RESOURCE;
        auto outPutTarget = rs->createRenderTarget("outputTarget", texProperty);

        RenderPassInfo renderPassInfo;
        renderPassInfo.renderTargetCount = 1;
        renderPassInfo.renderTargets[0].target.renderTarget = outPutTarget;
        renderPassInfo.depthTarget.target.depthStencil = nullptr;
        renderPassInfo.renderTargets[0].clearColour = { 0.678431f, 0.847058f, 0.901960f, 1.000000000f };
        renderPassInfo.viewport = false;
        renderPassInfo.cbh = cbh;
        const uint32_t numMips = static_cast<uint32_t>(floor(log2(dim))) + 1;

        

        rs->beginCommandBuffer(cbh);
        {
            RenderTargetBarrier uavBarriers[] = {
               {
               rt,
               RESOURCE_STATE_COMMON,
               RESOURCE_STATE_COPY_DEST},
            };
            rs->resourceBarrier(0, nullptr, 0, nullptr, 1, uavBarriers, &cbh);
        }

        {
            RenderTargetBarrier uavBarriers[] = {
               {
               outPutTarget,
               RESOURCE_STATE_SHADER_RESOURCE,
               RESOURCE_STATE_RENDER_TARGET},
            };
            rs->resourceBarrier(0, nullptr, 0, nullptr, 1, uavBarriers, &cbh);
        }
        rs->endCommandBuffer(cbh);
        rs->flushCmd(cqh, cbh, true);

        for (uint32_t m = 0; m < numMips; m++) 
        {
            for (uint32_t f = 0; f < 6; f++)
            {
                rs->beginCommandBuffer(cbh);
                uint32_t width = static_cast<float>(dim * std::pow(0.5f, m));
                uint32_t height = static_cast<float>(dim * std::pow(0.5f, m));

                auto perspective = Ogre::Math::makePerspectiveMatrixRH((float)(Ogre::Math::PI / 2.0), 1.0f, 0.1f, 512);
                if (type == CubeType_Irradiance)
                {
                    pushBlockIrradiance.mvp = perspective * matrices[f];
                    pushBlockIrradiance.mvp = pushBlockIrradiance.mvp.transpose();

                    rs->updateBufferObject(
                        pushBlockHandle,
                        (const char*)&pushBlockIrradiance,
                        sizeof(pushBlockIrradiance), 0, &cbh);

                }
                else
                {
                    pushBlockPrefilterEnv.mvp = perspective * matrices[f];
                    pushBlockPrefilterEnv.mvp = pushBlockPrefilterEnv.mvp.transpose();
                    pushBlockPrefilterEnv.roughness = (float)m / (float)(numMips - 1);

                    rs->updateBufferObject(
                        pushBlockHandle,
                        (const char*)&pushBlockPrefilterEnv,
                        sizeof(pushBlockPrefilterEnv), 0, &cbh);
                }
                rs->setViewport(0, 0, width, height, 0.0f, 1.0f, &cbh);
                rs->setScissor(0, 0, width, height, &cbh);
                rs->beginRenderPass(renderPassInfo);

                // Pass parameters for current pass using a push constant block
                rs->bindPipeline(cbh, pipelineHandle);
                rs->bindDescriptorSet(cbh, programHandle, zeroDescSet);

                auto bufHandle = vertexData->getBuffer(0);
                rs->bindVertexBuffer(cbh, 0, &bufHandle, nullptr);

                if (indexData)
                {
                    auto indexHandle = indexData->getHandle();
                    rs->bindIndexBuffer(cbh, indexHandle, indexData->getIndexSize(), 0);
                    
                    IndexDataView* view = subMesh->getIndexView();
                    rs->drawIndexed(view->mIndexCount, 1,
                        view->mIndexLocation, view->mBaseVertexLocation, 0, &cbh);
                }

                rs->endRenderPass(renderPassInfo);

                RenderTargetBarrier rtBarriers[] =
                {
                    {
                        outPutTarget,
                        RESOURCE_STATE_RENDER_TARGET,
                        RESOURCE_STATE_PRESENT
                    }
                };
                rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers, &cbh);

                ImageCopyDesc copyRegion;
                
                copyRegion.srcSubresource.aspectMask = 0;
                copyRegion.srcSubresource.baseArrayLayer = 0;
                copyRegion.srcSubresource.mipLevel = 0;
                copyRegion.srcSubresource.layerCount = 1;

                copyRegion.dstSubresource.aspectMask = 0;
                copyRegion.dstSubresource.baseArrayLayer = f;
                copyRegion.dstSubresource.mipLevel = m;
                copyRegion.dstSubresource.layerCount = 1;

                copyRegion.extent.width = width;
                copyRegion.extent.height = height;
                copyRegion.extent.depth = 1;
                copyRegion.srcOffset = Ogre::Vector3i(0);
                copyRegion.dstOffset = Ogre::Vector3i(0);
                rs->copyImage(cbh, rt, outPutTarget, copyRegion);

                rtBarriers[0] =
                {
                    outPutTarget,
                    RESOURCE_STATE_COPY_SOURCE,
                    RESOURCE_STATE_RENDER_TARGET
                };
                rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers, &cbh);
                rs->endCommandBuffer(cbh);
                rs->flushCmd(cqh, cbh, true);
            }
        }

        

        rs->beginCommandBuffer(cbh);
        {
            RenderTargetBarrier uavBarriers[] =
            {
                   rt,
                   RESOURCE_STATE_COPY_DEST,
                   RESOURCE_STATE_SHADER_RESOURCE
            };
            rs->resourceBarrier(0, nullptr, 0, nullptr, 1, uavBarriers, &cbh);
        }
        rs->endCommandBuffer(cbh);
        rs->flushCmd(cqh, cbh, true);

        return rt;
    }

    Ogre::RenderTarget* generateBRDFLUT(
        Handle<HwCommandQueue> cqh, 
        Handle<HwCommandBuffer> cbh,
        const std::string& name)
    {
        auto dim = 512;
        const uint32_t numMips = static_cast<uint32_t>(floor(log2(dim))) + 1;

        Ogre::TextureProperty texProperty;
        
        RenderSystem* rs = Root::getSingleton().getRenderSystem();

        texProperty._width = dim;
        texProperty._height = dim;
        texProperty._tex_usage = TEXTURE_USAGE_COLOR_ATTACHMENT_BIT;
        texProperty._tex_format = PF_FLOAT16_GR;
        texProperty._samplerParams.filterMag = filament::backend::SamplerFilterType::LINEAR;
        texProperty._samplerParams.filterMin = filament::backend::SamplerFilterType::LINEAR;
        texProperty._samplerParams.mipMapMode = filament::backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
        texProperty._samplerParams.wrapS = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
        texProperty._samplerParams.wrapT = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
        texProperty._samplerParams.wrapR = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
        texProperty._samplerParams.anisotropyLog2 = 0;
        texProperty._need_mipmap = false;
        texProperty._initState = RESOURCE_STATE_SHADER_RESOURCE;
        Ogre::RenderTarget* rt = rs->createRenderTarget(name, texProperty);
        ShaderInfo shaderInfo;
        shaderInfo.shaderName = "generateBRDFLUT";
        Handle<HwProgram> programHandle = rs->createShaderProgram(shaderInfo, nullptr);

       
        backend::RasterState rasterState;
        rasterState.colorWrite = true;
        rasterState.renderTargetCount = 1;
        rasterState.depthWrite = false;
        rasterState.depthTest = false;
        rasterState.pixelFormat[0] = PF_FLOAT16_GR;
        Handle<HwPipeline> pipelineHandle = rs->createPipeline(rasterState, programHandle);
        RenderPassInfo renderPassInfo;
        renderPassInfo.renderTargetCount = 1;
        renderPassInfo.renderTargets[0].target.renderTarget = rt;
        renderPassInfo.depthTarget.target.depthStencil = nullptr;
        renderPassInfo.renderTargets[0].clearColour = { 0.0f, 0.0f, 0.0f, 1.000000000f };
        renderPassInfo.cbh = cbh;

        rs->beginCommandBuffer(cbh);
        RenderTargetBarrier uavBarriers[] = {
               {
               rt,
               RESOURCE_STATE_SHADER_RESOURCE,
               RESOURCE_STATE_RENDER_TARGET},
        };
        rs->resourceBarrier(0, nullptr, 0, nullptr, 1, uavBarriers, &cbh);

        rs->beginRenderPass(renderPassInfo);
        rs->bindPipeline(cbh, pipelineHandle);
        rs->draw(3, 1, 0, 0, &cbh);
        rs->endRenderPass(renderPassInfo);

        uavBarriers[0] = {
               rt,
               RESOURCE_STATE_RENDER_TARGET,
               RESOURCE_STATE_SHADER_RESOURCE
        };
        rs->resourceBarrier(0, nullptr, 0, nullptr, 1, uavBarriers, &cbh);
        rs->endCommandBuffer(cbh);
        rs->flushCmd(cqh, cbh, true);

        return rt;
    }
}