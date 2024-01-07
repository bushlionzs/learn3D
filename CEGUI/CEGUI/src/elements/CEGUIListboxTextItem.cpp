

#include "elements/CEGUIListboxTextItem.h"
#include "CEGUIFontManager.h"
#include "CEGUIFont.h"
#include "CEGUIWindow.h"
#include "CEGUIImage.h"
#include "elements/CEGUIListbox.h"


namespace CEGUI
{

const colour	ListboxTextItem::DefaultTextColour		= 0xFFFFFFFF;



ListboxTextItem::ListboxTextItem(const String& text, uint item_id, void* item_data, bool disabled, bool auto_delete) :
	ListboxItem(text, item_id, item_data, disabled, auto_delete),
	d_textCols(DefaultTextColour, DefaultTextColour, DefaultTextColour, DefaultTextColour),
	d_font(NULL),
	d_horzFormateing( LeftAligned )
{
}



const Font* ListboxTextItem::getFont(void) const
{
	
	if (d_font != NULL)
	{
		return d_font;
	}
	
	else if (d_owner != NULL)
	{
		return d_owner->getFont();
	}
	
	else
	{
		return System::getSingleton().getDefaultFont();
	}

}



void ListboxTextItem::setFont(const String& font_name)
{
	setFont(FontManager::getSingleton().getFont(font_name));
}


Size ListboxTextItem::getPixelSize(const Window* pParent) 
{
	Size tmp(0,0);

	const Font* fnt = getFont();

	if (fnt != NULL)
	{
		Rect rect;
		if(pParent->testClassName((utf8*)"Listbox"))
		{
			rect = Rect(Point(0, 0), ((Listbox*)pParent)->getListRenderArea().getSize());
		}
		else
		{
			rect = Rect(Point(0, 0), pParent->getAbsoluteSize());
		}
		switch( d_horzFormateing )
		{
		case LeftAligned:	
		case RightAligned:	
		case Centred:		
		case Justified:		
			tmp = fnt->getLineSize(d_itemText );
			break;
		case WordWrapLeftAligned:
		case WordWrapRightAligned:
		case WordWrapCentred:
		case WordWrapJustified: 	
			tmp = fnt->getFormattedSize(d_itemText, rect, d_horzFormateing);
			break;
		default:
			break;
		}
	}
	tmp.d_height += Font::LineSpace;
	return tmp;
}



void ListboxTextItem::draw(const Vector3& position, float alpha, const Rect& clipper) const
{
	
	if (d_showNormalBrush && d_normalBrush != 0)
	{
		d_normalBrush->draw(clipper, position.d_z, clipper, getModulateAlphaColourRect(d_selectCols, alpha));
	}

	if (d_selected && (d_selectBrush != NULL))
	{
		d_selectBrush->draw(clipper, position.d_z, clipper, getModulateAlphaColourRect(d_selectCols, alpha));
	}

	const Font* fnt = getFont();

	if (fnt != NULL)
	{
        Vector3 finalPos(position);
        finalPos.d_y -= PixelAligned((fnt->getLineSpacing() - fnt->getBaseline()) * 0.5f);
		fnt->drawText( getOwnerWindow(), d_itemText, finalPos, clipper, getModulateAlphaColourRect(d_textCols, alpha));
	}

}

void ListboxTextItem::draw(RenderCache& cache,const Rect& targetRect, float zBase, float alpha, const Rect* clipper) const
{
	
    if (d_showNormalBrush && d_normalBrush != 0)
    {
        cache.cacheImage(*d_normalBrush, targetRect, zBase, getModulateAlphaColourRect(d_selectCols, alpha), clipper);
    }

	if (d_selected && d_selectBrush != 0)
	{
		cache.cacheImage(*d_selectBrush, targetRect, zBase, getModulateAlphaColourRect(d_selectCols, alpha), clipper);
	}

    const Font* font = getFont();

    if (font)
    {
        Rect finalPos(targetRect);
		finalPos.d_top += PixelAligned( Font::LineSpace * 0.5f);
		cache.cacheText( getOwnerWindow(), d_itemText, font, d_horzFormateing, finalPos, zBase, getModulateAlphaColourRect(d_textCols, alpha), clipper);
    }
}



void ListboxTextItem::setTextColours(colour top_left_colour, colour top_right_colour, colour bottom_left_colour, colour bottom_right_colour)
{
	d_textCols.d_top_left		= top_left_colour;
	d_textCols.d_top_right		= top_right_colour;
	d_textCols.d_bottom_left	= bottom_left_colour;
	d_textCols.d_bottom_right	= bottom_right_colour;
}


} 
