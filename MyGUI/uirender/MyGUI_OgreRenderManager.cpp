/*!
	@file
	@author		Albert Semenov
	@date		04/2008
*/
#include <OgreHeader.h>
#include "MyGUI_OgreDataManager.h"
#include "MyGUI_OgreRenderManager.h"
#include "MyGUI_OgreTexture.h"
#include "MyGUI_OgreVertexBuffer.h"
#include "MyGUI_LogManager.h"
#include "MyGUI_OgreDiagnostic.h"
#include "MyGUI_Timer.h"
#include "MyGUI_Gui.h"
#include "OgreSceneManager.h"
#include "OgreViewport.h"
#include "OgreRoot.h"
#include "OgreMaterialManager.h"
#include "OgreRenderWindow.h"
#include "OgreTextureManager.h"
#include "OgreRenderTexture.h"
#include "MyGUI_OgreRenderable.h"
#include "MyGUI_OgreVertexBuffer.h"
#include "MyGUI_OgreTexture.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"


namespace MyGUI
{

	OgreRenderManager& OgreRenderManager::getInstance()
	{
		return *getInstancePtr();
	}
	OgreRenderManager* OgreRenderManager::getInstancePtr()
	{
		return static_cast<OgreRenderManager*>(RenderManager::getInstancePtr());
	}

	OgreRenderManager::OgreRenderManager() :
		Ogre::MoveObject("mygui"),
		mUpdate(false),
		mSceneManager(nullptr),
		mWindow(nullptr),
		mActiveViewport(0),
		mRenderSystem(nullptr),
		mIsInitialise(false),
		mManualRender(false),
		mCountBatch(0)
	{
	}

	void OgreRenderManager::initialise(Ogre::RenderWindow* _window, Ogre::SceneManager* _scene)
	{
		MYGUI_PLATFORM_ASSERT(!mIsInitialise, getClassTypeName() << " initialised twice");
		MYGUI_PLATFORM_LOG(Info, "* Initialise: " << getClassTypeName());

		mSceneManager = nullptr;
		mWindow = nullptr;
		mUpdate = false;
		mRenderSystem = nullptr;
		mActiveViewport = 0;

		Ogre::Root* root = Ogre::Root::getSingletonPtr();
		if (root != nullptr)
			setRenderSystem(root->getRenderSystem());
		setRenderWindow(_window);
		setSceneManager(_scene);

		mMaterial = Ogre::MaterialManager::getSingleton().create("MyGUI/Default", "");
		mMaterial->touch();

		mNode = mSceneManager->getRoot()->createChildSceneNode("mygui");
		mNode->attachObject(this);
		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully initialized");
		mIsInitialise = true;
	}

	void OgreRenderManager::shutdown()
	{
		MYGUI_PLATFORM_ASSERT(mIsInitialise, getClassTypeName() << " is not initialised");
		MYGUI_PLATFORM_LOG(Info, "* Shutdown: " << getClassTypeName());

		destroyAllResources();

		setSceneManager(nullptr);
		setRenderWindow(nullptr);
		setRenderSystem(nullptr);

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully shutdown");
		mIsInitialise = false;
	}

	void OgreRenderManager::setRenderSystem(RenderSystem* _render)
	{
		if (mRenderSystem != nullptr)
		{

			mRenderSystem = nullptr;
		}

		mRenderSystem = _render;

		if (mRenderSystem != nullptr)
		{


			VertexElementType vertex_type = VET_COLOUR_ABGR;

			if (vertex_type == VET_COLOUR_ABGR)
				mVertexFormat = VertexColourType::ColourABGR;
			else if (vertex_type == VET_COLOUR_ARGB)
				mVertexFormat = VertexColourType::ColourARGB;

			updateRenderInfo();
		}
	}

	RenderSystem* OgreRenderManager::getRenderSystem() const
	{
		return mRenderSystem;
	}

	void OgreRenderManager::setRenderWindow(Ogre::RenderWindow* _window)
	{
		mWindow = _window;

		if (mWindow != nullptr)
		{
			if (mWindow->getNumViewports() <= mActiveViewport &&
				!mWindow->getViewport(mActiveViewport)->getOverlaysEnabled())
			{
				MYGUI_PLATFORM_LOG(Warning, "Overlays are disabled. MyGUI won't render in selected viewport.");
			}

			windowResized(mWindow);
		}
	}

	void OgreRenderManager::setSceneManager(Ogre::SceneManager* _scene)
	{
		mSceneManager = _scene;
	}

	void OgreRenderManager::setActiveViewport(unsigned short _num)
	{
		mActiveViewport = _num;

		if (mWindow != nullptr)
		{
			if (mWindow->getNumViewports() <= mActiveViewport)
			{
				MYGUI_PLATFORM_LOG(Error, "Invalid active viewport index selected. There is no viewport with given index.");
			}

			windowResized(mWindow);
		}
	}

	void OgreRenderManager::renderQueueStarted(
		uint8 queueGroupId,
		const Ogre::String& invocation,
		bool& skipThisInvocation)
	{
		
	}


	void OgreRenderManager::eventOccurred(const Ogre::String& eventName, const Ogre::NameValuePairList* parameters)
	{
		if (eventName == "DeviceLost")
		{
		}
		else if (eventName == "DeviceRestored")
		{
			mUpdate = true;
		}
	}

	IVertexBuffer* OgreRenderManager::createVertexBuffer()
	{
		return new OgreVertexBuffer();
	}

	void OgreRenderManager::destroyVertexBuffer(IVertexBuffer* _buffer)
	{
		delete _buffer;
	}

	void OgreRenderManager::windowResized(Ogre::RenderWindow* _window)
	{
		if (_window->getNumViewports() > mActiveViewport)
		{
			Ogre::Viewport* port = _window->getViewport(mActiveViewport);
            Ogre::OrientationMode orient = port->getOrientationMode();
			if (orient == Ogre::OR_DEGREE_90 || orient == Ogre::OR_DEGREE_270)
				setViewSize(port->getActualHeight(), port->getActualWidth());
			else
				setViewSize(port->getActualWidth(), port->getActualHeight());

		}
	}

	void OgreRenderManager::updateRenderInfo()
	{
		if (mRenderSystem != nullptr)
		{
			
			mInfo.maximumDepth = 0.0f;
			mInfo.hOffset = 0.0;
			mInfo.vOffset = 0.0;
			mInfo.aspectCoef = float(mViewSize.height) / float(mViewSize.width);
			mInfo.pixScaleX = 1.0f / float(mViewSize.width);
			mInfo.pixScaleY = 1.0f / float(mViewSize.height);
		}
	}

	void OgreRenderManager::doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count)
	{
		auto itor = mVertexMap.find(_buffer);

		if (itor == mVertexMap.end())
		{
			MyGUIRender* render = new MyGUIRender;
			OgreVertexBuffer* vb = (OgreVertexBuffer*)_buffer;
			vb->getRenderOperation()->vertexData->vertexCount = _count;
			render->update(vb, (OgreTexture*)_texture);
			mRenderables.push_back(render);
			mVertexMap.emplace(_buffer, render);
		}
		else
		{
			OgreVertexBuffer* vb = (OgreVertexBuffer*)_buffer;
			vb->getRenderOperation()->vertexData->vertexCount = _count;
			mRenderables.push_back(itor->second);
		}
	}

	void OgreRenderManager::begin()
	{
	}

	void OgreRenderManager::end()
	{
	}

	ITexture* OgreRenderManager::createTexture(const std::string& _name)
	{
		MapTexture::const_iterator item = mTextures.find(_name);
		MYGUI_PLATFORM_ASSERT(item == mTextures.end(), "Texture '" << _name << "' already exist");

		OgreTexture* texture = new OgreTexture(_name, OgreDataManager::getInstance().getGroup());
		mTextures[_name] = texture;
		return texture;
	}

	void OgreRenderManager::destroyTexture(ITexture* _texture)
	{
		if (_texture == nullptr) return;

		MapTexture::iterator item = mTextures.find(_texture->getName());
		MYGUI_PLATFORM_ASSERT(item != mTextures.end(), "Texture '" << _texture->getName() << "' not found");

		mTextures.erase(item);
		delete _texture;
	}

	ITexture* OgreRenderManager::getTexture(const std::string& _name)
	{
		if (_name.empty())
			return nullptr;
		MapTexture::const_iterator item = mTextures.find(_name);
		if (item == mTextures.end())
		{
			Ogre::TexturePtr texture = (Ogre::TexturePtr)Ogre::TextureManager::getSingleton().getByName(
				_name);
			if (texture)
			{
				ITexture* result = createTexture(_name);
				static_cast<OgreTexture*>(result)->setOgreTexture(texture);
				return result;
			}
			return nullptr;
		}
		return item->second;
	}

	bool OgreRenderManager::isFormatSupported(PixelFormat _format, TextureUsage _usage)
	{
		return Ogre::TextureManager::getSingleton().isFormatSupported(
			Ogre::TEX_TYPE_2D,
			OgreTexture::convertFormat(_format),
			OgreTexture::convertUsage(_usage));
	}

	void OgreRenderManager::destroyAllResources()
	{
		for (MapTexture::const_iterator item = mTextures.begin(); item != mTextures.end(); ++item)
		{
			delete item->second;
		}
		mTextures.clear();

		for (auto& shaderInfo : mRegisteredShaders)
		{
			delete shaderInfo.second;
		}
		mRegisteredShaders.clear();
	}

#if MYGUI_DEBUG_MODE == 1
	bool OgreRenderManager::checkTexture(ITexture* _texture)
	{
		for (MapTexture::const_iterator item = mTextures.begin(); item != mTextures.end(); ++item)
		{
			if (item->second == _texture)
				return true;
		}
		return false;
	}
#endif

	const IntSize& OgreRenderManager::getViewSize() const
	{
		return mViewSize;
	}

	VertexColourType OgreRenderManager::getVertexFormat() const
	{
		return mVertexFormat;
	}

	const RenderTargetInfo& OgreRenderManager::getInfo() const
	{
		return mInfo;
	}

	size_t OgreRenderManager::getActiveViewport() const
	{
		return mActiveViewport;
	}

	Ogre::RenderWindow* OgreRenderManager::getRenderWindow() const
	{
		return mWindow;
	}

	bool OgreRenderManager::getManualRender() const
	{
		return mManualRender;
	}

	void OgreRenderManager::setManualRender(bool _value)
	{
		mManualRender = _value;
	}

	size_t OgreRenderManager::getBatchCount() const
	{
		return mCountBatch;
	}

	void OgreRenderManager::setViewSize(int _width, int _height)
	{
		mViewSize.set(_width, _height);
		mUpdate = true;
		updateRenderInfo();
		onResizeView(mViewSize);
	}

	void OgreRenderManager::registerShader(
		const std::string& _shaderName,
		const std::string& _vertexProgramFile,
		const std::string& _fragmentProgramFile)
	{
		
	}

	std::string OgreRenderManager::getShaderExtension() const
	{
		return "hlsl";
	}

	void OgreRenderManager::beginRttRender(bool isFlippedTexture)
	{
		setShaderProjectionMatrix(isFlippedTexture);
	}

	void OgreRenderManager::endRttRender()
	{
		setShaderProjectionMatrix(false);
	}

	void OgreRenderManager::doRenderRtt(IVertexBuffer* _buffer, ITexture* _texture, size_t _count, Ogre::RenderTexture* rtt)
	{
		doRender(_buffer, _texture, _count);
	}

	OgreShaderInfo* OgreRenderManager::getShaderInfo(const std::string& _shaderName) const
	{
		return nullptr;
	}

	const AxisAlignedBox& OgreRenderManager::getBoundingBox(void) const
	{
		static AxisAlignedBox aa;
		aa.setInfinite();
		return aa;
	}

	void OgreRenderManager::update(float delta)
	{
		onFrameEvent(delta);
	}

	const std::vector<Renderable*>& OgreRenderManager::getRenderableList()
	{
		mRenderables.clear();
		

		mCountBatch = 0;

		/*static Timer timer;
		static unsigned long last_time = timer.getMilliseconds();
		unsigned long now_time = timer.getMilliseconds();
		unsigned long time = now_time - last_time;

		onFrameEvent(time / 1000.0f);

		last_time = now_time;*/

		begin();
		onRenderToTarget(this, mUpdate);
		end();

		mUpdate = false;

		return mRenderables;
	}

	OgreShaderInfo* OgreRenderManager::createShader(
		const std::string& _shaderName,
		const std::string& _vertexProgramFile,
		const std::string& _fragmentProgramFile)
	{
		return nullptr;
	}

	void OgreRenderManager::setShaderProjectionMatrix(bool isFlipped)
	{
		Ogre::Matrix4 projectionMatrix;
		mRenderSystem->_convertProjectionMatrix(Ogre::Matrix4::IDENTITY, projectionMatrix, true);

		if (isFlipped)
		{
			projectionMatrix[1][0] = -projectionMatrix[1][0];
			projectionMatrix[1][1] = -projectionMatrix[1][1];
			projectionMatrix[1][2] = -projectionMatrix[1][2];
			projectionMatrix[1][3] = -projectionMatrix[1][3];
		}

	}

} // namespace MyGUI
