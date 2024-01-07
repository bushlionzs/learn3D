

#ifndef _CEGUIFalTextComponent_h_
#define _CEGUIFalTextComponent_h_

#include "falagard/CEGUIFalComponentBase.h"


namespace CEGUI
{
    
    class CEGUIEXPORT TextComponent : public FalagardComponentBase
    {
    public:
        
        TextComponent();

        
        const String& getText() const;

        
        void setText(const String& text);

        
        const String& getFont() const;

        
        void setFont(const String& font);

        
        VerticalTextFormatting getVerticalFormatting() const;

        
        void setVerticalFormatting(VerticalTextFormatting fmt);

        
        HorizontalTextFormatting getHorizontalFormatting() const;

        
        void setHorizontalFormatting(HorizontalTextFormatting fmt);

        
        void writeXMLToStream(OutStream& out_stream) const;

    protected:
        
        void render_impl(Window& srcWindow, Rect& destRect, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const;

    private:
        String               d_text;            
        String               d_font;            
        VerticalTextFormatting   d_vertFormatting;  
        HorizontalTextFormatting d_horzFormatting;  
    };

} 


#endif  
