

#include "elements/CEGUIListboxItem.h"
#include "CEGUISystem.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"



namespace CEGUI
{

const colour	ListboxItem::DefaultSelectionColour	= 0xFF4444AA;


ListboxItem::ListboxItem(const String& text, uint item_id, void* item_data, bool disabled, bool auto_delete) :
	d_itemText(text),
	d_itemID(item_id),
	d_itemData(item_data),
    d_selected(false),
	d_showNormalBrush(false),
	d_disabled(disabled),
    d_autoDelete(auto_delete),
	d_owner(NULL),
    d_selectCols(DefaultSelectionColour, DefaultSelectionColour, DefaultSelectionColour, DefaultSelectionColour),
	d_normalBrush(NULL),
	d_selectBrush(NULL),
	d_tagText("")
{
}



void ListboxItem::setSelectionBrushImage(const String& imageset, const String& image)
{
	setSelectionBrushImage(ImagesetManager::getSingleton().getImageset(imageset)->getImage(image));
}


void ListboxItem::setNormalBrushImage(const String& imageset, const String& image)
{
	setNormalBrushImage(ImagesetManager::getSingleton().getImageset(imageset)->getImage(image));
}


ColourRect ListboxItem::getModulateAlphaColourRect(const ColourRect& cols, float alpha) const
{
	return ColourRect
		(
			calculateModulatedAlphaColour(cols.d_top_left, alpha),
			calculateModulatedAlphaColour(cols.d_top_right, alpha),
			calculateModulatedAlphaColour(cols.d_bottom_left, alpha),
			calculateModulatedAlphaColour(cols.d_bottom_right, alpha)
		);
}



colour ListboxItem::calculateModulatedAlphaColour(colour col, float alpha) const
{
	colour temp(col);
	temp.setAlpha(temp.getAlpha() * alpha);
	return temp;
}



void ListboxItem::setSelectionColours(colour top_left_colour, colour top_right_colour, colour bottom_left_colour, colour bottom_right_colour)
{
	d_selectCols.d_top_left		= top_left_colour;
	d_selectCols.d_top_right	= top_right_colour;
	d_selectCols.d_bottom_left	= bottom_left_colour;
	d_selectCols.d_bottom_right	= bottom_right_colour;
}

} 
