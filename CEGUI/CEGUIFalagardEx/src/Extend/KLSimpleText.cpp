
#include "KLSimpleText.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIFont.h"


namespace CEGUI
{
	const utf8  KLSimpleText::WidgetTypeName[] = "Falagard/SimpleText";

	KLSimpleTextProperties::VertFormatting	KLSimpleText::d_vertFormattingProperty;
	KLSimpleTextProperties::HorzFormatting	KLSimpleText::d_horzFormattingProperty;
	KLSimpleTextProperties::TextScale			KLSimpleText::d_textScaleProperty;
	KLSimpleTextProperties::TextColor			KLSimpleText::d_textColorProperty;

    KLSimpleText::KLSimpleText(const String& type, const String& name) :
        Window(type, name),
		d_horzFormatting(LeftAligned),
		d_vertFormatting(VertCentred)
    {
		d_fScaleX = 1;
		d_fScaleY = 1;
		d_TextColour = colour( 1,1,1,1 );
        addSimpleTextProperties();
		d_recalculation = false;
   }

    KLSimpleText::~KLSimpleText()
    {
    }

	void KLSimpleText::addSimpleTextProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( KLSimpleText )
		   CEGUI_ADD_STATICPROPERTY( &d_vertFormattingProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_horzFormattingProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_textScaleProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_textColorProperty );
		CEGUI_END_ADD_STATICPROPERTY
    }

	
	void KLSimpleText::setVerticalFormatting(VertFormatting v_fmt)
	{
		d_vertFormatting = v_fmt;
		requestRedraw();
	}
	

	
	void KLSimpleText::setHorizontalFormatting(HorzFormatting h_fmt)
	{
		d_horzFormatting = h_fmt;
		requestRedraw();
	}

	
	void KLSimpleText::populateRenderCache()
	{
		const Font* font = getFont();
		
		if (font == 0 || d_text.empty())
			return;

		int nOffset = font->getFontVertOffset();
	
		
		Rect textArea(getTextRenderArea());
		Rect clipper(textArea);

		float textHeight = font->getFormattedSize(d_text, textArea, (TextFormatting)d_horzFormatting,d_fScaleX, d_fScaleY ).d_height;

		
		switch(d_vertFormatting)
		{
		case TopAligned:
			textArea.d_top += 1; 
			break;

		case VertCentred:
			{
				int fSpace = (int)(textArea.getHeight() - textHeight) * 0.5f;
				textArea.d_top += fSpace;
			}
			break;

		case BottomAligned:
			textArea.d_top = textArea.d_bottom - textHeight;
			break;
		}

		textArea.d_top += nOffset;
		textArea.d_bottom += nOffset;

		
	    ColourRect final_cols( d_TextColour );
		final_cols.setAlpha( d_alpha );

		d_validSize = 0;

		if(d_clippedByParent)
		{
			d_renderCache.cacheText(this, 
				d_text, font, (TextFormatting)d_horzFormatting, textArea, 0, final_cols, 0, false, d_fScaleX, d_fScaleY);
		}
		else
		{
			d_renderCache.cacheText(this, 
				d_text, font, (TextFormatting)d_horzFormatting, textArea, 0, final_cols, &clipper, true, d_fScaleX, d_fScaleY);
		}
	}

	void KLSimpleText::setTextScale( Size  scale )
	{
		d_fScaleX = scale.d_width;
		d_fScaleY = scale.d_height; 
		requestRedraw();
	}
    
    Window* KLSimpleTextFactory::createWindow(const String& name)
    {
        return new KLSimpleText(d_type, name);
    }

    void KLSimpleTextFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}