#pragma once
#include"VulkanCommon.h"
#include "RenderSystem.h"
#include "OgreBlendMode.h"
#include "OgreCommon.h"
#include "OgreHardwareVertexBuffer.h"

namespace Ogre 
{
    class  VulkanMappings
	{
	public:

		/// return a Vulkan equivalent for a Ogre SceneBlendFactor value
		static VkBlendFactor get(SceneBlendFactor sbf, bool forAlpha);
		/// return a Vulkan equivalent for a Ogre SceneBlendOperation value
		static VkBlendOp get(SceneBlendOperation sbo);
		/// return a Vulkan equivalent for a Ogre CompareFunction value
		static VkCompareOp get(CompareFunction cf);

		static VkPrimitiveTopology get(OperationType opType);

		static LPCSTR getSemanticName(VertexElementSemantic sem);

		static PixelFormat _getClosestSupportedPF(PixelFormat ogrePF);

		static VkFormat _getPF(PixelFormat ogrePF);

		static VkFormat _getGammaFormat(VkFormat format, bool appendSRGB);

		static VkSamplerAddressMode getWrapMode(filament::backend::SamplerWrapMode mode);
		static VkFilter getFilter(filament::backend::SamplerMinFilter filter);
		static VkFilter getFilter(filament::backend::SamplerFilterType filter);
		static VkSamplerMipmapMode getMipmapMode(filament::backend::SamplerMipMapMode filter);
		static float getMaxLod(filament::backend::SamplerMipMapMode mipMapMode);
		static VkBool32 getCompareEnable(filament::backend::SamplerCompareMode mode);
		static VkCompareOp getCompareOp(filament::backend::SamplerCompareFunc func);
	};
}

