

#ifndef _FalMultiLineEditbox_h_
#define _FalMultiLineEditbox_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIMultiLineEditbox.h"
#include "FalMultiLineEditboxProperties.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
   
    class FALAGARDBASE_API FalagardMultiLineEditbox : public MultiLineEditbox
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardMultiLineEditbox(const String& type, const String& name);

        
        ~FalagardMultiLineEditbox();

        const Image* getSelectionBrushImage() const;
        void setSelectionBrushImage(const Image* image);

    protected:
        
        Scrollbar* createVertScrollbar(const String& name) const;
        Scrollbar* createHorzScrollbar(const String& name) const;
        void cacheEditboxBaseImagery();
        virtual void cacheCaratImagery(const Rect& textArea);
        Rect getTextRenderArea(void) const;

        
        static FalagardMultiLineEditboxProperties::SelectionBrushImage d_selectionBrushProperty;
    };

    
    class FALAGARDBASE_API FalagardMultiLineEditboxFactory : public WindowFactory
    {
    public:
        FalagardMultiLineEditboxFactory(void) : WindowFactory(FalagardMultiLineEditbox::WidgetTypeName) { }
        ~FalagardMultiLineEditboxFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
