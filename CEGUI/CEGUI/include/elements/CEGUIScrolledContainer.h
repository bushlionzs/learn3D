

#ifndef _CEGUIScrolledContainer_h_
#define _CEGUIScrolledContainer_h_

#include "CEGUIWindow.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIScrolledContainerProperties.h"
#include <map>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class CEGUIEXPORT ScrolledContainer : public Window
    {
    public:
        
        static const String WidgetTypeName;     
        static const String EventNamespace;     
        static const String EventContentChanged;    
        static const String EventAutoSizeSettingChanged;    

        
        
        ScrolledContainer(const String& type, const String& name);

        
        ~ScrolledContainer(void);

        
        
        bool isContentPaneAutoSized(void) const;

        
        void setContentPaneAutoSized(bool setting);

        
        const Rect& getContentArea(void) const;

        
        void setContentArea(const Rect& area);

        
        Rect getChildExtentsArea(void) const;

    protected:
        

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"ScrolledContainer")	return true;
			return Window::testClassName_impl(class_name);
		}

        
        void drawSelf(float z) {};

        
        
        virtual void onContentChanged(WindowEventArgs& e);

        
        virtual void onAutoSizeSettingChanged(WindowEventArgs& e);

        
        
        bool handleChildSized(const EventArgs& e);

        
        bool handleChildMoved(const EventArgs& e);

        
        Rect getUnclippedInnerRect(void) const;
        void onChildAdded(WindowEventArgs& e);
        void onChildRemoved(WindowEventArgs& e);
        void onParentSized(WindowEventArgs& e);

        
        typedef std::multimap<Window*, Event::Connection>  ConnectionTracker;
        ConnectionTracker d_eventConnections;   
        Rect d_contentArea;     
        bool d_autosizePane;    

    private:
	    
	    static ScrolledContainerProperties::ContentPaneAutoSized	d_autoSizedProperty;
	    static ScrolledContainerProperties::ContentArea             d_contentAreaProperty;
	    static ScrolledContainerProperties::ChildExtentsArea        d_childExtentsAreaProperty;

	    
	    void addScrolledContainerProperties(void);
    };

    
    class ScrolledContainerFactory : public WindowFactory
    {
    public:
        ScrolledContainerFactory(void) : WindowFactory(ScrolledContainer::WidgetTypeName) { }
        ~ScrolledContainerFactory(void){}

        Window* createWindow(const String& name)
        {
            ScrolledContainer* wnd = new ScrolledContainer(d_type, name);
            return wnd;
        }

        void destroyWindow(Window* window)
        {
            if (window->getType() == d_type)
                delete window;
        }

    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
