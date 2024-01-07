

#include "elements/CEGUIPopupMenu.h"
#include "elements/CEGUIMenuItem.h"
#include "ceguiwindowmanager.h"
#include "CEGUIExceptions.h"


namespace CEGUI
{


PopupMenuProperties::FadeInTime		PopupMenu::d_fadeInTimeProperty;
PopupMenuProperties::FadeOutTime	PopupMenu::d_fadeOutTimeProperty;



const String PopupMenu::EventNamespace("PopupMenu");



PopupMenu::PopupMenu(const String& type, const String& name)
	: MenuBase(type, name),
	d_origAlpha(d_alpha),
	d_fadeOutTime(0),
	d_fadeInTime(0),
	d_fading(false),
	d_fadingOut(false)
{
	d_itemSpacing = 2;
	d_horzPadding = 10;
	d_vertPadding = 2;
	d_borderWidth = 0;

	addPopupMenuProperties();

	
	d_autoResize = true;

	
	setClippedByParent(false);

	
	hide();
}



PopupMenu::~PopupMenu(void)
{
}



void PopupMenu::openPopupMenu(void)
{
	
	if (d_fading)
	{
		
		if (!d_fadingOut)
		{
			
			return;
		}
		
		else
		{
			
			if (d_fadeInTime>0.0f&&d_fadeOutTime>0.0f)
			{
				
				d_fadeElapsed = ((d_fadeOutTime-d_fadeElapsed)/d_fadeOutTime)*d_fadeInTime;
			}
			else
			{
				
				d_fadeElapsed = 0;
			}
			
			d_fadingOut=false;
		}

	}
	
	else if (d_fadeInTime>0.0f)
	{
		d_fading = true;
		d_fadingOut=false;
		setAlpha(0.0f);
		d_fadeElapsed = 0;
	}
	
	else
	{
		d_fading = false;
		setAlpha(d_origAlpha);
	}
	
	show();
	moveToFront();
}



void PopupMenu::closePopupMenu(void)
{
	
	if (d_fading)
	{
		
		if (d_fadingOut)
		{
			
			return;
		}
		
		else
		{
			
			if (d_fadeInTime>0.0f&&d_fadeOutTime>0.0f)
			{
				
				d_fadeElapsed = ((d_fadeInTime-d_fadeElapsed)/d_fadeInTime)*d_fadeOutTime;
			}
			else
			{
				
				d_fadeElapsed = 0;
			}
			
			d_fadingOut=true;
		}

	}
	
	else if (d_fadeOutTime>0.0f)
	{
		d_fading = true;
		d_fadingOut=true;
		setAlpha(d_origAlpha);
		d_fadeElapsed = 0;
	}
	
	else
	{
		d_fading = false;
		hide();
	}

}
Window* PopupMenu::addPopItem(ItemEntry* pItem, const String& text)
{	
	if(pItem)
	{
		pItem->setText(text);
		addChildWindow(pItem);
	}
	return pItem;
}
void PopupMenu::removePopItem(size_t positon)
{
	if(positon > d_listItems.size())
	{
		throw InvalidRequestException((utf8*)"PopupMenu::removePopItem - the specified is not exists.");	
	}
	removeItem(d_listItems[positon]);
}

void PopupMenu::removeAllPopItem()
{
	for (uint i=0; i<d_listItems.size(); i++)
	{
		removeChildWindow(d_listItems[i]);			
	}
	d_listItems.clear();

	WindowEventArgs args(this);
	onListContentsChanged(args);
}


void PopupMenu::updateSelf(float elapsed)
{
    ItemListBase::updateSelf(elapsed);
    
    
    if (d_fading)
    {
		d_fadeElapsed+=elapsed;

		
		if (d_fadingOut)
		{
			if (d_fadeElapsed>=d_fadeOutTime)
			{
				hide();
				d_fading=false;
			}
			else
			{
				setAlpha(d_origAlpha*(d_fadeOutTime-d_fadeElapsed)/d_fadeOutTime);
			}

		}

		
		else
		{
			if (d_fadeElapsed>=d_fadeInTime)
			{
				d_fading=false;
				setAlpha(d_origAlpha);
			}
			else
			{
				setAlpha(d_origAlpha*d_fadeElapsed/d_fadeInTime);
			}

		}

	}

}



void PopupMenu::layoutItemWidgets()
{
	
	Rect render_rect = getItemRenderArea();

	
	const float x0 = render_rect.d_left+d_borderWidth;
	float y0 = render_rect.d_top+d_borderWidth;

	Rect rect;
	Size sz(render_rect.getWidth()-d_borderWidth-d_borderWidth,0); 

	
	ItemEntryList::iterator item = d_listItems.begin();
	while ( item != d_listItems.end() )
	{
		
		sz.d_height = (*item)->getItemPixelSize().d_height; 
		sz.d_height += d_vertPadding+d_vertPadding;

		
		rect.setPosition( Point(x0, y0) );
		rect.setSize( sz );
		(*item)->setRect(Absolute,rect);
		
		y0 += sz.d_height + d_itemSpacing;

		item++; 
	}
}



Size PopupMenu::getContentSize()
{
	
	float widest = 0;
	float total_height = 0;
	
	size_t count = 0;
	size_t max = d_listItems.size();
	while (count < max)
	{
		const Size sz = d_listItems[count]->getItemPixelSize();
		if (sz.d_width > widest)
			widest = sz.d_width;
		total_height += sz.d_height;

		count++;
	}
	
	const float dbl_border = d_borderWidth+d_borderWidth;

	
	total_height += 2.0f*count*d_vertPadding;
	
	total_height += (count-1)*d_itemSpacing;
	
	total_height += dbl_border;

	
	widest += d_horzPadding+d_horzPadding;
	
	widest += dbl_border;

	
	return Size( widest, total_height );
}



void PopupMenu::onAlphaChanged(WindowEventArgs& e)
{
	ItemListBase::onAlphaChanged(e);
	
	
	if (!d_fading)
	{
		d_origAlpha = d_alpha;
	}
}



void PopupMenu::addPopupMenuProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( PopupMenu );
	   CEGUI_ADD_STATICPROPERTY( &d_fadeInTimeProperty );
       CEGUI_ADD_STATICPROPERTY( &d_fadeOutTimeProperty );
	CEGUI_END_ADD_STATICPROPERTY
}
void PopupMenu::onParentSized(WindowEventArgs& e)
{
	MenuBase::onParentSized( e );
	layoutItemWidgets();
}

} 
