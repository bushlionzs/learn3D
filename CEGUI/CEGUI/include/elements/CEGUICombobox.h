

#ifndef _CEGUICombobox_h_
#define _CEGUICombobox_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIComboboxProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT Combobox : public Window
{
public:
	static const String EventNamespace;				

	
	
	static const String EventReadOnlyModeChanged;			
	static const String EventValidationStringChanged;		
	static const String EventMaximumTextLengthChanged;	
	static const String EventTextInvalidated;				
	static const String EventInvalidEntryAttempted;		
	static const String EventCaratMoved;					
	static const String EventTextSelectionChanged;		
	static const String EventEditboxFull;					
	static const String EventTextAccepted;				

	
	static const String EventListContentsChanged;			
	static const String EventListSelectionChanged;		
	static const String EventSortModeChanged;				
	static const String EventVertScrollbarModeChanged;	
	static const String EventHorzScrollbarModeChanged;	

	
	static const String EventDropListDisplayed;			
	static const String EventDropListRemoved;				
	static const String EventListSelectionAccepted;		

	void setComboboxScrollbarMaxWidth(int maxWidth);

	
	virtual bool	isHit(const Point& position) const		{return false;}


	
	bool	getSingleClickEnabled(void) const;


	
	bool	isDropDownListVisible(void) const;


	
	
	bool	hasInputFocus(void) const;


	
	bool	isReadOnly(void) const;


	
	bool	isTextValid(void) const;


	
	const String&	getValidationString(void) const;


	
	size_t	getCaratIndex(void) const;


	
	size_t	getSelectionStartIndex(void) const;


	
	size_t	getSelectionEndIndex(void) const;

	
	
	size_t	getSelectionLength(void) const;


	
	size_t	getMaxTextLength(void) const;


	
	colour	getNormalTextColour(void) const;


	
	colour	getSelectedTextColour(void) const;


	
	colour	getNormalSelectBrushColour(void) const;


	
	colour	getInactiveSelectBrushColour(void) const;


	
	
	size_t	getItemCount(void) const;

	
	
	ListboxItem*	getSelectedItem(void) const;


	
	ListboxItem*	getListboxItemFromIndex(size_t index) const;


	
	size_t	getItemIndex(const ListboxItem* item) const;


	
	bool	isSortEnabled(void) const;


	
	bool	isItemSelected(size_t index) const;


	
	ListboxItem*	findItemWithText(const String& text, const ListboxItem* start_item);


	
	bool	isListboxItemInList(const ListboxItem* item) const;


	
	bool	isVertScrollbarAlwaysShown(void) const;


	
	bool	isHorzScrollbarAlwaysShown(void) const;


	
	
	virtual void	initialise(void);


	
	void	showDropList(void);


	
	void	hideDropList(void);


	
	void	setSingleClickEnabled(bool setting);


	
	
	void	setReadOnly(bool setting);


	
	void	setValidationString(const String& validation_string);


	
	void	setCaratIndex(size_t carat_pos);


	
	void	setSelection(size_t start_pos, size_t end_pos);
	

	
	void	setMaxTextLength(size_t max_len);


	
	void	setNormalTextColour(colour col);


	
	void	setSelectedTextColour(colour col);


	
	void	setNormalSelectBrushColour(colour col);


	
	void	setInactiveSelectBrushColour(colour col);


	
	void	activateEditbox(void);


	
	
	void	resetList(void);


	
	void	addItem(ListboxItem* item);


	
	void	insertItem(ListboxItem* item, const ListboxItem* position);


	
	void	removeItem(const ListboxItem* item);


	
	void	clearAllSelections(void);


	
	void	setSortingEnabled(bool setting);

	
	
	void	setShowVertScrollbar(bool setting);


	
	void	setShowHorzScrollbar(bool setting);


	
	void	setItemSelectState(ListboxItem* item, bool state);


	
	void	setItemSelectState(size_t item_index, bool state);


	
	void	handleUpdatedListItemData(void);


	
	
	Combobox(const String& type, const String& name);


	
	virtual ~Combobox(void);


protected:
	

	
	virtual	Editbox*	createEditbox(const String& name) const		= 0;


	
	virtual	PushButton*	createPushButton(const String& name) const	= 0;


	
	virtual	ComboDropList*	createDropList(const String& name) const	= 0;


	
	bool	button_PressHandler(const EventArgs& e);


	
	bool	droplist_SelectionAcceptedHandler(const EventArgs& e);


	
	bool	droplist_HiddenHandler(const EventArgs& e);


	
	bool	editbox_MouseDownHandler(const EventArgs& e);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Combobox")	return true;
		return Window::testClassName_impl(class_name);
	}


	
	bool editbox_ReadOnlyChangedHandler(const EventArgs& e);
	bool editbox_ValidationStringChangedHandler(const EventArgs& e);
	bool editbox_MaximumTextLengthChangedHandler(const EventArgs& e);
	bool editbox_TextInvalidatedEventHandler(const EventArgs& e);
	bool editbox_InvalidEntryAttemptedHandler(const EventArgs& e);
	bool editbox_CaratMovedHandler(const EventArgs& e);
	bool editbox_TextSelectionChangedHandler(const EventArgs& e);
	bool editbox_EditboxFullEventHandler(const EventArgs& e);
	bool editbox_TextAcceptedEventHandler(const EventArgs& e);
	bool editbox_TextChangedEventHandler(const EventArgs& e);
	bool listbox_ListContentsChangedHandler(const EventArgs& e);
	bool listbox_ListSelectionChangedHandler(const EventArgs& e);
	bool listbox_SortModeChangedHandler(const EventArgs& e);
	bool listbox_VertScrollModeChangedHandler(const EventArgs& e);
	bool listbox_HorzScrollModeChangedHandler(const EventArgs& e);

	
	bool	MouseEnters( const EventArgs& e);
	bool	MouseLeaves( const EventArgs& e);
	
	
	virtual	void	onReadOnlyChanged(WindowEventArgs& e);


	
	virtual	void	onValidationStringChanged(WindowEventArgs& e);


	
	virtual	void	onMaximumTextLengthChanged(WindowEventArgs& e);


	
	virtual	void	onTextInvalidatedEvent(WindowEventArgs& e);


	
	virtual	void	onInvalidEntryAttempted(WindowEventArgs& e);


	
	virtual	void	onCaratMoved(WindowEventArgs& e);


	
	virtual	void	onTextSelectionChanged(WindowEventArgs& e);


	
	virtual	void	onEditboxFullEvent(WindowEventArgs& e);


	
	virtual	void	onTextAcceptedEvent(WindowEventArgs& e);


	
	virtual	void	onListContentsChanged(WindowEventArgs& e);


	
	virtual	void	onListSelectionChanged(WindowEventArgs& e);


	
	virtual	void	onSortModeChanged(WindowEventArgs& e);


	
	virtual	void	onVertScrollbarModeChanged(WindowEventArgs& e);


	
	virtual	void	onHorzScrollbarModeChanged(WindowEventArgs& e);


	
	virtual	void	onDropListDisplayed(WindowEventArgs& e);


	
	virtual	void	onDroplistRemoved(WindowEventArgs& e);


	
	virtual	void	onListSelectionAccepted(WindowEventArgs& e);


	virtual void    onSized(WindowEventArgs& e);


	
	virtual	void	onFontChanged(WindowEventArgs& e);
	virtual void	onTextChanged(WindowEventArgs& e);
	virtual void	onActivated(ActivationEventArgs& e);


	
	Editbox*		d_editbox;		
	ComboDropList*	d_droplist;		
	PushButton*		d_button;		
	bool			d_singleClickOperation;		
	
	bool            d_bUseComboboxScrollbarMaxWidth;
	int			    d_comboboxScrollbarMaxWidth;
	
private:
	
	static ComboboxProperties::ReadOnly						d_readOnlyProperty;
	static ComboboxProperties::ValidationString				d_validationStringProperty;
	static ComboboxProperties::CaratIndex					d_caratIndexProperty;
	static ComboboxProperties::EditSelectionStart			d_selStartProperty;
	static ComboboxProperties::EditSelectionLength			d_selLengthProperty;
	static ComboboxProperties::MaxEditTextLength			d_maxTextLengthProperty;
	static ComboboxProperties::NormalEditTextColour			d_normalTextColourProperty;
	static ComboboxProperties::SelectedEditTextColour		d_selectedTextColourProperty;
	static ComboboxProperties::ActiveEditSelectionColour	d_activeSelectionColourProperty;
	static ComboboxProperties::InactiveEditSelectionColour	d_inactiveSelectionColourProperty;
	static ComboboxProperties::SortList						d_sortProperty;
	static ComboboxProperties::ForceVertScrollbar			d_forceVertProperty;
	static ComboboxProperties::ForceHorzScrollbar			d_forceHorzProperty;
	static ComboboxProperties::SingleClickMode				d_singleClickOperationProperty;

	static ComboboxProperties::DropButtonAndVertScrollbarMaxWidth  d_dropButtonAndVertScrollbarMaxWidthProperty;

	
	void	addComboboxProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
