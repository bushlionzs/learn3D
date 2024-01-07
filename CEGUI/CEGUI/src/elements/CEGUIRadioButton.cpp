

#include "elements/CEGUIRadioButton.h"


namespace CEGUI
{
const String RadioButton::EventNamespace("RadioButton");


RadioButtonProperties::Selected	RadioButton::d_selectedProperty;
RadioButtonProperties::GroupID	RadioButton::d_groupIDProperty;




const String RadioButton::EventSelectStateChanged( (utf8*)"SelectStateChanged" );



RadioButton::RadioButton(const String& type, const String& name) :
	ButtonBase(type, name),
	d_selected(false),
	d_groupID(0)
{
	addRadioButtonProperties();
}



RadioButton::~RadioButton(void)
{
}



void RadioButton::setSelected(bool select)
{
	if (select != d_selected)
	{
		d_selected = select;
		requestRedraw();

		
		if (d_selected)
		{
			deselectOtherButtonsInGroup();
		}

		WindowEventArgs args(this);
		onSelectStateChanged(args);
	}

}



void RadioButton::setGroupID(ulong group)
{
	d_groupID = group;

	if (d_selected)
	{
		deselectOtherButtonsInGroup();
	}

}


void RadioButton::deselectOtherButtonsInGroup(void) const
{
	
	if (d_parent != NULL)
	{
		int child_count = d_parent->getChildCount();

		
		for (int child = 0; child < child_count; ++child)
		{
			
			if (d_parent->getChildAtIdx(child)->getType() == getType())
			{
				RadioButton* rb = (RadioButton*)d_parent->getChildAtIdx(child);

				
				if (rb->isSelected() && (rb != this) && (rb->getGroupID() == d_groupID))
				{
					
					rb->setSelected(false);
				}

			}

		}

	}

}



void RadioButton::onSelectStateChanged(WindowEventArgs& e)
{
	fireEvent(EventSelectStateChanged, e, EventNamespace);
}



void RadioButton::onMouseButtonUp(MouseEventArgs& e)
{
	if ((e.button == LeftButton) && isPushed())
	{
		Window* sheet = System::getSingleton().getGUISheet();

		if (sheet != NULL)
		{
			
			if (this == sheet->getChildAtPosition(e.position))
			{
				
				setSelected(true);
			}

		}

		e.handled = true;
	}

	
	ButtonBase::onMouseButtonUp(e);
}



RadioButton* RadioButton::getSelectedButtonInGroup(void) const
{
	
	if (d_parent != NULL)
	{
		int child_count = d_parent->getChildCount();

		
		for (int child = 0; child < child_count; ++child)
		{
			
			if (d_parent->getChildAtIdx(child)->getType() == getType())
			{
				RadioButton* rb = (RadioButton*)d_parent->getChildAtIdx(child);

				
				if (rb->isSelected() && (rb->getGroupID() == d_groupID))
				{
					
					return rb;
				}

			}

		}

	}

	
	return NULL;
}


void RadioButton::addRadioButtonProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( RadioButton );
	   CEGUI_ADD_STATICPROPERTY( &d_selectedProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_groupIDProperty );
	CEGUI_END_ADD_STATICPROPERTY
}


} 
