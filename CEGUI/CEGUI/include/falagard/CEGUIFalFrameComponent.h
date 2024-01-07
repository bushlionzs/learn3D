

#ifndef _CEGUIFalFrameComponent_h_
#define _CEGUIFalFrameComponent_h_

#include "falagard/CEGUIFalComponentBase.h"


namespace CEGUI
{
    
    class CEGUIEXPORT FrameComponent : public FalagardComponentBase
    {
    public:
        
        FrameComponent();

        
        VerticalFormatting getBackgroundVerticalFormatting() const;

        
        void setBackgroundVerticalFormatting(VerticalFormatting fmt);

        
        HorizontalFormatting getBackgroundHorizontalFormatting() const;

        
        void setBackgroundHorizontalFormatting(HorizontalFormatting fmt);

        
        const Image* getImage(FrameImageComponent part) const;

        
        void setImage(FrameImageComponent part, const Image* image);

        
        void setImage(FrameImageComponent part, const String& imageset, const String& image);

        
        void writeXMLToStream(OutStream& out_stream) const;

    protected:
        
        void render_impl(Window& srcWindow, Rect& destRect, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const;

        
        void doBackgroundRender(Window& srcWindow, Rect& destRect, float base_z, const ColourRect& colours, const Rect* clipper, bool clipToDisplay) const;

        
        VerticalFormatting   d_vertFormatting;  
        HorizontalFormatting d_horzFormatting;  
        
        const Image* d_frameImages[FIC_FRAME_IMAGE_COUNT];  
    };

} 


#endif  
