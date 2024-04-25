/*
 * Copyright (C) 2019 The Android Open Source Project
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
#include "VulkanContext.h"
#include "VulkanTexture.h"
#include <backend/PixelBufferDescriptor.h>

#include <utils/Panic.h>
#include <utils/FixedCapacityVector.h>

#include <algorithm> // for std::max


using utils::FixedCapacityVector;


namespace {

} // end anonymous namespace

namespace filament::backend {

VkImage VulkanAttachment::getImage() const {
    return texture ? texture->getVkImage() : VK_NULL_HANDLE;
}

VkFormat VulkanAttachment::getFormat() const {
    return texture ? texture->getVkFormat() : VK_FORMAT_UNDEFINED;
}

VulkanLayout VulkanAttachment::getLayout() const {
    return VulkanLayout::UNDEFINED;
}

VkExtent2D VulkanAttachment::getExtent2D() const {
    assert_invariant(texture);
    return { std::max(1u, (uint32_t)texture->getWidth() >> level), std::max(1u, (uint32_t)texture->getHeight() >> level)};
}

VkImageView VulkanAttachment::getImageView(VkImageAspectFlags aspect) {
    assert_invariant(texture);
    return texture->getVkImageView();
}

VkImageSubresourceRange VulkanAttachment::getSubresourceRange(VkImageAspectFlags aspect) const {
    assert_invariant(texture);
    return {
            .aspectMask = aspect,
            .baseMipLevel = uint32_t(level),
            .levelCount = 1,
            .baseArrayLayer = uint32_t(layer),
            .layerCount = 1,
    };
}

} // namespace filament::backend
