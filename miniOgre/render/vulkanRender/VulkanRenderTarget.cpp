#include "OgreHeader.h"
#include "VulkanRenderTarget.h"
#include "VulkanTexture.h"
#include "VulkanHelper.h"
#include "VulkanRenderSystem.h"
#include "VulkanTools.h"

namespace Ogre
{

	VulkanRenderTarget::VulkanRenderTarget(
		const String& name, 
		VulkanPlatform* platform,
		VulkanCommands* commands, 
		TextureProperty&texProperty)
	{
		mName = name;
		mTarget = new VulkanTexture(name, platform, commands, &texProperty);
		mWidth = mTarget->getWidth();
		mHeight = mTarget->getHeight();
	}

	VulkanRenderTarget::VulkanRenderTarget(VulkanSwapChain* swapChain, bool depth)
	{
		mSwapChain = swapChain;
		mDepth = depth;

		mWidth = swapChain->getExtent().width;
		mHeight = swapChain->getExtent().height;
	}

	VulkanRenderTarget::~VulkanRenderTarget()
	{

	}

	VkImageView VulkanRenderTarget::getImageView(uint32_t index)
	{
		if (mSwapChain)
		{
			if (mDepth)
			{
				return mSwapChain->getDepth()->getVkImageView();
			}
			return mSwapChain->getCurrentColor()->getVkImageView();
		}
		return mTarget->getVkImageViewEx(index);
	}

	VkImage VulkanRenderTarget::getImage()
	{
		if (mSwapChain)
		{
			if (mDepth)
			{
				return mSwapChain->getDepth()->getVkImage();
			}
			return mSwapChain->getCurrentColor()->getVkImage();;
		}
		return mTarget->getVkImage();
	}

	VkImageAspectFlags VulkanRenderTarget::getAspectFlag()
	{
		if (mTarget)
		{
			return mTarget->getAspectFlag();
		}
		if (mDepth)
		{
			return mSwapChain->getDepth()->getAspectFlag();
		}
		return mSwapChain->getCurrentColor()->getAspectFlag();
	}

	uint32 VulkanRenderTarget::getWidth(void) const
	{
		if (mSwapChain)
		{
			return mSwapChain->getExtent().width;
		}
		return mWidth;
	}

	uint32 VulkanRenderTarget::getHeight(void) const
	{
		if (mSwapChain)
		{
			return mSwapChain->getExtent().height;
		}
		return mHeight;
	}

	Ogre::OgreTexture* VulkanRenderTarget::getTarget()
	{
		if (mSwapChain)
		{
			if (mDepth)
			{
				return mSwapChain->getDepth();
			}
			return mSwapChain->getCurrentColor();
		}
		return mTarget;
	}
}