

#include "CEGUIExceptions.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIItemListBase.h"
#include "elements/CEGUIItemEntry.h"

#include <algorithm>


namespace CEGUI
{


ItemListBaseProperties::AutoResizeEnabled	ItemListBase::d_autoResizeEnabledProperty;




const String ItemListBase::EventNamespace("ItemListBase");
const String ItemListBase::EventListContentsChanged( (utf8*)"ListItemsChanged" );

	

ItemListBase::ItemListBase(const String& type, const String& name)
	: Window(type, name),
	d_autoResize(false)
{
	
	addItemListBaseProperties();
}



ItemListBase::~ItemListBase(void)
{
	resetList_impl();
}



void ItemListBase::initialise(void)
{
	
}



ItemEntry* ItemListBase::getItemFromIndex(size_t index) const
{
	if (index < d_listItems.size())
	{
		return d_listItems[index];
	}
	else
	{
		throw InvalidRequestException((utf8*)"ItemListBase::getItemFromIndex - the specified index is out of range for this ItemListBase.");
	}
}



size_t ItemListBase::getItemIndex(const ItemEntry* item) const
{
	ItemEntryList::const_iterator pos = std::find(d_listItems.begin(), d_listItems.end(), item);

	if (pos != d_listItems.end())
	{
		return std::distance(d_listItems.begin(), pos);
	}
	else
	{
		throw InvalidRequestException((utf8*)"ItemListBase::getItemIndex - the specified ItemEntry is not attached to this ItemListBase.");
	}

}



ItemEntry* ItemListBase::findItemWithText(const String& text, const ItemEntry* start_item)
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



bool ItemListBase::isItemInList(const ItemEntry* item) const
{
	return std::find(d_listItems.begin(), d_listItems.end(), item) != d_listItems.end();
}




void ItemListBase::resetList(void)
{
	if (resetList_impl())
	{
		WindowEventArgs args(this);
		onListContentsChanged(args);
	}

}



void ItemListBase::addItem(ItemEntry* item)
{
	if (item != NULL)
	{
		
		d_listItems.push_back(item);
		addChildWindow(item);
		WindowEventArgs args(this);
		onListContentsChanged(args);
	}

}



void ItemListBase::insertItem(ItemEntry* item, const ItemEntry* position)
{
	if (item != NULL)
	{
		
		ItemEntryList::iterator ins_pos;

		if (position == NULL)
		{
			ins_pos = d_listItems.begin();
		}
		else
		{
			ins_pos = std::find(d_listItems.begin(), d_listItems.end(), position);

			
			if (ins_pos == d_listItems.end())
			{
				throw InvalidRequestException((utf8*)"ItemListBase::insertItem - the specified ItemEntry for parameter 'position' is not attached to this ItemListBase.");
			}

		}
		
		d_listItems.insert(ins_pos, item);
		addChildWindow(item);

		WindowEventArgs args(this);
		onListContentsChanged(args);
	}

}



void ItemListBase::removeItem(ItemEntry* item)
{
	if (item != NULL)
	{
		ItemEntryList::iterator pos = std::find(d_listItems.begin(), d_listItems.end(), item);

		
		if (pos != d_listItems.end())
		{
			
			d_listItems.erase(pos);

			removeChildWindow(item);
			WindowManager::getSingleton().destroyWindow(item);

			WindowEventArgs args(this);
			onListContentsChanged(args);
		}

	}
	
}


void ItemListBase::setAutoResizeEnabled(bool setting)
{
	bool old = d_autoResize;
	d_autoResize = setting;

	
	if ( d_autoResize && !old )
	{
		sizeToContent();
	}

}


void ItemListBase::handleUpdatedItemData(void)
{
	WindowEventArgs args(this);
	onListContentsChanged(args);
}


void ItemListBase::onListContentsChanged(WindowEventArgs& e)
{	
	requestRedraw();

	
	if ( d_autoResize )
	{
		sizeToContent();
	}
	
	layoutItemWidgets();
	fireEvent(EventListContentsChanged, e, EventNamespace);
}



void ItemListBase::onSized(WindowEventArgs& e)
{
	
	Window::onSized(e);

	

	e.handled = true;
}



bool ItemListBase::resetList_impl(void)
{
	
	if (getItemCount() == 0)
	{
		return false;
	}
	
	else
	{
		
		for (size_t i = 0; i < getItemCount(); ++i)
		{
			removeChildWindow(d_listItems[i]);
			WindowManager::getSingleton().destroyWindow(d_listItems[i]);
		}

		
		d_listItems.clear();

		return true;
	}

}



void ItemListBase::addItemListBaseProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( ItemListBase );
       CEGUI_ADD_STATICPROPERTY( &d_autoResizeEnabledProperty );
	CEGUI_END_ADD_STATICPROPERTY
}



void ItemListBase::addChild_impl(Window* wnd)
{
	Window::addChild_impl(wnd);

	
	if (wnd->testClassName("ItemEntry")&&!isItemInList((ItemEntry*)wnd))
	{
		
		d_listItems.push_back((ItemEntry*)wnd);
		WindowEventArgs args(this);
		onListContentsChanged(args);
	}

}

} 
