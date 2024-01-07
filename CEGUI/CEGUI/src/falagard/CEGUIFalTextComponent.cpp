

#include "falagard/CEGUIFalTextComponent.h"
#include "falagard/CEGUIFalXMLEnumHelper.h"
#include "CEGUIFontManager.h"
#include "CEGUIExceptions.h"
#include "CEGUIPropertyHelper.h"
#include <iostream>


namespace CEGUI
{
    TextComponent::TextComponent() :
        d_vertFormatting(VTF_TOP_ALIGNED),
        d_horzFormatting(HTF_LEFT_ALIGNED)
    {}

    const String& TextComponent::getText() const
    {
        return d_text;
    }

    void TextComponent::setText(const String& text)
    {
        d_text = text;
    }

    const String& TextComponent::getFont() const
    {
        return d_font;
    }

    void TextComponent::setFont(const String& font)
    {
        d_font = font;
    }

    VerticalTextFormatting TextComponent::getVerticalFormatting() const
    {
        return d_vertFormatting;
    }

    void TextComponent::setVerticalFormatting(VerticalTextFormatting fmt)
    {
        d_vertFormatting = fmt;
    }

    HorizontalTextFormatting TextComponent::getHorizontalFormatting() const
    {
        return d_horzFormatting;
    }

    void TextComponent::setHorizontalFormatting(HorizontalTextFormatting fmt)
    {
        d_horzFormatting = fmt;
    }

    void TextComponent::render_impl(Window& srcWindow, Rect& destRect, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const
    {
        
        const Font* font;

        try
        {
            font = d_font.empty() ? srcWindow.getFont() : FontManager::getSingleton().getFont(d_font);
        }
        catch (UnknownObjectException)
        {
            font = 0;
        }

        
        if (!font)
            return;

        HorizontalTextFormatting horzFormatting = d_horzFormatPropertyName.empty() ? d_horzFormatting :
            FalagardXMLHelper::stringToHorzTextFormat(srcWindow.getProperty(d_horzFormatPropertyName));

        VerticalTextFormatting vertFormatting = d_vertFormatPropertyName.empty() ? d_vertFormatting :
            FalagardXMLHelper::stringToVertTextFormat(srcWindow.getProperty(d_vertFormatPropertyName));

        
        ColourRect finalColours;
        initColoursRect(srcWindow, modColours, finalColours);

        
        const String& renderString = d_text.empty() ? srcWindow.getText() : d_text;

        
        float textHeight = font->getFormattedSize(renderString, destRect, (TextFormatting)horzFormatting).d_height;

        
        switch(vertFormatting)
        {
        case VTF_CENTRE_ALIGNED:
            destRect.d_top += (destRect.getHeight() - textHeight) * 0.5f;
            break;

        case VTF_BOTTOM_ALIGNED:
            destRect.d_top = destRect.d_bottom - textHeight;
            break;

        default:
            
            break;
        }

        
        srcWindow.getRenderCache().cacheText((const Window*)(&srcWindow), renderString, font, (TextFormatting)horzFormatting, destRect, base_z, finalColours, clipper, clipToDisplay);
    }

    void TextComponent::writeXMLToStream(OutStream& out_stream) const
    {
        
        out_stream << "<TextComponent>" << std::endl;
        
        d_area.writeXMLToStream(out_stream);

        
        out_stream << "<Text font=\"" << d_font << "\" string=\"" << d_text << "\" />" << std::endl;

        
        writeColoursXML(out_stream);

        
        if (!writeVertFormatXML(out_stream))
        {
            
            out_stream << "<VertFormat type=\"" << FalagardXMLHelper::vertTextFormatToString(d_vertFormatting) << "\" />" << std::endl;
        }

        
        if (!writeHorzFormatXML(out_stream))
        {
            
            out_stream << "<HorzFormat type=\"" << FalagardXMLHelper::horzTextFormatToString(d_horzFormatting) << "\" />" << std::endl;
        }

        
        out_stream << "</TextComponent>" << std::endl;
    }

} 
