

#ifndef _CEGUIFalImagerySection_h_
#define _CEGUIFalImagerySection_h_

#include "falagard/CEGUIFalImageryComponent.h"
#include "falagard/CEGUIFalTextComponent.h"
#include "falagard/CEGUIFalFrameComponent.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class CEGUIEXPORT ImagerySection
    {
    public:
        
        ImagerySection();

        
        ImagerySection(const String& name);

        
        void render(Window& srcWindow, float base_z, const CEGUI::ColourRect* modColours = 0, const Rect* clipper = 0, bool clipToDisplay = false) const;

        
        void render(Window& srcWindow, const Rect& baseRect, float base_z, const CEGUI::ColourRect* modColours = 0, const Rect* clipper = 0, bool clipToDisplay = false) const;

        
        void addImageryComponent(const ImageryComponent& img);

        
        void clearImageryComponents();

        
        void addTextComponent(const TextComponent& text);

        
        void clearTextComponents();

        
        void clearFrameComponents();

        
        void addFrameComponent(const FrameComponent& frame);

        
        const ColourRect& getMasterColours() const;

        
        void setMasterColours(const ColourRect& cols);

        
        const String& getName() const;

        
        void setMasterColoursPropertySource(const String& property);

        
        void setMasterColoursPropertyIsColourRect(bool setting = true);

        
        Rect getBoundingRect(const Window& wnd) const;

        
        Rect getBoundingRect(const Window& wnd, const Rect& rect) const;

        
        void writeXMLToStream(OutStream& out_stream) const;

    protected:
        
        void initMasterColourRect(const Window& wnd, ColourRect& cr) const;

    private:
        typedef std::vector<ImageryComponent> ImageryList;
        typedef std::vector<TextComponent> TextList;
        typedef std::vector<FrameComponent> FrameList;

        CEGUI::String       d_name;             
        CEGUI::ColourRect   d_masterColours;    
        FrameList           d_frames;           
        ImageryList         d_images;           
        TextList            d_texts;            
        String              d_colourPropertyName;   
        bool                d_colourProperyIsRect;  
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
