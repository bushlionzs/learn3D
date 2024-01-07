

#ifndef _CEGUIFalSectionSpecification_h_
#define _CEGUIFalSectionSpecification_h_

#include "CEGUIWindow.h"



namespace CEGUI
{
    
    class WidgetLookFeel;

    
    class CEGUIEXPORT SectionSpecification
    {
    public:
        
        SectionSpecification(const String& owner, const String& sectionName);

        
        SectionSpecification(const String& owner, const String& sectionName, const ColourRect& cols);

        
        void render(Window& srcWindow, float base_z, const ColourRect* modcols = 0, const Rect* clipper = 0, bool clipToDisplay = false) const;

        
        void render(Window& srcWindow, const Rect& baseRect, float base_z, const ColourRect* modcols = 0, const Rect* clipper = 0, bool clipToDisplay = false) const;

        
        const String& getOwnerWidgetLookFeel() const;

        
        const String& getSectionName() const;

        
        const ColourRect& getOverrideColours() const;

        
        void setOverrideColours(const ColourRect& cols);

        
        bool isUsingOverrideColours() const;

        
        void setUsingOverrideColours(bool setting = true);

        
        void setOverrideColoursPropertySource(const String& property);

        
        void setOverrideColoursPropertyIsColourRect(bool setting = true);

        
        void writeXMLToStream(OutStream& out_stream) const;

    protected:
        
        void initColourRectForOverride(const Window& wnd, ColourRect& cr) const;

    private:
        String          d_owner;                
        String          d_sectionName;          
        ColourRect      d_coloursOverride;      
        bool            d_usingColourOverride;  
        String          d_colourPropertyName;   
        bool            d_colourProperyIsRect;  
    };


} 


#endif  
