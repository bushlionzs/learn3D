

#include "elements/CEGUIMenuItem.h"
#include "elements/CEGUIMenubar.h"
#include "elements/CEGUIPopupMenu.h"

#include "CEGUILogger.h"


namespace CEGUI
{


MenuItemProperties::HoverColour			MenuItem::d_hoverColourProperty;
MenuItemProperties::PushedColour		MenuItem::d_pushedColourProperty;
MenuItemProperties::OpenedColour		MenuItem::d_openedColourProperty;
MenuItemProperties::NormalTextColour	MenuItem::d_normalTextColourProperty;
MenuItemProperties::DisabledTextColour	MenuItem::d_disabledTextColourProperty;




const colour	MenuItem::DefaultHoverColour		= 0xFFFFFFFF;
const colour	MenuItem::DefaultPushedColour		= 0xFFFFFFFF;
const colour	MenuItem::DefaultOpenedColour		= 0xFFEFEFEF;
const colour	MenuItem::DefaultNormalTextColour	= 0xFFFFFFFF;
const colour	MenuItem::DefaultDisabledTextColour	= 0xFF7F7F7F;


const String MenuItem::EventNamespace("MenuItem");
const String MenuItem::EventClicked( (utf8*)"Clicked" );



MenuItem::MenuItem(const String& type, const String& name)
	: TextItem(type, name),
	d_pushed(false),
	d_hovering(false),
	d_opened(false),
	d_hoverColour(DefaultHoverColour),
	d_pushedColour(DefaultPushedColour),
	d_openedColour(DefaultOpenedColour),
	d_normalTextColour(DefaultNormalTextColour),
	d_disabledTextColour(DefaultDisabledTextColour),
	d_popup(NULL)
{
	
	setWantsMultiClickEvents(false);
	
	addMenuItemProperties();
}



MenuItem::~MenuItem(void)
{
}



void MenuItem::updateInternalState(const Point& mouse_pos)
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

				
				if (getParent()->testClassName("MenuBase"))
				{
					MenuBase* menu = (MenuBase*)getParent();

					
					if (menu->isItemInList(this))
					{
						
						if ( !menu->isMultiplePopupsAllowed() && menu->getPopupMenuItem()!=NULL )
						{
							
							openPopupMenu();
						}

					}

				}

			}

		}

	}

	
	if (oldstate != d_hovering)
	{
		requestRedraw();
	}

}



void MenuItem::setPopupMenu(PopupMenu* popup)
{
	
	if (isChild(popup))
	{
		d_popup = popup;
		return;
	}

	
	addChildWindow(popup);
	d_popup = popup;
}


void MenuItem::openPopupMenu()
{
	
	if ( d_popup == NULL || d_opened )
		return;

	
	MenuBase* menu = (Menubar*)getParent();
	if (getParent()->testClassName("Menubar") && menu->isItemInList(this))
	{
		
		Point pos(0,getAbsoluteRect().getHeight());
		d_popup->setPosition(Absolute,pos);

		menu->changePopupMenuItem(this);
	}
	
	else if (getParent()->testClassName("PopupMenu") && menu->isItemInList(this))
	{
		
		const Rect absrect = getAbsoluteRect();
		Point pos(absrect.getWidth(),0);
		d_popup->setPosition(Absolute,pos);

		menu->changePopupMenuItem(this);
	}
	
	else
	{
		
		d_popup->openPopupMenu();
	}

	d_opened = true;
	requestRedraw();
}



void MenuItem::closePopupMenu(bool notify)
{
	
	if ( d_popup == NULL || !d_opened )
		return;

	
	
	
	MenuBase* menu = (MenuBase*)getParent();
	if (notify && getParent()->testClassName("MenuBase") && menu->isItemInList(this) && !menu->isMultiplePopupsAllowed())
	{
		menu->changePopupMenuItem(NULL);
	}
	
	else
	{
		
		
		d_popup->closePopupMenu();
	}

	d_opened = false;
	requestRedraw();
}



bool MenuItem::togglePopupMenu(void)
{
	if (d_opened)
	{
		closePopupMenu();
		return false;
	}

	openPopupMenu();
	return true;
}


void MenuItem::setHoverColour(const colour& col)
{
	if (d_hoverColour != col)
	{
		d_hoverColour = col;
		requestRedraw();
	}

}



void MenuItem::setPushedColour(const colour& col)
{
	if (d_pushedColour != col)
	{
		d_pushedColour = col;
		requestRedraw();
	}

}



void MenuItem::setOpenedColour(const colour& col)
{
	if (d_openedColour != col)
	{
		d_openedColour = col;
		requestRedraw();
	}

}



void MenuItem::setNormalTextColour(const colour& col)
{
	if (d_normalTextColour != col)
	{
		d_normalTextColour = col;
		requestRedraw();
	}

}



void MenuItem::setDisabledTextColour(const colour& col)
{
	if (d_disabledTextColour != col)
	{
		d_disabledTextColour = col;
		requestRedraw();
	}

}



void MenuItem::closeAllMenuItemPopups()
{
	
	PopupMenu* pop = (PopupMenu*)getParent();
	if (getParent()->testClassName("PopupMenu") && pop->isItemInList(this))
	{
		
		MenuItem* item = (MenuItem*)pop->getParent();
		if (item!=NULL && pop->getParent()->testClassName("MenuItem"))
		{
			
			item->closePopupMenu();
			
			item->closeAllMenuItemPopups();
		}
		
		else
		{
			pop->closePopupMenu();
		}
	}
}



void MenuItem::onClicked(WindowEventArgs& e)
{
	
	if (!d_opened && !d_popupWasClosed)
	{
		closeAllMenuItemPopups();
	}
	d_popupWasClosed=false;
	fireEvent(EventClicked, e, EventNamespace);
}



void MenuItem::onMouseMove(MouseEventArgs& e)
{
	
	
	
	
	

	
	Window::onMouseMove(e);

	updateInternalState(e.position);
	e.handled = true;
}



void MenuItem::onMouseButtonDown(MouseEventArgs& e)
{
	
	Window::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		d_popupWasClosed = false;
		if (captureInput())
		{
			d_pushed = true;
			updateInternalState(e.position);
			d_popupWasClosed = !togglePopupMenu();
			requestRedraw();
		}

		
		e.handled = true;
	}

}



void MenuItem::onMouseButtonUp(MouseEventArgs& e)
{
	
	Window::onMouseButtonUp(e);

	if (e.button == LeftButton)
	{
		releaseInput();
		
		
		if ( !d_popupWasClosed && System::getSingleton().getGUISheet()->getChildAtPosition(e.position) == this )
		{
			WindowEventArgs we(this);
			onClicked(we);
		}

		
		e.handled = true;
	}

}


void MenuItem::onCaptureLost(WindowEventArgs& e)
{
	
	Window::onCaptureLost(e);

	d_pushed = false;
	updateInternalState(MouseCursor::getSingleton().getPosition());
	requestRedraw();

	
	e.handled = true;
}



void MenuItem::onMouseLeaves(MouseEventArgs& e)
{
	
	Window::onMouseLeaves(e);

	d_hovering = false;
	requestRedraw();

	e.handled = true;
}



void MenuItem::addChild_impl(Window* wnd)
{
	TextItem::addChild_impl(wnd);

	
	if (wnd->testClassName("PopupMenu") && d_popup==NULL)
	{
		setPopupMenu((PopupMenu*)wnd);
	}

}



void MenuItem::addMenuItemProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( MenuItem );
	   CEGUI_ADD_STATICPROPERTY( &d_hoverColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_pushedColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_openedColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_normalTextColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_disabledTextColourProperty );
	CEGUI_END_ADD_STATICPROPERTY
}

} 
