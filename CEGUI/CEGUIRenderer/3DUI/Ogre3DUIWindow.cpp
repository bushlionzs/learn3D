#include <OgreHeader.h>
#include "Ogre3DUIWindow.h"


namespace CEGUI
{
	const utf8  Ogre3DUIWindow::WidgetTypeName[] = "3D/DefaultWindow";

	Ogre3DUIWindowProperties::Ogre3DUIGeometryType		Ogre3DUIWindow::mOgre3DUIGeometryTypeProperty;
	
	Ogre3DUIWindowProperties::Ogre3DSecondTextureName	Ogre3DUIWindow::mOgre3DSecondTextureNameProperty;
	Ogre3DUIWindowProperties::Ogre3DUIType		Ogre3DUIWindow::m3DUITypeProperty;

	Ogre3DUIWindowProperties::OgreSceneObjectName	 Ogre3DUIWindow::mSceneObjectNameProperty;
	Ogre3DUIWindowProperties::OgreMovableType	Ogre3DUIWindow::mMovableTypeProperty;
	Ogre3DUIWindowProperties::OgreMovableResource	Ogre3DUIWindow::mMovableResourceProperty;


	Ogre3DUIWindow::Ogre3DUIWindow(const String& type, const String& name)
		:Window(type, name)
	{
		CEGUI_START_ADD_STATICPROPERTY( Ogre3DUIWindow )
			CEGUI_ADD_STATICPROPERTY( &mOgre3DUIGeometryTypeProperty );
			
			CEGUI_ADD_STATICPROPERTY( &mOgre3DSecondTextureNameProperty );
			CEGUI_ADD_STATICPROPERTY( &m3DUITypeProperty );

			CEGUI_ADD_STATICPROPERTY( &mSceneObjectNameProperty );
			CEGUI_ADD_STATICPROPERTY( &mMovableTypeProperty );
			CEGUI_ADD_STATICPROPERTY( &mMovableResourceProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	Ogre3DUIWindow::~Ogre3DUIWindow()
	{

	}

	void Ogre3DUIWindow::set3DUIGeometryType(const String &place)
	{
		if(place =="scene")
		{
			mOgre3DUIInnerProperties.mOgre3dWindowPlaceType = O3DUIPT_SCENE;
		}
		else if(place == "node")
		{
			mOgre3DUIInnerProperties.mOgre3dWindowPlaceType = O3DUIPT_UINODE;
		}
		else if(place == "custom")
		{
			mOgre3DUIInnerProperties.mOgre3dWindowPlaceType = O3DUIPT_CUSTOM;
		}
		else
		{
			mOgre3DUIInnerProperties.mOgre3dWindowPlaceType = O3DUIPT_UNKOWN;
		}
	}
	void Ogre3DUIWindow::set3DUIType(const String &type)
	{
		if(type == "rect")
		{
			mOgre3DUIInnerProperties.mOgre3DUIType = O3DUIT_RECT;
		}
		else if(type == "circle")
		{
			mOgre3DUIInnerProperties.mOgre3DUIType = O3DUIT_CIRCLE;
		}
		else if(type == "triangle")
		{
			mOgre3DUIInnerProperties.mOgre3DUIType = O3DUIT_TRI;
		}
		else if(type == "custom")
		{
			mOgre3DUIInnerProperties.mOgre3DUIType = O3DUIT_CUSTOM;
		}
		else
		{
			mOgre3DUIInnerProperties.mOgre3DUIType = O3DUIT_UNKOWN;
		}
	}

	String Ogre3DUIWindow::get3DUIGeometryType() const
	{
		if(mOgre3DUIInnerProperties.mOgre3dWindowPlaceType == O3DUIPT_SCENE)
		{
			return "scene";
		}
		else if(mOgre3DUIInnerProperties.mOgre3dWindowPlaceType == O3DUIPT_UINODE)
		{
			return "node";
		}
		else if(mOgre3DUIInnerProperties.mOgre3dWindowPlaceType == O3DUIPT_CUSTOM)
		{
			return "custom";
		}
		else
		{
			return "unknown";
		}		
	}

	String Ogre3DUIWindow::get3DUIType() const
	{
		if(mOgre3DUIInnerProperties.mOgre3DUIType == O3DUIT_RECT)
		{
			return "rect";
		}
		else if(mOgre3DUIInnerProperties.mOgre3DUIType == O3DUIT_CIRCLE)
		{
			return "circle";
		}
		else if(mOgre3DUIInnerProperties.mOgre3DUIType == O3DUIT_TRI )
		{
			return "triangle";
		}
		else if(mOgre3DUIInnerProperties.mOgre3DUIType == O3DUIT_CUSTOM)
		{
			return "custom";
		}
		else
		{
			return "unknown";
		}
	}

	void Ogre3DUIWindow::setSecondTextureName(const String &name)
	{
		mOgre3DUIInnerProperties.mSecondTextureName = name;
	}
	String Ogre3DUIWindow::getSecondTextureName() const
	{
		return mOgre3DUIInnerProperties.mSecondTextureName;
	}

	void Ogre3DUIWindow::setSceneObjectName(const String &name)
	{
		mOgre3DUIInnerProperties.mMovableName = name;
	}
	String Ogre3DUIWindow::getSceneObjectName() const
	{
		return mOgre3DUIInnerProperties.mMovableName;
	}

	void Ogre3DUIWindow::setLogicModelObjPointer(const void* pointer)
	{
		mOgre3DUIInnerProperties.mPointerValueofOrphigineLogicmodelObj = const_cast<void *>(pointer);
	}
	void* Ogre3DUIWindow::getLogicModelObjPointer() const
	{
		return mOgre3DUIInnerProperties.mPointerValueofOrphigineLogicmodelObj;
	}

	void Ogre3DUIWindow::setCameraPointer(const void* pointer)
	{
		mOgre3DUIInnerProperties.mPointerValueofCamera = const_cast<void *>(pointer);
	}
	void* Ogre3DUIWindow::getCameraPointer() const
	{
		return mOgre3DUIInnerProperties.mPointerValueofCamera;
	}

	void Ogre3DUIWindow::setMovableType(const String &name)
	{
		mOgre3DUIInnerProperties.mMovableType = name;
	}
	String Ogre3DUIWindow::getMovableType() const
	{
		return mOgre3DUIInnerProperties.mMovableType;
	}

	void Ogre3DUIWindow::setMovableResourceName(const String &name)
	{
		mOgre3DUIInnerProperties.mMovableResourceName = name;
	}
	String Ogre3DUIWindow::getMovableResourceName() const
	{
		return mOgre3DUIInnerProperties.mMovableResourceName;
	}


	void Ogre3DUIWindow::drawSelf(float z)
	{
		draw3DWindow(z);
	}

	void Ogre3DUIWindow::draw3DWindow(float z)
	{
		System::getSingleton().getRenderer()->add3DWindow(z,this);
	}

	bool	Ogre3DUIWindow::testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"3D/DefaultWindow")	return true;
		return false;
	}

	size_t Ogre3DUIWindow::getVertexNum() const
	{
		if(mOgre3DUIInnerProperties.mOgre3DUIType  == O3DUIT_RECT)
		{
			return 6;
		}
		else
		{
			assert(false);
			return 0;
		}
	}

	Window* Ogre3DUIWindowFactory::createWindow(const String& name)
	{
		return new Ogre3DUIWindow(d_type, name);
	}

	void Ogre3DUIWindowFactory::destroyWindow(Window* window)
	{
		delete window;
	}
}