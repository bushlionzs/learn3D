

#ifndef _CEGUIMultiColumnList_h_
#define _CEGUIMultiColumnList_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "CEGUIListHeader.h"
#include "elements/CEGUIMultiColumnListProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


struct CEGUIEXPORT MCLGridRef
{
	MCLGridRef(uint r, uint c) : row(r), column(c) {}

	uint	row;		
	uint	column;		

	
	MCLGridRef& operator=(const MCLGridRef& rhs);
	bool operator<(const MCLGridRef& rhs) const;
	bool operator<=(const MCLGridRef& rhs) const;
	bool operator>(const MCLGridRef& rhs) const;
	bool operator>=(const MCLGridRef& rhs) const;
	bool operator==(const MCLGridRef& rhs) const;
	bool operator!=(const MCLGridRef& rhs) const;
};



class CEGUIEXPORT MultiColumnList : public Window
{
public:
	static const String EventNamespace;				
	

	
	
	static const String EventSelectionModeChanged;		
	static const String EventNominatedSelectColumnChanged;
	static const String EventNominatedSelectRowChanged;	
	static const String EventVertScrollbarModeChanged;	
	static const String EventHorzScrollbarModeChanged;	
	static const String EventSelectionChanged;			
	static const String EventListContentsChanged;			
	static const String EventSortColumnChanged;			
	static const String EventSortDirectionChanged;		
	static const String EventListColumnSized;				
	static const String EventListColumnMoved;				
	static const String EventItemDoubleClicked;			


	
	
	enum SelectionMode
	{
		RowSingle,					
		RowMultiple,				
		CellSingle,					
		CellMultiple,				
		NominatedColumnSingle,		
		NominatedColumnMultiple,	
		ColumnSingle,				
		ColumnMultiple,				
		NominatedRowSingle,			
		NominatedRowMultiple		
	};



	

	void postSizeChanged(void);
	void updateTotalRowsHeight();

	
	bool	isUserSortControlEnabled(void) const;


	
	bool	isUserColumnSizingEnabled(void) const;


	
	bool	isUserColumnDraggingEnabled(void) const;


	
	uint	getColumnCount(void) const;


	
	uint	getRowCount(void) const;


	
	uint	getSortColumn(void) const;

	
	
	uint	getColumnWithID(uint col_id) const;


	
	uint	getColumnWithHeaderText(const String& text) const;


	
	float	getTotalColumnHeadersWidth(void) const;


	
	float	getColumnHeaderWidth(uint col_idx) const;


	
	ListHeaderSegment::SortDirection	getSortDirection(void) const;


	
	ListHeaderSegment&	getHeaderSegmentForColumn(uint col_idx) const;


	
	uint	getItemRowIndex(const ListboxItem* item) const;


	
	uint	getItemColumnIndex(const ListboxItem* item) const;


	
	MCLGridRef	getItemGridReference(const ListboxItem* item) const;

	
	
	ListboxItem*	getItemAtGridReference(const MCLGridRef& grid_ref) const;


	
	bool	isListboxItemInColumn(const ListboxItem* item, uint col_idx) const;


	
	bool	isListboxItemInRow(const ListboxItem* item, uint row_idx) const;


	
	bool	isListboxItemInList(const ListboxItem* item) const;


	
	ListboxItem*	findColumnItemWithText(const String& text, uint col_idx, const ListboxItem* start_item) const;


	
	ListboxItem*	findRowItemWithText(const String& text, uint row_idx, const ListboxItem* start_item) const;


	
	ListboxItem*	findListItemWithText(const String& text, const ListboxItem* start_item) const;


	
	ListboxItem*	getFirstSelectedItem(void) const;


	
	ListboxItem*	getNextSelected(const ListboxItem* start_item) const;


	
	uint	getSelectedCount(void) const;


	
	bool	isItemSelected(const MCLGridRef& grid_ref) const;


	
	uint	getNominatedSelectionColumnID(void) const;


	
	uint	getNominatedSelectionColumn(void) const;


	
	uint	getNominatedSelectionRow(void) const;


	
	MultiColumnList::SelectionMode	getSelectionMode(void) const;


	
	bool	isVertScrollbarAlwaysShown(void) const;


	
	bool	isHorzScrollbarAlwaysShown(void) const;


	
	uint	getColumnID(uint col_idx) const;


	
	uint	getRowID(uint row_idx) const;


	
	uint	getRowWithID(uint row_id) const;


	
	
	virtual void	initialise(void);


	
	void	resetList(void);


	
	void	addColumn(const String& text, uint col_id, float width);

	void	addColumnSortFlag(uint sortFlag);


	
	void	insertColumn(const String& text, uint col_id, float width, uint position);


	
	void	removeColumn(uint col_idx);

	
	void removeAllContent();
	
	void	removeColumnWithID(uint col_id);


	
	void	moveColumn(uint col_idx, uint position);


	
	void	moveColumnWithID(uint col_id, uint position);


	
	uint	addRow(uint row_id = 0);


	
	uint	addRow(ListboxItem* item, uint col_id, uint row_id = 0, uint char_index = 0 );


	void	setRowIndexChar(unsigned int row_id, unsigned int char_index);

	
	uint	insertRow(uint row_idx, uint row_id = 0);


	
	uint	insertRow(ListboxItem* item, uint col_id, uint row_idx, uint row_id = 0);


	
	void	removeRow(uint row_idx);


	
	void	setItem(ListboxItem* item, const MCLGridRef& position);


	
	void	setItem(ListboxItem* item, uint col_id, uint row_idx);


	
	void	setSelectionMode(MultiColumnList::SelectionMode sel_mode);


	
	void	setNominatedSelectionColumnID(uint col_id);


	
	void	setNominatedSelectionColumn(uint col_idx);


	
	void	setNominatedSelectionRow(uint row_idx);


	
	void	setSortDirection(ListHeaderSegment::SortDirection direction);


	
	void	setSortColumn(uint col_idx);


	
	void	setSortColumnByID(uint col_id);

	
	
	void	setShowVertScrollbar(bool setting);


	
	void	setShowHorzScrollbar(bool setting);

	
	
	void	clearAllSelections(void);


	
	void	setItemSelectState(ListboxItem* item, bool state);


	
	void	setItemSelectState(const MCLGridRef& grid_ref, bool state);

	
	
	void	handleUpdatedItemData(void);


	
	void	setColumnHeaderWidth(uint col_idx, float width);


	
	void	setUserSortControlEnabled(bool setting);


	
	void	setUserColumnSizingEnabled(bool setting);


	
	void	setUserColumnDraggingEnabled(bool setting);


	
	void	autoSizeColumnHeader(uint col_idx);


	
	void	setRowID(uint row_idx, uint row_id);

	void	setShowHeader(bool bnoheader);

	bool injectIndexChar(uint index);

	
	
	MultiColumnList(const String& type, const String& name);


	
	virtual ~MultiColumnList(void);


protected:
	
	
	virtual	Rect	getListRenderArea(void) const		= 0;


	
	virtual ListHeader*	createListHeader(const String& name) const		= 0;
 

	
	virtual Scrollbar*	createVertScrollbar(const String& name) const		= 0;
 

	
	virtual Scrollbar*	createHorzScrollbar(const String& name) const		= 0;


	
	virtual	void	cacheListboxBaseImagery()		= 0;


	

    
	virtual	void populateRenderCache();


	
	void	configureScrollbars(void);


	
	bool	selectRange(const MCLGridRef& start, const MCLGridRef& end);


	
	float	getTotalRowsHeight(void) const;


	
	float	getWidestColumnItemWidth(uint col_idx) const;


	
	float	getHighestRowItemHeight(uint row_idx) const;


	
	bool	clearAllSelections_impl(void);


	
	ListboxItem*	getItemAtPoint(const Point& pt) const;


	
	bool	setItemSelectState_impl(const MCLGridRef grid_ref, bool state);


	
	void	setSelectForItemsInRow(uint row_idx, bool state);


	
	void	setSelectForItemsInColumn(uint col_idx, bool state);


	
	void	moveColumn_impl(uint col_idx, uint position);


	
	bool	resetList_impl(void);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"MultiColumnList")	return true;
		return Window::testClassName_impl(class_name);
	}

    
    int writePropertiesXML(OutStream& out_stream) const;

	
	
	virtual	void	onSelectionModeChanged(WindowEventArgs& e);


	
	virtual	void	onNominatedSelectColumnChanged(WindowEventArgs& e);


	
	virtual	void	onNominatedSelectRowChanged(WindowEventArgs& e);


	
	virtual	void	onVertScrollbarModeChanged(WindowEventArgs& e);


	
	virtual	void	onHorzScrollbarModeChanged(WindowEventArgs& e);


	
	virtual	void	onSelectionChanged(WindowEventArgs& e);

	virtual	void	onItemDoubleClicked(WindowEventArgs& e);

	
	virtual	void	onListContentsChanged(WindowEventArgs& e);


	
	virtual	void	onSortColumnChanged(WindowEventArgs& e);


	
	virtual	void	onSortDirectionChanged(WindowEventArgs& e);


	
	virtual	void	onListColumnSized(WindowEventArgs& e);


	
	virtual	void	onListColumnMoved(WindowEventArgs& e);


	
	virtual void	onSized(WindowEventArgs& e);
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual	void	onMouseWheel(MouseEventArgs& e);
	virtual void	onMouseDoubleClicked(MouseEventArgs& e);

	
	bool	handleHeaderScroll(const EventArgs& e);
	bool	handleHeaderSegMove(const EventArgs& e);
	bool	handleColumnSizeChange(const EventArgs& e);
	bool	handleHorzScrollbar(const EventArgs& e);
	bool	handleVertScrollbar(const EventArgs& e);
	bool	handleSortColumnChange(const EventArgs& e);
	bool	handleSortDirectionChange(const EventArgs& e);
	bool	handleHeaderSegDblClick(const EventArgs& e);

    
	struct ListRow
	{
		typedef	std::vector<ListboxItem*>	RowItems;
		RowItems	d_items;
		uint		d_sortColumn;
		uint		d_rowID;
		uint		d_indexChar;
		uint     d_maxHeight; 
		std::vector<uint>	d_isIntSort;

		
		ListboxItem* const& operator[](uint idx) const	{return d_items[idx];}
		ListboxItem*&	operator[](uint idx) {return d_items[idx];}
		bool	operator<(const ListRow& rhs) const;
		bool	operator>(const ListRow& rhs) const;
	};


	
	static bool pred_descend(const ListRow& a, const ListRow& b);


	
	
	Scrollbar*	d_vertScrollbar;	
	Scrollbar*	d_horzScrollbar;	
	ListHeader*	d_header;			
	bool	d_showheader;			
	bool	d_forceVertScroll;		
	bool	d_forceHorzScroll;		

	
	SelectionMode	d_selectMode;	
	uint	d_nominatedSelectCol;	
	uint	d_nominatedSelectRow;	
	bool	d_multiSelect;			
	bool	d_fullRowSelect;		
	bool	d_fullColSelect;		
	bool	d_useNominatedRow;		
	bool	d_useNominatedCol;		
	ListboxItem*	d_lastSelected;	

	
	typedef std::vector<ListRow>		ListItemGrid;
	ListItemGrid	d_grid;			

	std::vector<uint>			d_isIntSort;
	float d_totalHeight; 

private:
	
	static MultiColumnListProperties::ColumnsMovable				d_columnsMovableProperty;
	static MultiColumnListProperties::ColumnsSizable				d_columnsSizableProperty;
	static MultiColumnListProperties::ForceHorzScrollbar			d_forceHorzScrollProperty;
	static MultiColumnListProperties::ForceVertScrollbar			d_forceVertScrollProperty;
	static MultiColumnListProperties::NominatedSelectionColumnID	d_nominatedSelectColProperty;
	static MultiColumnListProperties::NominatedSelectionRow			d_nominatedSelectRowProperty;
	static MultiColumnListProperties::SelectionMode					d_selectModeProperty;
	static MultiColumnListProperties::SortColumnID					d_sortColumnIDProperty;
	static MultiColumnListProperties::SortDirection					d_sortDirectionProperty;
	static MultiColumnListProperties::SortSettingEnabled			d_sortSettingProperty;
	static MultiColumnListProperties::ColumnHeader					d_columnHeaderProperty;
	static MultiColumnListProperties::RowCount						d_rowCountProperty;
	static MultiColumnListProperties::NoHeader						d_noHeaderProperty;

	
	void	addMultiColumnListProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
