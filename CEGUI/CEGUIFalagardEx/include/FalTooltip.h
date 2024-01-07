

#ifndef _FalTooltip_h_
#define _FalTooltip_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUITooltip.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardTooltip : public Tooltip
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardTooltip(const String& type, const String& name);

        
        ~FalagardTooltip();

    protected:
        
        void populateRenderCache();
        Size getTextSize() const;

    };

    
    class FALAGARDBASE_API FalagardTooltipFactory : public WindowFactory
    {
    public:
        FalagardTooltipFactory(void) : WindowFactory(FalagardTooltip::WidgetTypeName) { }
        ~FalagardTooltipFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
