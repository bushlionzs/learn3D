

#include "CEGUIExceptions.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIListbox.h"
#include "elements/CEGUIListboxItem.h"
#include "elements/CEGUIScrollbar.h"
#include "elements/CEGUITooltip.h"

#include <algorithm>


namespace CEGUI
{
const String Listbox::EventNamespace("Listbox");


ListboxProperties::Sort					Listbox::d_sortProperty;
ListboxProperties::MultiSelect			Listbox::d_multiSelectProperty;
ListboxProperties::ForceVertScrollbar	Listbox::d_forceVertProperty;
ListboxProperties::ForceHorzScrollbar	Listbox::d_forceHorzProperty;
ListboxProperties::ItemTooltips			Listbox::d_itemTooltipsProperty;
ListboxProperties::SelectionColour			Listbox::d_SelectionColourProperty;




const String Listbox::EventListContentsChanged( (utf8*)"ListItemsChanged" );
const String Listbox::EventSelectionChanged( (utf8*)"ItemSelectionChanged" );
const String Listbox::EventSortModeChanged( (utf8*)"SortModeChanged" );
const String Listbox::EventMultiselectModeChanged( (utf8*)"MuliselectModeChanged" );
const String Listbox::EventVertScrollbarModeChanged( (utf8*)"VertScrollModeChanged" );
const String Listbox::EventHorzScrollbarModeChanged( (utf8*)"HorzScrollModeChanged" );
const String Listbox::EventMouseMoveItemChanged( (utf8*)"MouseMoveItemChanged" );

	

Listbox::Listbox(const String& type, const String& name)
	: Window(type, name),
	d_sorted(false),
	d_multiselect(false),
	d_forceVertScroll(false),
	d_forceHorzScroll(false),
	d_itemTooltips(false),
	d_lastSelected(NULL),
	d_MouseMoveSel(NULL),
	d_curIndex(0),
	d_refIndex(0),
	d_selectionColour(0xFF4444AA)
{
	addListboxProperties();
}



Listbox::~Listbox(void)
{
	resetList_impl();
}



void Listbox::initialise(void)
{
	
	d_horzScrollbar = NULL;
	d_vertScrollbar = NULL;

	if( WindowManager::getSingleton().isWindowPresent( getName() + "__auto_vscrollbar__") )
	{
		d_vertScrollbar = createVertScrollbar(getName() + "__auto_vscrollbar__");
		addChildWindow(d_vertScrollbar);
		 d_vertScrollbar->subscribeEvent(Scrollbar::EventScrollPositionChanged, Event::Subscriber(&Listbox::handle_scrollChange, this));
	}
	if( WindowManager::getSingleton().isWindowPresent( getName() + "__auto_hscrollbar__") )
	{
		d_horzScrollbar = createHorzScrollbar(getName() + "__auto_hscrollbar__");
		addChildWindow(d_horzScrollbar);
		d_horzScrollbar->subscribeEvent(Scrollbar::EventScrollPositionChanged, Event::Subscriber(&Listbox::handle_scrollChange, this));
	}

	

	configureScrollbars();
	performChildWindowLayout();
}












size_t Listbox::getSelectedCount(void) const
{
	size_t count = 0;

	for (size_t index = 0; index < d_listItems.size(); ++index)
	{
		if (d_listItems[index]->isSelected())
		{
			count++;
		}

	}

	return count;
}



ListboxItem* Listbox::getFirstSelectedItem(void) const
{
	return getNextSelected(NULL);
}


ListboxItem* Listbox::getMouseMoveSelectedItem(void) const
{
	return d_MouseMoveSel;
}

size_t	Listbox::getMouseMoveSelectedItemIndex(void) const
{
	if(d_MouseMoveSel)
		return getItemIndex( d_MouseMoveSel);
	else
		return 19810313;
}

ListboxItem* Listbox::getNextSelected(const ListboxItem* start_item) const
{
	
	size_t index = (start_item == NULL) ? 0 : (getItemIndex(start_item) + 1);

	while (index < d_listItems.size())
	{
		
		if (d_listItems[index]->isSelected())
		{
			return d_listItems[index];
		}
		
		else
		{
			index++;
		}

	}

	
	return NULL;
}



ListboxItem* Listbox::getListboxItemFromIndex(size_t index) const
{
	if (index < d_listItems.size())
	{
		return d_listItems[index];
	}
	else
	{
		throw InvalidRequestException((utf8*)"Listbox::getListboxItemFromIndex - the specified index is out of range for this Listbox.");
	}
}



size_t Listbox::getItemIndex(const ListboxItem* item) const
{
	LBItemList::const_iterator pos = std::find(d_listItems.begin(), d_listItems.end(), item);

	if (pos != d_listItems.end())
	{
		return std::distance(d_listItems.begin(), pos);
	}
	else
	{
		throw InvalidRequestException((utf8*)"Listbox::getItemIndex - the specified ListboxItem is not attached to this Listbox.");
	}

}



bool Listbox::isItemSelected(size_t index) const
{
	if (index < d_listItems.size())
	{
		return d_listItems[index]->isSelected();
	}
	else
	{
		throw InvalidRequestException((utf8*)"Listbox::isItemSelected - the specified index is out of range for this Listbox.");
	}

}



ListboxItem* Listbox::findItemWithText(const String& text, const ListboxItem* start_item)
{
	
	size_t index = (start_item == NULL) ? 0 : (getItemIndex(start_item) + 1);

	while (index < d_listItems.size())
	{
		
		if (d_listItems[index]->getText() == text)
		{
			return d_listItems[index];
		}
		
		else
		{
			index++;
		}

	}

	
	return NULL;
}



bool Listbox::isListboxItemInList(const ListboxItem* item) const
{
	return std::find(d_listItems.begin(), d_listItems.end(), item) != d_listItems.end();
}




void Listbox::resetList(void)
{
	if (resetList_impl())
	{
		WindowEventArgs args(this);
		onListContentsChanged(args);
	}

}



void Listbox::addItem(ListboxItem* item)
{
	if (item != NULL)
	{
		
		item->setOwnerWindow(this);
		item->setSelectionColours(d_selectionColour);
		
		if (isSortEnabled())
		{
			d_listItems.insert(std::upper_bound(d_listItems.begin(), d_listItems.end(), item, &lbi_less), item);
		
		}
		
		else
		{
			d_listItems.push_back(item);
		}

		WindowEventArgs args(this);
		onListContentsChanged(args);
	}

}

void Listbox::onCharacter(KeyEventArgs& e)
{
	
	Window::onCharacter(e);

	
	if( d_listItems.size() == 0 )
	{
		e.handled = true;
		return;
	}

	
	String str;
	str = e.codepoint;
	((Font*)getFont())->prepareString( str );

	
	
	bool modified = false;

	
	
	
	if( (d_lastSelected && str != d_lastSelected->getTagText()) ||
		d_curIndex >= d_listItems.size() )
	{
		d_curIndex = 0;
		d_vertScrollbar->setScrollPosition( 0 );
	}

	
	
	bool secondSearch = false;

	
	while(1)
	{
		if ( str == d_listItems[d_curIndex]->getTagText())
		{
			
			modified = true;
			d_lastSelected->setSelected(false);

			ListboxItem* pItem = d_listItems[d_curIndex];
			pItem->setSelected(true);
			d_lastSelected = pItem->isSelected() ? pItem : NULL;

			
			float pos = 0.0f;
			float height = d_listItems[d_curIndex]->getPixelSize( this ).d_height;
			if( d_curIndex > d_refIndex )
				pos = (d_curIndex - d_refIndex) * height;

			d_vertScrollbar->setScrollPosition( pos );

			d_curIndex++;

			break;
		}
		else
		{
			d_curIndex++;	
			
			
			if( d_curIndex >= d_listItems.size() )
			{
				if( !secondSearch )
				{
					d_curIndex = 0;
					d_vertScrollbar->setScrollPosition( 0 );
					secondSearch = true;
				}
				else
				{
					break;
				}
			}
		}
	}

	if( modified )
	{
		WindowEventArgs args(this);
		onSelectionChanged(args);
	}

	e.handled = true;
}

void Listbox::setSelectionColur(colour c)
{
	d_selectionColour = c;
}



















void Listbox::insertItem(ListboxItem* item, const ListboxItem* position)
{
	
	if (isSortEnabled())
	{
		addItem(item);
	}
	else if (item != NULL)
	{
		
		item->setOwnerWindow(this);
		item->setSelectionColours(d_selectionColour);
		
		LBItemList::iterator ins_pos;

		if (position == NULL)
		{
			ins_pos = d_listItems.begin();
		}
		else
		{
			ins_pos = std::find(d_listItems.begin(), d_listItems.end(), position);

			
			if (ins_pos == d_listItems.end())
			{
				throw InvalidRequestException((utf8*)"Listbox::insertItem - the specified ListboxItem for parameter 'position' is not attached to this Listbox.");
			}

		}
		
		d_listItems.insert(ins_pos, item);

		WindowEventArgs args(this);
		onListContentsChanged(args);

	}

}



void Listbox::removeItem(const ListboxItem* item)
{
	if (item != NULL)
	{
		LBItemList::iterator pos = std::find(d_listItems.begin(), d_listItems.end(), item);

		
		if (pos != d_listItems.end())
		{
			
			(*pos)->setOwnerWindow(NULL);

			
			d_listItems.erase(pos);

			
			if (item == d_lastSelected)
			{
				d_lastSelected = NULL;
			}

			if (item == d_MouseMoveSel)
			{
				d_MouseMoveSel = NULL;
			}

			
			if (item->isAutoDeleted())
			{
				
				delete item;
			}

			WindowEventArgs args(this);
			onListContentsChanged(args);
		}


	}
	
}



void Listbox::clearAllSelections(void)
{
	
	if (clearAllSelections_impl())
	{
		WindowEventArgs args(this);
		onSelectionChanged(args);
	}

}



void Listbox::setSortingEnabled(bool setting)
{
	
	if (d_sorted != setting)
	{
		d_sorted = setting;

		
		if (d_sorted)
		{
			std::sort(d_listItems.begin(), d_listItems.end(), &lbi_greater);
		}

        WindowEventArgs args(this);
		onSortModeChanged(args);
	}

}



void Listbox::setMultiselectEnabled(bool setting)
{
	
	if (d_multiselect != setting)
	{
		d_multiselect = setting;

		
        WindowEventArgs args(this);
		if ((!d_multiselect) && (getSelectedCount() > 1))
		{
			ListboxItem* itm = getFirstSelectedItem();

			while ((itm = getNextSelected(itm)))
			{
				itm->setSelected(false);
			}

			onSelectionChanged(args);

		}

		onMultiselectModeChanged(args);
	}

}

void Listbox::setItemTooltipsEnabled(bool setting)
{
	d_itemTooltips = setting;
}




void Listbox::setShowVertScrollbar(bool setting)
{
	if (d_forceVertScroll != setting)
	{
		d_forceVertScroll = setting;

		configureScrollbars();
		WindowEventArgs args(this);
		onVertScrollbarModeChanged(args);
	}

}



void Listbox::setShowHorzScrollbar(bool setting)
{
	if (d_forceHorzScroll != setting)
	{
		d_forceHorzScroll = setting;

		configureScrollbars();
		WindowEventArgs args(this);
		onHorzScrollbarModeChanged(args);
	}

}



void Listbox::setItemSelectState(ListboxItem* item, bool state)
{
	LBItemList::iterator pos = std::find(d_listItems.begin(), d_listItems.end(), item);

	if (pos != d_listItems.end())
	{
		setItemSelectState(std::distance(d_listItems.begin(), pos), state);
	}
	else
	{
		throw InvalidRequestException((utf8*)"Listbox::setItemSelectState - the specified ListboxItem is not attached to this Listbox.");
	}
}

void Listbox::setItemSelectStateByItemID(uint itemid, bool state)
{

	for (size_t i = 0; i < getItemCount(); ++i)
	{
		if(d_listItems[i]->getID() == itemid)
		{
			return setItemSelectState(i,state);
		}
	}

	throw InvalidRequestException((utf8*)"Listbox::setItemSelectStateByItemID - the specified ListboxItem is not attached to this Listbox.");
}


void Listbox::setItemSelectState(size_t item_index, bool state)
{
	if (item_index < getItemCount())
	{
		
		if (d_listItems[item_index]->isSelected() != state)
		{
			
			if (state && !d_multiselect)
			{
				clearAllSelections_impl();
			}

			d_listItems[item_index]->setSelected(state);
			ensureItemIsVisible(item_index);
            WindowEventArgs args(this);
			onSelectionChanged(args);
		}

	}
	else
	{
		throw InvalidRequestException((utf8*)"Listbox::setItemSelectState - the value passed in the 'item_index' parameter is out of range for this Listbox.");
	}

}



void Listbox::handleUpdatedItemData(void)
{
	configureScrollbars();
	requestRedraw();
}



void Listbox::populateRenderCache()
{
    
    cacheListboxBaseImagery();

    
    
    
    Vector3	itemPos;
    Size	itemSize;
    Rect	itemClipper, itemRect;
    float	widest = getWidestItemWidth();

    
    Rect itemsArea(getListRenderArea());

    
	itemPos.d_x = itemsArea.d_left;
	itemPos.d_y = itemsArea.d_top;
	if( d_horzScrollbar )
		itemPos.d_x = itemsArea.d_left - d_horzScrollbar->getScrollPosition();
	if( d_vertScrollbar )
		itemPos.d_y = itemsArea.d_top - d_vertScrollbar->getScrollPosition();
    itemPos.d_z = System::getSingleton().getRenderer()->getZLayer(3) - System::getSingleton().getRenderer()->getCurrentZ();

    float alpha = getEffectiveAlpha();

    
    size_t itemCount = getItemCount();

    for (size_t i = 0; i < itemCount; ++i)
    {
        itemSize.d_height = d_listItems[i]->getPixelSize( this ).d_height;

        
        itemSize.d_width = std::max(itemsArea.getWidth(), widest);

        
        itemRect.d_left	= itemPos.d_x;
        itemRect.d_top	= itemPos.d_y;
        itemRect.setSize(itemSize);
        itemClipper = itemRect.getIntersection(itemsArea);

        
        if (itemClipper.getWidth() == 0)
        {
            itemPos.d_y += itemSize.d_height;
            continue;
        }

        
        d_listItems[i]->draw(d_renderCache, itemRect, itemPos.d_z, alpha, &itemClipper);

        
        itemPos.d_y += itemSize.d_height;
    }

}



void Listbox::configureScrollbars(void)
{
	
	
	
	
	
	
	
	
	float totalHeight	= getTotalItemsHeight();
	float widestItem	= getWidestItemWidth();

	
	
	
	
	
	if ((totalHeight > getListRenderArea().getHeight()) || d_forceVertScroll)
	{
		if( d_vertScrollbar )
			d_vertScrollbar->show();

		
		if ((widestItem > getListRenderArea().getWidth()) || d_forceHorzScroll)
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
		
		if ((widestItem > getListRenderArea().getWidth()) || d_forceHorzScroll)
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
		d_horzScrollbar->setDocumentSize(widestItem);
		d_horzScrollbar->setPageSize(renderArea.getWidth());
		d_horzScrollbar->setStepSize(std::max(1.0f, renderArea.getWidth() / 10.0f));
		d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition());
	}
}



void Listbox::selectRange(size_t start, size_t end)
{
	
	if (d_listItems.size() > 0)
	{
		
		if (start > d_listItems.size())
		{
			start = 0;
		}

		
		if (end >= d_listItems.size())
		{
			end = d_listItems.size() - 1;
		}

		
		if (start > end)
		{
			size_t tmp;
			tmp = start;
			start = end;
			end = tmp;
		}

		
		for( ; start <= end; ++start)
		{
			d_listItems[start]->setSelected(true);
		}

	}

}



float Listbox::getTotalItemsHeight(void) const
{
	float height = 0;

	for (size_t i = 0; i < getItemCount(); ++i)
	{
		height += d_listItems[i]->getPixelSize( this ).d_height;
	}

	return height;
}



float Listbox::getItemHeight(void) const
{
	float height = 0;

	for (size_t i = 0; i < getItemCount(); ++i)
	{
		height = d_listItems[i]->getPixelSize( this ).d_height;
		break;
	}

	return height;
}


float Listbox::getWidestItemWidth(void) const
{
	float widest = 0;

	for (size_t i = 0; i < getItemCount(); ++i)
	{
		float thisWidth = d_listItems[i]->getPixelSize( this ).d_width;

		if (thisWidth > widest)
		{
			widest = thisWidth;
		}

	}

	return widest;
}



bool Listbox::clearAllSelections_impl(void)
{
	
	bool modified = false;

	for (size_t index = 0; index < d_listItems.size(); ++index)
	{
		if (d_listItems[index]->isSelected())
		{
			d_listItems[index]->setSelected(false);
			modified = true;
		}

	}

	return modified;
}



ListboxItem* Listbox::getItemAtPoint(const Point& pt) const
{
	Rect renderArea(getListRenderArea());

	
	if (renderArea.isPointInRect(pt))
	{
		float y = renderArea.d_top - d_vertScrollbar->getScrollPosition();

		
		if (pt.d_y >= y)
		{
			for (size_t i = 0; i < getItemCount(); ++i)
			{
				y += d_listItems[i]->getPixelSize( this ).d_height;

				if (pt.d_y < y)
				{
					return d_listItems[i];
				}

			}
		}
	}

	return NULL;
}


void Listbox::onListContentsChanged(WindowEventArgs& e)
{
	configureScrollbars();
	requestRedraw();
	fireEvent(EventListContentsChanged, e, EventNamespace);
}



void Listbox::onSelectionChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventSelectionChanged, e, EventNamespace);
}



void Listbox::onSortModeChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventSortModeChanged, e, EventNamespace);
}



void Listbox::onMultiselectModeChanged(WindowEventArgs& e)
{
	fireEvent(EventMultiselectModeChanged, e, EventNamespace);
}



void Listbox::onVertScrollbarModeChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventVertScrollbarModeChanged, e, EventNamespace);
}



void Listbox::onHorzScrollbarModeChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventHorzScrollbarModeChanged, e, EventNamespace);
}



void Listbox::onSized(WindowEventArgs& e)
{
	
	Window::onSized(e);

	configureScrollbars();

	e.handled = true;
}



void Listbox::onMouseButtonDown(MouseEventArgs& e)
{
	
	Window::onMouseButtonDown(e);

	
	{
		bool modified = false;

		
		if (!(e.sysKeys & Control) || !d_multiselect)
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

			
			if (((e.sysKeys & Shift) && (d_lastSelected != NULL)) && d_multiselect)
			{
				selectRange(getItemIndex(item), getItemIndex(d_lastSelected));
			}
			else
			{
				item->setSelected(item->isSelected() ^ true);
			}

			
			d_lastSelected = item->isSelected() ? item : NULL;
			if( d_lastSelected )
				d_curIndex = getItemIndex( d_lastSelected );
		}

		
		if (modified)
		{
			WindowEventArgs args(this);
			onSelectionChanged(args);
		}
		
		e.handled = true;
	}

}



void Listbox::onMouseWheel(MouseEventArgs& e)
{
	
	Window::onMouseWheel(e);

	if ( d_vertScrollbar && d_vertScrollbar->isVisible() && (d_vertScrollbar->getDocumentSize() > d_vertScrollbar->getPageSize()))
	{
		d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition() + d_vertScrollbar->getStepSize() * -e.wheelChange);
	}
	else if ( d_horzScrollbar && d_horzScrollbar->isVisible() && (d_horzScrollbar->getDocumentSize() > d_horzScrollbar->getPageSize()))
	{
		d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition() + d_horzScrollbar->getStepSize() * -e.wheelChange);
	}

	e.handled = true;
}


void Listbox::onMouseMove(MouseEventArgs& e)
{
    Point posi = relativeToAbsolute(screenToWindow(e.position));
    ListboxItem* item = getItemAtPoint(posi);
    if (item != d_MouseMoveSel)
    {
        if (item != NULL)
        {
			item->setShowNormalBrush(true);
            setTooltipText(item->getTooltipText());
        }
        else
        {
            setTooltipText("");
        }
		if( d_MouseMoveSel )
			d_MouseMoveSel->setShowNormalBrush(false);
        d_MouseMoveSel = item;

		fireEvent(EventMouseMoveItemChanged, e, EventNamespace);
		requestRedraw();
    }
	
	
	
	
	
	
	
	
	

    if (d_itemTooltips)
    {

        
        
        Tooltip* tooltip = getTooltip();

        if (tooltip)
        {
            if (tooltip->getTargetWindow() != this)
                tooltip->setTargetWindow(this);
            else
                tooltip->positionSelf();
        }
    }

    Window::onMouseMove(e);
}


void Listbox::onMouseLeaves(MouseEventArgs& e)
{
	if( d_MouseMoveSel )
	{	
		d_MouseMoveSel->setShowNormalBrush(false);
		requestRedraw();
	}
	d_MouseMoveSel = 0;
	 Window::onMouseLeaves(e);
}



void Listbox::ensureItemIsVisible(size_t item_index)
{
	
	if (item_index >= getItemCount())
	{
		d_vertScrollbar->setScrollPosition(d_vertScrollbar->getDocumentSize() - d_vertScrollbar->getPageSize());
	}
	else
	{
		float bottom;
		float listHeight = getListRenderArea().getHeight();
		float top = 0;

		
		size_t i;
		for (i = 0; i < item_index; ++i)
		{
			top += d_listItems[i]->getPixelSize( this ).d_height;
		}

		
		bottom = top + d_listItems[i]->getPixelSize( this ).d_height;

		
		float currPos = d_vertScrollbar->getScrollPosition();
		top		-= currPos;
		bottom	-= currPos;

		
		if ((top < 0.0f) || ((bottom - top) > listHeight))
		{
			
			d_vertScrollbar->setScrollPosition(currPos + top);
		}
		
		else if (bottom >= listHeight)
		{
			
			d_vertScrollbar->setScrollPosition(currPos + bottom - listHeight);		
		}
		
		
	}

}



void Listbox::ensureItemIsVisible(const ListboxItem* item)
{
	ensureItemIsVisible(getItemIndex(item));
}



bool Listbox::isVertScrollbarAlwaysShown(void) const
{
	return d_forceVertScroll;
}



bool Listbox::isHorzScrollbarAlwaysShown(void) const
{
	return d_forceHorzScroll;
}


void Listbox::addListboxProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( Listbox );
	   CEGUI_ADD_STATICPROPERTY( &d_sortProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_multiSelectProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_forceHorzProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_forceVertProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_itemTooltipsProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_SelectionColourProperty );
	CEGUI_END_ADD_STATICPROPERTY
}



bool Listbox::resetList_impl(void)
{
	
	if (getItemCount() == 0)
	{
		return false;
	}
	
	else
	{
		
		for (size_t i = 0; i < getItemCount(); ++i)
		{
			
			if (d_listItems[i]->isAutoDeleted())
			{
				
				delete d_listItems[i];
			}

		}

		
		d_listItems.clear();

		d_lastSelected = NULL;

		d_MouseMoveSel = NULL;

		return true;
	}

}


bool Listbox::handle_scrollChange(const EventArgs& args)
{
    
    requestRedraw();
    return true;
}






bool lbi_less(const ListboxItem* a, const ListboxItem* b)
{
	return *a < *b;
}


bool lbi_greater(const ListboxItem* a, const ListboxItem* b)
{
	return *a > *b;
}

} 
