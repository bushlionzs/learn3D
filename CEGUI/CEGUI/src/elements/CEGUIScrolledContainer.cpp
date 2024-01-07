

#include "elements/CEGUIScrolledContainer.h"


namespace CEGUI
{   
    
    
    
    const String ScrolledContainer::WidgetTypeName("ScrolledContainer");
    
    const String ScrolledContainer::EventNamespace("ScrolledContainer");
    const String ScrolledContainer::EventContentChanged("ContentChanged");
    const String ScrolledContainer::EventAutoSizeSettingChanged("AutoSizeSettingChanged");
    
    ScrolledContainerProperties::ContentPaneAutoSized ScrolledContainer::d_autoSizedProperty;
    ScrolledContainerProperties::ContentArea          ScrolledContainer::d_contentAreaProperty;
    ScrolledContainerProperties::ChildExtentsArea     ScrolledContainer::d_childExtentsAreaProperty;
    
    
    ScrolledContainer::ScrolledContainer(const String& type, const String& name) :
        Window(type, name),
        d_contentArea(0, 0, 0, 0),
        d_autosizePane(true)
    {
        addScrolledContainerProperties();
    }

    ScrolledContainer::~ScrolledContainer(void)
    {
    }

    bool ScrolledContainer::isContentPaneAutoSized(void) const
    {
        return d_autosizePane;
    }

    void ScrolledContainer::setContentPaneAutoSized(bool setting)
    {
        if (d_autosizePane != setting)
        {
            d_autosizePane = setting;

            
            WindowEventArgs args1(this);
            onAutoSizeSettingChanged(args1);
        }
    }

    const Rect& ScrolledContainer::getContentArea(void) const
    {
        return d_contentArea;
    }

    void ScrolledContainer::setContentArea(const Rect& area)
    {
        if (!d_autosizePane)
        {
            d_contentArea = area;
            
            
            WindowEventArgs args(this);
            onContentChanged(args);
       }

    }

    Rect ScrolledContainer::getChildExtentsArea(void) const
    {
        uint childCount = getChildCount();

        
        if (childCount != 0)
        {
            Window* wnd = getChildAtIdx(0);
            Rect extents(wnd->getAbsoluteRect());

            
            for (uint i = 1; i < childCount; ++i)
            {
                wnd = getChildAtIdx(i);
                Rect area(wnd->getAbsoluteRect());

                if (area.d_left < extents.d_left)
                    extents.d_left = area.d_left;

                if (area.d_top < extents.d_top)
                    extents.d_top = area.d_top;

                if (area.d_right > extents.d_right)
                    extents.d_right = area.d_right;

                if (area.d_bottom > extents.d_bottom)
                    extents.d_bottom = area.d_bottom;
            }

            return extents;
        }
        else
        {
            return Rect(0, 0, 0, 0);
        }
    }

    void ScrolledContainer::onContentChanged(WindowEventArgs& e)
    {
        if (d_autosizePane)
        {
            d_contentArea = getChildExtentsArea();
        }

        fireEvent(EventContentChanged, e, EventNamespace);
    }

    void ScrolledContainer::onAutoSizeSettingChanged(WindowEventArgs& e)
    {
        fireEvent(EventAutoSizeSettingChanged, e, EventNamespace);

        if (d_autosizePane)
        {
            WindowEventArgs args(this);
            onContentChanged(args);
        }
    }

    bool ScrolledContainer::handleChildSized(const EventArgs& e)
    {
        
        WindowEventArgs args(this);
        onContentChanged(args);
        return true;
    }

    bool ScrolledContainer::handleChildMoved(const EventArgs& e)
    {
        
        WindowEventArgs args(this);
        onContentChanged(args);
        return true;
    }

    Rect ScrolledContainer::getUnclippedInnerRect(void) const
    {
        
        
        return d_parent ?
            d_parent->getUnclippedInnerRect() :
            System::getSingleton().getRenderer()->getRect();
    }

    void ScrolledContainer::onChildAdded(WindowEventArgs& e)
    {
        Window::onChildAdded(e);

        
        d_eventConnections.insert(std::make_pair(e.window,
            e.window->subscribeEvent(Window::EventSized,
                Event::Subscriber(&ScrolledContainer::handleChildSized, this))));
        d_eventConnections.insert(std::make_pair(e.window,
            e.window->subscribeEvent(Window::EventMoved,
                Event::Subscriber(&ScrolledContainer::handleChildMoved, this))));

        
        WindowEventArgs args(this);
        onContentChanged(args);
    }

    void ScrolledContainer::onChildRemoved(WindowEventArgs& e)
    {
        Window::onChildRemoved(e);

        
        ConnectionTracker::iterator conn;
        while ((conn = d_eventConnections.find(e.window)) != d_eventConnections.end())
        {
            conn->second->disconnect();
            d_eventConnections.erase(conn);
        }

        
        WindowEventArgs args(this);
        onContentChanged(args);
    }

    void ScrolledContainer::onParentSized(WindowEventArgs& e)
    {
        Window::onParentSized(e);

        
        WindowEventArgs args(this);
        onContentChanged(args);
    }

    void ScrolledContainer::addScrolledContainerProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( ScrolledContainer );
           CEGUI_ADD_STATICPROPERTY( &d_autoSizedProperty );
           CEGUI_ADD_STATICPROPERTY( &d_contentAreaProperty );
           CEGUI_ADD_STATICPROPERTY( &d_childExtentsAreaProperty );
	CEGUI_END_ADD_STATICPROPERTY
	}

} 
