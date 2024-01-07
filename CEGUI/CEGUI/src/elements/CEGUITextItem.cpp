

#include "elements/CEGUITextItem.h"
#include "elements/CEGUIItemListBase.h"
#include "CEGUIFont.h"


namespace CEGUI
{


TextItemProperties::TextXOffset		TextItem::d_textXOffsetProperty;
TextItemProperties::TextColour		TextItem::d_textColourProperty;
TextItemProperties::TextFormatting	TextItem::d_textFormattingProperty;


const colour	TextItem::DefaultTextColour	= 0xFFFFFFFF;


TextItem::TextItem(const String& type, const String& name) :
	ItemEntry(type, name),
	d_textColour(DefaultTextColour),
	d_textFormatting(LeftAligned),
	d_textXOffset(0.0f)
{
	addTextItemProperties();
}



TextItem::~TextItem(void)
{
}



void TextItem::onTextChanged(WindowEventArgs& e)
{
	Window::onTextChanged(e);
	
	
	Window* parent = getParent();
	ItemListBase* ilb = (ItemListBase*)parent;
	if (parent!=NULL && parent->testClassName("ItemListBase") && ilb->isItemInList(this))
	{
		ilb->handleUpdatedItemData();
	}
	
	requestRedraw();
	e.handled = true;
}



void TextItem::populateRenderCache()
{
	Rect absrect(0,0,d_pixelSize.d_width, d_pixelSize.d_height);
	
	ColourRect colours(d_textColour);
	colours.modulateAlpha(getEffectiveAlpha());
		
	
	
	
	absrect.d_top += PixelAligned((absrect.getHeight() - Font::LineSpace) / 2);
    absrect.d_left += PixelAligned(d_textXOffset);

    float zBase = System::getSingleton().getRenderer()->getZLayer(2) - System::getSingleton().getRenderer()->getCurrentZ();

    d_renderCache.cacheText(this, getText(), getFont(), d_textFormatting, absrect, zBase, colours);
}



Size TextItem::getItemPixelSize()
{
	const Font *f = getFont();
	
	return Size(f->getTextExtent(getText())+(d_textXOffset<0?-d_textXOffset:d_textXOffset), f->getLineSpacing()+1);
}



void TextItem::addTextItemProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( TextItem );
	   CEGUI_ADD_STATICPROPERTY( &d_textColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_textFormattingProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_textXOffsetProperty );
	CEGUI_END_ADD_STATICPROPERTY
}

} 
