

#include "elements/CEGUICombobox.h"
#include "elements/CEGUIEditbox.h"
#include "elements/CEGUIPushButton.h"
#include "elements/CEGUIComboDropList.h"
#include "elements/CEGUIListboxItem.h"
#include "elements/CEGUIScrollbar.h"




namespace CEGUI
{
const String Combobox::EventNamespace("Combobox");


ComboboxProperties::ReadOnly					Combobox::d_readOnlyProperty;
ComboboxProperties::ValidationString			Combobox::d_validationStringProperty;
ComboboxProperties::CaratIndex					Combobox::d_caratIndexProperty;
ComboboxProperties::EditSelectionStart			Combobox::d_selStartProperty;
ComboboxProperties::EditSelectionLength			Combobox::d_selLengthProperty;
ComboboxProperties::MaxEditTextLength			Combobox::d_maxTextLengthProperty;
ComboboxProperties::NormalEditTextColour		Combobox::d_normalTextColourProperty;
ComboboxProperties::SelectedEditTextColour		Combobox::d_selectedTextColourProperty;
ComboboxProperties::ActiveEditSelectionColour	Combobox::d_activeSelectionColourProperty;
ComboboxProperties::InactiveEditSelectionColour	Combobox::d_inactiveSelectionColourProperty;
ComboboxProperties::SortList					Combobox::d_sortProperty;
ComboboxProperties::ForceVertScrollbar			Combobox::d_forceVertProperty;
ComboboxProperties::ForceHorzScrollbar			Combobox::d_forceHorzProperty;
ComboboxProperties::SingleClickMode				Combobox::d_singleClickOperationProperty;
ComboboxProperties::DropButtonAndVertScrollbarMaxWidth				Combobox::d_dropButtonAndVertScrollbarMaxWidthProperty;




const String Combobox::EventReadOnlyModeChanged( (utf8*)"ReadOnlyChanged" );
const String Combobox::EventValidationStringChanged( (utf8*)"ValidationStringChanged" );
const String Combobox::EventMaximumTextLengthChanged( (utf8*)"MaximumTextLengthChanged" );
const String Combobox::EventTextInvalidated( (utf8*)"TextInvalidatedEvent" );
const String Combobox::EventInvalidEntryAttempted( (utf8*)"InvalidEntryAttempted" );
const String Combobox::EventCaratMoved( (utf8*)"CaratMoved" );
const String Combobox::EventTextSelectionChanged( (utf8*)"TextSelectionChanged" );
const String Combobox::EventEditboxFull( (utf8*)"EditboxFullEvent" );
const String Combobox::EventTextAccepted( (utf8*)"TextAcceptedEvent" );


const String Combobox::EventListContentsChanged( (utf8*)"ListContentsChanged" );
const String Combobox::EventListSelectionChanged( (utf8*)"ListSelectionChanged" );
const String Combobox::EventSortModeChanged( (utf8*)"SortModeChanged" );
const String Combobox::EventVertScrollbarModeChanged( (utf8*)"VertScrollbarModeChanged" );
const String Combobox::EventHorzScrollbarModeChanged( (utf8*)"HorzScrollbarModeChanged" );


const String Combobox::EventDropListDisplayed( (utf8*)"DropListDisplayed" );
const String Combobox::EventDropListRemoved( (utf8*)"DropListRemoved" );
const String Combobox::EventListSelectionAccepted( (utf8*)"ListSelectionAccepted" );

	

Combobox::Combobox(const String& type, const String& name) :
	Window(type, name)
{
	d_singleClickOperation = false;
	d_comboboxScrollbarMaxWidth = 1000;
	d_bUseComboboxScrollbarMaxWidth = false;
	addComboboxProperties();
}



Combobox::~Combobox(void)
{
}



void Combobox::initialise(void)
{
	d_editbox	= createEditbox(getName() + "__auto_editbox__");
	d_droplist	= createDropList(getName() + "__auto_droplist__");
	d_button	= createPushButton(getName() + "__auto_button__");
    d_droplist->setFont(getFont());
    d_editbox->setFont(getFont());

	addChildWindow(d_editbox);
	addChildWindow(d_droplist);
	addChildWindow(d_button);

	if(d_droplist)
	{
		Scrollbar* pScrollbar = d_droplist->getVertScrollbar();
		if(pScrollbar)
		{
			pScrollbar->setUsedInCombobox(true);
		}
	}
	

	
	d_button->subscribeEvent(PushButton::EventMouseButtonDown, Event::Subscriber(&CEGUI::Combobox::button_PressHandler, this));
	d_droplist->subscribeEvent(ComboDropList::EventListSelectionAccepted, Event::Subscriber(&CEGUI::Combobox::droplist_SelectionAcceptedHandler, this));
	d_droplist->subscribeEvent(Window::EventHidden, Event::Subscriber(&CEGUI::Combobox::droplist_HiddenHandler, this));
	d_editbox->subscribeEvent(Window::EventMouseButtonDown, Event::Subscriber(&CEGUI::Combobox::editbox_MouseDownHandler, this));

	
	d_editbox->subscribeEvent(Editbox::EventReadOnlyModeChanged, Event::Subscriber(&CEGUI::Combobox::editbox_ReadOnlyChangedHandler, this));
	d_editbox->subscribeEvent(Editbox::EventValidationStringChanged, Event::Subscriber(&CEGUI::Combobox::editbox_ValidationStringChangedHandler, this));
	d_editbox->subscribeEvent(Editbox::EventMaximumTextLengthChanged, Event::Subscriber(&CEGUI::Combobox::editbox_MaximumTextLengthChangedHandler, this));
	d_editbox->subscribeEvent(Editbox::EventTextInvalidated, Event::Subscriber(&CEGUI::Combobox::editbox_TextInvalidatedEventHandler, this));
	d_editbox->subscribeEvent(Editbox::EventInvalidEntryAttempted, Event::Subscriber(&CEGUI::Combobox::editbox_InvalidEntryAttemptedHandler, this));
	d_editbox->subscribeEvent(Editbox::EventCaratMoved, Event::Subscriber(&CEGUI::Combobox::editbox_CaratMovedHandler, this));
	d_editbox->subscribeEvent(Editbox::EventTextSelectionChanged, Event::Subscriber(&CEGUI::Combobox::editbox_TextSelectionChangedHandler, this));
	d_editbox->subscribeEvent(Editbox::EventEditboxFull, Event::Subscriber(&CEGUI::Combobox::editbox_EditboxFullEventHandler, this));
	d_editbox->subscribeEvent(Editbox::EventTextAccepted, Event::Subscriber(&CEGUI::Combobox::editbox_TextAcceptedEventHandler, this));
	d_editbox->subscribeEvent(Editbox::EventTextChanged, Event::Subscriber(&CEGUI::Combobox::editbox_TextChangedEventHandler, this));
	d_droplist->subscribeEvent(Listbox::EventListContentsChanged, Event::Subscriber(&CEGUI::Combobox::listbox_ListContentsChangedHandler, this));
	d_droplist->subscribeEvent(Listbox::EventSelectionChanged, Event::Subscriber(&CEGUI::Combobox::listbox_ListSelectionChangedHandler, this));
	d_droplist->subscribeEvent(Listbox::EventSortModeChanged, Event::Subscriber(&CEGUI::Combobox::listbox_SortModeChangedHandler, this));
	d_droplist->subscribeEvent(Listbox::EventVertScrollbarModeChanged, Event::Subscriber(&CEGUI::Combobox::listbox_VertScrollModeChangedHandler, this));
	d_droplist->subscribeEvent(Listbox::EventHorzScrollbarModeChanged, Event::Subscriber(&CEGUI::Combobox::listbox_HorzScrollModeChangedHandler, this));

	d_editbox->subscribeEvent( Window::EventMouseEnters, Event::Subscriber(&CEGUI::Combobox::MouseEnters, this) );
	d_editbox->subscribeEvent( Window::EventMouseLeaves, Event::Subscriber(&CEGUI::Combobox::MouseLeaves, this) );
	d_droplist->subscribeEvent( Window::EventMouseEnters, Event::Subscriber(&CEGUI::Combobox::MouseEnters, this) );
	d_droplist->subscribeEvent( Window::EventMouseLeaves, Event::Subscriber(&CEGUI::Combobox::MouseLeaves, this) );
	d_button->subscribeEvent( Window::EventMouseEnters, Event::Subscriber(&CEGUI::Combobox::MouseEnters, this) );
	d_button->subscribeEvent( Window::EventMouseLeaves, Event::Subscriber(&CEGUI::Combobox::MouseLeaves, this) );
	
	performChildWindowLayout();
}

void Combobox::onSized(WindowEventArgs& e)
{
	Window::onSized(e);

	if(d_bUseComboboxScrollbarMaxWidth)
	{
		float maxWidth = d_comboboxScrollbarMaxWidth;

		if(d_button)
		{
			if(d_button->getAbsoluteWidth() > maxWidth)
			{
				d_button->setWidth(CEGUI::Absolute, maxWidth);
				d_button->setWindowYPosition(UDim(0, 0));
			}
		}

		if(d_editbox)
		{
			float editWidth = getAbsoluteWidth() - maxWidth;
			d_editbox->setWidth(Absolute, editWidth);
		}

		if(d_droplist)
		{
			Scrollbar* pScrollbar = d_droplist->getVertScrollbar();
			if(pScrollbar)
			{
				pScrollbar->setComboboxScrollbarMaxWidth(maxWidth);
			}
		}
	}
}

void Combobox::setComboboxScrollbarMaxWidth(int maxWidth)
{
	d_bUseComboboxScrollbarMaxWidth = true;
	d_comboboxScrollbarMaxWidth = maxWidth;
}

bool	Combobox::MouseEnters( const EventArgs& e)
{
	MouseEventArgs ma(NULL);
	ma.handled = e.handled;
	ma.window = this;
	fireEvent(EventMouseEnters, ma, EventNamespace);
	return true;
} 
bool	Combobox::MouseLeaves( const EventArgs& e)
{
	MouseEventArgs ma(NULL);
	ma.handled = e.handled;
	ma.window = this;
	
	fireEvent(EventMouseLeaves, ma, EventNamespace);
	return true;
}


void Combobox::showDropList(void)
{
	
	d_droplist->repositionSelf(d_editbox);
	
	d_droplist->show();
	d_droplist->activate();
	d_droplist->captureInput();

	
	WindowEventArgs args(this);
	onDropListDisplayed(args);
}



void Combobox::hideDropList(void)
{
	
	
	d_droplist->releaseInput();
}



bool Combobox::hasInputFocus(void) const
{
	return d_editbox->hasInputFocus();
}



bool Combobox::isReadOnly(void) const
{
	return d_editbox->isReadOnly();
}



bool Combobox::isTextValid(void) const
{
	return d_editbox->isTextValid();
}



const String& Combobox::getValidationString(void) const
{
	return d_editbox->getValidationString();
}



size_t Combobox::getCaratIndex(void) const
{
	return d_editbox->getCaratIndex();
}



size_t Combobox::getSelectionStartIndex(void) const
{
	return d_editbox->getSelectionStartIndex();
}



size_t Combobox::getSelectionEndIndex(void) const
{
	return d_editbox->getSelectionEndIndex();
}



size_t Combobox::getSelectionLength(void) const
{
	return d_editbox->getSelectionLength();
}



size_t Combobox::getMaxTextLength(void) const
{
	return d_editbox->getMaxTextLength();
}



colour Combobox::getNormalTextColour(void) const	
{
	return d_editbox->getNormalTextColour();
}



colour Combobox::getSelectedTextColour(void) const
{
	return d_editbox->getSelectedTextColour();
}



colour Combobox::getNormalSelectBrushColour(void) const
{
	return d_editbox->getNormalSelectBrushColour();
}



colour Combobox::getInactiveSelectBrushColour(void) const
{
	return d_editbox->getInactiveSelectBrushColour();
}



void Combobox::setReadOnly(bool setting)
{
	d_editbox->setReadOnly(setting);
}



void Combobox::setValidationString(const String& validation_string)
{
	d_editbox->setValidationString(validation_string);
}



void Combobox::setCaratIndex(size_t carat_pos)
{
	d_editbox->setCaratIndex(carat_pos);
}



void Combobox::setSelection(size_t start_pos, size_t end_pos)
{
	d_editbox->setSelection(start_pos, end_pos);
}



void Combobox::setMaxTextLength(size_t max_len)
{
	d_editbox->setMaxTextLength(max_len);
}



void Combobox::setNormalTextColour(colour col)
{
	d_editbox->setNormalTextColour(col);
}



void Combobox::setSelectedTextColour(colour col)
{
	d_editbox->setSelectedTextColour(col);
}



void Combobox::setNormalSelectBrushColour(colour col)
{
	d_editbox->setNormalSelectBrushColour(col);
}



void Combobox::setInactiveSelectBrushColour(colour col)
{
	d_editbox->setInactiveSelectBrushColour(col);
}



size_t Combobox::getItemCount(void) const
{
	return d_droplist->getItemCount();
}



ListboxItem* Combobox::getSelectedItem(void) const
{
	ListboxItem* pSelectedItem = d_droplist->getFirstSelectedItem();
	if(pSelectedItem)
		return pSelectedItem;
	
	return d_droplist->findItemWithText(d_editbox->getText(), NULL);
}



ListboxItem* Combobox::getListboxItemFromIndex(size_t index) const
{
	return d_droplist->getListboxItemFromIndex(index);
}



size_t Combobox::getItemIndex(const ListboxItem* item) const
{
	return d_droplist->getItemIndex(item);
}



bool Combobox::isSortEnabled(void) const
{
	return d_droplist->isSortEnabled();
}



bool Combobox::isItemSelected(size_t index) const
{
	return d_droplist->isItemSelected(index);
}



ListboxItem* Combobox::findItemWithText(const String& text, const ListboxItem* start_item)
{
	return d_droplist->findItemWithText(text, start_item);
}



bool Combobox::isListboxItemInList(const ListboxItem* item) const
{
	return d_droplist->isListboxItemInList(item);
}



void Combobox::resetList(void)
{
	d_droplist->resetList();
}



void Combobox::addItem(ListboxItem* item)
{
	d_droplist->addItem(item);
}



void Combobox::insertItem(ListboxItem* item, const ListboxItem* position)
{
	d_droplist->insertItem(item, position);
}



void Combobox::removeItem(const ListboxItem* item)
{
	d_droplist->removeItem(item);
}



void Combobox::clearAllSelections(void)
{
	d_droplist->clearAllSelections();
}



void Combobox::setSortingEnabled(bool setting)
{
	d_droplist->setSortingEnabled(setting);
}



void Combobox::setShowVertScrollbar(bool setting)
{
	d_droplist->setShowVertScrollbar(setting);
}



void Combobox::setShowHorzScrollbar(bool setting)
{
	d_droplist->setShowHorzScrollbar(setting);
}



void Combobox::setItemSelectState(ListboxItem* item, bool state)
{
	d_droplist->setItemSelectState(item, state);
}



void Combobox::setItemSelectState(size_t item_index, bool state)
{
	d_droplist->setItemSelectState(item_index, state);
}



void Combobox::handleUpdatedListItemData(void)
{
	d_droplist->handleUpdatedItemData();
}



void Combobox::onReadOnlyChanged(WindowEventArgs& e)
{
	fireEvent(EventReadOnlyModeChanged, e, EventNamespace);
}



void Combobox::onValidationStringChanged(WindowEventArgs& e)
{
	fireEvent(EventValidationStringChanged, e, EventNamespace);
}



void Combobox::onMaximumTextLengthChanged(WindowEventArgs& e)
{
	fireEvent(EventMaximumTextLengthChanged, e, EventNamespace);
}



void Combobox::onTextInvalidatedEvent(WindowEventArgs& e)
{
	fireEvent(EventTextInvalidated, e, EventNamespace);
}



void Combobox::onInvalidEntryAttempted(WindowEventArgs& e)
{
	fireEvent(EventInvalidEntryAttempted, e, EventNamespace);
}



void Combobox::onCaratMoved(WindowEventArgs& e)
{
	fireEvent(EventCaratMoved, e, EventNamespace);
}



void Combobox::onTextSelectionChanged(WindowEventArgs& e)
{
	fireEvent(EventTextSelectionChanged, e, EventNamespace);
}



void Combobox::onEditboxFullEvent(WindowEventArgs& e)
{
	fireEvent(EventEditboxFull, e, EventNamespace);
}



void Combobox::onTextAcceptedEvent(WindowEventArgs& e)
{
	fireEvent(EventTextAccepted, e, EventNamespace);
}



void Combobox::onListContentsChanged(WindowEventArgs& e)
{
	fireEvent(EventListContentsChanged, e, EventNamespace);
}



void Combobox::onListSelectionChanged(WindowEventArgs& e)
{
	fireEvent(EventListSelectionChanged, e, EventNamespace);
}



void Combobox::onSortModeChanged(WindowEventArgs& e)
{
	fireEvent(EventSortModeChanged, e, EventNamespace);
}



void Combobox::onVertScrollbarModeChanged(WindowEventArgs& e)
{
	fireEvent(EventVertScrollbarModeChanged, e, EventNamespace);
}



void Combobox::onHorzScrollbarModeChanged(WindowEventArgs& e)
{
	fireEvent(EventHorzScrollbarModeChanged, e, EventNamespace);
}



void Combobox::onDropListDisplayed(WindowEventArgs& e)
{
	fireEvent(EventDropListDisplayed, e, EventNamespace);
}



void Combobox::onDroplistRemoved(WindowEventArgs& e)
{
	fireEvent(EventDropListRemoved, e, EventNamespace);
}



void Combobox::onListSelectionAccepted(WindowEventArgs& e)
{
	fireEvent(EventListSelectionAccepted, e, EventNamespace);
}



void Combobox::onFontChanged(WindowEventArgs& e)
{
    
    d_editbox->setFont(getFont());
    d_droplist->setFont(getFont());

    
    Window::onFontChanged(e);
}



void Combobox::onTextChanged(WindowEventArgs& e)
{
	
	if (d_editbox->getText() != d_text)
	{
		
		d_editbox->setText(d_text);
		e.handled = true;

		Window::onTextChanged(e);
	}

}




bool Combobox::button_PressHandler(const EventArgs& e)
{
	const MouseEventArgs& mouseEvent = (const MouseEventArgs&)e;
	if(mouseEvent.button != LeftButton) return true;

	showDropList();

	
	ListboxItem* item = d_droplist->findItemWithText(d_editbox->getText(), NULL);

	if (item != NULL)
	{
		d_droplist->setItemSelectState(item, true);
		d_droplist->ensureItemIsVisible(item);
	}
	
	else
	{
		d_droplist->clearAllSelections();
	}

	return true;
}



bool Combobox::droplist_SelectionAcceptedHandler(const EventArgs& e)
{
	
	ListboxItem* item = ((ComboDropList*)((WindowEventArgs&)e).window)->getFirstSelectedItem();

	if (item != NULL)
	{
		
		d_editbox->setText(item->getText());

		
		if (!isReadOnly())
		{
			d_editbox->setSelection(0, item->getText().length());
			d_editbox->setCaratIndex(item->getText().length());
		}

		d_editbox->setCaratIndex(0);

		
		WindowEventArgs args(this);
		onListSelectionAccepted(args);

		
		d_editbox->activate();
	}

	return true;
}



bool Combobox::droplist_HiddenHandler(const EventArgs& e)
{
	WindowEventArgs args(this);
	onDroplistRemoved(args);

	return true;
}



bool Combobox::editbox_MouseDownHandler(const EventArgs& e)
{
	
	if (((const MouseEventArgs&)e).button == LeftButton)
	{
		
		if (d_editbox->isReadOnly())
		{
			showDropList();

			
			ListboxItem* item = d_droplist->findItemWithText(d_editbox->getText(), NULL);

			if (item != NULL)
			{
				d_droplist->setItemSelectState(item, true);
				d_droplist->ensureItemIsVisible(item);
			}
			
			else
			{
				d_droplist->clearAllSelections();
			}

			return true;
		}
	}

	return false;
}



bool Combobox::isVertScrollbarAlwaysShown(void) const
{
	return d_droplist->isVertScrollbarAlwaysShown();
}



bool Combobox::isHorzScrollbarAlwaysShown(void) const
{
	return d_droplist->isHorzScrollbarAlwaysShown();
}



void Combobox::addComboboxProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( Combobox );
	   CEGUI_ADD_STATICPROPERTY( &d_sortProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_forceHorzProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_forceVertProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_readOnlyProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_validationStringProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_maxTextLengthProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_selStartProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_selLengthProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_normalTextColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_selectedTextColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_activeSelectionColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_inactiveSelectionColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_caratIndexProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_singleClickOperationProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_dropButtonAndVertScrollbarMaxWidthProperty );

	CEGUI_END_ADD_STATICPROPERTY
}



void Combobox::activateEditbox(void)
{
	if(Window::getCaptureWindow() == this->d_droplist) return;

	if (!d_editbox->isActive())
	{
		d_editbox->activate();
	}
}




void Combobox::onActivated(ActivationEventArgs& e)
{
	if (!isActive())
	{
		Window::onActivated(e);
		activateEditbox();
	}

}



bool Combobox::getSingleClickEnabled(void) const
{
	return d_singleClickOperation;
}



bool Combobox::isDropDownListVisible(void) const
{
	return d_droplist->isVisible();
}



void Combobox::setSingleClickEnabled(bool setting)
{
	d_singleClickOperation = setting;
	d_droplist->setAutoArmEnabled(setting);
}





bool Combobox::editbox_ReadOnlyChangedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onReadOnlyChanged(args);

	return true;
}


bool Combobox::editbox_ValidationStringChangedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onValidationStringChanged(args);

	return true;
}


bool Combobox::editbox_MaximumTextLengthChangedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onMaximumTextLengthChanged(args);

	return true;
}


bool Combobox::editbox_TextInvalidatedEventHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onTextInvalidatedEvent(args);

	return true;
}


bool Combobox::editbox_InvalidEntryAttemptedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onInvalidEntryAttempted(args);

	return true;
}


bool Combobox::editbox_CaratMovedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onCaratMoved(args);

	return true;
}


bool Combobox::editbox_TextSelectionChangedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onTextSelectionChanged(args);

	return true;
}


bool Combobox::editbox_EditboxFullEventHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onEditboxFullEvent(args);

	return true;
}


bool Combobox::editbox_TextAcceptedEventHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onTextAcceptedEvent(args);

	return true;
}


bool Combobox::editbox_TextChangedEventHandler(const EventArgs& e)
{
	
	setText(((const WindowEventArgs&)e).window->getText());

	return true;
}


bool Combobox::listbox_ListContentsChangedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onListContentsChanged(args);

	return true;
}


bool Combobox::listbox_ListSelectionChangedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onListSelectionChanged(args);

	return true;
}


bool Combobox::listbox_SortModeChangedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onSortModeChanged(args);

	return true;
}


bool Combobox::listbox_VertScrollModeChangedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onVertScrollbarModeChanged(args);

	return true;
}


bool Combobox::listbox_HorzScrollModeChangedHandler(const EventArgs& e)
{
	WindowEventArgs	args(this);
	onHorzScrollbarModeChanged(args);

	return true;
}

} 
