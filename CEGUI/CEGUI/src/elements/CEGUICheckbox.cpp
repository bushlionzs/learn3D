

#include "elements/CEGUICheckbox.h"


namespace CEGUI
{
const String Checkbox::EventNamespace("Checkbox");


CheckboxProperties::Selected	Checkbox::d_selectedProperty;




const String Checkbox::EventCheckStateChanged( (utf8*)"CheckStateChanged" );



Checkbox::Checkbox(const String& type, const String& name) :
	ButtonBase(type, name),
	d_selected(false)
{
	addCheckboxProperties();
}



Checkbox::~Checkbox(void)
{
}



void Checkbox::setSelected(bool select)
{
	if (select != d_selected)
	{
		d_selected = select;
		requestRedraw();

        WindowEventArgs args(this);
		onSelectStateChange(args);
	}

}



void Checkbox::onSelectStateChange(WindowEventArgs& e)
{
	fireEvent(EventCheckStateChanged, e, EventNamespace);
}



void Checkbox::onMouseButtonUp(MouseEventArgs& e)
{
	if ((e.button == LeftButton) && isPushed())
	{
		Window* sheet = System::getSingleton().getGUISheet();

		if (sheet != NULL)
		{
			
			if (this == sheet->getChildAtPosition(e.position))
			{
				
				setSelected(d_selected ^ true);
			}

		}

		e.handled = true;
	}

	
	ButtonBase::onMouseButtonUp(e);
}


void Checkbox::addCheckboxProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( Checkbox );
	   CEGUI_ADD_STATICPROPERTY( &d_selectedProperty );
	CEGUI_END_ADD_STATICPROPERTY
}



} 
