
#include "KLDragTitle.h"
#include "CEGUIExceptions.h"
#include "CEGUIWindowManager.h"
#include "CEGUIPropertyHelper.h"
#include "KLBoundWindow.h"

namespace CEGUI
{
    const utf8  KLDragTitle::WidgetTypeName[] = "Falagard/DragTitle";

	KLDragTitleProperties::DragTarget		KLDragTitle::d_dragTargetProperty;

    KLDragTitle::KLDragTitle(const String& type, const String& name) :
        Window(type, name),
		d_dragging(false)
    {
        addDragTitleProperties();

        setAlwaysOnTop(true);
	}

    KLDragTitle::~KLDragTitle()
    {
    }

	void KLDragTitle::addDragTitleProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( KLDragTitle )
		   CEGUI_ADD_STATICPROPERTY( &d_dragTargetProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	String KLDragTitle::getDragTarget(void) const				
	{ 
		return d_dragTarget ? d_dragTarget->getName() : (utf8*)"";
	}

	void KLDragTitle::setDragTarget(const String& strName)
	{ 
		Window* pWindow = WindowManager::getSingleton().getWindow(strName);
		if(pWindow && pWindow->testClassName((utf8*)"KLBoundWindow"))
		{
			d_dragTarget = (CEGUI::KLBoundWindow*)pWindow;
		}
		else
		{
			d_dragTarget = 0;
		}
	}

	void KLDragTitle::onMouseMove(MouseEventArgs& e)
	{
		
		Window::onMouseMove(e);

		if (d_dragging && (d_dragTarget != NULL))
		{
			Vector2 delta(screenToWindow(e.position));

			if (getMetricsMode() == Relative)
			{
				delta = relativeToAbsolute(delta);
			}

			
			delta -= d_dragPoint;

			
			((KLBoundWindow*)d_dragTarget)->offsetPixelPosition(delta);

			e.handled = true;
		}
	}

	void KLDragTitle::onMouseButtonDown(MouseEventArgs& e)
	{
		
		Window::onMouseButtonDown(e);

		if (e.button == LeftButton)
		{
			if (d_dragTarget != NULL)
			{
				
				if (captureInput())
				{
					
					d_dragging = true;
					d_dragPoint = screenToWindow(e.position);

					if (getMetricsMode() == Relative)
					{
						d_dragPoint = relativeToAbsolute(d_dragPoint);
					}
				}
			}
		}

		e.handled = true;
	}
	
	void KLDragTitle::onMouseButtonUp(MouseEventArgs& e)
	{
		
		Window::onMouseButtonUp(e);

		if (e.button == LeftButton)
		{
			releaseInput();
			e.handled = true;
		}
	}

	
	void KLDragTitle::onCaptureLost(WindowEventArgs& e)
	{
		
		Window::onCaptureLost(e);

		
		d_dragging = false;
	}

    Window* KLDragTitleFactory::createWindow(const String& name)
    {
        return new KLDragTitle(d_type, name);
    }

    void KLDragTitleFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}