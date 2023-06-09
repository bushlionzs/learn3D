/*!
	@file
	@author		Albert Semenov
	@date		04/2008
*/

#ifndef MYGUI_OGRE_RENDER_MANAGER_H_
#define MYGUI_OGRE_RENDER_MANAGER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_RenderFormat.h"
#include "MyGUI_IVertexBuffer.h"
#include "MyGUI_RenderManager.h"

#include "renderSystem.h"
#include "OgreMoveObject.h"
#include <unordered_map>

namespace MyGUI
{

	struct OgreShaderInfo
	{

	};

	class MyGUIRender;
	class IVertexBuffer;
	class OgreRenderManager :
		public RenderManager,
		public IRenderTarget,
		public Ogre::MoveObject
	{
	public:
		OgreRenderManager();

		void initialise(Ogre::RenderWindow* _window, SceneManager* _scene);
		void shutdown();

		static OgreRenderManager& getInstance();
		static OgreRenderManager* getInstancePtr();

		/** @see RenderManager::getViewSize */
		const IntSize& getViewSize() const override;

		/** @see RenderManager::getVertexFormat */
		VertexColourType getVertexFormat() const override;

		/** @see RenderManager::createVertexBuffer */
		IVertexBuffer* createVertexBuffer() override;
		/** @see RenderManager::destroyVertexBuffer */
		void destroyVertexBuffer(IVertexBuffer* _buffer) override;

		/** @see RenderManager::createTexture */
		ITexture* createTexture(const std::string& _name) override;
		/** @see RenderManager::destroyTexture */
		void destroyTexture(ITexture* _texture) ;
		/** @see RenderManager::getTexture */
		ITexture* getTexture(const std::string& _name);

		/** @see RenderManager::isFormatSupported */
		bool isFormatSupported(PixelFormat _format, TextureUsage _usage);

		/** @see IRenderTarget::begin */
		void begin();
		/** @see IRenderTarget::end */
		void end();

		/** @see IRenderTarget::doRender */
		void doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count);

		/** @see IRenderTarget::getInfo */
		const RenderTargetInfo& getInfo() const override;

		void setRenderSystem(RenderSystem* _render);
		RenderSystem* getRenderSystem() const;

		void setRenderWindow(Ogre::RenderWindow* _window);

		/** Set scene manager where MyGUI will be rendered */
		void setSceneManager(SceneManager* _scene);

		/** Get GUI viewport index */
		size_t getActiveViewport() const;

		/** Set GUI viewport index */
		void setActiveViewport(unsigned short _num);

		Ogre::RenderWindow* getRenderWindow() const;

		bool getManualRender() const;
		void setManualRender(bool _value);

		size_t getBatchCount() const;

		/** @see RenderManager::setViewSize */
		void setViewSize(int _width, int _height) override;

		/** @see RenderManager::registerShader */
		void registerShader(
			const std::string& _shaderName,
			const std::string& _vertexProgramFile,
			const std::string& _fragmentProgramFile) override;

#if MYGUI_DEBUG_MODE == 1
		virtual bool checkTexture(ITexture* _texture);
#endif

		std::string getShaderExtension() const;

	/*internal:*/
		/* for use with RTT */
		void beginRttRender(bool isFlippedTexture);
		void endRttRender();
		void doRenderRtt(IVertexBuffer* _buffer, ITexture* _texture, size_t _count, Ogre::RenderTexture* rtt);
		OgreShaderInfo* getShaderInfo(const std::string& _shaderName) const;

		virtual const AxisAlignedBox& getBoundingBox(void) const;

		void update(float delta);
		virtual const std::vector<Renderable*>& getRenderableList();
	private:
		void renderQueueStarted(
			uint8 queueGroupId,
			const Ogre::String& invocation,
			bool& skipThisInvocation);

		virtual void windowResized(Ogre::RenderWindow* _window);

		// restore buffers
		void eventOccurred(const Ogre::String& eventName, const Ogre::NameValuePairList* parameters);

		void destroyAllResources();
		void updateRenderInfo();

		OgreShaderInfo* createShader(
			const std::string& _shaderName,
			const std::string& _vertexProgramFile,
			const std::string& _fragmentProgramFile);

		void setShaderProjectionMatrix(bool isFlipped);

	private:
		// флаг для обновления всех и вся
		bool mUpdate;

		IntSize mViewSize;

		Ogre::SceneManager* mSceneManager;

		VertexColourType mVertexFormat;

		// окно, на которое мы подписываемся для изменения размеров
		Ogre::RenderWindow* mWindow;

		// вьюпорт, с которым работает система
		unsigned short mActiveViewport;

		RenderSystem* mRenderSystem;
		RenderTargetInfo mInfo;

		typedef std::map<std::string, ITexture*> MapTexture;
		MapTexture mTextures;

		bool mIsInitialise;
		bool mManualRender;
		size_t mCountBatch;

		OgreShaderInfo* mDefaultShader = nullptr;
		std::map<std::string, OgreShaderInfo*> mRegisteredShaders;

		Ogre::MaterialPtr mMaterial;

		std::unordered_map<IVertexBuffer*, MyGUIRender*> mVertexMap;

		Ogre::SceneNode* mNode;
	};

} // namespace MyGUI

#endif // MYGUI_OGRE_RENDER_MANAGER_H_
