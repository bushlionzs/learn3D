
#include "KLActorWindow.h"
#include "CEGUIImageset.h"
#include "CEGUISystem.h"
#include "CEGUIRenderer.h"
#include "CEGUITexture.h"
#include "OgreCEGUIRenderer.h"
#include "CEGUIWindowManager.h"


namespace CEGUI
{
	const utf8 KLActorWindow::WidgetTypeName[] = "Falagard/ActorWindow";

    const String KLActorWindow::EventNamespace("Falagard/MeshWindow");

    const String KLActorWindow::EventMeshHook("MeshHook");
    const String KLActorWindow::EventMeshShown("MeshShown");
    const String KLActorWindow::EventMeshHidden("MeshHidden");

    
	KLActorWindowProperties::FakeObject	KLActorWindow::d_fakeObjectProperty;
	KLActorWindowProperties::ShowControl	KLActorWindow::d_showControlProperty;

	KLActorWindow::KLActorWindow(const String& type, const String& name):
		StaticImage(type, name)
	{
		addMeshWindowProperties();
	}

	KLActorWindow::~KLActorWindow(void)
	{
	}

	void KLActorWindow::addMeshWindowProperties(void)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLActorWindow )
		   CEGUI_ADD_STATICPROPERTY( &d_fakeObjectProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_showControlProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	void KLActorWindow::setShowControl(const String& windowName)
	{
		d_showControlWindowName = windowName;

		
		Window* pControlWindow = WindowManager::getSingleton().getWindow(windowName);
		if(!pControlWindow) return;

		
		pControlWindow->subscribeEvent(EventShown,
			CEGUI::Event::Subscriber(&CEGUI::KLActorWindow::handleControlShown, this));

		pControlWindow->subscribeEvent(EventHidden,
			CEGUI::Event::Subscriber(&CEGUI::KLActorWindow::handleControlHidden, this));
	}

	void KLActorWindow::onParentHidden(void)
	{
		StaticImage::onParentHidden();

		WindowEventArgs args(this);
		fireEvent(EventMeshHidden, args, EventNamespace);
	}

	void KLActorWindow::setFakeObject(const String& fakeObject)
	{ 
		d_fakeObjectName = fakeObject;

		if(!d_fakeObjectName.empty() )
		{
			WindowEventArgs args(this);
			fireEvent(EventMeshShown, args, EventNamespace);
		}
	}

	bool KLActorWindow::handleControlShown(const CEGUI::EventArgs& e)
	{
		WindowEventArgs args(this);
		fireEvent(EventMeshShown, args, EventNamespace);

		requestRedraw();
		return false;
	}

	bool KLActorWindow::handleControlHidden(const CEGUI::EventArgs& e)
	{
		WindowEventArgs args(this);
		fireEvent(EventMeshHidden, args, EventNamespace);

		return false;
	}

	void KLActorWindow::subscribeShownEvent(Event::Subscriber subscriber)
	{
		subscribeEvent(EventMeshShown, subscriber);
	}
	
	void KLActorWindow::subscribeHidenEvent(Event::Subscriber subscriber)
	{
		subscribeEvent(EventMeshHidden, subscriber);
	}
	
	void KLActorWindow::subscribeHookEvent(Event::Subscriber subscriber)
	{
		subscribeEvent(EventMeshHook, subscriber);
	}

	void KLActorWindow::populateRenderCache()
	{
		d_image.setVertFormatting(RenderableImage::VertStretched);
		d_image.setHorzFormatting(RenderableImage::HorzStretched);

		d_image.draw(d_renderCache);
	}

	
    Window* KLActorWindowFactory::createWindow(const String& name)
    {
        return new KLActorWindow(d_type, name);
    }

    void KLActorWindowFactory::destroyWindow(Window* window)
    {
        delete window;
    }
};