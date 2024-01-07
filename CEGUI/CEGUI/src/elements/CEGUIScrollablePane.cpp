

#include "elements/CEGUIScrollablePane.h"
#include "elements/CEGUIScrolledContainer.h"
#include "elements/CEGUIScrollbar.h"
#include "CEGUIWindowManager.h"
#include <math.h>


namespace CEGUI
{
    
    
    const String ScrollablePane::EventNamespace("ScrollablePane");
    const String ScrollablePane::EventContentPaneChanged("ContentPaneChanged");
    const String ScrollablePane::EventVertScrollbarModeChanged("VertScrollbarModeChanged");
    const String ScrollablePane::EventHorzScrollbarModeChanged("HorzScrollbarModeChanged");
    const String ScrollablePane::EventAutoSizeSettingChanged("AutoSizeSettingChanged");
    const String ScrollablePane::EventContentPaneScrolled("ContentPaneScrolled");
    
    ScrollablePaneProperties::ForceHorzScrollbar   ScrollablePane::d_horzScrollbarProperty;
    ScrollablePaneProperties::ForceVertScrollbar   ScrollablePane::d_vertScrollbarProperty;
    ScrollablePaneProperties::ContentPaneAutoSized ScrollablePane::d_autoSizedProperty;
    ScrollablePaneProperties::ContentArea          ScrollablePane::d_contentAreaProperty;
    ScrollablePaneProperties::HorzStepSize         ScrollablePane::d_horzStepProperty;
    ScrollablePaneProperties::HorzOverlapSize      ScrollablePane::d_horzOverlapProperty;
    ScrollablePaneProperties::HorzScrollPosition   ScrollablePane::d_horzScrollPositionProperty;
    ScrollablePaneProperties::VertStepSize         ScrollablePane::d_vertStepProperty;
    ScrollablePaneProperties::VertOverlapSize      ScrollablePane::d_vertOverlapProperty;
    ScrollablePaneProperties::VertScrollPosition   ScrollablePane::d_vertScrollPositionProperty;
    

    ScrollablePane::ScrollablePane(const String& type, const String& name) :
        Window(type, name),
        d_forceVertScroll(false),
        d_forceHorzScroll(false),
        d_contentRect(0, 0, 0, 0),
        d_vertStep(0.1f),
        d_vertOverlap(0.01f),
        d_horzStep(0.1f),
        d_horzOverlap(0.01f),
        d_vertScrollbar(0),
        d_horzScrollbar(0),
        d_container(0)
    {
        addScrollablePaneProperties();
    }

    ScrollablePane::~ScrollablePane(void)
    {
    }

    const ScrolledContainer* ScrollablePane::getContentPane(void) const
    {
        assert (d_container != 0);
        return d_container;
    }

    bool ScrollablePane::isVertScrollbarAlwaysShown(void) const
    {
        return d_forceVertScroll;
    }

    void ScrollablePane::setShowVertScrollbar(bool setting)
    {
        if (d_forceVertScroll != setting)
        {
            d_forceVertScroll = setting;

            configureScrollbars();
            WindowEventArgs args(this);
            onVertScrollbarModeChanged(args);
        }
    }

    bool ScrollablePane::isHorzScrollbarAlwaysShown(void) const
    {
        return d_forceHorzScroll;
    }

    void ScrollablePane::setShowHorzScrollbar(bool setting)
    {
        if (d_forceHorzScroll != setting)
        {
            d_forceHorzScroll = setting;

            configureScrollbars();
            WindowEventArgs args(this);
            onHorzScrollbarModeChanged(args);
        }
    }

    bool ScrollablePane::isContentPaneAutoSized(void) const
    {
        assert(d_container != 0);
        return d_container->isContentPaneAutoSized();
    }

    void ScrollablePane::setContentPaneAutoSized(bool setting)
    {
        assert(d_container != 0);
        d_container->setContentPaneAutoSized(setting);
    }

    const Rect& ScrollablePane::getContentPaneArea(void) const
    {
        assert(d_container != 0);
        return d_container->getContentArea();
    }

    void ScrollablePane::setContentPaneArea(const Rect& area)
    {
        assert(d_container != 0);
        d_container->setContentArea(area);
    }

    float ScrollablePane::getHorizontalStepSize(void) const
    {
        return d_horzStep;
    }

    void ScrollablePane::setHorizontalStepSize(float step)
    {
        d_horzStep = step;
        configureScrollbars();
    }

    float ScrollablePane::getHorizontalOverlapSize(void) const
    {
        return d_horzOverlap;
    }

    void ScrollablePane::setHorizontalOverlapSize(float overlap)
    {
        d_horzOverlap = overlap;
        configureScrollbars();
    }

    float ScrollablePane::getHorizontalScrollPosition(void) const
    {
        assert(d_horzScrollbar != 0);
        float docSz = d_horzScrollbar->getDocumentSize();
        return (docSz != 0) ? d_horzScrollbar->getScrollPosition() / docSz : 0.0f;
    }

    void ScrollablePane::setHorizontalScrollPosition(float position)
    {
        assert(d_horzScrollbar != 0);
        d_horzScrollbar->setScrollPosition(d_horzScrollbar->getDocumentSize() * position);
    }

    float ScrollablePane::getVerticalStepSize(void) const
    {
        return d_vertStep;
    }

    void ScrollablePane::setVerticalStepSize(float step)
    {
        d_vertStep = step;
        configureScrollbars();
    }

    float ScrollablePane::getVerticalOverlapSize(void) const
    {
        return d_vertOverlap;
    }

    void ScrollablePane::setVerticalOverlapSize(float overlap)
    {
        d_vertOverlap = overlap;
        configureScrollbars();
    }

    float ScrollablePane::getVerticalScrollPosition(void) const
    {
        assert(d_vertScrollbar != 0);
        float docSz = d_vertScrollbar->getDocumentSize();
        return (docSz != 0) ? d_vertScrollbar->getScrollPosition() / docSz : 0.0f;
    }

    void ScrollablePane::setVerticalScrollPosition(float position)
    {
        assert(d_vertScrollbar != 0);
        d_vertScrollbar->setScrollPosition(d_vertScrollbar->getDocumentSize() * position);
    }

    void ScrollablePane::initialise(void)
    {
        String widgetName;
        
        widgetName = d_name + "__auto_hscrollbar__";
        d_horzScrollbar = createHorizontalScrollbar(widgetName);
        
        assert(d_horzScrollbar != 0);
        assert(d_horzScrollbar->getName() == widgetName);

        
        widgetName = d_name + "__auto_vscrollbar__";
        d_vertScrollbar = createVerticalScrollbar(widgetName);
        
        assert(d_vertScrollbar != 0);
        assert(d_vertScrollbar->getName() == widgetName);

        
        d_container = 
            static_cast<ScrolledContainer*>(WindowManager::getSingleton().createWindow(
                ScrolledContainer::WidgetTypeName, d_name + "__auto_container__"));

        
        addChildWindow(d_horzScrollbar);
        addChildWindow(d_vertScrollbar);
        addChildWindow(d_container);

        
        d_horzScrollbar->setAlwaysOnTop(true);
        d_vertScrollbar->setAlwaysOnTop(true);
        
        
        d_container->setSize(Relative, Size(1.0f, 1.0f));

        
        d_vertScrollbar->subscribeEvent(
            Scrollbar::EventScrollPositionChanged,
            Event::Subscriber(&ScrollablePane::handleScrollChange, this));
        d_horzScrollbar->subscribeEvent(
            Scrollbar::EventScrollPositionChanged,
            Event::Subscriber(&ScrollablePane::handleScrollChange, this));
        d_container->subscribeEvent(
            ScrolledContainer::EventContentChanged,
            Event::Subscriber(&ScrollablePane::handleContentAreaChange, this));
        d_container->subscribeEvent(
            ScrolledContainer::EventAutoSizeSettingChanged,
            Event::Subscriber(&ScrollablePane::handleAutoSizePaneChanged, this));

        
        configureScrollbars();
    }

    void ScrollablePane::configureScrollbars(void)
    {
        
        assert(d_container != 0);
        assert(d_vertScrollbar != 0);
        assert(d_horzScrollbar != 0);

        
        d_vertScrollbar->setVisible(isVertScrollbarNeeded());
        d_horzScrollbar->setVisible(isHorzScrollbarNeeded());

        
        
        if (d_horzScrollbar->isVisible())
        {
            d_vertScrollbar->setVisible(isVertScrollbarNeeded());
        }

        performChildWindowLayout();

        
        Rect viewableArea(getViewableArea());
		if( d_vertScrollbar )
		{
			
			d_vertScrollbar->setDocumentSize(fabsf(d_contentRect.getHeight()));
			d_vertScrollbar->setPageSize(viewableArea.getHeight());
			d_vertScrollbar->setStepSize(std::max(1.0f, viewableArea.getHeight() * d_vertStep));
			d_vertScrollbar->setOverlapSize(std::max(1.0f, viewableArea.getHeight() * d_vertOverlap));
			d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition());
		}

		if( d_horzScrollbar )
		{
				
			d_horzScrollbar->setDocumentSize(fabsf(d_contentRect.getWidth()));
			d_horzScrollbar->setPageSize(viewableArea.getWidth());
			d_horzScrollbar->setStepSize(std::max(1.0f, viewableArea.getWidth() * d_horzStep));
			d_horzScrollbar->setOverlapSize(std::max(1.0f, viewableArea.getWidth() * d_horzOverlap));
			d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition());	
		}
    }

    bool ScrollablePane::isHorzScrollbarNeeded(void) const
    {
        assert(d_container != 0);

        return ((fabs(d_contentRect.getWidth()) > getViewableArea().getWidth()) || d_forceHorzScroll);
    }

    bool ScrollablePane::isVertScrollbarNeeded(void) const
    {
        assert(d_container != 0);

        return ((fabs(d_contentRect.getHeight()) > getViewableArea().getHeight()) || d_forceVertScroll);
    }

    void ScrollablePane::updateContainerPosition(void)
    {
        assert(d_container != 0);
        assert(d_horzScrollbar != 0);
        assert(d_vertScrollbar != 0);
		float fhorz = 0;
		float fvert = 0;
		if( d_horzScrollbar )
			fhorz = d_horzScrollbar->getScrollPosition();
		if( d_vertScrollbar )
			fvert = d_vertScrollbar->getScrollPosition();
        
        
        Point basePos(-fhorz, -fvert);

        
        
        Point bias(d_contentRect.d_left, d_contentRect.d_top);

        
        
        d_container->setPosition(Absolute, basePos - bias);
    }

    void ScrollablePane::onContentPaneChanged(WindowEventArgs& e)
    {
        fireEvent(EventContentPaneChanged, e, EventNamespace);
    }

    void ScrollablePane::onVertScrollbarModeChanged(WindowEventArgs& e)
    {
        fireEvent(EventVertScrollbarModeChanged, e, EventNamespace);
    }

    void ScrollablePane::onHorzScrollbarModeChanged(WindowEventArgs& e)
    {
        fireEvent(EventHorzScrollbarModeChanged, e, EventNamespace);
    }

    void ScrollablePane::onAutoSizeSettingChanged(WindowEventArgs& e)
    {
        fireEvent(EventAutoSizeSettingChanged, e, EventNamespace);
    }

    void ScrollablePane::onContentPaneScrolled(WindowEventArgs& e)
    {
        updateContainerPosition();
        fireEvent(EventContentPaneScrolled, e, EventNamespace);
    }

    bool ScrollablePane::handleScrollChange(const EventArgs& e)
    {
        WindowEventArgs args(this);
        onContentPaneScrolled(args);
        return true;
    }

    bool ScrollablePane::handleContentAreaChange(const EventArgs& e)
    {
        assert(d_container != 0);
        assert(d_horzScrollbar != 0);
        assert(d_vertScrollbar != 0);

        
        Rect contentArea(d_container->getContentArea());

        
        float xChange = contentArea.d_left - d_contentRect.d_left;
        float yChange = contentArea.d_top - d_contentRect.d_top;

        
        d_contentRect = contentArea;

        configureScrollbars();

        
        d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition() - xChange);
        d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition() - yChange);

        
        
        
        if (xChange || yChange)
        {
            updateContainerPosition();
        }
    
        
        WindowEventArgs args(this);
        onContentPaneChanged(args);

        return true;
    }

    bool ScrollablePane::handleAutoSizePaneChanged(const EventArgs& e)
    {
        
        WindowEventArgs args(this);
        fireEvent(EventAutoSizeSettingChanged, args, EventNamespace);
        return args.handled;
    }

    void ScrollablePane::addChild_impl(Window* wnd)
    {
        
        assert(wnd != 0);

        
        if (wnd->getName().find("__auto_") != String::npos)
        {
            
            Window::addChild_impl(wnd);
        }
        
        else
        {
            
            assert(d_container != 0);
            d_container->addChildWindow(wnd);
        }
    }

    void ScrollablePane::removeChild_impl(Window* wnd)
    {
        
        assert(wnd != 0);

        
        if (wnd->getName().find("__auto_") != String::npos)
        {
            
            Window::removeChild_impl(wnd);
        }
        
        else
        {
            
            assert(d_container != 0);
            d_container->removeChildWindow(wnd);
        }
    }

    void ScrollablePane::onSized(WindowEventArgs& e)
    {
        Window::onSized(e);
        configureScrollbars();
        updateContainerPosition();

        e.handled = true;
    }

    void ScrollablePane::onMouseWheel(MouseEventArgs& e)
    {
        
        Window::onMouseWheel(e);

        if (d_vertScrollbar->isVisible() && (d_vertScrollbar->getDocumentSize() > d_vertScrollbar->getPageSize()))
        {
            d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition() + d_vertScrollbar->getStepSize() * -e.wheelChange);
        }
        else if (d_horzScrollbar->isVisible() && (d_horzScrollbar->getDocumentSize() > d_horzScrollbar->getPageSize()))
        {
            d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition() + d_horzScrollbar->getStepSize() * -e.wheelChange);
        }

        e.handled = true;
    }

    void ScrollablePane::addScrollablePaneProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( ScrollablePane );
           CEGUI_ADD_STATICPROPERTY( &d_horzScrollbarProperty );
           CEGUI_ADD_STATICPROPERTY( &d_vertScrollbarProperty );
           CEGUI_ADD_STATICPROPERTY( &d_autoSizedProperty );
           CEGUI_ADD_STATICPROPERTY( &d_contentAreaProperty );
           CEGUI_ADD_STATICPROPERTY( &d_horzStepProperty );
           CEGUI_ADD_STATICPROPERTY( &d_horzOverlapProperty );
           CEGUI_ADD_STATICPROPERTY( &d_horzScrollPositionProperty );
           CEGUI_ADD_STATICPROPERTY( &d_vertStepProperty );
           CEGUI_ADD_STATICPROPERTY( &d_vertOverlapProperty );
           CEGUI_ADD_STATICPROPERTY( &d_vertScrollPositionProperty );
	CEGUI_END_ADD_STATICPROPERTY
	}

} 
