

#include "elements/CEGUITabButton.h"


namespace CEGUI
{
const String TabButton::EventNamespace("TabButton");


const String TabButton::EventClicked( (utf8*)"Clicked" );



TabButton::TabButton(const String& type, const String& name) :
	ButtonBase(type, name),
    d_selected(false), 
    d_rightOfSelected(true)
{
}



TabButton::~TabButton(void)
{
}


void TabButton::onClicked(WindowEventArgs& e)
{
	fireEvent(EventClicked, e, EventNamespace);
}



void TabButton::onMouseButtonUp(MouseEventArgs& e)
{
	if ((e.button == LeftButton) && isPushed())
	{
		Window* sheet = System::getSingleton().getGUISheet();

		if (sheet != NULL)
		{
			
			if (this == sheet->getChildAtPosition(e.position))
			{
				
				WindowEventArgs args(this);
				onClicked(args);
			}

		}

		e.handled = true;
	}

	
	ButtonBase::onMouseButtonUp(e);
}

void TabButton::drawSelf(float z)
{
	if (isDisabled())
	{
		drawDisabled(z);
	}
	else if (isHovering())
	{
		drawHover(z);
	}
    else if (d_selected)
    {
        drawPushed(z);
    }
    else
    {
        drawNormal(z);
    }
}

void TabButton::setTargetWindow(Window* wnd)
{
    d_targetWindow = wnd;
    
    setText(wnd->getText());
    
}

} 
