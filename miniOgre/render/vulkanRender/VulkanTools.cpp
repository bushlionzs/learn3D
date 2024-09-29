/*
* Assorted commonly used Vulkan helper functions
*
* Copyright (C) 2016 by Sascha Willems - www.saschawillems.de
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "OgreHeader.h"
#include "VulkanTools.h"
#include "VulkanTexture.h"
#include "VulkanHelper.h"
#include "VulkanBuffer.h"
#include "glslUtil.h"
#include <spirv.hpp>
#include <platform_file.h>

namespace vks
{
	namespace tools
	{
		bool errorModeSilent = false;

		std::string errorString(VkResult errorCode)
		{
			switch (errorCode)
			{
#define STR(r) case VK_ ##r: return #r
				STR(NOT_READY);
				STR(TIMEOUT);
				STR(EVENT_SET);
				STR(EVENT_RESET);
				STR(INCOMPLETE);
				STR(ERROR_OUT_OF_HOST_MEMORY);
				STR(ERROR_OUT_OF_DEVICE_MEMORY);
				STR(ERROR_INITIALIZATION_FAILED);
				STR(ERROR_DEVICE_LOST);
				STR(ERROR_MEMORY_MAP_FAILED);
				STR(ERROR_LAYER_NOT_PRESENT);
				STR(ERROR_EXTENSION_NOT_PRESENT);
				STR(ERROR_FEATURE_NOT_PRESENT);
				STR(ERROR_INCOMPATIBLE_DRIVER);
				STR(ERROR_TOO_MANY_OBJECTS);
				STR(ERROR_FORMAT_NOT_SUPPORTED);
				STR(ERROR_SURFACE_LOST_KHR);
				STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
				STR(SUBOPTIMAL_KHR);
				STR(ERROR_OUT_OF_DATE_KHR);
				STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
				STR(ERROR_VALIDATION_FAILED_EXT);
				STR(ERROR_INVALID_SHADER_NV);
#undef STR
			default:
				return "UNKNOWN_ERROR";
			}
		}

		std::string physicalDeviceTypeString(VkPhysicalDeviceType type)
		{
			switch (type)
			{
#define STR(r) case VK_PHYSICAL_DEVICE_TYPE_ ##r: return #r
				STR(OTHER);
				STR(INTEGRATED_GPU);
				STR(DISCRETE_GPU);
				STR(VIRTUAL_GPU);
				STR(CPU);
#undef STR
			default: return "UNKNOWN_DEVICE_TYPE";
			}
		}

		VkBool32 getSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat *depthFormat)
		{
			// Since all depth formats may be optional, we need to find a suitable depth format to use
			// Start with the highest precision packed format
			std::vector<VkFormat> depthFormats = {
				VK_FORMAT_D32_SFLOAT_S8_UINT,
				VK_FORMAT_D32_SFLOAT,
				VK_FORMAT_D24_UNORM_S8_UINT,
				VK_FORMAT_D16_UNORM_S8_UINT,
				VK_FORMAT_D16_UNORM
			};

			for (auto& format : depthFormats)
			{
				VkFormatProperties formatProps;
				vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &formatProps);
				// Format must support depth stencil attachment for optimal tiling
				if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				{
					*depthFormat = format;
					return true;
				}
			}

			return false;
		}

		VkBool32 formatHasStencil(VkFormat format)
		{
			std::vector<VkFormat> stencilFormats = {
				VK_FORMAT_S8_UINT,
				VK_FORMAT_D16_UNORM_S8_UINT,
				VK_FORMAT_D24_UNORM_S8_UINT,
				VK_FORMAT_D32_SFLOAT_S8_UINT,
			};
			return std::find(stencilFormats.begin(), stencilFormats.end(), format) != std::end(stencilFormats);
		}

		// Returns if a given format support LINEAR filtering
		VkBool32 formatIsFilterable(VkPhysicalDevice physicalDevice, VkFormat format, VkImageTiling tiling)
		{
			VkFormatProperties formatProps;
			vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &formatProps);

			if (tiling == VK_IMAGE_TILING_OPTIMAL)
				return formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT;

			if (tiling == VK_IMAGE_TILING_LINEAR)
				return formatProps.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT;

			return false;
		}

		// Create an image memory barrier for changing the layout of
		// an image and put it into an active command buffer
		// See chapter 11.4 "Image Layout" for details

		void setImageLayout(
			VkCommandBuffer cmdbuffer,
			VkImage image,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkImageSubresourceRange subresourceRange,
			VkPipelineStageFlags srcStageMask,
			VkPipelineStageFlags dstStageMask)
		{
			// Create an image barrier object
			VkImageMemoryBarrier imageMemoryBarrier = vks::initializers::imageMemoryBarrier();
			imageMemoryBarrier.oldLayout = oldImageLayout;
			imageMemoryBarrier.newLayout = newImageLayout;
			imageMemoryBarrier.image = image;
			imageMemoryBarrier.subresourceRange = subresourceRange;

			// Source layouts (old)
			// Source access mask controls actions that have to be finished on the old layout
			// before it will be transitioned to the new layout
			switch (oldImageLayout)
			{
			case VK_IMAGE_LAYOUT_UNDEFINED:
				// Image layout is undefined (or does not matter)
				// Only valid as initial layout
				// No flags required, listed only for completeness
				imageMemoryBarrier.srcAccessMask = 0;
				break;

			case VK_IMAGE_LAYOUT_PREINITIALIZED:
				// Image is preinitialized
				// Only valid as initial layout for linear images, preserves memory contents
				// Make sure host writes have been finished
				imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
				// Image is a color attachment
				// Make sure any writes to the color buffer have been finished
				imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
				// Image is a depth/stencil attachment
				// Make sure any writes to the depth/stencil buffer have been finished
				imageMemoryBarrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
				// Image is a transfer source
				// Make sure any reads from the image have been finished
				imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
				// Image is a transfer destination
				// Make sure any writes to the image have been finished
				imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
				// Image is read by a shader
				// Make sure any shader reads from the image have been finished
				imageMemoryBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
				break;
			default:
				// Other source layouts aren't handled (yet)
				break;
			}

			// Target layouts (new)
			// Destination access mask controls the dependency for the new image layout
			switch (newImageLayout)
			{
			case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
				// Image will be used as a transfer destination
				// Make sure any writes to the image have been finished
				imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
				// Image will be used as a transfer source
				// Make sure any reads from the image have been finished
				imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				break;

			case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
				// Image will be used as a color attachment
				// Make sure any writes to the color buffer have been finished
				imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
				// Image layout will be used as a depth/stencil attachment
				// Make sure any writes to depth/stencil buffer have been finished
				imageMemoryBarrier.dstAccessMask = imageMemoryBarrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
				// Image will be read in a shader (sampler, input attachment)
				// Make sure any writes to the image have been finished
				if (imageMemoryBarrier.srcAccessMask == 0)
				{
					imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
				}
				imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
				break;
			default:
				// Other source layouts aren't handled (yet)
				break;
			}

			// Put barrier inside setup command buffer
			vkCmdPipelineBarrier(
				cmdbuffer,
				srcStageMask,
				dstStageMask,
				0,
				0, nullptr,
				0, nullptr,
				1, &imageMemoryBarrier);
		}

		// Fixed sub resource on first mip level and layer
		void setImageLayout(
			VkCommandBuffer cmdbuffer,
			VkImage image,
			VkImageAspectFlags aspectMask,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkPipelineStageFlags srcStageMask,
			VkPipelineStageFlags dstStageMask)
		{
			VkImageSubresourceRange subresourceRange = {};
			subresourceRange.aspectMask = aspectMask;
			subresourceRange.baseMipLevel = 0;
			subresourceRange.levelCount = 1;
			subresourceRange.layerCount = 1;
			setImageLayout(cmdbuffer, image, oldImageLayout, newImageLayout, subresourceRange, srcStageMask, dstStageMask);
		}

		void insertImageMemoryBarrier(
			VkCommandBuffer cmdbuffer,
			VkImage image,
			VkAccessFlags srcAccessMask,
			VkAccessFlags dstAccessMask,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkPipelineStageFlags srcStageMask,
			VkPipelineStageFlags dstStageMask,
			VkImageSubresourceRange subresourceRange)
		{
			VkImageMemoryBarrier imageMemoryBarrier = vks::initializers::imageMemoryBarrier();
			imageMemoryBarrier.srcAccessMask = srcAccessMask;
			imageMemoryBarrier.dstAccessMask = dstAccessMask;
			imageMemoryBarrier.oldLayout = oldImageLayout;
			imageMemoryBarrier.newLayout = newImageLayout;
			imageMemoryBarrier.image = image;
			imageMemoryBarrier.subresourceRange = subresourceRange;

			vkCmdPipelineBarrier(
				cmdbuffer,
				srcStageMask,
				dstStageMask,
				0,
				0, nullptr,
				0, nullptr,
				1, &imageMemoryBarrier);
		}

		void exitFatal(const std::string& message, int32_t exitCode)
		{
#if defined(_WIN32)
			if (!errorModeSilent) {
				MessageBox(NULL, message.c_str(), NULL, MB_OK | MB_ICONERROR);
			}
#elif defined(__ANDROID__)
            LOGE("Fatal error: %s", message.c_str());
			vks::android::showAlert(message.c_str());
#endif
			std::cerr << message << "\n";
#if !defined(__ANDROID__)
			exit(exitCode);
#endif
		}

		void exitFatal(const std::string& message, VkResult resultCode)
		{
			exitFatal(message, (int32_t)resultCode);
		}


		VkShaderModule loadShaderBinary(const char *fileName, VkDevice device)
		{
			std::ifstream is(fileName, std::ios::binary | std::ios::in | std::ios::ate);

			if (is.is_open())
			{
				size_t size = is.tellg();
				is.seekg(0, std::ios::beg);
				char* shaderCode = new char[size];
				is.read(shaderCode, size);
				is.close();

				assert(size > 0);

				VkShaderModule shaderModule;
				VkShaderModuleCreateInfo moduleCreateInfo{};
				moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				moduleCreateInfo.codeSize = size;
				moduleCreateInfo.pCode = (uint32_t*)shaderCode;

				VK_CHECK_RESULT(vkCreateShaderModule(device, &moduleCreateInfo, NULL, &shaderModule));

				delete[] shaderCode;

				return shaderModule;
			}
			else
			{
				std::cerr << "Error: Could not open shader file \"" << fileName << "\"" << "\n";
				return VK_NULL_HANDLE;
			}
		}

		VkShaderModule loadShaderAssic(const char* fileName, VkDevice device, Ogre::ShaderType type)
		{
			std::string content;
			get_file_content(fileName, content);

			std::string result;
			std::string strName(fileName);
			std::string entryPoint("main");
			std::vector<std::pair<std::string, std::string>> shaderMacros;
			shaderc_shader_kind kind = shaderc_glsl_vertex_shader;
			std::vector<GlslInputDesc> inputDesc;
			VkShaderModuleInfo shaderModuleInfo;
			switch (type)
			{
			case VertexShader:
				shaderModuleInfo.shaderType = Ogre::ShaderType::VertexShader;
				glslCompileShader(strName, content, entryPoint, shaderMacros, shaderModuleInfo);
				break;
			case PixelShader:
				shaderModuleInfo.shaderType = Ogre::ShaderType::PixelShader;
				glslCompileShader(strName, content, entryPoint, shaderMacros, shaderModuleInfo);
				break;
			default:
				assert(false);
				break;
			}
			return shaderModuleInfo.shaderModule;
		}

		VkShaderModule loadShaderMemory(const std::string& code, VkDevice device)
		{
			VkShaderModule shaderModule;
			VkShaderModuleCreateInfo moduleCreateInfo{};
			moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			moduleCreateInfo.codeSize = code.size();
			moduleCreateInfo.pCode = (uint32_t*)code.data();

			VK_CHECK_RESULT(vkCreateShaderModule(device, &moduleCreateInfo, NULL, &shaderModule));

			return shaderModule;
		}

		bool fileExists(const std::string &filename)
		{
			std::ifstream f(filename.c_str());
			return !f.fail();
		}

		uint32_t alignedSize(uint32_t value, uint32_t alignment)
        {
	        return (value + alignment - 1) & ~(alignment - 1);
        }

		uint64_t getBufferDeviceAddress(VkDevice device, VkBuffer buffer)
		{
			VkBufferDeviceAddressInfoKHR bufferDeviceAI{};
			bufferDeviceAI.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
			bufferDeviceAI.buffer = buffer;
			return vkGetBufferDeviceAddressKHR(device, &bufferDeviceAI);
		}

		uint64_t getBufferDeviceAddress(VulkanBuffer* buffer)
		{
			VkBufferDeviceAddressInfoKHR bufferDeviceAI{};
			bufferDeviceAI.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
			bufferDeviceAI.buffer = buffer->buffer;
			return vkGetBufferDeviceAddressKHR(buffer->device, &bufferDeviceAI);
		}

		void copyBufferToImage(
			VkCommandBuffer commandBuffer,
			VkBuffer buffer,
			VkImage image,
			VulkanTexture* tex)
		{
			uint32_t mipLevels = tex->getSourceMipmaps() + 1;
			uint32_t face_count = tex->getFace();

			std::vector<VkBufferImageCopy> regions;
			regions.reserve(face_count * mipLevels);

			uint32_t offset = 0;
			for (uint32_t face = 0; face < face_count; face++)
			{
				uint32_t width = tex->getWidth();
				uint32_t height = tex->getHeight();
				for (uint32_t i = 0; i < mipLevels; i++)
				{
					VkBufferImageCopy bufferCopyRegion = {};
					bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					bufferCopyRegion.imageSubresource.mipLevel = i;
					bufferCopyRegion.imageSubresource.baseArrayLayer = face;
					bufferCopyRegion.imageSubresource.layerCount = 1;
					bufferCopyRegion.imageExtent.width = width;
					bufferCopyRegion.imageExtent.height = height;
					bufferCopyRegion.imageExtent.depth = 1;
					bufferCopyRegion.bufferOffset = offset;
					regions.push_back(bufferCopyRegion);

					if (width > 1)width /= 2;
					if (height > 1)height /= 2;
					offset += tex->getBuffer(face, i)->getSizeInBytes();
				}
			}


			VkImageSubresourceRange subresourceRange = {};
			subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			subresourceRange.baseMipLevel = 0;
			subresourceRange.levelCount = mipLevels;
			subresourceRange.layerCount = face_count;

			vks::tools::setImageLayout(
				commandBuffer,
				image,
				VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				subresourceRange);
			vkCmdCopyBufferToImage(commandBuffer, buffer, image,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, (uint32_t)regions.size(), regions.data());

			insertImageMemoryBarrier(
				commandBuffer,
				image,
				VK_ACCESS_TRANSFER_WRITE_BIT,
				VK_ACCESS_TRANSFER_READ_BIT,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				VK_PIPELINE_STAGE_TRANSFER_BIT,
				VK_PIPELINE_STAGE_TRANSFER_BIT,
				subresourceRange);
		}

		void generateMipmaps(VkCommandBuffer commandBuffer, VulkanTexture* tex)
		{
			auto mipLevels = tex->getMipLevels();
			uint32_t face_count = tex->getFace();
			

			VkImage image = tex->getVkImage();

			VkImageSubresourceRange subresourceRange = {};
			subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			subresourceRange.layerCount = face_count;
			subresourceRange.baseArrayLayer = 0;
			subresourceRange.baseMipLevel = 0;
			subresourceRange.levelCount = 1;
			insertImageMemoryBarrier(
				commandBuffer,
				image,
				VK_ACCESS_TRANSFER_READ_BIT,
				VK_ACCESS_SHADER_READ_BIT,
				VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
				VK_PIPELINE_STAGE_TRANSFER_BIT,
				VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
				subresourceRange);

			for (auto face = 0; face < face_count; face++)
			{
				uint32_t width = tex->getTextureProperty()->_width;
				uint32_t height = tex->getTextureProperty()->_height;
				

				for (uint32_t i = 1; i < mipLevels; i++) {
					VkImageBlit imageBlit{};
					VkImageSubresourceRange mipSubRange = {};
					mipSubRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					mipSubRange.baseMipLevel = i;
					mipSubRange.levelCount = 1;
					mipSubRange.layerCount = 1;
					mipSubRange.baseArrayLayer = face;

					insertImageMemoryBarrier(
						commandBuffer,
						image,
						0,
						VK_ACCESS_TRANSFER_WRITE_BIT,
						VK_IMAGE_LAYOUT_UNDEFINED,
						VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
						VK_PIPELINE_STAGE_TRANSFER_BIT,
						VK_PIPELINE_STAGE_TRANSFER_BIT,
						mipSubRange);

					imageBlit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					imageBlit.srcSubresource.layerCount = 1;
					imageBlit.srcSubresource.mipLevel = i - 1;
					imageBlit.srcSubresource.baseArrayLayer = face;
					imageBlit.srcOffsets[1].x = int32_t(width >> (i - 1));
					imageBlit.srcOffsets[1].y = int32_t(height >> (i - 1));
					imageBlit.srcOffsets[1].z = 1;

					imageBlit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					imageBlit.dstSubresource.layerCount = 1;
					imageBlit.dstSubresource.mipLevel = i;
					imageBlit.dstSubresource.baseArrayLayer = face;
					imageBlit.dstOffsets[1].x = int32_t(width >> i);
					imageBlit.dstOffsets[1].y = int32_t(height >> i);
					imageBlit.dstOffsets[1].z = 1;

					vkCmdBlitImage(commandBuffer, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &imageBlit, VK_FILTER_LINEAR);

					insertImageMemoryBarrier(
						commandBuffer,
						image,
						VK_ACCESS_TRANSFER_WRITE_BIT,
						VK_ACCESS_TRANSFER_READ_BIT,
						VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
						VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
						VK_PIPELINE_STAGE_TRANSFER_BIT,
						VK_PIPELINE_STAGE_TRANSFER_BIT,
						mipSubRange);
				}
			}

			subresourceRange.baseMipLevel = 0;
			subresourceRange.levelCount = mipLevels;
			subresourceRange.baseArrayLayer = 0;
			subresourceRange.layerCount = face_count;
			insertImageMemoryBarrier(
				commandBuffer,
				image,
				VK_ACCESS_TRANSFER_READ_BIT,
				VK_ACCESS_SHADER_READ_BIT,
				VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
				VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				VK_PIPELINE_STAGE_TRANSFER_BIT,
				VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
				subresourceRange);
		}

		void createVulkanImage(VkFormat format, VkExtent3D extent, VulkanImage& result)
		{
			auto device = VulkanHelper::getSingletonPtr()->_getVkDevice();
			// Release ressources if image is to be recreated
			if (result.image != VK_NULL_HANDLE) {
				vkDestroyImageView(device, result.view, nullptr);
				vkDestroyImage(device, result.image, nullptr);
				vkFreeMemory(device, result.memory, nullptr);
				result = {};
			}

			VkImageCreateInfo image = vks::initializers::imageCreateInfo();
			image.imageType = VK_IMAGE_TYPE_2D;
			image.format = format;
			image.extent = extent;
			image.mipLevels = 1;
			image.arrayLayers = 1;
			image.samples = VK_SAMPLE_COUNT_1_BIT;
			image.tiling = VK_IMAGE_TILING_OPTIMAL;
			image.usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_STORAGE_BIT;
			image.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			VK_CHECK_RESULT(vkCreateImage(device, &image, nullptr, &result.image));

			VkMemoryRequirements memReqs;
			vkGetImageMemoryRequirements(device, result.image, &memReqs);
			VkMemoryAllocateInfo memoryAllocateInfo = vks::initializers::memoryAllocateInfo();
			memoryAllocateInfo.allocationSize = memReqs.size;
			memoryAllocateInfo.memoryTypeIndex = VulkanHelper::getSingletonPtr()->_findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
			VK_CHECK_RESULT(vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &result.memory));
			VK_CHECK_RESULT(vkBindImageMemory(device, result.image, result.memory, 0));

			VkImageViewCreateInfo colorImageView = vks::initializers::imageViewCreateInfo();
			colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
			colorImageView.format = format;
			colorImageView.subresourceRange = {};
			colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			colorImageView.subresourceRange.baseMipLevel = 0;
			colorImageView.subresourceRange.levelCount = 1;
			colorImageView.subresourceRange.baseArrayLayer = 0;
			colorImageView.subresourceRange.layerCount = 1;
			colorImageView.image = result.image;
			VK_CHECK_RESULT(vkCreateImageView(device, &colorImageView, nullptr, &result.view));
			
			VkCommandBuffer cmdBuffer = VulkanHelper::getSingletonPtr()->beginSingleTimeCommands();
			vks::tools::setImageLayout(cmdBuffer, result.image,
				VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_GENERAL,
				{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });
			VulkanHelper::getSingletonPtr()->endSingleTimeCommands(cmdBuffer);
		}

		std::tuple<uint32_t, uint32_t, uint32_t> getShaderBindings(const std::string& blob)
		{
			std::unordered_map<uint32_t, uint32_t> targetToSet, targetToBinding;


			constexpr size_t HEADER_SIZE = 5;

			size_t const dataSize = blob.size() / 4;
			uint32_t const* data = (uint32_t*)blob.data();

			for (uint32_t cursor = HEADER_SIZE, cursorEnd = dataSize; cursor < cursorEnd;) {
				uint32_t const firstWord = data[cursor];
				uint32_t const wordCount = firstWord >> 16;
				uint32_t const op = firstWord & 0x0000FFFF;

				switch (op) {
				case spv::Op::OpDecorate: {
					if (data[cursor + 2] == spv::Decoration::DecorationDescriptorSet) {
						uint32_t const targetVar = data[cursor + 1];
						uint32_t const setId = data[cursor + 3];
						targetToSet[targetVar] = setId;
					}
					else if (data[cursor + 2] == spv::Decoration::DecorationBinding) {
						uint32_t const targetVar = data[cursor + 1];
						uint32_t const binding = data[cursor + 3];
						targetToBinding[targetVar] = binding;
					}
					break;
				}
				default:
					break;
				}
				cursor += wordCount;
			}

			constexpr uint32_t UBO = 0;
			constexpr uint32_t SAMPLER = 1;
			constexpr uint32_t IATTACHMENT = 2;
			uint32_t ubo = 0, sampler = 0, inputAttachment = 0;

			for (auto const& [target, setId] : targetToSet) {
				uint32_t const binding = targetToBinding[target];
				assert_invariant(binding < 32);
				switch (setId) {
				case UBO:
					ubo |= (1 << binding);
					break;
				case SAMPLER:
					sampler |= (1 << binding);
					break;
				case IATTACHMENT:
					inputAttachment |= (1 << binding);
					break;
				default:
					PANIC_POSTCONDITION("unexpected %d", (int)setId);
				}
			}
			return { ubo, sampler, inputAttachment };
		}
	}

}
