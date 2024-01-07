

#ifndef _FalSystemButton_h_
#define _FalSystemButton_h_

#include "FalModule.h"
#include "FalButton.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardSystemButton : public FalagardButton
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardSystemButton(const String& type, const String& name);

        
        ~FalagardSystemButton();

        Rect getPixelRect(void) const;
    };

    
    class FALAGARDBASE_API FalagardSystemButtonFactory : public WindowFactory
    {
    public:
        FalagardSystemButtonFactory(void) : WindowFactory(FalagardSystemButton::WidgetTypeName) { }
        ~FalagardSystemButtonFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
