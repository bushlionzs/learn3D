


#ifndef  _OGRE3DUIWINDOW_H
#define  _OGRE3DUIWINDOW_H

#include "CEGUIWindow.h"
#include "CEGUIWindowFactory.h"
#include "OgreUIPreDefine.h"
#include "Ogre3DUIWindowProperties.h"
#include "OgreMatrix4.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{
	class  Ogre3DUIWindow : public Window
	{
	public:
		static const utf8   WidgetTypeName[];

		enum Ogre3DUIGeometryTypeE
		{
			O3DUIPT_SCENE,
			O3DUIPT_UINODE,
			O3DUIPT_CUSTOM,
			O3DUIPT_UNKOWN,
		};

		enum Ogre3DUITypeE
		{
			O3DUIT_RECT,
			O3DUIT_CIRCLE,
			O3DUIT_TRI,
			
			O3DUIT_CUSTOM,
			O3DUIT_UNKOWN,
		};

		struct Ogre3DUIInnerProperties
		{
			Ogre::Matrix4 mWorldMatrix;
			Ogre::Matrix4 mViewMatrix;
			Ogre::Matrix4 mPerspectiveMatrix;
			String mObjName;

			Ogre3DUIGeometryTypeE mOgre3dWindowPlaceType;
			Ogre3DUITypeE mOgre3DUIType;
			
			String mSecondTextureName;

			String mMovableType;
			String mMovableName;
			String mMovableResourceName;

			void *mPointerValueofOrphigineLogicmodelObj;
			void *mPointerValueofCamera;

			Ogre3DUIInnerProperties()
			{
				mWorldMatrix = Ogre::Matrix4::IDENTITY;
				mViewMatrix = Ogre::Matrix4::IDENTITY;
				mPerspectiveMatrix = Ogre::Matrix4::IDENTITY;
				
				mMovableType = "";
				mMovableName = "";
				mMovableResourceName = "";

				mSecondTextureName = "";
				mObjName = "";
				mOgre3dWindowPlaceType = O3DUIPT_UNKOWN;
				mOgre3DUIType = O3DUIT_UNKOWN;

				mPointerValueofOrphigineLogicmodelObj = 0;
				mPointerValueofCamera = 0;
			}
			~Ogre3DUIInnerProperties()
			{
				
			}
		};

	public:
		void set3DUIGeometryType(const String &place);
		String get3DUIGeometryType() const;

		void set3DUIType(const String &type);
		String get3DUIType() const;

		
		
		

		void setSecondTextureName(const String &name);
		String getSecondTextureName() const;


		void setSceneObjectName(const String &name);
		String getSceneObjectName() const;

		void setLogicModelObjPointer(const void* pointer);
		void* getLogicModelObjPointer() const;

		void setCameraPointer(const void* pointer);
		void* getCameraPointer() const;

		void setMovableType(const String &type);
		String getMovableType() const;

		void setMovableResourceName(const String & name);
		String getMovableResourceName() const;

		size_t getVertexNum() const;

		Ogre3DUIWindow(const String& type, const String& name);
		virtual ~Ogre3DUIWindow();

		
		

	protected:
		
		virtual void drawSelf(float z);
		virtual void draw3DWindow(float z);
		virtual bool	testClassName_impl(const String& class_name) const;
	private:
		Ogre3DUIInnerProperties mOgre3DUIInnerProperties;

		static Ogre3DUIWindowProperties::Ogre3DUIGeometryType	mOgre3DUIGeometryTypeProperty;
		
		static Ogre3DUIWindowProperties::Ogre3DSecondTextureName	mOgre3DSecondTextureNameProperty; 
		static Ogre3DUIWindowProperties::Ogre3DUIType	m3DUITypeProperty;

		static Ogre3DUIWindowProperties::OgreSceneObjectName	mSceneObjectNameProperty;
		static Ogre3DUIWindowProperties::OgreMovableType	mMovableTypeProperty;
		static Ogre3DUIWindowProperties::OgreMovableResource	mMovableResourceProperty;
	};

	class  Ogre3DUIWindowFactory : public WindowFactory
	{
	public:
		Ogre3DUIWindowFactory(void) : WindowFactory(Ogre3DUIWindow::WidgetTypeName) { }
		~Ogre3DUIWindowFactory(void){}
		Window* createWindow(const String& name);
		void destroyWindow(Window* window);
	};
} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif