

#include "elements/CEGUITitlebar.h"
#include "elements/CEGUIFrameWindow.h"
#include "CEGUIMouseCursor.h"


namespace CEGUI
{
const String Titlebar::EventNamespace("Titlebar");


TitlebarProperties::DraggingEnabled	Titlebar::d_dragEnabledProperty;
TitlebarProperties::CaptionColour	Titlebar::d_captionColourProperty;



Titlebar::Titlebar(const String& type, const String& name) :
	Window(type, name)
{
	addTitlebarProperties();

	setAlwaysOnTop(true);

	
	d_dragging = false;
	d_dragEnabled = true;
}


Titlebar::~Titlebar(void)
{
}



bool Titlebar::isDraggingEnabled(void) const
{
	return d_dragEnabled;
}



void Titlebar::setDraggingEnabled(bool setting)
{
	if (d_dragEnabled != setting)
	{
		d_dragEnabled = setting;

		
		if ((!d_dragEnabled) && d_dragging)
		{
			releaseInput();
		}

		
		WindowEventArgs args(this);
		onDraggingModeChanged(args);
	}

}



void Titlebar::onMouseMove(MouseEventArgs& e)
{
	
	Window::onMouseMove(e);

	if (d_dragging && (d_parent != NULL))
	{
		Vector2 delta(screenToWindow(e.position));

		if (getMetricsMode() == Relative)
		{
			delta = relativeToAbsolute(delta);
		}

		
		delta -= d_dragPoint;

		
		((FrameWindow*)d_parent)->offsetPixelPosition(delta);

		e.handled = true;
	}
}



void Titlebar::onMouseButtonDown(MouseEventArgs& e)
{
	
	Window::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		if ((d_parent != NULL) && d_dragEnabled)
		{
			
			if (captureInput())
			{
				
				d_dragging = true;
				d_dragPoint = screenToWindow(e.position);

				if (getMetricsMode() == Relative)
				{
					d_dragPoint = relativeToAbsolute(d_dragPoint);
				}

				
				d_oldCursorArea = MouseCursor::getSingleton().getConstraintArea();

				
				Rect constrainArea;

				if ((d_parent == NULL) || (d_parent->getParent() == NULL))
				{
					constrainArea = System::getSingleton().getRenderer()->getRect().getIntersection(d_oldCursorArea);
				}
				else 
				{
					constrainArea = d_parent->getParent()->getInnerRect().getIntersection(d_oldCursorArea);
				}

				MouseCursor::getSingleton().setConstraintArea(&constrainArea);
			}

		}

		e.handled = true;
	}
}



void Titlebar::onMouseButtonUp(MouseEventArgs& e)
{
	
	Window::onMouseButtonUp(e);

	if (e.button == LeftButton)
	{
		releaseInput();
		e.handled = true;
	}

}



void Titlebar::onMouseDoubleClicked(MouseEventArgs& e)
{
	
	Window::onMouseDoubleClicked(e);

	if (e.button == LeftButton)
	{
		
		if (d_parent != NULL && d_parent->testClassName( (CEGUI::utf8*)"FrameWindow" ) )
		{
			
			((FrameWindow*)d_parent)->toggleRollup();
		}

		e.handled = true;
	}

}



void Titlebar::onCaptureLost(WindowEventArgs& e)
{
	
	Window::onCaptureLost(e);

	
	d_dragging = false;

	
	MouseCursor::getSingleton().setConstraintArea(&d_oldCursorArea);
}



void Titlebar::onFontChanged(WindowEventArgs& e)
{
	Window::onFontChanged(e);

	if (d_parent != NULL)
	{
		d_parent->performChildWindowLayout();
	}
}



void Titlebar::addTitlebarProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( Titlebar );
	   CEGUI_ADD_STATICPROPERTY( &d_dragEnabledProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_captionColourProperty );
	CEGUI_END_ADD_STATICPROPERTY
}



colour	Titlebar::getCaptionColour(void) const
{
	return d_captionColour;
}



void Titlebar::setCaptionColour(const colour& col)
{
	d_captionColour = col;
	requestRedraw();
}

} 
