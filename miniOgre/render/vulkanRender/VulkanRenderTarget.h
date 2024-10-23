#pragma once
#include "OgreTexture.h"
#include "OgreRenderTarget.h"
#include "VulkanCommon.h"
#include "VulkanCommands.h"
#include "VulkanSwapChain.h"

class VulkanTexture;
namespace Ogre
{
	class VulkanRenderTarget: public Ogre::RenderTarget
	{
	public:
		VulkanRenderTarget(
			const String&name, 
			VulkanPlatform* platform,
			VulkanCommands* commands, 
			TextureProperty& texProperty);
		VulkanRenderTarget(VulkanSwapChain* swapChain, bool depth = false);
		~VulkanRenderTarget();


		VkImageView getImageView();
		VkImage getImage();
		VkImageAspectFlags getAspectFlag();
		virtual Ogre::OgreTexture* getTarget();

	private:
		VulkanTexture* mTarget = nullptr;
		
		VulkanSwapChain* mSwapChain = nullptr;
		bool mDepth = false;
	};
}
