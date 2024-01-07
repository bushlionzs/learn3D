

#include "elements/CEGUIMenubar.h"
#include "elements/CEGUIPopupMenu.h"
#include "elements/CEGUIMenuItem.h"


namespace CEGUI
{


const String Menubar::EventNamespace("Menubar");


Menubar::Menubar(const String& type, const String& name)
	: MenuBase(type, name)
{
	d_itemSpacing = 10;
	d_horzPadding = d_vertPadding = 3;
	d_borderWidth = 5;
}



Menubar::~Menubar(void)
{
}



void Menubar::layoutItemWidgets()
{
	Rect render_rect = getItemRenderArea();
	float x0 = PixelAligned(render_rect.d_left+d_borderWidth);
	
	Rect rect;

	ItemEntryList::iterator item = d_listItems.begin();
	while ( item != d_listItems.end() )
	{
		Size optimal = (*item)->getItemPixelSize();
		optimal.d_width += 2*d_horzPadding;
		optimal.d_height += 2*d_vertPadding;

		(*item)->setVerticalAlignment(VA_CENTRE);
		rect.setPosition( Point(x0,0) );
		rect.setSize( Size( PixelAligned(optimal.d_width), PixelAligned(optimal.d_height) ) );

		(*item)->setRect(Absolute,rect);
		
		x0 += optimal.d_width + d_itemSpacing;

		item++;
	}

}



Size Menubar::getContentSize()
{
	
	float tallest = 0;
	float total_width = 0;
	
	size_t count = 0;
	size_t max = d_listItems.size();
	while (count < max)
	{
		const Size sz = d_listItems[count]->getItemPixelSize();
		if (sz.d_height > tallest)
			tallest = sz.d_height;
		total_width += sz.d_width;

		count++;
	}
	
	const float dbl_border = d_borderWidth+d_borderWidth;

	
	total_width += 2.0f*count*d_horzPadding;
	
	total_width += (count-1)*d_itemSpacing;
	
	total_width += dbl_border;

	
	tallest += d_vertPadding+d_vertPadding;
	
	tallest += dbl_border;

	
	return Size( total_width, tallest);
}

} 
