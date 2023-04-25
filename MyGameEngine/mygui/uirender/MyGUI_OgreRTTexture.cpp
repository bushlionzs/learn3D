/*!
	@file
	@author		Albert Semenov
	@date		10/2009
*/
#include <OgreHeader.h>
#include <cstring>
#include "MyGUI_OgreRTTexture.h"
#include "MyGUI_OgreRenderManager.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "OgreRenderTexture.h"
#include "OgreViewport.h"
#include "OgreCamera.h"


namespace MyGUI
{

	OgreRTTexture::OgreRTTexture(Ogre::TexturePtr _texture) :
		mViewport(nullptr),
		mSaveViewport(nullptr),
		mTexture(_texture)
	{
		Ogre::Root* root = Ogre::Root::getSingletonPtr();
		if (root != nullptr)
		{
			RenderSystem* system = root->getRenderSystem();
			if (system != nullptr)
			{
				size_t width = mTexture->getWidth();
				size_t height = mTexture->getHeight();

				mRenderTargetInfo.maximumDepth = 1.0f;
				mRenderTargetInfo.hOffset = 0.0f;
				mRenderTargetInfo.vOffset = 0.0f;
				mRenderTargetInfo.aspectCoef = float(height) / float(width);
				mRenderTargetInfo.pixScaleX = 1.0f / float(width);
				mRenderTargetInfo.pixScaleY = 1.0f / float(height);
			}
		}
	}

	void OgreRTTexture::begin()
	{
		Ogre::RenderTexture* rtt = mTexture->getBuffer()->getRenderTarget();

		if (mViewport == nullptr)
		{
			mViewport = rtt->addViewport(nullptr);
		}

		RenderSystem* system = Ogre::Root::getSingleton().getRenderSystem();
		mSaveViewport = system->_getViewport();
		system->_setViewport(mViewport->getCamera(), mViewport);
		system->clearFrameBuffer(Ogre::FBT_COLOUR, Ogre::ColourValue::ZERO);

		OgreRenderManager::getInstance().beginRttRender(mTexture->getBuffer()->getRenderTarget()->requiresTextureFlipping());
	}

	void OgreRTTexture::end()
	{
		RenderSystem* system = Ogre::Root::getSingleton().getRenderSystem();
		system->_setViewport(mSaveViewport->getCamera(), mSaveViewport);

		OgreRenderManager::getInstance().endRttRender();
	}

	void OgreRTTexture::doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count)
	{
		OgreRenderManager::getInstance().doRenderRtt(_buffer, _texture, _count, mTexture->getBuffer()->getRenderTarget());
	}

} // namespace MyGUI
