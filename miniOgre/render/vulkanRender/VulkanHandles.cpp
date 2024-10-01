/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "OgreHeader.h"
#include "VulkanHandles.h"
#include "VulkanConstants.h"
#include "VulkanMemory.h"
#include "VulkanUtility.h"
#include "utils/Log.h"


#include <utils/Panic.h>    // ASSERT_POSTCONDITION

using namespace bluevk;

namespace filament::backend {

    namespace {

        void flipVertically(VkRect2D* rect, uint32_t framebufferHeight) {
            rect->offset.y = framebufferHeight - rect->offset.y - rect->extent.height;
        }

        void flipVertically(VkViewport* rect, uint32_t framebufferHeight) {
            rect->y = framebufferHeight - rect->y - rect->height;
        }

        void clampToFramebuffer(VkRect2D* rect, uint32_t fbWidth, uint32_t fbHeight) {
            int32_t x = std::max(rect->offset.x, 0);
            int32_t y = std::max(rect->offset.y, 0);
            int32_t right = std::min(rect->offset.x + (int32_t)rect->extent.width, (int32_t)fbWidth);
            int32_t top = std::min(rect->offset.y + (int32_t)rect->extent.height, (int32_t)fbHeight);
            rect->offset.x = std::min(x, (int32_t)fbWidth);
            rect->offset.y = std::min(y, (int32_t)fbHeight);
            rect->extent.width = std::max(right - x, 0);
            rect->extent.height = std::max(top - y, 0);
        }

        template<typename Bitmask>
        static constexpr Bitmask fromStageFlags(ShaderStageFlags2 flags, uint8_t binding) {
            Bitmask ret = 0;
            if (flags & ShaderStageFlags2::VERTEX) {
                ret |= (getVertexStage<Bitmask>() << binding);
            }
            if (flags & ShaderStageFlags2::FRAGMENT) {
                ret |= (getFragmentStage<Bitmask>() << binding);
            }
            return ret;
        }

        constexpr decltype(VulkanProgram::MAX_SHADER_MODULES) MAX_SHADER_MODULES =
            VulkanProgram::MAX_SHADER_MODULES;

        using LayoutDescriptionList = VulkanProgram::LayoutDescriptionList;

        template<typename Bitmask>
        void addDescriptors(Bitmask mask,
            utils::FixedCapacityVector<DescriptorSetLayoutBinding>& outputList) {
            constexpr uint8_t MODULE_OFFSET = (sizeof(Bitmask) * 8) / MAX_SHADER_MODULES;
            for (uint8_t i = 0; i < MODULE_OFFSET; ++i) {
                bool const hasVertex = (mask & (1ULL << i)) != 0;
                bool const hasFragment = (mask & (1ULL << (MODULE_OFFSET + i))) != 0;
                if (!hasVertex && !hasFragment) {
                    continue;
                }

                DescriptorSetLayoutBinding binding{
                    .binding = i,
                    .flags = DescriptorFlags::NONE,
                    .count = 0,// This is always 0 for now as we pass the size of the UBOs in the Driver API
                    // instead.
                };
                if (hasVertex) {
                    binding.stageFlags = ShaderStageFlags2::VERTEX;
                }
                if (hasFragment) {
                    binding.stageFlags = static_cast<ShaderStageFlags2>(
                        binding.stageFlags | ShaderStageFlags2::FRAGMENT);
                }
                if constexpr (std::is_same_v<Bitmask, UniformBufferBitmask>) {
                    binding.type = DescriptorType::UNIFORM_BUFFER;
                }
                else if constexpr (std::is_same_v<Bitmask, SamplerBitmask>) {
                    binding.type = DescriptorType::SAMPLER;
                }
                else if constexpr (std::is_same_v<Bitmask, InputAttachmentBitmask>) {
                    binding.type = DescriptorType::INPUT_ATTACHMENT;
                }
                outputList.push_back(binding);
            }
        }

        inline VkDescriptorSetLayout createDescriptorSetLayout(VkDevice device,
            VkDescriptorSetLayoutCreateInfo const& info) {
            VkDescriptorSetLayout layout;
            vkCreateDescriptorSetLayout(device, &info, VKALLOC, &layout);
            return layout;
        }

    } // anonymous namespace


    VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(VkDevice device, VkDescriptorSetLayoutCreateInfo const& info,
        Bitmask const& bitmask)
        : VulkanResource(VulkanResourceType::DESCRIPTOR_SET_LAYOUT),
        mDevice(device),
        vklayout(createDescriptorSetLayout(device, info)),
        bitmask(bitmask),
        bindings(getBindings(bitmask)),
        count(Count::fromLayoutBitmask(bitmask)) {
    }

    VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout() {
        vkDestroyDescriptorSetLayout(mDevice, vklayout, VKALLOC);
    }

    VulkanProgram::VulkanProgram(VkDevice device, Program const& builder) noexcept
        : HwProgram(builder.getName()),
        VulkanResource(VulkanResourceType::PROGRAM),
        mDevice(device) {
        assert(false);
    }

    VulkanProgram::~VulkanProgram() {
        for (auto shader : mInfo->shaders) {
            vkDestroyShaderModule(mDevice, shader, VKALLOC);
        }
        delete mInfo;
    }

    // Creates a special "default" render target (i.e. associated with the swap chain)
    VulkanRenderTarget::VulkanRenderTarget() :
        HwRenderTarget(0, 0),
        VulkanResource(VulkanResourceType::RENDER_TARGET),
        mOffscreen(false), mSamples(1) {}

    

    VulkanRenderTarget::VulkanRenderTarget(VkDevice device, VkPhysicalDevice physicalDevice,
        VulkanContext const& context, VmaAllocator allocator, VulkanCommands* commands,
        uint32_t width, uint32_t height, uint8_t samples,
        VulkanAttachment color[MRT::MAX_SUPPORTED_RENDER_TARGET_COUNT],
        VulkanAttachment depthStencil[2], VulkanStagePool& stagePool)
        : HwRenderTarget(width, height),
        VulkanResource(VulkanResourceType::RENDER_TARGET),
        mOffscreen(true),
        mSamples(samples) {
        
    }

    void VulkanRenderTarget::transformClientRectToPlatform(VkRect2D* bounds) const {
        const auto& extent = getExtent();
        flipVertically(bounds, extent.height);
        clampToFramebuffer(bounds, extent.width, extent.height);
    }

    void VulkanRenderTarget::transformClientRectToPlatform(VkViewport* bounds) const {
        flipVertically(bounds, getExtent().height);
    }

    VkExtent2D VulkanRenderTarget::getExtent() const {
        return { width, height };
    }

    VulkanAttachment& VulkanRenderTarget::getColor(int target) {
        return mColor[target];
    }

    VulkanAttachment& VulkanRenderTarget::getMsaaColor(int target) {
        return mMsaaAttachments[target];
    }

    VulkanAttachment& VulkanRenderTarget::getDepth() {
        return mDepth;
    }

    VulkanAttachment& VulkanRenderTarget::getMsaaDepth() {
        return mMsaaDepthAttachment;
    }

    uint8_t VulkanRenderTarget::getColorTargetCount(const VulkanRenderPass& pass) const {
        if (!mOffscreen) {
            return 1;
        }
        uint8_t count = 0;
        for (uint8_t i = 0; i < MRT::MAX_SUPPORTED_RENDER_TARGET_COUNT; i++) {
            if (!mColor[i].texture) {
                continue;
            }
            // NOTE: This must be consistent with VkRenderPass construction (see VulkanFboCache).
            if (!(pass.params.subpassMask & (1 << i)) || pass.currentSubpass == 1) {
                count++;
            }
        }
        return count;
    }

    VulkanVertexBufferInfo::VulkanVertexBufferInfo(
        uint8_t bufferCount, uint8_t attributeCount, AttributeArray const& attributes)
        : HwVertexBufferInfo(bufferCount, attributeCount),
        VulkanResource(VulkanResourceType::VERTEX_BUFFER_INFO),
        mInfo(attributes.size()) {

        
    }

    VulkanVertexBuffer::VulkanVertexBuffer(VulkanContext& context, VulkanStagePool& stagePool,
        VulkanResourceAllocator* allocator,
        uint32_t vertexCount, Handle<HwVertexBufferInfo> vbih)
        : HwVertexBuffer(vertexCount),
        VulkanResource(VulkanResourceType::VERTEX_BUFFER),
        vbih(vbih),
        mBuffers(MAX_VERTEX_BUFFER_COUNT), // TODO: can we do better here?
        mResources(allocator) {
    }

    void VulkanVertexBuffer::setBuffer(VulkanResourceAllocator const& allocator,
        VulkanBufferObject* bufferObject, uint32_t index) {

    }

    VulkanBufferObject::VulkanBufferObject(VmaAllocator allocator, VulkanStagePool& stagePool,
        uint32_t byteCount, BufferObjectBinding bindingType)
        : HwBufferObject(byteCount),
        VulkanResource(VulkanResourceType::BUFFER_OBJECT),
        buffer(allocator, stagePool, getBufferObjectUsage(bindingType), byteCount),
        bindingType(bindingType) {}

    VulkanTimerQuery::VulkanTimerQuery(std::tuple<uint32_t, uint32_t> indices)
        : VulkanThreadSafeResource(VulkanResourceType::TIMER_QUERY),
        mStartingQueryIndex(std::get<0>(indices)),
        mStoppingQueryIndex(std::get<1>(indices)) {}

    void VulkanTimerQuery::setFence(std::shared_ptr<VulkanCmdFence> fence) noexcept {
        std::unique_lock<utils::Mutex> lock(mFenceMutex);
        mFence = fence;
    }

    bool VulkanTimerQuery::isCompleted() noexcept {
       

        return true;
    }

    VulkanTimerQuery::~VulkanTimerQuery() = default;

    VulkanRenderPrimitive::VulkanRenderPrimitive(VulkanResourceAllocator* resourceAllocator,
        PrimitiveType pt, Handle<HwVertexBuffer> vbh, Handle<HwIndexBuffer> ibh)
        : VulkanResource(VulkanResourceType::RENDER_PRIMITIVE),
        mResources(resourceAllocator) {
        
    }

    using Bitmask = VulkanDescriptorSetLayout::Bitmask;

    Bitmask Bitmask::fromBackendLayout(descset::DescriptorSetLayout const& layout) {
        Bitmask mask;
        for (auto const& binding : layout.bindings) {
            switch (binding.type) {
            case descset::DescriptorType::UNIFORM_BUFFER: {
                if (binding.flags == descset::DescriptorFlags::DYNAMIC_OFFSET) {
                    mask.dynamicUbo |= fromStageFlags<UniformBufferBitmask>(binding.stageFlags,
                        binding.binding);
                }
                else {
                    mask.ubo |= fromStageFlags<UniformBufferBitmask>(binding.stageFlags,
                        binding.binding);
                }
                break;
            }
            case descset::DescriptorType::SAMPLER: {
                mask.sampler |= fromStageFlags<SamplerBitmask>(binding.stageFlags, binding.binding);
                break;
            }
            case descset::DescriptorType::INPUT_ATTACHMENT: {
                mask.inputAttachment |=
                    fromStageFlags<InputAttachmentBitmask>(binding.stageFlags, binding.binding);
                break;
            }
            }
        }
        return mask;
    }
    

} // namespace filament::backend
