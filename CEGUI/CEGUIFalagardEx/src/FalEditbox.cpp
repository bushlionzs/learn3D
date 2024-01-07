

#include "FalEditbox.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardEditbox::WidgetTypeName[] = "Falagard/Editbox";

    FalagardEditbox::FalagardEditbox(const String& type, const String& name) :
        Editbox(type, name),
        d_lastTextOffset(0)
    {
    }

    FalagardEditbox::~FalagardEditbox()
    {
    }

    void FalagardEditbox::populateRenderCache()
    {
        const StateImagery* imagery;

        
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : (isReadOnly() ? "ReadOnly" : "Enabled"));

        
        imagery->render(*this);

        
        const Rect textArea(wlf.getNamedArea("TextArea").getArea().getPixelRect(*this));

        
        
        
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
        
        text_part_rect.d_top += (textArea.getHeight() - font->getLineSpacing()) * 0.5f;

        
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

        
        
        
        if (active)
        {
            Rect caratRect(textArea);
            caratRect.d_left += extentToCarat + textOffset;

            caratImagery.render(*this, caratRect, 0, 0, &textArea);
        }
    }

    size_t FalagardEditbox::getTextIndexFromPosition(const Point& pt) const
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

    
    
    
    Window* FalagardEditboxFactory::createWindow(const String& name)
    {
        return new FalagardEditbox(d_type, name);
    }

    void FalagardEditboxFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
