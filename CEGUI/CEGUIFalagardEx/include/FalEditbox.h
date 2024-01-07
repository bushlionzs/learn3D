

#ifndef _FalEditbox_h_
#define _FalEditbox_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIEditbox.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardEditbox : public Editbox
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardEditbox(const String& type, const String& name);

        
        ~FalagardEditbox();

    protected:
        
        void populateRenderCache();
        size_t getTextIndexFromPosition(const Point& pt) const;

        
        float	d_lastTextOffset;		
    };

    
    class FALAGARDBASE_API FalagardEditboxFactory : public WindowFactory
    {
    public:
        FalagardEditboxFactory(void) : WindowFactory(FalagardEditbox::WidgetTypeName) { }
        ~FalagardEditboxFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
