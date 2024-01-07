

#include "elements/CEGUIMultiColumnList.h"
#include "CEGUIExceptions.h"
#include "elements/CEGUIScrollbar.h"
#include "elements/CEGUIListHeader.h"
#include "elements/CEGUIListboxItem.h"
#include "CEGUILogger.h"
#include "CEGUIPropertyHelper.h"
#include <algorithm>

#include "CEGUIWindowManager.h"

namespace CEGUI
{

#define OPTIMIZE_MULTILIST 1

const String MultiColumnList::EventNamespace("MultiColumnList");


MultiColumnListProperties::ColumnsMovable				MultiColumnList::d_columnsMovableProperty;
MultiColumnListProperties::ColumnsSizable				MultiColumnList::d_columnsSizableProperty;
MultiColumnListProperties::ForceHorzScrollbar			MultiColumnList::d_forceHorzScrollProperty;
MultiColumnListProperties::ForceVertScrollbar			MultiColumnList::d_forceVertScrollProperty;
MultiColumnListProperties::NominatedSelectionColumnID	MultiColumnList::d_nominatedSelectColProperty;
MultiColumnListProperties::NominatedSelectionRow		MultiColumnList::d_nominatedSelectRowProperty;
MultiColumnListProperties::SelectionMode				MultiColumnList::d_selectModeProperty;
MultiColumnListProperties::SortColumnID					MultiColumnList::d_sortColumnIDProperty;
MultiColumnListProperties::SortDirection				MultiColumnList::d_sortDirectionProperty;
MultiColumnListProperties::SortSettingEnabled			MultiColumnList::d_sortSettingProperty;
MultiColumnListProperties::ColumnHeader					MultiColumnList::d_columnHeaderProperty;
MultiColumnListProperties::RowCount						MultiColumnList::d_rowCountProperty;
MultiColumnListProperties::NoHeader						MultiColumnList::d_noHeaderProperty;



const String MultiColumnList::EventSelectionModeChanged( (utf8*)"SelectModeChanged" );
const String MultiColumnList::EventNominatedSelectColumnChanged( (utf8*)"NomSelColChanged" );
const String MultiColumnList::EventNominatedSelectRowChanged( (utf8*)"NomSelRowChanged" );
const String MultiColumnList::EventVertScrollbarModeChanged( (utf8*)"VertBarModeChanged" );
const String MultiColumnList::EventHorzScrollbarModeChanged( (utf8*)"HorzBarModeChanged" );
const String MultiColumnList::EventSelectionChanged( (utf8*)"SelectionChanged" );
const String MultiColumnList::EventListContentsChanged( (utf8*)"ContentsChanged" );
const String MultiColumnList::EventSortColumnChanged( (utf8*)"SortColChanged" );
const String MultiColumnList::EventSortDirectionChanged( (utf8*)"SortDirChanged" );
const String MultiColumnList::EventListColumnSized( (utf8*)"ColSized" );
const String MultiColumnList::EventListColumnMoved( (utf8*)"ColMoved" );
const String MultiColumnList::EventItemDoubleClicked( (utf8*)"ItemDoubleClicked" );

	

MultiColumnList::MultiColumnList(const String& type, const String& name) :
	Window(type, name),
	d_forceVertScroll(false),
	d_forceHorzScroll(false),
	d_nominatedSelectCol(0),
	d_nominatedSelectRow(0),
	d_lastSelected(NULL),
	d_showheader(true)
{
	
	addMultiColumnListProperties();

	
	d_selectMode = CellSingle;		
	setSelectionMode(RowSingle);

	d_horzScrollbar = NULL;
	d_header = NULL;
	d_vertScrollbar = NULL;

#if OPTIMIZE_MULTILIST
	
	d_totalHeight = 0.f;
#endif
}



MultiColumnList::~MultiColumnList(void)
{
	
	resetList_impl();
}



bool MultiColumnList::isUserSortControlEnabled(void) const
{
	return d_header->isSortingEnabled();
}



bool MultiColumnList::isUserColumnSizingEnabled(void) const
{
	return d_header->isColumnSizingEnabled();
}



bool MultiColumnList::isUserColumnDraggingEnabled(void) const
{
	return d_header->isColumnDraggingEnabled();
}



uint MultiColumnList::getColumnCount(void) const
{
	return d_header->getColumnCount();
}



uint MultiColumnList::getRowCount(void) const
{
	return (uint)d_grid.size();
}



uint MultiColumnList::getSortColumn(void) const
{
	return d_header->getSortColumn();
}



uint MultiColumnList::getColumnWithID(uint col_id) const
{
	return d_header->getColumnFromID(col_id);
}



uint MultiColumnList::getColumnWithHeaderText(const String& text) const
{
	return d_header->getColumnWithText(text);
}



float MultiColumnList::getTotalColumnHeadersWidth(void) const
{
	float width = d_header->getTotalSegmentsPixelExtent();

	if (getMetricsMode() == Relative)
	{
		width = absoluteToRelativeX(width);
	}

	return width;
}



float MultiColumnList::getColumnHeaderWidth(uint col_idx) const
{
	float width = d_header->getColumnPixelWidth(col_idx);

	if (getMetricsMode() == Relative)
	{
		width = absoluteToRelativeX(width);
	}

	return width;
}



ListHeaderSegment::SortDirection MultiColumnList::getSortDirection(void) const
{
	return d_header->getSortDirection();
}



ListHeaderSegment& MultiColumnList::getHeaderSegmentForColumn(uint col_idx) const
{
	return d_header->getSegmentFromColumn(col_idx);
}



uint MultiColumnList::getItemRowIndex(const ListboxItem* item) const
{
	for (uint i = 0; i < getRowCount(); ++i)
	{
		if (isListboxItemInRow(item, i))
		{
			return i;
		}

	}

	
	throw InvalidRequestException((utf8*)"MultiColumnList::getItemRowIndex - the given ListboxItem is not attached to this MultiColumnList.");
}



uint MultiColumnList::getItemColumnIndex(const ListboxItem* item) const
{
	for (uint i = 0; i < getColumnCount(); ++i)
	{
		if (isListboxItemInColumn(item, i))
		{
			return i;
		}

	}

	
	throw InvalidRequestException((utf8*)"MultiColumnList::getItemColumnIndex - the given ListboxItem is not attached to this MultiColumnList.");
}



MCLGridRef MultiColumnList::getItemGridReference(const ListboxItem* item) const
{
	return MCLGridRef(getItemRowIndex(item), getItemColumnIndex(item));
}



ListboxItem* MultiColumnList::getItemAtGridReference(const MCLGridRef& grid_ref) const
{
	
	if (grid_ref.column >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::getItemAtGridReference - the column given in the grid reference is out of range.");
	}
	else if (grid_ref.row >= getRowCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::getItemAtGridReference - the row given in the grid reference is out of range.");
	}
	else
	{
		return d_grid[grid_ref.row][grid_ref.column];
	}

}



bool MultiColumnList::isListboxItemInColumn(const ListboxItem* item, uint col_idx) const
{
	
	if (col_idx >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::isListboxItemInColumn - the column index given is out of range.");
	}
	else
	{
		for (uint i = 0; i < getRowCount(); ++i)
		{
			if (d_grid[i][col_idx] == item)
			{
				return true;
			}

		}

		
		return false;
	}

}



bool MultiColumnList::isListboxItemInRow(const ListboxItem* item, uint row_idx) const
{
	
	if (row_idx >= getRowCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::isListboxItemInRow - the row index given is out of range.");
	}
	else
	{
		for (uint i = 0; i < getColumnCount(); ++i)
		{
			if (d_grid[row_idx][i] == item)
			{
				return true;
			}

		}

		
		return false;
	}

}



bool MultiColumnList::isListboxItemInList(const ListboxItem* item) const
{
	for (uint i = 0; i < getRowCount(); ++i)
	{
		for (uint j = 0; j < getColumnCount(); ++j)
		{
			if (d_grid[i][j] == item)
			{
				return true;
			}

		}

	}

	return false;
}



ListboxItem* MultiColumnList::findColumnItemWithText(const String& text, uint col_idx, const ListboxItem* start_item) const
{
	
	if (col_idx >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::findColumnItemWithText - specified column index is out of range.");
	}

	
	uint i = (start_item == NULL) ? 0 : getItemRowIndex(start_item) + 1;

	for ( ; i < getRowCount(); ++i)
	{
		
		if (d_grid[i][col_idx]->getText() == text)
		{
			return d_grid[i][col_idx];
		}

	}

	
	return NULL;
}



ListboxItem* MultiColumnList::findRowItemWithText(const String& text, uint row_idx, const ListboxItem* start_item) const
{
	
	if (row_idx >= getRowCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::findRowItemWithText - specified row index is out of range.");
	}

	
	uint i = (start_item == NULL) ? 0 : getItemColumnIndex(start_item) + 1;

	for ( ; i < getColumnCount(); ++i)
	{
		
		if (d_grid[row_idx][i]->getText() == text)
		{
			return d_grid[row_idx][i];
		}

	}

	
	return NULL;
}



ListboxItem* MultiColumnList::findListItemWithText(const String& text, const ListboxItem* start_item) const
{
	MCLGridRef startRef(0, 0);
	
	
	if (start_item != NULL)
	{
		startRef = getItemGridReference(start_item);
		++startRef.column;
	}

	
	for (uint i = startRef.row; i < getRowCount(); ++i)
	{
		for (uint j = startRef.column; j < getColumnCount(); ++j)
		{
			
			if (d_grid[i][j]->getText() == text)
			{
				return d_grid[i][j];
			}

		}

	}

	
	return NULL;
}



ListboxItem* MultiColumnList::getFirstSelectedItem(void) const
{
	return getNextSelected(NULL);
}



ListboxItem* MultiColumnList::getNextSelected(const ListboxItem* start_item) const
{
	MCLGridRef startRef(0, 0);

	
	if (start_item != NULL)
	{
		startRef = getItemGridReference(start_item);
		++startRef.column;
	}

	
	for (uint i = startRef.row; i < getRowCount(); ++i)
	{
		for (uint j = startRef.column; j < getColumnCount(); ++j)
		{
			
			ListboxItem* item = d_grid[i][j];

			if ((item != NULL) && item->isSelected())
			{
				d_grid[i][j]->setID(i);
				return d_grid[i][j];
			}

		}

	}

	
	return NULL;
}



uint MultiColumnList::getSelectedCount(void) const
{
	uint count = 0;

	for (uint i = 0; i < getRowCount(); ++i)
	{
		for (uint j = 0; j < getColumnCount(); ++j)
		{
			ListboxItem* item = d_grid[i][j];

			if ((item != NULL) && item->isSelected())
			{
				++count;
			}

		}

	}

	return count;
}



bool MultiColumnList::isItemSelected(const MCLGridRef& grid_ref) const
{
	ListboxItem* item = getItemAtGridReference(grid_ref);

	if (item != NULL)
	{
		return item->isSelected();
	}

	
	return false;
}



uint MultiColumnList::getNominatedSelectionColumnID(void) const
{
	return d_header->getSegmentFromColumn(d_nominatedSelectCol).getID();
}



uint MultiColumnList::getNominatedSelectionColumn(void) const
{
	return d_nominatedSelectCol;
}



uint MultiColumnList::getNominatedSelectionRow(void) const
{
	return d_nominatedSelectRow;
}



MultiColumnList::SelectionMode MultiColumnList::getSelectionMode(void) const
{
	return d_selectMode;
}



void MultiColumnList::initialise(void)
{
	
	if( WindowManager::getSingleton().isWindowPresent( getName() + "__auto_vscrollbar__") )
	{
		d_vertScrollbar = createVertScrollbar(getName() + "__auto_vscrollbar__");
		addChildWindow(d_vertScrollbar);
		d_vertScrollbar->subscribeEvent(Scrollbar::EventScrollPositionChanged, Event::Subscriber(&CEGUI::MultiColumnList::handleVertScrollbar, this));
	}
	if( WindowManager::getSingleton().isWindowPresent( getName() + "__auto_hscrollbar__") )
	{
		d_horzScrollbar = createHorzScrollbar(getName() + "__auto_hscrollbar__");
		addChildWindow(d_vertScrollbar);
		d_horzScrollbar->subscribeEvent(Scrollbar::EventScrollPositionChanged, Event::Subscriber(&CEGUI::MultiColumnList::handleHorzScrollbar, this));
	}
	d_header		= createListHeader(getName() + "__auto_listheader__");

	
	
	addChildWindow(d_header);

	
	d_header->subscribeEvent(ListHeader::EventSegmentRenderOffsetChanged, Event::Subscriber(&CEGUI::MultiColumnList::handleHeaderScroll, this));
	d_header->subscribeEvent(ListHeader::EventSegmentSequenceChanged, Event::Subscriber(&CEGUI::MultiColumnList::handleHeaderSegMove, this));
	d_header->subscribeEvent(ListHeader::EventSegmentSized, Event::Subscriber(&CEGUI::MultiColumnList::handleColumnSizeChange, this));
	d_header->subscribeEvent(ListHeader::EventSortColumnChanged , Event::Subscriber(&CEGUI::MultiColumnList::handleSortColumnChange, this));
	d_header->subscribeEvent(ListHeader::EventSortDirectionChanged, Event::Subscriber(&CEGUI::MultiColumnList::handleSortDirectionChange, this));
	d_header->subscribeEvent(ListHeader::EventSplitterDoubleClicked, Event::Subscriber(&CEGUI::MultiColumnList::handleHeaderSegDblClick, this));
	 


	
	setSortDirection(ListHeaderSegment::None);

	
	configureScrollbars();
	performChildWindowLayout();
}



void MultiColumnList::resetList(void)
{
	if (resetList_impl())
	{
		WindowEventArgs args(this);
		onListContentsChanged(args);
	}

}



void MultiColumnList::addColumn(const String& text, uint col_id, float width)
{
	insertColumn(text, col_id, width, getColumnCount());
}

void MultiColumnList::addColumnSortFlag( uint sortFlag )
{
	d_isIntSort.push_back(sortFlag);
}



void MultiColumnList::insertColumn(const String& text, uint col_id, float width, uint position)
{
	
	if (position > getColumnCount())
	{
		position = getColumnCount();
	}

	
	if (getMetricsMode() == Relative)
	{
		width = relativeToAbsoluteX(width);
	}

	
	d_header->insertColumn(text, col_id, d_header->absoluteToRelativeX(width), position);

	
	for (uint i = 0; i < getRowCount(); ++i)
	{
		d_grid[i].d_items.insert(d_grid[i].d_items.begin() + position, NULL);
	}

	
	if ((d_nominatedSelectCol >= position) && (getColumnCount() > 1))
	{
		d_nominatedSelectCol++;
	}

	
	WindowEventArgs args(this);
	onListContentsChanged(args);
}

void MultiColumnList::removeAllContent()
{
	uint select = 0;
	while(getColumnCount())
	{
		removeColumn(select);
	}
}

void MultiColumnList::removeColumn(uint col_idx)
{
	
	if (col_idx >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::removeColumn - the specified column index is out of range.");
	}
	else
	{
		
		if (d_nominatedSelectCol == col_idx)
		{
			d_nominatedSelectCol = 0;
		}

		
		for (uint i = 0; i < getRowCount(); ++i)
		{
			
			ListboxItem* item = d_grid[i][col_idx];

			
			d_grid[i].d_items.erase(d_grid[i].d_items.begin() + col_idx);

			
			if ((item != NULL) && item->isAutoDeleted())
			{
				delete item;
			}

		}

		
		d_header->removeColumn(col_idx);

		
		WindowEventArgs args(this);
		onListContentsChanged(args);
	}

}



void MultiColumnList::removeColumnWithID(uint col_id)
{
	removeColumn(getColumnWithID(col_id));
}



void MultiColumnList::moveColumn(uint col_idx, uint position)
{
	
	d_header->moveColumn(col_idx, position);
}



void MultiColumnList::moveColumnWithID(uint col_id, uint position)
{
	moveColumn(getColumnWithID(col_id), position);
}



uint MultiColumnList::addRow(uint row_id)
{
	return addRow(NULL, 0, row_id);
}



uint MultiColumnList::addRow(ListboxItem* item, uint col_id, uint row_id, uint char_index)
{
	uint col_idx = 0;

	
	ListRow row;
	row.d_sortColumn = getSortColumn();
	row.d_items.resize(getColumnCount(), NULL);
	row.d_rowID = row_id;
	row.d_indexChar = char_index;
	row.d_isIntSort = d_isIntSort;

#if OPTIMIZE_MULTILIST
	
	row.d_maxHeight = 0;
#endif

	if (item != NULL)
	{
		
		col_idx = getColumnWithID(col_id);

		
		item->setOwnerWindow(this);
		row[col_idx] = item;
	}

	uint pos;
	uint curRowHeight = 0;

	
	if (getSortDirection() != ListHeaderSegment::None)
	{
        
        ListItemGrid::iterator ins_pos = std::upper_bound(d_grid.begin(), d_grid.end(), row);
        
        ListItemGrid::iterator final_pos = d_grid.insert(ins_pos, row);
		
		pos = (uint)std::distance(d_grid.begin(), final_pos);
#if OPTIMIZE_MULTILIST
		
		final_pos->d_maxHeight = curRowHeight = getHighestRowItemHeight(pos);
#endif
	}
	
	else
	{
		pos = getRowCount();
		d_grid.push_back(row);
#if OPTIMIZE_MULTILIST
		
		ListItemGrid::iterator end_pos = d_grid.end();
		--end_pos;
		end_pos->d_maxHeight = curRowHeight = getHighestRowItemHeight(pos);
#endif
	}
#if OPTIMIZE_MULTILIST
	
	d_totalHeight += curRowHeight;
#endif
	
	WindowEventArgs args(this);
	onListContentsChanged(args);

	return pos;
}


void MultiColumnList::setRowIndexChar(unsigned int row_id, unsigned int char_index)
{
	
	if (row_id >= getRowCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::getItemAtGridReference - the row given in the grid reference is out of range.");
	}
	else
	{
		ListRow findRow = d_grid[row_id];
		findRow.d_indexChar = char_index;
	}
}


uint MultiColumnList::insertRow(uint row_idx, uint row_id)
{
	return insertRow(NULL, 0, row_idx, row_id);
}



uint MultiColumnList::insertRow(ListboxItem* item, uint col_id, uint row_idx, uint row_id)
{
	
	if (getSortDirection() != ListHeaderSegment::None)
	{
		return addRow(item, col_id);
	}
	else
	{
		
		ListRow row;
		row.d_sortColumn = getSortColumn();
		row.d_items.resize(getColumnCount(), NULL);
		row.d_rowID = row_id;

		
		if (row_idx > getRowCount())
		{
			row_idx = getRowCount();
		}

		ListItemGrid::iterator final_pos = d_grid.insert(d_grid.begin() + row_idx, row);

		
		setItem(item, col_id, row_idx);

#if OPTIMIZE_MULTILIST
		
		final_pos->d_maxHeight = getHighestRowItemHeight(row_idx);
		d_totalHeight += final_pos->d_maxHeight;
#endif

		
		WindowEventArgs args(this);
		onListContentsChanged(args);

		return row_idx;
	}

}



void MultiColumnList::removeRow(uint row_idx)
{
	
	if (row_idx >= getRowCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::removeRow - The specified row index is out of range.");
	}
	else
	{
		
		for (uint i = 0; i < getColumnCount(); ++i)
		{
			ListboxItem* item = d_grid[row_idx][i];

			if ((item != NULL) && item->isAutoDeleted())
			{
				delete item;
			}

		}

#if OPTIMIZE_MULTILIST
		
		ListItemGrid::iterator delpos = d_grid.begin() + row_idx;
		d_totalHeight -= delpos->d_maxHeight;
		
		d_grid.erase(delpos);
#else
		
		d_grid.erase(d_grid.begin() + row_idx);

#endif


		
		if (d_nominatedSelectRow == row_idx)
		{
			d_nominatedSelectRow = 0;
		}

		
		WindowEventArgs args(this);
		onListContentsChanged(args);
	}

}



void MultiColumnList::setItem(ListboxItem* item, const MCLGridRef& position)
{
	
	if (position.column >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::setItem - the specified column index is invalid.");
	}
	else if (position.row >= getRowCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::setItem - the specified row index is invalid.");
	}

	
	ListboxItem* oldItem = d_grid[position.row][position.column];

	if ((oldItem != NULL) && oldItem->isAutoDeleted())
	{
		delete oldItem;
	}

	
	if (item != NULL)
		item->setOwnerWindow(this);

	d_grid[position.row][position.column] = item;


	
	WindowEventArgs args(this);
	onListContentsChanged(args);
}



void MultiColumnList::setItem(ListboxItem* item, uint col_id, uint row_idx)
{
	setItem(item, MCLGridRef(row_idx, getColumnWithID(col_id)));
}



void MultiColumnList::setSelectionMode(MultiColumnList::SelectionMode sel_mode)
{
	if (d_selectMode != sel_mode)
	{
		d_selectMode = sel_mode;

		clearAllSelections();

		switch(d_selectMode)
		{
		case RowSingle:
			d_multiSelect		= false;
			d_fullRowSelect		= true;
			d_fullColSelect		= false;
			d_useNominatedCol	= false;
			d_useNominatedRow	= false;
			break;

		case RowMultiple:
			d_multiSelect		= true;
			d_fullRowSelect		= true;
			d_fullColSelect		= false;
			d_useNominatedCol	= false;
			d_useNominatedRow	= false;
			break;

		case CellSingle:
			d_multiSelect		= false;
			d_fullRowSelect		= false;
			d_fullColSelect		= false;
			d_useNominatedCol	= false;
			d_useNominatedRow	= false;
			break;

		case CellMultiple:
			d_multiSelect		= true;
			d_fullRowSelect		= false;
			d_fullColSelect		= false;
			d_useNominatedCol	= false;
			d_useNominatedRow	= false;
			break;

		case NominatedColumnSingle:
			d_multiSelect		= false;
			d_fullRowSelect		= false;
			d_fullColSelect		= false;
			d_useNominatedCol	= true;
			d_useNominatedRow	= false;
			break;

		case NominatedColumnMultiple:
			d_multiSelect		= true;
			d_fullRowSelect		= false;
			d_fullColSelect		= false;
			d_useNominatedCol	= true;
			d_useNominatedRow	= false;
			break;

		case ColumnSingle:
			d_multiSelect		= false;
			d_fullRowSelect		= false;
			d_fullColSelect		= true;
			d_useNominatedCol	= false;
			d_useNominatedRow	= false;
			break;

		case ColumnMultiple:
			d_multiSelect		= true;
			d_fullRowSelect		= false;
			d_fullColSelect		= true;
			d_useNominatedCol	= false;
			d_useNominatedRow	= false;
			break;

		case NominatedRowSingle:
			d_multiSelect		= false;
			d_fullRowSelect		= false;
			d_fullColSelect		= false;
			d_useNominatedCol	= false;
			d_useNominatedRow	= true;
			break;

		case NominatedRowMultiple:
			d_multiSelect		= true;
			d_fullRowSelect		= false;
			d_fullColSelect		= false;
			d_useNominatedCol	= false;
			d_useNominatedRow	= true;
			break;

		default:
			throw InvalidRequestException((utf8*)"MultiColumnList::setSelectionMode - invalid or unknown SelectionMode value supplied.");
			break;

		}

		
		WindowEventArgs args(this);
		onSelectionModeChanged(args);
	}

}



void MultiColumnList::setNominatedSelectionColumnID(uint col_id)
{
	setNominatedSelectionColumn(getColumnWithID(col_id));
}



void MultiColumnList::setNominatedSelectionColumn(uint col_idx)
{
	if (d_nominatedSelectCol != col_idx)
	{
		clearAllSelections();

		d_nominatedSelectCol = col_idx;

		
		WindowEventArgs args(this);
		onNominatedSelectColumnChanged(args);
	}

}



void MultiColumnList::setNominatedSelectionRow(uint row_idx)
{
	if (d_nominatedSelectRow != row_idx)
	{
		clearAllSelections();

		d_nominatedSelectRow = row_idx;

		
		WindowEventArgs args(this);
		onNominatedSelectRowChanged(args);
	}

}



void MultiColumnList::setSortDirection(ListHeaderSegment::SortDirection direction)
{
	if (getSortDirection() != direction)
	{
		
		d_header->setSortDirection(direction);
	}

}



void MultiColumnList::setSortColumn(uint col_idx)
{
	if (getSortColumn() != col_idx)
	{
		
		d_header->setSortColumn(col_idx);
	}

}



void MultiColumnList::setSortColumnByID(uint col_id)
{
	if (d_header->getSegmentFromColumn(getSortColumn()).getID() != col_id)
	{
		
		d_header->setSortColumnFromID(col_id);
	}

}



void MultiColumnList::setShowVertScrollbar(bool setting)
{
	if (d_forceVertScroll != setting)
	{
		d_forceVertScroll = setting;

		configureScrollbars();

		
		WindowEventArgs args(this);
		onVertScrollbarModeChanged(args);
	}

}



void MultiColumnList::setShowHorzScrollbar(bool setting)
{
	if (d_forceHorzScroll != setting)
	{
		d_forceHorzScroll = setting;

		configureScrollbars();

		
		WindowEventArgs args(this);
		onHorzScrollbarModeChanged(args);
	}

}



void MultiColumnList::clearAllSelections(void)
{
	
	if (clearAllSelections_impl())
	{
		
		WindowEventArgs args(this);
		onSelectionChanged(args);
	}


}



void MultiColumnList::setItemSelectState(ListboxItem* item, bool state)
{
	setItemSelectState(getItemGridReference(item), state);
}



void MultiColumnList::setItemSelectState(const MCLGridRef& grid_ref, bool state)
{
	if (setItemSelectState_impl(grid_ref, state))
	{
		
		uint lessRow	= 3;
		float pos = 0.0f;
		float height = getHighestRowItemHeight(0);
		if( grid_ref.row > lessRow )
			pos = (grid_ref.row - lessRow) * height;
		if( d_vertScrollbar )
			d_vertScrollbar->setScrollPosition( pos );

		
		WindowEventArgs args(this);
		onSelectionChanged(args);
	}

}



void MultiColumnList::handleUpdatedItemData(void)
{
	configureScrollbars();
	requestRedraw();
}



void MultiColumnList::setColumnHeaderWidth(uint col_idx, float width)
{
	if (getMetricsMode() == Relative)
	{
		width = relativeToAbsoluteX(width);
	}

	d_header->setColumnPixelWidth(col_idx, width);
}

void MultiColumnList::postSizeChanged(void)
{
	Window::postSizeChanged();

	updateTotalRowsHeight();
	configureScrollbars();
}

void MultiColumnList::configureScrollbars(void)
{
	float totalHeight	= getTotalRowsHeight();
	float fullWidth		= d_header->getTotalSegmentsPixelExtent();

	
	
	
	
	if ((totalHeight > getListRenderArea().getHeight()) || d_forceVertScroll)
	{
		if( d_vertScrollbar )
			d_vertScrollbar->show();

		
		if ((fullWidth > getListRenderArea().getWidth()) || d_forceHorzScroll)
		{
			if( d_horzScrollbar )
				d_horzScrollbar->show();
		}
		else
		{
			if( d_horzScrollbar )
				d_horzScrollbar->hide();
		}

	}
	else
	{
		
		if ((fullWidth > getListRenderArea().getWidth()) || d_forceHorzScroll)
		{
			if( d_horzScrollbar )
				d_horzScrollbar->show();

			
			if ((totalHeight > getListRenderArea().getHeight()) || d_forceVertScroll)
			{
				if( d_vertScrollbar )
					d_vertScrollbar->show();
			}
			else
			{
				if( d_vertScrollbar )
					d_vertScrollbar->hide();
			}

		}
		else
		{
			if( d_vertScrollbar )
				d_vertScrollbar->hide();
			if( d_horzScrollbar )
				d_horzScrollbar->hide();
		}

	}

	
	
	
	Rect renderArea(getListRenderArea());
	if( d_vertScrollbar )
	{
		d_vertScrollbar->setDocumentSize(totalHeight);
		d_vertScrollbar->setPageSize(renderArea.getHeight());
		d_vertScrollbar->setStepSize(std::max(1.0f, renderArea.getHeight() / 10.0f));
		d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition());
	}
	if( d_horzScrollbar )
	{
		d_horzScrollbar->setDocumentSize(fullWidth);
		d_horzScrollbar->setPageSize(renderArea.getWidth());
		d_horzScrollbar->setStepSize(std::max(1.0f, renderArea.getWidth() / 10.0f));
		d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition());
	}
}



bool MultiColumnList::selectRange(const MCLGridRef& start, const MCLGridRef& end)
{
	MCLGridRef tmpStart(start);
	MCLGridRef tmpEnd(end);

	
	if (tmpStart.column > tmpEnd.column)
	{
		tmpStart.column = tmpEnd.column;
		tmpEnd.column = start.column;
	}

	if (tmpStart.row > tmpEnd.row)
	{
		tmpStart.row = tmpEnd.row;
		tmpEnd.row = start.row;
	}

	bool modified = false;

	
	for (uint i = tmpStart.row; i <= tmpEnd.row; ++i)
	{
		for (uint j = tmpStart.column; j <= tmpEnd.column; ++j)
		{
			ListboxItem* item = d_grid[i][j];

			if (item != NULL)
			{
				modified |= setItemSelectState_impl(getItemGridReference(item), true);
			}

		}

	}

	return modified;
}



float MultiColumnList::getTotalRowsHeight(void) const
{
#if OPTIMIZE_MULTILIST
	
	return d_totalHeight;
#else
	float height = 0.0f;

	for (uint i = 0; i < getRowCount(); ++i)
	{
		height += getHighestRowItemHeight(i);
	}

	return height;
#endif
}

void MultiColumnList::updateTotalRowsHeight()
{
	float height = 0.0f;
	for (uint i = 0; i < getRowCount(); ++i)
	{
		height += getHighestRowItemHeight(i);
	}
	d_totalHeight = height;
}



float MultiColumnList::getWidestColumnItemWidth(uint col_idx) const
{
	if (col_idx >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::getWidestColumnItemWidth - specified column is out of range.");
	}
	else
	{
		float width = 0.0f;

		
		for (uint i = 0; i < getRowCount(); ++i)
		{
			ListboxItem* item = d_grid[i][col_idx];

			
			if (item != NULL)
			{
				Size sz(item->getPixelSize( this ));

				
				if (sz.d_width > width)
				{
					
					width = sz.d_width;
				}

			}

		}

		
		return width;
	}

}



float MultiColumnList::getHighestRowItemHeight(uint row_idx) const
{
	if (row_idx >= getRowCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::getHighestRowItemHeight - specified row is out of range.");
	}
	else
	{
		float height = 0.0f;
		
		for (uint i = 0; i < getColumnCount(); ++i)
		{
			ListboxItem* item = d_grid[row_idx][i];

			
			if (item != NULL)
			{
				Size sz(item->getPixelSize( this ));

				
				if (sz.d_height > height)
				{
					
					height = sz.d_height;
				}

			}
		}
#if OPTIMIZE_MULTILIST
		
		const ListRow* row = &d_grid[row_idx];
		((CEGUI::MultiColumnList::ListRow *)row)->d_maxHeight = height;
#endif
		
		return height;
	}
	
}



bool MultiColumnList::clearAllSelections_impl(void)
{
	
	bool modified = false;

	for (uint i = 0; i < getRowCount(); ++i)
	{
		for (uint j = 0; j < getColumnCount(); ++j)
		{
			ListboxItem* item = d_grid[i][j];

			
			if ((item != NULL) && item->isSelected())
			{
				
				item->setSelected(false);
				modified = true;
			}

		}

	}

	
	return modified;
}



ListboxItem* MultiColumnList::getItemAtPoint(const Point& pt) const
{
	Rect listArea(getListRenderArea());

	float y = listArea.d_top;
	float x = listArea.d_left;
	if( d_vertScrollbar )
		y -= d_vertScrollbar->getScrollPosition();
	if( d_horzScrollbar )
		x -= d_horzScrollbar->getScrollPosition();

	
	if (pt.d_y < d_header->getAbsoluteHeight() || pt.d_x > listArea.d_right - d_vertScrollbar->getAbsoluteWidth())
		return NULL;

	for (uint i = 0; i < getRowCount(); ++i)
	{
		y += getHighestRowItemHeight(i);

		
		if (pt.d_y < y)
		{
			
			for (uint j = 0; j < getColumnCount(); ++j)
			{
				x += d_header->getColumnPixelWidth(j);

				
				if (pt.d_x < x)
				{
					
					return d_grid[i][j];
				}

			}

		}

	}

	return NULL;
}



bool MultiColumnList::setItemSelectState_impl(const MCLGridRef grid_ref, bool state)
{
	
	if (grid_ref.column >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::setItemSelectState - the specified column index is invalid.");
	}
	else if (grid_ref.row >= getRowCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::setItemSelectState - the specified row index is invalid.");
	}

	
	if (d_grid[grid_ref.row][grid_ref.column]->isSelected() != state)
	{
		
		if ((!d_useNominatedCol || (d_nominatedSelectCol == grid_ref.column)) &&
			(!d_useNominatedRow || (d_nominatedSelectRow == grid_ref.row)))
		{
			
			if (state && (!d_multiSelect))
			{
				clearAllSelections_impl();
			}

			
			if (d_fullRowSelect)
			{
				
				setSelectForItemsInRow(grid_ref.row, state);
			}
			
			else if (d_fullColSelect)
			{
				
				setSelectForItemsInColumn(grid_ref.column, state);

			}
			
			else
			{
				d_grid[grid_ref.row][grid_ref.column]->setSelected(state);
			}

			return true;
		}

	}

	return false;
}



void MultiColumnList::setSelectForItemsInRow(uint row_idx, bool state)
{
	for (uint i = 0; i < getColumnCount(); ++i)
	{
		ListboxItem* item = d_grid[row_idx][i];

		if (item != NULL)
		{
			item->setSelected(state);
		}

	}

}



void MultiColumnList::setSelectForItemsInColumn(uint col_idx, bool state)
{
	for (uint i = 0; i < getRowCount(); ++i)
	{
		ListboxItem* item = d_grid[i][col_idx];

		if (item != NULL)
		{
			item->setSelected(state);
		}

	}

}


void MultiColumnList::moveColumn_impl(uint col_idx, uint position)
{
	
	if (col_idx >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::moveColumn - the specified source column index is out of range.");
	}
	else
	{
		
		if (position > getColumnCount())
		{
			position = getColumnCount();
		}

		
		if (d_nominatedSelectCol == col_idx)
		{
			d_nominatedSelectCol = position;
		}
		else if ((col_idx < d_nominatedSelectCol) && (position >= d_nominatedSelectCol))
		{
			d_nominatedSelectCol--;
		}
		else if ((col_idx > d_nominatedSelectCol) && (position <= d_nominatedSelectCol))
		{
			d_nominatedSelectCol++;
		}

		
		for (uint i = 0; i < getRowCount(); ++i)
		{
			
			ListboxItem* item = d_grid[i][col_idx];

			
			d_grid[i].d_items.erase(d_grid[i].d_items.begin() + col_idx);

			
			d_grid[i].d_items.insert(d_grid[i].d_items.begin() + position, item);
		}

	}

}




void MultiColumnList::populateRenderCache()
{
    
	cacheListboxBaseImagery();

    
    
    
    Vector3	itemPos;
    Size	itemSize;
    Rect	itemClipper, itemRect;

    
    Rect itemsArea(getListRenderArea());
    if(!d_showheader)
	{
		itemsArea.d_top -= d_header->getAbsoluteHeight();
	}
    




    
    itemPos.d_y = itemsArea.d_top;
	if( d_vertScrollbar )
		itemPos.d_y -= d_vertScrollbar->getScrollPosition();
    itemPos.d_z = System::getSingleton().getRenderer()->getZLayer(3) - System::getSingleton().getRenderer()->getCurrentZ();

    float alpha = getEffectiveAlpha();

    
    for (uint i = 0; i < getRowCount(); ++i)
    {
        
        itemPos.d_x = itemsArea.d_left;
		if( d_horzScrollbar )
			itemPos.d_x -= d_horzScrollbar->getScrollPosition();

        
        itemSize.d_height = getHighestRowItemHeight(i);

        
        for (uint j = 0; j < getColumnCount(); ++j)
        {
            
            itemSize.d_width = d_header->getColumnPixelWidth(j);

            ListboxItem* item = d_grid[i][j];

            
            if (item)
            {
                
                itemRect.d_left	= itemPos.d_x;
                itemRect.d_top	= itemPos.d_y;
                itemRect.setSize(itemSize);
                itemClipper = itemRect.getIntersection(itemsArea);

                
                if (itemClipper.getWidth() == 0)
                {
                    itemPos.d_x += itemSize.d_width;
                    continue;
                }

                
                item->draw(d_renderCache, itemRect, itemPos.d_z, alpha, &itemClipper);
            }

            
            itemPos.d_x += itemSize.d_width;
        }

        
        itemPos.d_y += itemSize.d_height;
    }

}



void MultiColumnList::onSelectionModeChanged(WindowEventArgs& e)
{
	fireEvent(EventSelectionModeChanged, e, EventNamespace);
}



void MultiColumnList::onNominatedSelectColumnChanged(WindowEventArgs& e)
{
	fireEvent(EventNominatedSelectColumnChanged, e, EventNamespace);
}



void MultiColumnList::onNominatedSelectRowChanged(WindowEventArgs& e)
{
	fireEvent(EventNominatedSelectRowChanged, e, EventNamespace);
}



void MultiColumnList::onVertScrollbarModeChanged(WindowEventArgs& e)
{
	fireEvent(EventVertScrollbarModeChanged, e, EventNamespace);
}



void MultiColumnList::onHorzScrollbarModeChanged(WindowEventArgs& e)
{
	fireEvent(EventHorzScrollbarModeChanged, e, EventNamespace);
}



void MultiColumnList::onSelectionChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventSelectionChanged, e, EventNamespace);
}



void MultiColumnList::onItemDoubleClicked(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventItemDoubleClicked, e, EventNamespace);
}


void MultiColumnList::onListContentsChanged(WindowEventArgs& e)
{
	configureScrollbars();
	requestRedraw();
	fireEvent(EventListContentsChanged, e, EventNamespace);
}



void MultiColumnList::onSortColumnChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventSortColumnChanged, e, EventNamespace);
}



void MultiColumnList::onSortDirectionChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventSortDirectionChanged, e, EventNamespace);
}



void MultiColumnList::onListColumnSized(WindowEventArgs& e)
{
	configureScrollbars();
	requestRedraw();
	fireEvent(EventListColumnSized, e, EventNamespace);
}



void MultiColumnList::onListColumnMoved(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventListColumnMoved, e, EventNamespace);
}



void MultiColumnList::onSized(WindowEventArgs& e)
{
	
	Window::onSized(e);

	configureScrollbars();

	e.handled = true;
}



void MultiColumnList::onMouseButtonDown(MouseEventArgs& e)
{
	
	Window::onMouseButtonDown(e);

	
	{
		bool modified = false;

		
		if (!(e.sysKeys & Control) || !d_multiSelect)
		{
			modified = clearAllSelections_impl();
		}

		Point localPos(screenToWindow(e.position));

		if (getMetricsMode() == Relative)
		{
			localPos = relativeToAbsolute(localPos);
		}

		ListboxItem* item = getItemAtPoint(localPos);

		if (item != NULL)
		{
			modified = true;

			
			if (((e.sysKeys & Shift) && (d_lastSelected != NULL)) && d_multiSelect)
			{
				modified |= selectRange(getItemGridReference(item), getItemGridReference(d_lastSelected));
			}
			else
			{
				modified |= setItemSelectState_impl(getItemGridReference(item), item->isSelected() ^ true);
			}

			
			d_lastSelected = item->isSelected() ? item : NULL;
		}

		
		if (modified)
		{
			WindowEventArgs args(this);
			onSelectionChanged(args);
		}
		
		e.handled = true;
	}

}

void MultiColumnList::onMouseDoubleClicked(MouseEventArgs& e)
{
	Window::onMouseDoubleClicked(e);

	bool modified = false;

	
	Point localPos(screenToWindow(e.position));
	
	if (!(e.sysKeys & Control) || !d_multiSelect)
	{
		Rect r = d_header->getRect();
		if (r.d_bottom <= localPos.d_y)
			modified = clearAllSelections_impl();
	}

	if (getMetricsMode() == Relative)
	{
		localPos = relativeToAbsolute(localPos);
	}

	ListboxItem* item = getItemAtPoint(localPos);

	if (item != NULL)
	{
		modified = true;

		
		if (((e.sysKeys & Shift) && (d_lastSelected != NULL)) && d_multiSelect)
		{
			modified |= selectRange(getItemGridReference(item), getItemGridReference(d_lastSelected));
		}
		else
		{
			modified |= setItemSelectState_impl(getItemGridReference(item), item->isSelected() ^ true);
		}

		
		d_lastSelected = item->isSelected() ? item : NULL;
	}
	else
	{
		modified = false;
		requestRedraw();
		WindowEventArgs args(this);
		onSelectionChanged(args);
	}

	
	if (modified)
	{
		WindowEventArgs args(this);
		onItemDoubleClicked(args);
	}

	e.handled = true;
}



void MultiColumnList::onMouseWheel(MouseEventArgs& e)
{
	
	Window::onMouseWheel(e);

	if (d_vertScrollbar && d_vertScrollbar->isVisible() && (d_vertScrollbar->getDocumentSize() > d_vertScrollbar->getPageSize()))
	{
		d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition() + d_vertScrollbar->getStepSize() * -e.wheelChange);
	}
	else if (d_horzScrollbar && d_horzScrollbar->isVisible() && (d_horzScrollbar->getDocumentSize() > d_horzScrollbar->getPageSize()))
	{
		d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition() + d_horzScrollbar->getStepSize() * -e.wheelChange);
	}

	e.handled = true;
}



bool MultiColumnList::handleHeaderScroll(const EventArgs& e)
{
	
	if( d_horzScrollbar )
		d_horzScrollbar->setScrollPosition(d_header->relativeToAbsoluteX(d_header->getSegmentOffset()));

	return true;
}



bool MultiColumnList::handleHeaderSegMove(const EventArgs& e)
{
	moveColumn_impl(((HeaderSequenceEventArgs&)e).d_oldIdx, ((HeaderSequenceEventArgs&)e).d_newIdx);

	
	WindowEventArgs args(this);
	onListColumnMoved(args);

	return true;
}




bool MultiColumnList::handleColumnSizeChange(const EventArgs& e)
{
	configureScrollbars();

	
	WindowEventArgs args(this);
	onListColumnSized(args);

	return true;
}



bool MultiColumnList::handleHorzScrollbar(const EventArgs& e)
{
	
	if( d_horzScrollbar )
		d_header->setSegmentOffset(d_header->absoluteToRelativeX(d_horzScrollbar->getScrollPosition()));
    requestRedraw();
	return true;
}


bool MultiColumnList::handleVertScrollbar(const EventArgs& e)
{
    requestRedraw();
	return true;
}



bool MultiColumnList::handleSortColumnChange(const EventArgs& e)
{
	uint col = getSortColumn();

	
	for (uint i = 0; i < getRowCount(); ++i)
	{
		d_grid[i].d_sortColumn = col;
	}

	
	ListHeaderSegment::SortDirection dir = getSortDirection();

	if (dir == ListHeaderSegment::Descending)
	{
		std::sort(d_grid.begin(), d_grid.end());
	}
	else if (dir == ListHeaderSegment::Ascending)
	{
		std::sort(d_grid.begin(), d_grid.end(), pred_descend);
	}

	

	
	WindowEventArgs args(this);
	onSortColumnChanged(args);

	return true;
}



bool MultiColumnList::handleSortDirectionChange(const EventArgs& e)
{
	
	ListHeaderSegment::SortDirection dir = getSortDirection();

	if (dir == ListHeaderSegment::Descending)
	{
		std::sort(d_grid.begin(), d_grid.end());
	}
	else if (dir == ListHeaderSegment::Ascending)
	{
		std::sort(d_grid.begin(), d_grid.end(), pred_descend);
	}

	

	
	WindowEventArgs args(this);
	onSortDirectionChanged(args);

	return true;
}



bool MultiColumnList::handleHeaderSegDblClick(const EventArgs& e)
{
	
	uint col = d_header->getColumnFromSegment((ListHeaderSegment&)*((WindowEventArgs&)e).window);

	autoSizeColumnHeader(col);

	return true;
}



void MultiColumnList::setUserSortControlEnabled(bool setting)
{
	d_header->setSortingEnabled(setting);
}



void MultiColumnList::setUserColumnSizingEnabled(bool setting)
{
	d_header->setColumnSizingEnabled(setting);
}



void MultiColumnList::setUserColumnDraggingEnabled(bool setting)
{
	d_header->setColumnDraggingEnabled(setting);
}



uint MultiColumnList::getColumnID(uint col_idx) const
{
	return d_header->getSegmentFromColumn(col_idx).getID();
}



uint MultiColumnList::getRowID(uint row_idx) const
{
	
	if (row_idx >= getRowCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::getRowID - the row index given is out of range.");
	}
	else
	{
		return d_grid[row_idx].d_rowID;
	}
}



uint MultiColumnList::getRowWithID(uint row_id) const
{
	for (uint i = 0; i < getRowCount(); ++i)
	{
		if (d_grid[i].d_rowID == row_id)
		{
			return i;
		}
	}

	
	throw InvalidRequestException((utf8*)"MultiColumnList::getRowWithID - no row with the requested ID is present.");
}



bool MultiColumnList::pred_descend(const ListRow& a, const ListRow& b)
{
	return a > b;
}



bool MultiColumnList::isVertScrollbarAlwaysShown(void) const
{
	return d_forceVertScroll;
}



bool MultiColumnList::isHorzScrollbarAlwaysShown(void) const
{
	return d_forceHorzScroll;
}



void MultiColumnList::addMultiColumnListProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( MultiColumnList );
	   CEGUI_ADD_STATICPROPERTY( &d_columnsSizableProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_columnsMovableProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_forceHorzScrollProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_forceVertScrollProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_nominatedSelectColProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_nominatedSelectRowProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_selectModeProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_sortColumnIDProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_sortDirectionProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_sortSettingProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_columnHeaderProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_rowCountProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_noHeaderProperty );
	CEGUI_END_ADD_STATICPROPERTY
}



bool MultiColumnList::resetList_impl(void)
{
	
	if (getRowCount() == 0)
	{
		return false;
	}
	
	else
	{
		for (uint i = 0; i < getRowCount(); ++i)
		{
			for (uint j = 0; j < getColumnCount(); ++j)
			{
				ListboxItem* item = d_grid[i][j];

				
				if ((item != NULL) && item->isAutoDeleted())
				{
					delete item;
				}

			}

		}

		
		d_grid.clear();

#if OPTIMIZE_MULTILIST	
		
		d_totalHeight = 0;
#endif

		
		d_nominatedSelectRow = 0;
		d_lastSelected = NULL;

		return true;
	}

}



void MultiColumnList::autoSizeColumnHeader(uint col_idx)
{
	
	if (col_idx >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::isListboxItemInColumn - the column index given is out of range.");
	}
	else
	{
		
		float width = std::max(getWidestColumnItemWidth(col_idx), ListHeader::MinimumSegmentPixelWidth);

		
		if (getMetricsMode() == Relative)
		{
			width = absoluteToRelativeX(width);
		}

		
		setColumnHeaderWidth(col_idx, width);
	}

}



void MultiColumnList::setRowID(uint row_idx, uint row_id)
{
	
	if (row_idx >= getRowCount())
	{
		throw InvalidRequestException((utf8*)"MultiColumnList::setRowID - the row index given is out of range.");
	}
	else
	{
		d_grid[row_idx].d_rowID = row_id;
	}
}

bool MultiColumnList::injectIndexChar(uint index)
{
	static const int refIndex = 3;

	ListboxItem *item = getNextSelected(NULL);
	uint currentSelection = 0;
	if(item)
	{
		currentSelection = getItemRowIndex(item) +1;
	}
	size_t num = d_grid.size();
	for(size_t i=currentSelection; i<num; i++)
	{
		if(d_grid[i].d_indexChar == index)
		{
			item = d_grid[i][0];
			if (item != NULL)
			{
				bool modified = true;
				modified |= setItemSelectState_impl(getItemGridReference(item), item->isSelected() ^ true);
				d_lastSelected = item->isSelected() ? item : NULL;

				float pos = 0.0f;
				float height = getHighestRowItemHeight(0);
				if( i > refIndex )
					pos = (i - refIndex) * height;
				if( d_vertScrollbar )
					d_vertScrollbar->setScrollPosition( pos );

				if(modified)
				{
					WindowEventArgs args(this);
					onSelectionChanged(args);
					return true;
				}
				else
				{
					return false;
				}

			}
		}
	}
	for(size_t i=0; i<currentSelection;i++)
	{
		if(d_grid[i].d_indexChar == index)
		{
			item = d_grid[i][0];
			if (item != NULL)
			{
				bool modified = true;
				modified |= setItemSelectState_impl(getItemGridReference(item), item->isSelected() ^ true);
				d_lastSelected = item->isSelected() ? item : NULL;

				float pos = 0.0f;
				float height = getHighestRowItemHeight(0);
				if( i > refIndex )
					pos = (i - refIndex) * height;
				if( d_vertScrollbar )
					d_vertScrollbar->setScrollPosition( pos );

				if(modified)
				{
					WindowEventArgs args(this);
					onSelectionChanged(args);
					return true;
				}
				else
				{
					return false;
				}
			}
		}		
	}
	return false;
}

void MultiColumnList::setShowHeader(bool bnoheader)
{
	if(!bnoheader != d_showheader)
	{
		d_showheader = !bnoheader;
		requestRedraw();
	}

	if(d_showheader)
	{
		d_header->show();
		if(d_vertScrollbar)
		{
			d_vertScrollbar->setYPosition(Absolute, d_vertScrollbar->getAbsoluteYPosition()+d_header->getAbsoluteHeight());
			d_vertScrollbar->setHeight(Absolute, d_vertScrollbar->getAbsoluteHeight()-d_header->getAbsoluteHeight());
		}
	}
	else
	{
		d_header->hide();
		if(d_vertScrollbar)
		{
			d_vertScrollbar->setYPosition(Absolute, d_vertScrollbar->getAbsoluteYPosition()-d_header->getAbsoluteHeight());
			d_vertScrollbar->setHeight(Absolute, d_vertScrollbar->getAbsoluteHeight()+d_header->getAbsoluteHeight());
		}
	}
}

int MultiColumnList::writePropertiesXML(OutStream& out_stream) const
{
    
    
    

    
    int propCnt = Window::writePropertiesXML(out_stream);

    
    for (uint i = 0; i < getColumnCount(); ++i)
    {
        ListHeaderSegment& seg = getHeaderSegmentForColumn(i);

        
        String propString("<Property Name=\"ColumnHeader\" Value=\"");
        
        propString += "text:";
        propString += seg.getText();
        
        propString += " width:";
        propString += PropertyHelper::floatToString(seg.getRelativeWidth());
        
        propString += " id:";
        propString += PropertyHelper::uintToString(seg.getID());
        
        propString += "\" />";

        
        out_stream << propString.c_str() << std::endl;

        ++propCnt;
    }

    
		try
		{
			uint sortColumnID = getColumnWithID(getSortColumn());
			if (sortColumnID != 0)
			{
				  out_stream << "<Property Name=\"SortColumnID\" Value=\"" << PropertyHelper::uintToString(sortColumnID).c_str() << "\" />" << std::endl;
					++propCnt;
			}
		}
		catch (InvalidRequestException)
		{
			
			Logger::getSingleton().logEvent("MultiColumnList::writePropertiesXML - invalid sort column requested. Continuing...", Errors);
		}

    return propCnt;
}






bool MultiColumnList::ListRow::operator<(const ListRow& rhs) const
{
	ListboxItem* a = d_items[d_sortColumn];
	ListboxItem* b = rhs.d_items[d_sortColumn];

	
	if (b == NULL)
	{
		return false;
	}
	else if (a == NULL)
	{
		return true;
	}
	else
	{
		if( d_sortColumn < d_isIntSort.size() && d_isIntSort[d_sortColumn] == 1 )
		{
			return PropertyHelper::stringToInt( a->getText() ) < PropertyHelper::stringToInt( b->getText() );
		}
		else
		{
			return a->getText() < b->getText();
		}
	}

}



bool MultiColumnList::ListRow::operator>(const ListRow& rhs) const
{
	ListboxItem* a = d_items[d_sortColumn];
	ListboxItem* b = rhs.d_items[d_sortColumn];

	
	if (a == NULL)
	{
		return false;
	}
	else if (b == NULL)
	{
		return true;
	}
	else
	{
		if( d_sortColumn < d_isIntSort.size() && d_isIntSort[d_sortColumn] == 1 )
		{
			return PropertyHelper::stringToInt( a->getText() ) > PropertyHelper::stringToInt( b->getText() );
		}
		else
		{
			return a->getText() > b->getText();
		}
	}
}






MCLGridRef& MCLGridRef::operator=(const MCLGridRef& rhs)
{
	column = rhs.column;
	row = rhs.row;
	return *this;
}



bool MCLGridRef::operator<(const MCLGridRef& rhs) const
{
	if ((row < rhs.row) ||
		((row == rhs.row) && (column < rhs.column)))
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool MCLGridRef::operator<=(const MCLGridRef& rhs) const
{
	return !operator>(rhs);
}



bool MCLGridRef::operator>(const MCLGridRef& rhs) const
{
	return (operator<(rhs) || operator==(rhs)) ? false : true;
}



bool MCLGridRef::operator>=(const MCLGridRef& rhs) const
{
	return !operator<(rhs);
}



bool MCLGridRef::operator==(const MCLGridRef& rhs) const
{
	return ((column == rhs.column) && (row == rhs.row)) ? true : false;
}



bool MCLGridRef::operator!=(const MCLGridRef& rhs) const
{
	return !operator==(rhs);
}

} 
