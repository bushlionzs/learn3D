#include "OgreHeader.h"
#include "VulkanWindow.h"
#include "OgreStringConverter.h"
#include "VulkanHelper.h"
#include "VulkanTools.h"
#include "VulkanRenderTarget.h"


VulkanWindow::VulkanWindow()
    :mSwapChain(nullptr),
    mDepthTarget(nullptr),
    mColorTarget(nullptr)
{
	
}

VulkanWindow::~VulkanWindow()
{

}

void VulkanWindow::create(VulkanSwapChain* swapChain)
{
    mSwapChain = swapChain;

    mWidth = mSwapChain->getExtent().width;
    mHeight = mSwapChain->getExtent().height;

    mColorTarget = new Ogre::VulkanRenderTarget(swapChain);
    mDepthTarget = new Ogre::VulkanRenderTarget(swapChain, true);
}

Ogre::RenderTarget* VulkanWindow::getColorTarget()
{
    return mColorTarget;
}

Ogre::RenderTarget* VulkanWindow::getDepthTarget()
{
    return mDepthTarget;
}



