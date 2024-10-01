#include <OgreHeader.h>
#include "VulkanLayoutCache.h"



VkDescriptorSetLayout VulkanLayoutCache::getLayout(descset::DescriptorSetLayout& layout) {
    Key key = VulkanDescriptorSetLayout::Bitmask::fromBackendLayout(layout);
    if (auto iter = mLayouts.find(key); iter != mLayouts.end()) {
        return iter->second;
    }

    VkDescriptorSetLayoutBinding toBind[50];
    uint32_t count = 0;

    for (auto const& binding : layout.bindings) {
        VkShaderStageFlags stages = 0;
        VkDescriptorType type;

        if (binding.stageFlags & ShaderStageFlags2::VERTEX) {
            stages |= VK_SHADER_STAGE_VERTEX_BIT;
        }
        if (binding.stageFlags & ShaderStageFlags2::FRAGMENT) {
            stages |= VK_SHADER_STAGE_FRAGMENT_BIT;
        }
        assert_invariant(stages != 0);

        switch (binding.type) {
        case DescriptorType::UNIFORM_BUFFER: {
            type = binding.flags == DescriptorFlags::DYNAMIC_OFFSET
                ? VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC
                : VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            break;
        }
        case DescriptorType::SAMPLER: {
            type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            break;
        }
        case DescriptorType::INPUT_ATTACHMENT: {
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