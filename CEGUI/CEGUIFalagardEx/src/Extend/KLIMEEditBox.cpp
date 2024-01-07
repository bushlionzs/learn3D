
#include "KLIMEEditBox.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIInputMethodEditor.h"


namespace CEGUI
{
    const utf8  KLIMEEditBox::WidgetTypeName[] = "Falagard/IMEEditBox";

    KLIMEEditBoxProperties::DefaultEditBox	KLIMEEditBox::d_defaultEditBoxProperty;

    KLIMEEditBox::KLIMEEditBox(const String& type, const String& name) :
        FalagardEditbox(type, name), 
		d_lastTextOffset(0),
		d_caretOn(true),
		d_lastTextLen(0)
    {
        addIMEEditBoxProperties();

		d_blinkTime = ImeModule::GetCaretBlinkTime()*0.001f;
		d_lastBlink = System::getSingleton().getCurTimeElapsed();
    }

    KLIMEEditBox::~KLIMEEditBox()
    {
    }

	void KLIMEEditBox::addIMEEditBoxProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( KLIMEEditBox )
		   CEGUI_ADD_STATICPROPERTY( &d_defaultEditBoxProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	bool KLIMEEditBox::hasInputFocus(void) const
	{
		return ImeModule::GetActiveIMEEditBox() == this;
	}

	void KLIMEEditBox::setCaratIndex(size_t carat_pos)
	{
		if( carat_pos == 0 )
		{
			d_lastTextLen = 0;
			d_lastTextOffset = 0;
		}
		FalagardEditbox::setCaratIndex(carat_pos);
	}

	void KLIMEEditBox::resetCaretBlink(void)
	{
		d_caretOn = true;
		d_lastBlink = System::getSingleton().getCurTimeElapsed();
		requestRedraw();
	}

	void KLIMEEditBox::onCaratMoved(WindowEventArgs& e)
	{
		resetCaretBlink();
		fireEvent(EventCaratMoved , e, EventNamespace);
	}

    void KLIMEEditBox::populateRenderCache()
    {
        const StateImagery* imagery;

        
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery("Normal");

        
        imagery->render(*this);

        
        Rect textArea(wlf.getNamedArea("TextArea").getArea().getPixelRect(*this));

        
        
        
        const Font* font = getFont();


        
        if (!font)
            return;
		
		
        
        
        String* editText;

        
        String maskedText;
        if (isTextMasked())
        {
            maskedText.insert(0, d_text.length(), getMaskCodePoint());
            editText = &maskedText;
        }
        
        else
        {
            editText = &d_text;
        }

		Rect absarea(Point(0,0), getAbsoluteSize());
		Size textSize = font->getFormattedSize( *editText, absarea, (TextFormatting)LeftAligned, 1);
		if(textSize.d_height == 0)
			textSize.d_height = font->getLineSpacing();
		
				
		textArea.d_top = PixelAligned((absarea.getHeight() - textSize.d_height) * 0.5f);
		textArea.d_bottom = textArea.d_top + textSize.d_height;
        
        float textOffset;
        float extentToCarat = font->getTextExtent(editText->substr(0, getCaratIndex()));

        
        const ImagerySection& caratImagery = wlf.getImagerySection("Carat");
        
        float caratWidth = caratImagery.getBoundingRect(*this, textArea).getWidth();

        
        if (!hasInputFocus())
        {
            textOffset = d_lastTextOffset;
        }
        
        else if ((d_lastTextOffset + extentToCarat) < 0)
        {
            textOffset = -extentToCarat;
        }
        
        else if ((d_lastTextOffset + extentToCarat) >= (textArea.getWidth() - caratWidth))
        {
            textOffset = textArea.getWidth() - extentToCarat - caratWidth;
        }
        
        else
        {
            textOffset = d_lastTextOffset;
        }

        ColourRect colours;
        float alpha_comp = getEffectiveAlpha();

        
        
        
        Rect text_part_rect(textArea);
        text_part_rect.d_left += textOffset;

        
        String sect = editText->substr(0, getSelectionStartIndex());
        colours.setColours(d_normalTextColour);
        colours.modulateAlpha(alpha_comp);
        d_renderCache.cacheText(this, sect, font, LeftAligned, text_part_rect, 0, colours, &textArea);

        
        text_part_rect.d_left += font->getTextExtent(sect);

        
        sect = editText->substr(getSelectionStartIndex(), getSelectionLength());
        colours.setColours(d_selectTextColour);
        colours.modulateAlpha(alpha_comp);
        d_renderCache.cacheText(this, sect, font, LeftAligned, text_part_rect, 0, colours, &textArea);

        
        text_part_rect.d_left += font->getTextExtent(sect);

        
        sect = editText->substr(getSelectionEndIndex());
        colours.setColours(d_normalTextColour);
        colours.modulateAlpha(alpha_comp);
        d_renderCache.cacheText(this, sect, font, LeftAligned, text_part_rect, 0, colours, &textArea);

        
        d_lastTextOffset = textOffset;

        
        bool active = (!isReadOnly()) && hasInputFocus();

        
        
        
        if (getSelectionLength() != 0)
        {
            
            float selStartOffset = font->getTextExtent(editText->substr(0, getSelectionStartIndex()));
            float selEndOffset   = font->getTextExtent(editText->substr(0, getSelectionEndIndex()));

            
            Rect hlarea(textArea);
            hlarea.d_left += textOffset + selStartOffset;
            hlarea.d_right = hlarea.d_left + (selEndOffset - selStartOffset);

            
            wlf.getStateImagery(active ? "ActiveSelection" : "InactiveSelection").render(*this, hlarea, 0, &textArea);
        }

        
        
        
        if (active && d_caretOn)
        {
            Rect caratRect(textArea); 
            caratRect.d_left += extentToCarat + textOffset;

            caratImagery.render(*this, caratRect, 0, 0, &caratRect);
        }
	}

	void KLIMEEditBox::updateSelf(float elapsed)
	{
		float time_now = System::getSingleton().getCurTimeElapsed();

		int textLen = (int)getText().size();
		if(textLen != d_lastTextLen) 
		{
			resetCaretBlink();
			d_lastTextLen = textLen;
		}

		
		
		
		if( time_now - d_lastBlink >= d_blinkTime )
		{
			d_caretOn = !d_caretOn;
			d_lastBlink = time_now;

			requestRedraw();
		}

		Editbox::updateSelf(elapsed);
	}

    size_t KLIMEEditBox::getTextIndexFromPosition(const Point& pt) const
    {
        
        
        
        float wndx = screenToWindowX(pt.d_x);

        if (getMetricsMode() == Relative)
        {
            wndx = relativeToAbsoluteX(wndx);
        }

        wndx -= d_lastTextOffset;

        
        
        
        if (isTextMasked())
        {
            return getFont()->getCharAtPixel(String(d_text.length(), getMaskCodePoint()), wndx);
        }
        else
        {
            return getFont()->getCharAtPixel(d_text, wndx);
        }
	}

	void KLIMEEditBox::onActivated(ActivationEventArgs& e)
	{
		FalagardEditbox::onActivated(e);

		if( !isReadOnly() )
		ImeModule::SetActiveIMEEditBox(this, true);
	}
		
	void KLIMEEditBox::onDeactivated(ActivationEventArgs& e)
	{
		FalagardEditbox::onDeactivated(e);

		
	}
	
	void KLIMEEditBox::onParentHidden(void)
	{
		FalagardEditbox::onParentHidden();

		if( !isReadOnly() )
		ImeModule::SetActiveIMEEditBox(this, false);
	}

	
	void KLIMEEditBox::onMouseButtonDown(MouseEventArgs& e)
	{
		
		Editbox::onMouseButtonDown(e);

		if( !isReadOnly() )
		ImeModule::SetActiveIMEEditBox(this, true);
	}
    
    
    Window* KLIMEEditBoxFactory::createWindow(const String& name)
    {
        return new KLIMEEditBox(d_type, name);
    }

    void KLIMEEditBoxFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}
