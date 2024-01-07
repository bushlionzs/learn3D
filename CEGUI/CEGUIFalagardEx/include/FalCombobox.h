

#ifndef _FalCombobox_h_
#define _FalCombobox_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUICombobox.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardCombobox : public Combobox
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardCombobox(const String& type, const String& name);

        
        ~FalagardCombobox();

    protected:
        
        void populateRenderCache();
        Editbox* createEditbox(const String& name) const;
        PushButton* createPushButton(const String& name) const;
        ComboDropList* createDropList(const String& name) const;
    };

    
    class FALAGARDBASE_API FalagardComboboxFactory : public WindowFactory
    {
    public:
        FalagardComboboxFactory(void) : WindowFactory(FalagardCombobox::WidgetTypeName) { }
        ~FalagardComboboxFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
