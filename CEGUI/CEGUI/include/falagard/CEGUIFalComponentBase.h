

#ifndef _CEGUIFalComponentBase_h_
#define _CEGUIFalComponentBase_h_

#include "falagard/CEGUIFalDimensions.h"
#include "CEGUIWindow.h"


namespace CEGUI
{
    
    class CEGUIEXPORT FalagardComponentBase
    {
    public:
        
        FalagardComponentBase();

        
        virtual ~FalagardComponentBase();

        
        void render(Window& srcWindow, float base_z, const CEGUI::ColourRect* modColours = 0, const Rect* clipper = 0, bool clipToDisplay = false) const;

        
        void render(Window& srcWindow, const Rect& baseRect, float base_z, const CEGUI::ColourRect* modColours = 0, const Rect* clipper = 0, bool clipToDisplay = false) const;

        
        const ComponentArea& getComponentArea() const;

        
        void setComponentArea(const ComponentArea& area);

        
        const ColourRect& getColours() const;

        
        void setColours(const ColourRect& cols);

        
        void setColoursPropertySource(const String& property);

        
        void setColoursPropertyIsColourRect(bool setting = true);

        
        void setVertFormattingPropertySource(const String& property);

        
        void setHorzFormattingPropertySource(const String& property);

    protected:
        
        void initColoursRect(const Window& wnd, const ColourRect* modCols, ColourRect& cr) const;

        
        virtual void render_impl(Window& srcWindow, Rect& destRect, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const = 0;

        
        bool writeColoursXML(OutStream& out_stream) const;

        
        bool writeVertFormatXML(OutStream& out_stream) const;

        
        bool writeHorzFormatXML(OutStream& out_stream) const;


        
        ComponentArea   d_area;                 
        ColourRect      d_colours;              
        String          d_colourPropertyName;   
        bool            d_colourProperyIsRect;  
        String          d_vertFormatPropertyName;   
        String          d_horzFormatPropertyName;   
    };
} 


#endif  
