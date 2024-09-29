#include <OgreHeader.h>
#include "VulkanLayoutCache.h"

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

VulkanLayoutCache::Key fromBackendLayout(const std::vector<DescriptorSetLayoutBindingInfo>& layout)
{
    VulkanLayoutCache::Key mask;
    for (auto const& binding : layout) {
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

VkDescriptorSetLayout VulkanLayoutCache::getLayout(const std::vector<DescriptorSetLayoutBindingInfo>& layout) {
    Key key = fromBackendLayout(layout);
    if (auto iter = mLayouts.find(key); iter != mLayouts.end()) {
        return iter->second;
    }

    VkDescriptorSetLayoutBinding toBind[50];
    uint32_t count = 0;

    for (auto const& binding : layout) {
        VkShaderStageFlags stages = 0;
        VkDescriptorType type;

        if (binding.stageFlags & descset::ShaderStageFlags2::VERTEX) {
            stages |= VK_SHADER_STAGE_VERTEX_BIT;
        }
        if (binding.stageFlags & descset::ShaderStageFlags2::FRAGMENT) {
            stages |= VK_SHADER_STAGE_FRAGMENT_BIT;
        }
        assert_invariant(stages != 0);

        switch (binding.type) {
        case descset::DescriptorType::UNIFORM_BUFFER: {
            type = binding.flags == descset::DescriptorFlags::DYNAMIC_OFFSET
                ? VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC
                : VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            break;
        }
        case descset::DescriptorType::SAMPLER: {
            type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            break;
        }
        case descset::DescriptorType::INPUT_ATTACHMENT: {
            type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
            break;
        }
        }
        toBind[count++] = {
                .binding = binding.binding,
                .descriptorType = type,
                .descriptorCount = 1,
                .stageFlags = stages,
        };
    }

    if (count == 0) {
        return VK_NULL_HANDLE;
    }

    VkDescriptorSetLayoutCreateInfo dlinfo = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .pNext = nullptr,
            .bindingCount = count,
            .pBindings = toBind,
    };

    VkDescriptorSetLayoutCreateInfo descriptorLayout =
        vks::initializers::descriptorSetLayoutCreateInfo(
            &toBind[0],
            count);

    VkDescriptorSetLayout vklayout;

    
    vkCreateDescriptorSetLayout(mDevice, &descriptorLayout,
        nullptr, &vklayout);

    mLayouts[key] = vklayout;

    return vklayout;
}