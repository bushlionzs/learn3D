

#ifndef _FalFrameWindow_h_
#define _FalFrameWindow_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIFrameWindow.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardFrameWindow : public FrameWindow
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardFrameWindow(const String& type, const String& name);

        
        ~FalagardFrameWindow();

        
        Rect getUnclippedInnerRect(void) const;

    protected:
        
        void populateRenderCache();
        Titlebar* createTitlebar(const String& name) const;
        PushButton* createCloseButton(const String& name) const;
    };

    
    class FALAGARDBASE_API FalagardFrameWindowFactory : public WindowFactory
    {
    public:
        FalagardFrameWindowFactory(void) : WindowFactory(FalagardFrameWindow::WidgetTypeName) { }
        ~FalagardFrameWindowFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
