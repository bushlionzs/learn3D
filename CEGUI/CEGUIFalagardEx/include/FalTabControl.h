

#ifndef _FalTabControl_h_
#define _FalTabControl_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUITabControl.h"
#include "FalTabControlProperties.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardTabControl : public TabControl
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardTabControl(const String& type, const String& name);

        
        ~FalagardTabControl();

        const String& getTabButtonType() const;
        void setTabButtonType(const String& type);

    protected:
        
        void populateRenderCache();
        TabPane* createTabContentPane(const String& name) const;
        TabButton* createTabButton(const String& name) const;
        Window* createTabButtonPane(const String& name) const;

        
        String  d_tabButtonType;

        
        static FalagardTabControlProperties::TabButtonType d_tabButtonTypeProperty;
    };

    
    class FALAGARDBASE_API FalagardTabControlFactory : public WindowFactory
    {
    public:
        FalagardTabControlFactory(void) : WindowFactory(FalagardTabControl::WidgetTypeName) { }
        ~FalagardTabControlFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
