

#ifndef _CEGUIListbox_h_
#define _CEGUIListbox_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIListboxProperties.h"
#include <vector>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT Listbox : public Window
{
public:
	static const String EventNamespace;				


	
	
	static const String EventListContentsChanged;			
	static const String EventSelectionChanged;			
	static const String EventSortModeChanged;				
	static const String EventMultiselectModeChanged;		
	static const String EventVertScrollbarModeChanged;	
	static const String EventHorzScrollbarModeChanged;	
	static const String EventMouseMoveItemChanged;	


	
	
	size_t	getItemCount(void) const		{return d_listItems.size();}

	
	
	size_t	getSelectedCount(void) const;


	
	ListboxItem*	getFirstSelectedItem(void) const;


	ListboxItem*	getMouseMoveSelectedItem(void) const;

	size_t	getMouseMoveSelectedItemIndex(void) const;



	
	ListboxItem*	getNextSelected(const ListboxItem* start_item) const;


	
	ListboxItem*	getListboxItemFromIndex(size_t index) const;


	
	size_t	getItemIndex(const ListboxItem* item) const;

	
	size_t	getRefIndex() const { return d_refIndex; }

	
	bool	isSortEnabled(void) const		{return d_sorted;}

	
	bool	isMultiselectEnabled(void) const	{return d_multiselect;}

	bool	isItemTooltipsEnabled(void) const	{return d_itemTooltips;}

	
	bool	isItemSelected(size_t index) const;


	
	ListboxItem*	findItemWithText(const String& text, const ListboxItem* start_item);


	
	bool	isListboxItemInList(const ListboxItem* item) const;

	
	

	
	bool	isVertScrollbarAlwaysShown(void) const;


	
	bool	isHorzScrollbarAlwaysShown(void) const;


	
	
	virtual void	initialise(void);


	
	void	resetList(void);


	
	void	addItem(ListboxItem* item);


	
	void	insertItem(ListboxItem* item, const ListboxItem* position);


	
	void	removeItem(const ListboxItem* item);


	
	void	clearAllSelections(void);


	
	void	setSortingEnabled(bool setting);

	
	
	void	setMultiselectEnabled(bool setting);


	
	void	setShowVertScrollbar(bool setting);


	
	void	setShowHorzScrollbar(bool setting);

	void	setItemTooltipsEnabled(bool setting);
	
	void	setItemSelectState(ListboxItem* item, bool state);
	
	
	void	setItemSelectStateByItemID(uint itemid, bool state);

	
	void	setItemSelectState(size_t item_index, bool state);

	
	void	setRefIndex(size_t refIndex) { d_refIndex = refIndex; }
	
	void	handleUpdatedItemData(void);


	
	void	ensureItemIsVisible(size_t item_index);


	
	void	ensureItemIsVisible(const ListboxItem* item);


	
	
	Listbox(const String& type, const String& name);


	
	virtual ~Listbox(void);


	
	
	virtual	Rect	getListRenderArea(void) const		= 0;

	void setSelectionColur(colour c);

	Scrollbar* getVertScrollbar(){ return d_vertScrollbar; }
	Scrollbar* getHorzScrollbar(){ return d_horzScrollbar; }

protected:

	
	virtual Scrollbar*	createVertScrollbar(const String& name) const		= 0;
 

	
	virtual Scrollbar*	createHorzScrollbar(const String& name) const		= 0;


	
	virtual	void cacheListboxBaseImagery() = 0;


	

	
	void	configureScrollbars(void);

	
	void	selectRange(size_t start, size_t end);


	
	float	getTotalItemsHeight(void) const;

	
	float	getItemHeight(void) const;

	
	float	getWidestItemWidth(void) const;


	
	bool	clearAllSelections_impl(void);


	
	ListboxItem*	getItemAtPoint(const Point& pt) const;


	
	bool	resetList_impl(void);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Listbox")	return true;
		return Window::testClassName_impl(class_name);
	}

	
    bool handle_scrollChange(const EventArgs& args);

    
    void populateRenderCache();


	
	
	virtual	void	onListContentsChanged(WindowEventArgs& e);


	
	virtual	void	onSelectionChanged(WindowEventArgs& e);


	
	virtual	void	onSortModeChanged(WindowEventArgs& e);


	
	virtual	void	onMultiselectModeChanged(WindowEventArgs& e);


	
	virtual	void	onVertScrollbarModeChanged(WindowEventArgs& e);


	
	virtual	void	onHorzScrollbarModeChanged(WindowEventArgs& e);


	
	virtual void	onSized(WindowEventArgs& e);
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual	void	onMouseWheel(MouseEventArgs& e);
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onMouseLeaves(MouseEventArgs& e);
	
	
	virtual void	onCharacter(KeyEventArgs& e);

	
	typedef	std::vector<ListboxItem*>	LBItemList;
	bool		d_sorted;				
	bool		d_multiselect;			
	bool		d_forceVertScroll;		
	bool		d_forceHorzScroll;		
	bool		d_itemTooltips;			
	Scrollbar*	d_vertScrollbar;	
	Scrollbar*	d_horzScrollbar;	
	LBItemList	d_listItems;		
	ListboxItem*	d_lastSelected;	
	ListboxItem*	d_MouseMoveSel;	

	
	size_t		d_curIndex;	
	size_t		d_refIndex;	
	colour d_selectionColour;
private:
	
	static ListboxProperties::Sort					d_sortProperty;
	static ListboxProperties::MultiSelect			d_multiSelectProperty;
	static ListboxProperties::ForceVertScrollbar	d_forceVertProperty;
	static ListboxProperties::ForceHorzScrollbar	d_forceHorzProperty;
	static ListboxProperties::ItemTooltips			d_itemTooltipsProperty;
	static ListboxProperties::SelectionColour			d_SelectionColourProperty;

	
	void	addListboxProperties(void);
};



bool lbi_less(const ListboxItem* a, const ListboxItem* b);



bool lbi_greater(const ListboxItem* a, const ListboxItem* b);

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
