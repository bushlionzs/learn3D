

#ifndef _FalStaticImage_h_
#define _FalStaticImage_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIStaticImage.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardStaticImage : public StaticImage
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardStaticImage(const String& type, const String& name);

        
        ~FalagardStaticImage();

		
		Rect getUnclippedInnerRect(void) const;

    protected:
        
        virtual void populateRenderCache();
    };

    
    class FALAGARDBASE_API FalagardStaticImageFactory : public WindowFactory
    {
    public:
        FalagardStaticImageFactory(void) : WindowFactory(FalagardStaticImage::WidgetTypeName) { }
        ~FalagardStaticImageFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
