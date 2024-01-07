

#include "elements/CEGUIButtonBase.h"
#include "CEGUIMouseCursor.h"


namespace CEGUI
{

ButtonBaseProperties::NormalTextColour		ButtonBase::d_normalTextColourProperty;
ButtonBaseProperties::HoverTextColour		ButtonBase::d_hoverTextColourProperty;
ButtonBaseProperties::PushedTextColour		ButtonBase::d_pushedTextColourProperty;
ButtonBaseProperties::DisabledTextColour	ButtonBase::d_disabledTextColourProperty;




const colour	ButtonBase::DefaultNormalLabelColour	= 0xFFFFFFFF;
const colour	ButtonBase::DefaultHoverLabelColour		= 0xFFFFFFFF;
const colour	ButtonBase::DefaultPushedLabelColour	= 0xFFFFFFFF;
const colour	ButtonBase::DefaultDisabledLabelColour	= 0xFF7F7F7F;



ButtonBase::ButtonBase(const String& type, const String& name) :
	Window(type, name),
	d_pushed(false),
	d_hovering(false),
	d_stayHover(false),
	d_normalColour(DefaultNormalLabelColour),
	d_hoverColour(DefaultHoverLabelColour),
	d_pushedColour(DefaultPushedLabelColour),
	d_disabledColour(DefaultDisabledLabelColour)
{
	addButtonBaseProperties();
}



ButtonBase::~ButtonBase(void)
{
}



void ButtonBase::updateInternalState(const Point& mouse_pos)
{
	bool oldstate = d_hovering;

	
	d_hovering = false;

	
	const Window* capture_wnd = getCaptureWindow();

	if ((capture_wnd == NULL) || (capture_wnd == this))
	{
		Window* sheet = System::getSingleton().getGUISheet();

		if (sheet != NULL)
		{
			
			if ((this == sheet->getChildAtPosition(mouse_pos)) != d_pushed)
			{
				d_hovering = true;
			}
		}
	}

	
	if (oldstate != d_hovering)
	{
		requestRedraw();
	}

}



void ButtonBase::setNormalTextColour(const colour& colour)
{
	if (d_normalColour != colour)
	{
		d_normalColour = colour;
		requestRedraw();
	}

}



void ButtonBase::setHoverTextColour(const colour& colour)
{
	if (d_hoverColour != colour)
	{
		d_hoverColour = colour;
		requestRedraw();
	}

}



void ButtonBase::setPushedTextColour(const colour& colour)
{
	if (d_pushedColour != colour)
	{
		d_pushedColour = colour;
		requestRedraw();
	}

}



void ButtonBase::setDisabledTextColour(const colour& colour)
{
	if (d_disabledColour != colour)
	{
		d_disabledColour = colour;
		requestRedraw();
	}

}

void ButtonBase::setStayHover(bool show)
{
	d_stayHover = show;
}


void ButtonBase::drawSelf(float z)
{
	if (isHovering() && !isDisabled())
	{
		drawHover(z);
	}
	else if (isPushed() || d_stayHover )
	{
		drawPushed(z);
	}
	else if (isDisabled())
	{
		drawDisabled(z);
	}
	else
	{
		drawNormal(z);
	}

}



void ButtonBase::onMouseMove(MouseEventArgs& e)
{
	
	
	
	
	

	
	Window::onMouseMove(e);

	if( d_pushed )
	{
		if( d_isInWindow && !isHit( e.position ) )
		{
			onMouseLeaves(e);
			d_isInWindow = true;
		}
		else if( !d_isInWindow && isHit( e.position ) )
		{
			onMouseEnters(e);
			d_isInWindow = false;
		}
	}

	updateInternalState(e.position);
	e.handled = true;
}



void ButtonBase::onMouseButtonDown(MouseEventArgs& e)
{
	
	Window::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		if (captureInput())
		{
			d_pushed = true;
			updateInternalState(e.position);
			requestRedraw();
		}
		d_isInWindow = true;

		
		e.handled = true;
	}

}



void ButtonBase::onMouseButtonUp(MouseEventArgs& e)
{
	
	Window::onMouseButtonUp(e);

	if ( e.button == LeftButton )
	{
		releaseInput();
		d_isInWindow = false;

		
		e.handled = true;
	}

}


void ButtonBase::onCaptureLost(WindowEventArgs& e)
{
	
	Window::onCaptureLost(e);

	d_pushed = false;
	updateInternalState(MouseCursor::getSingleton().getPosition());
	requestRedraw();

	
	e.handled = true;
}



void ButtonBase::onMouseLeaves(MouseEventArgs& e)
{
	
	Window::onMouseLeaves(e);

	d_pushed   = false;
	d_hovering = false;
	requestRedraw();

	e.handled = true;
}





















void ButtonBase::addButtonBaseProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( ButtonBase );
	   CEGUI_ADD_STATICPROPERTY( &d_normalTextColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_hoverTextColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_pushedTextColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_disabledTextColourProperty );
	CEGUI_END_ADD_STATICPROPERTY
}

} 
