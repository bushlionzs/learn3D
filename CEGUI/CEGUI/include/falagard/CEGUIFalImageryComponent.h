

#ifndef _CEGUIFalImageryComponent_h_
#define _CEGUIFalImageryComponent_h_

#include "falagard/CEGUIFalComponentBase.h"


namespace CEGUI
{
    
    class CEGUIEXPORT ImageryComponent : public FalagardComponentBase
    {
    public:
        
        ImageryComponent();

        
        const Image* getImage() const;

        
        void setImage(const Image* image);

        
        void setImage(const String& imageset, const String& image);

        
        VerticalFormatting getVerticalFormatting() const;

        
        void setVerticalFormatting(VerticalFormatting fmt);

        
        HorizontalFormatting getHorizontalFormatting() const;

        
        void setHorizontalFormatting(HorizontalFormatting fmt);

        
        void writeXMLToStream(OutStream& out_stream) const;

        
        bool isImageFetchedFromProperty() const;

        
        const String& getImagePropertySource() const;

        
        void setImagePropertySource(const String& property);

    protected:
        
        void render_impl(Window& srcWindow, Rect& destRect, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const;

        const Image*         d_image;           
        VerticalFormatting   d_vertFormatting;  
        HorizontalFormatting d_horzFormatting;  
        String  d_imagePropertyName;            
    };

} 


#endif  
