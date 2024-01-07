

#include "elements/CEGUIStaticText.h"
#include "CEGUIFont.h"
#include "CEGUIWindowManager.h"
#include "CEGUIExceptions.h"
#include "elements/CEGUIScrollbar.h"


namespace CEGUI
{
const String StaticText::EventNamespace("StaticText");


StaticTextProperties::TextColours		StaticText::d_textColoursProperty;
StaticTextProperties::VertFormatting	StaticText::d_vertFormattingProperty;
StaticTextProperties::HorzFormatting	StaticText::d_horzFormattingProperty;
StaticTextProperties::VertScrollbar		StaticText::d_vertScrollbarProperty;
StaticTextProperties::HorzScrollbar		StaticText::d_horzScrollbarProperty;
StaticTextProperties::TextScale			StaticText::d_textScaleProperty;


StaticText::StaticText(const String& type, const String& name) :
	Static(type, name),
	d_horzFormatting(LeftAligned),
	d_vertFormatting(VertCentred),
    d_textCols(0xFFFFFFFF),
	d_enableVertScrollbar(false),
	d_enableHorzScrollbar(false),
	d_fScaleX( 1 ),
	d_fScaleY( 1 )

{
	addStaticTextProperties();

}



StaticText::~StaticText(void)
{
}



void StaticText::setTextColours(const ColourRect& colours)
{
	d_textCols = colours;
	requestRedraw();
}



void StaticText::setTextColours(const colour& top_left_colour, const colour& top_right_colour, const colour& bottom_left_colour, const colour& bottom_right_colour)
{
	d_textCols.d_top_left		= top_left_colour;
	d_textCols.d_top_right		= top_right_colour;
	d_textCols.d_bottom_left	= bottom_left_colour;
	d_textCols.d_bottom_right	= bottom_right_colour;
	requestRedraw();
}



void StaticText::setFormatting(HorzFormatting h_fmt, VertFormatting v_fmt)
{
	d_horzFormatting = h_fmt;
	d_vertFormatting = v_fmt;
	requestRedraw();
}



void StaticText::setVerticalFormatting(VertFormatting v_fmt)
{
	d_vertFormatting = v_fmt;
	requestRedraw();
}



void StaticText::setHorizontalFormatting(HorzFormatting h_fmt)
{
	d_horzFormatting = h_fmt;
	requestRedraw();
}



void StaticText::populateRenderCache()
{
	
	Static::populateRenderCache();

	const Font* font = getFont();
    
    if (font == 0)
        return;

	
	Rect absarea(getTextRenderArea());
	Rect clipper(absarea);

	float textHeight = font->getFormattedSize(d_text, absarea, (TextFormatting)d_horzFormatting, d_fScaleX).d_height;

	
	if (d_horzScrollbar && d_horzScrollbar->isVisible())
	{
		switch(d_horzFormatting)
		{
		case LeftAligned:
		case WordWrapLeftAligned:
		case Justified:
		case WordWrapJustified:
			absarea.offset(Point(-d_horzScrollbar->getScrollPosition(), 0));
			break;

		case Centred:
		case WordWrapCentred:
			absarea.setWidth(d_horzScrollbar->getDocumentSize());
			absarea.offset(Point(-d_horzScrollbar->getScrollPosition(), 0));
			break;

		case RightAligned:
		case WordWrapRightAligned:
			absarea.offset(Point(d_horzScrollbar->getScrollPosition(), 0));
			break;
		}

	}

	
	if( d_vertScrollbar )
	{
		switch(d_vertFormatting)
		{
		case TopAligned:
			absarea.d_top -= d_vertScrollbar->getScrollPosition();
			break;

		case VertCentred:
			
			if (d_vertScrollbar->isVisible())
			{
				absarea.d_top -= d_vertScrollbar->getScrollPosition();
			}
			
			else
			{
				absarea.d_top += PixelAligned((absarea.getHeight() - textHeight) * 0.5f);
			}

			break;

		case BottomAligned:
			absarea.d_top = absarea.d_bottom - textHeight;
			absarea.d_top += d_vertScrollbar->getScrollPosition();
			break;
		}
	}

    
    ColourRect final_cols(d_textCols);
    final_cols.modulateAlpha(getEffectiveAlpha());
    
	
    d_renderCache.cacheText(this, d_text, font, (TextFormatting)d_horzFormatting, absarea, 0, final_cols, &clipper, true, d_fScaleX, d_fScaleY );
}



void StaticText::addStaticTextProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( StaticText );
	   CEGUI_ADD_STATICPROPERTY( &d_textScaleProperty  );
	   CEGUI_ADD_STATICPROPERTY( &d_textColoursProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_vertFormattingProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_horzFormattingProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_vertScrollbarProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_horzScrollbarProperty );
	CEGUI_END_ADD_STATICPROPERTY
}



void StaticText::initialise(void)
{
	Static::initialise();

	d_horzScrollbar = NULL;
	d_vertScrollbar = NULL;

	if( WindowManager::getSingleton().isWindowPresent( getName() + "__auto_vscrollbar__") )
	{
		d_vertScrollbar = createVertScrollbar(getName() + "__auto_vscrollbar__");
		addChildWindow(d_vertScrollbar);
		 d_vertScrollbar->subscribeEvent(Scrollbar::EventScrollPositionChanged, Event::Subscriber(&StaticText::handleScrollbarChange, this));
	}
	if( WindowManager::getSingleton().isWindowPresent( getName() + "__auto_hscrollbar__") )
	{
		d_horzScrollbar = createHorzScrollbar(getName() + "__auto_hscrollbar__");
		addChildWindow(d_horzScrollbar);
		d_horzScrollbar->subscribeEvent(Scrollbar::EventScrollPositionChanged, Event::Subscriber(&StaticText::handleScrollbarChange, this));
	}


	
	performChildWindowLayout();
}



Rect StaticText::getTextRenderArea(void) const
{
	Rect area(Point(0,0), getAbsoluteSize());

	if (d_horzScrollbar->isVisible())
	{
		area.d_bottom -= d_horzScrollbar->getAbsoluteHeight();
	}
	else if (d_frameEnabled)
	{
		area.d_bottom -= d_bottom_height;
	}

	if (d_vertScrollbar->isVisible())
	{
		area.d_right -= d_vertScrollbar->getAbsoluteWidth();
	}
	else if (d_frameEnabled)
	{
		area.d_right -= d_right_width;
	}

	if (d_frameEnabled)
	{
		area.d_left	+= d_left_width;
		area.d_top	+= d_top_height;
	}

	return area;
}



void StaticText::configureScrollbars(void)
{
    Scrollbar* vertScrollbar;
    Scrollbar* horzScrollbar;

    try
    {
        vertScrollbar = d_vertScrollbar;
        horzScrollbar = d_horzScrollbar;
    }
    catch (UnknownObjectException)
    {
        
        return;
    }

	const Font* font = getFont();

    
	if (font == 0)
	   return;

	Rect initialArea(getTextRenderArea());

	Size sz = font->getFormattedSize(d_text, initialArea, (TextFormatting)d_horzFormatting, d_fScaleX);
	float totalHeight	= sz.d_height;
	float widestItem	= sz.d_width;

	
	
	
	
	if ((totalHeight > getTextRenderArea().getHeight()) && d_enableVertScrollbar)
	{
		if( vertScrollbar )
			vertScrollbar->show();

		
		if ((widestItem > getTextRenderArea().getWidth()) && d_enableHorzScrollbar)
		{
			if( horzScrollbar )
				horzScrollbar->show();
		}
		else
		{
			if( horzScrollbar )
				horzScrollbar->hide();
		}

	}
	else
	{
		
		if ((widestItem > getTextRenderArea().getWidth()) && d_enableHorzScrollbar)
		{
			if( horzScrollbar )
				horzScrollbar->show();

			
			if ((totalHeight > getTextRenderArea().getHeight()) && d_enableVertScrollbar)
			{
				if( vertScrollbar )
					vertScrollbar->show();
			}
			else
			{
				if( vertScrollbar )
					vertScrollbar->hide();
			}

		}
		else
		{
			if( vertScrollbar )
				vertScrollbar->hide();
			if( horzScrollbar )
				horzScrollbar->hide();
		}

	}

	
	
	
	Rect renderArea(getTextRenderArea());
	if( vertScrollbar )
	{
		vertScrollbar->setDocumentSize(totalHeight);
		vertScrollbar->setPageSize(renderArea.getHeight());
		vertScrollbar->setStepSize(std::max(1.0f, renderArea.getHeight() / 10.0f));
		vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition());
	}
	if( horzScrollbar )
	{
		horzScrollbar->setDocumentSize(widestItem);
		horzScrollbar->setPageSize(renderArea.getWidth());
		horzScrollbar->setStepSize(std::max(1.0f, renderArea.getWidth() / 10.0f));
		horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition());
	}
}



bool StaticText::isVerticalScrollbarEnabled(void) const
{
	return d_enableVertScrollbar;
}



bool StaticText::isHorizontalScrollbarEnabled(void) const
{
	return d_enableHorzScrollbar;
}



void StaticText::setVerticalScrollbarEnabled(bool setting)
{
	d_enableVertScrollbar = setting;
	configureScrollbars();
	performChildWindowLayout();
}



void StaticText::setHorizontalScrollbarEnabled(bool setting)
{
	d_enableHorzScrollbar = setting;
	configureScrollbars();
	performChildWindowLayout();
}



void StaticText::onTextChanged(WindowEventArgs& e)
{
	Static::onTextChanged(e);

	configureScrollbars();
	requestRedraw();
}



void StaticText::onSized(WindowEventArgs& e)
{
	Static::onSized(e);

	configureScrollbars();
}



void StaticText::onFontChanged(WindowEventArgs& e)
{
	Static::onFontChanged(e);

	configureScrollbars();
	requestRedraw();
}



void StaticText::onMouseWheel(MouseEventArgs& e)
{
	
	Static::onMouseWheel(e);

	if ( d_vertScrollbar && d_vertScrollbar->isVisible() && (d_vertScrollbar->getDocumentSize() > d_vertScrollbar->getPageSize()))
	{
		d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition() + d_vertScrollbar->getStepSize() * -e.wheelChange);
	}
	else if (d_horzScrollbar && d_horzScrollbar->isVisible() && (d_horzScrollbar->getDocumentSize() > d_horzScrollbar->getPageSize()))
	{
		d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition() + d_horzScrollbar->getStepSize() * -e.wheelChange);
	}

	e.handled = true;
}



bool StaticText::handleScrollbarChange(const EventArgs& e)
{
	requestRedraw();

	return true;
}


Rect StaticText::getUnclippedInnerRect(void) const
{
	
	
	return Window::getUnclippedInnerRect();
}

void	StaticText::setTextScale( Size  scale )
{
	d_fScaleX = scale.d_width;
	d_fScaleY = scale.d_height; 
	requestRedraw();
}

} 
