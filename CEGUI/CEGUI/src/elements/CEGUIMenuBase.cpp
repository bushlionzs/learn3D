

#include "elements/CEGUIMenuBase.h"
#include "elements/CEGUIPopupMenu.h"
#include "elements/CEGUIMenuItem.h"


namespace CEGUI
{


MenuBaseProperties::ItemSpacing			MenuBase::d_itemSpacingProperty;
MenuBaseProperties::HorzPadding			MenuBase::d_horzPaddingProperty;
MenuBaseProperties::VertPadding			MenuBase::d_vertPaddingProperty;
MenuBaseProperties::BorderWidth			MenuBase::d_borderWidthProperty;
MenuBaseProperties::BackgroundColours	MenuBase::d_backgroundColoursProperty;
MenuBaseProperties::AllowMultiplePopups	MenuBase::d_allowMultiplePopupsProperty;



const colour MenuBase::DefaultBackgroundColour = 0xFFFFFFFF;


const String MenuBase::EventNamespace("MenuBase");
const String MenuBase::EventPopupOpened( (utf8*)"PopupOpened" );
const String MenuBase::EventPopupClosed( (utf8*)"PopupClosed" );


MenuBase::MenuBase(const String& type, const String& name)
	: ItemListBase(type, name),
	d_itemSpacing(0.0f),
	d_horzPadding(0.0f),
	d_vertPadding(0.0f),
	d_borderWidth(0.0f),
	d_backgroundColours(DefaultBackgroundColour),
	d_popup(NULL),
	d_allowMultiplePopups(false)
{
	
	addMenuBaseProperties();
}



MenuBase::~MenuBase(void)
{
}



void MenuBase::changePopupMenuItem(MenuItem* item)
{
	if (!d_allowMultiplePopups&&d_popup==item)
		return;

	if (!d_allowMultiplePopups&&d_popup!=NULL)
	{
		d_popup->closePopupMenu(false);
		WindowEventArgs we(d_popup->getPopupMenu());
		d_popup = NULL;
		onPopupClosed(we);
	}

	if (item!=NULL)
	{
		d_popup = item;
		d_popup->getPopupMenu()->openPopupMenu();
		WindowEventArgs we(d_popup->getPopupMenu());
		onPopupOpened(we);
	}

}


void MenuBase::onPopupOpened(WindowEventArgs& e)
{
	fireEvent(EventPopupOpened, e, EventNamespace);
}



void MenuBase::onPopupClosed(WindowEventArgs& e)
{
	fireEvent(EventPopupClosed, e, EventNamespace);
}


void MenuBase::addMenuBaseProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( MenuBase );
	   CEGUI_ADD_STATICPROPERTY( &d_itemSpacingProperty );
       CEGUI_ADD_STATICPROPERTY( &d_horzPaddingProperty );
       CEGUI_ADD_STATICPROPERTY( &d_vertPaddingProperty );
       CEGUI_ADD_STATICPROPERTY( &d_borderWidthProperty );
       CEGUI_ADD_STATICPROPERTY( &d_backgroundColoursProperty );
       CEGUI_ADD_STATICPROPERTY( &d_allowMultiplePopupsProperty );
	CEGUI_END_ADD_STATICPROPERTY
}

} 
