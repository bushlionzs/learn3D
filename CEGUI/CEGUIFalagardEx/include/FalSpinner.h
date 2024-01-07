

#ifndef _FalSpinner_h_
#define _FalSpinner_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUISpinner.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardSpinner : public Spinner
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardSpinner(const String& type, const String& name);

        
        ~FalagardSpinner();

    protected:
        
        void populateRenderCache();
        PushButton* createIncreaseButton(const String& name) const;
        PushButton* createDecreaseButton(const String& name) const;
        Editbox* createEditbox(const String& name) const;

    };

    
    class FALAGARDBASE_API FalagardSpinnerFactory : public WindowFactory
    {
    public:
        FalagardSpinnerFactory(void) : WindowFactory(FalagardSpinner::WidgetTypeName) { }
        ~FalagardSpinnerFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
