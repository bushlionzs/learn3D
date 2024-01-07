

#include "CEGUIExceptions.h"
#include "elements/CEGUITabControl.h"
#include "elements/CEGUITabButton.h"
#include "elements/CEGUIStatic.h"
#include "elements/CEGUIGUISheet.h"
#include "CEGUIFont.h"
#include "CEGUIWindowManager.h"


namespace CEGUI
{
const String TabControl::EventNamespace("TabControl");


TabControlProperties::TabHeight		            TabControl::d_tabHeightProperty;
TabControlProperties::AbsoluteTabHeight	        TabControl::d_absoluteTabHeightProperty;
TabControlProperties::RelativeTabHeight	        TabControl::d_relativeTabHeightProperty;
TabControlProperties::TabTextPadding		    TabControl::d_tabTextPaddingProperty;
TabControlProperties::AbsoluteTabTextPadding	TabControl::d_absoluteTabTextPaddingProperty;
TabControlProperties::RelativeTabTextPadding	TabControl::d_relativeTabTextPaddingProperty;



const String TabControl::EventSelectionChanged( (utf8*)"TabSelectionChanged" );

	

TabControl::TabControl(const String& type, const String& name)
	: Window(type, name),
    d_tabButtonPane(NULL),
    d_tabContentPane(NULL),
    d_nextTabIndex(0)
{
	addTabControlProperties();
    setRelativeTabHeight(0.05f);
    setAbsoluteTabTextPadding(5);
}



TabControl::~TabControl(void)
{
    
}


void TabControl::initialise(void)
{
	
	d_tabContentPane = createTabContentPane(getName() + "__auto_TabPane__");
    d_tabButtonPane = createTabButtonPane(getName() + "__auto_TabPane__Buttons");

	addChildWindow(d_tabContentPane);
    addChildWindow(d_tabButtonPane);

	performChildWindowLayout();
}

uint TabControl::getTabCount(void) const
{   
    return d_tabContentPane->getChildCount();
}

Window*	TabControl::getTabContents(const String& name) const
{
    return d_tabContentPane->getChild(name);
}

Window*	TabControl::getTabContents(uint ID) const
{
    return d_tabContentPane->getChild(ID);
}

Window*	TabControl::getTabContentsAtIndex(uint index) const
{
    return d_tabButtonIndexMap.find(index)->second->getTargetWindow();
}


bool TabControl::isTabContentsSelected(Window* wnd) const
{
	TabButton* button = getButtonForTabContents(wnd);
	return button->isSelected();
}


uint TabControl::getSelectedTabIndex() const
{
    uint index;
    TabButtonIndexMap::const_iterator i, iend;
    iend = d_tabButtonIndexMap.end();
    for (i = d_tabButtonIndexMap.begin(); i != iend; ++i)
    {
        
        TabButton* tb = i->second;
        if (tb->isSelected())
        {
            index = i->first;
			break;
        }
	}
	return index;
}


void TabControl::setSelectedTab(const String &name)
{
    
    Window* wnd = d_tabContentPane->getChild(name);

    selectTab_impl(wnd);
}

void TabControl::setSelectedTab(uint ID)
{
    
    Window* wnd = d_tabContentPane->getChild(ID);

    selectTab_impl(wnd);
}

void TabControl::setSelectedTabAtIndex(uint index)
{
	Window* wnd = getTabContentsAtIndex(index);
	selectTab_impl(wnd);
}

float TabControl::getTabHeight(void) const
{
    MetricsMode mode = getMetricsMode();
    if (mode == Relative)
    {
        return d_rel_tabHeight;
    }
    else
    {
        return d_abs_tabHeight;
    }
}


void TabControl::setRelativeTabHeight(float height)
{
    d_rel_tabHeight = height;
    d_abs_tabHeight = relativeToAbsoluteY(height);

    performChildWindowLayout();
}

void TabControl::setAbsoluteTabHeight(float height)
{
    d_abs_tabHeight = height;
    d_rel_tabHeight = absoluteToRelativeY(height);

    performChildWindowLayout();
}

void TabControl::setTabHeight(float height)
{
    if (getMetricsMode() == Relative)
    {
        setRelativeTabHeight(height);
    }
    else
    {
        setAbsoluteTabHeight(height);
    }
}

float TabControl::getTabTextPadding(void) const
{
    MetricsMode mode = getMetricsMode();
    if (mode == Relative)
    {
        return d_rel_tabPadding;
    }
    else
    {
        return d_abs_tabPadding;
    }
}


void TabControl::setRelativeTabTextPadding(float height)
{
    d_rel_tabPadding = height;
    d_abs_tabPadding = relativeToAbsoluteY(height);

    performChildWindowLayout();
}

void TabControl::setAbsoluteTabTextPadding(float height)
{
    d_abs_tabPadding = height;
    d_rel_tabPadding = absoluteToRelativeY(height);

    performChildWindowLayout();
}

void TabControl::setTabTextPadding(float height)
{
    if (getMetricsMode() == Relative)
    {
        setRelativeTabTextPadding(height);
    }
    else
    {
        setAbsoluteTabTextPadding(height);
    }
}


void TabControl::addTab(Window* wnd)
{
    
    addButtonForTabContent(wnd);
    
    d_tabContentPane->addChildWindow(wnd);
    
    if (getTabCount() == 1)
    {
        setSelectedTab(wnd->getName());
    }
    else
    {
        
        wnd->setVisible(false);
    }
    
    performChildWindowLayout();
    requestRedraw();
    
    wnd->subscribeEvent(Window::EventTextChanged, 
        Event::Subscriber(&TabControl::handleContentWindowTextChanged, this));

}

void TabControl::removeTab(const String& name)
{
    
    if (!d_tabContentPane->isChild(name))
        return;

    Window* wnd = d_tabContentPane->getChild(name);
    
    bool reselect = wnd->isVisible();
    
    d_tabContentPane->removeChildWindow(name);

    
    removeButtonForTabContent(wnd);

    if (reselect)
    {
        
        if (getTabCount() > 0)
        {
            setSelectedTab(d_tabContentPane->getChildAtIdx(0)->getName());
        }
    }

    performChildWindowLayout();

    requestRedraw();
}

void TabControl::removeTab(uint ID)
{
    
    if (!d_tabContentPane->isChild(ID))
        return;

    Window* wnd = d_tabContentPane->getChild(ID);
    
    bool reselect = wnd->isVisible();
    
    d_tabContentPane->removeChildWindow(ID);

    
    removeButtonForTabContent(wnd);

    if (reselect)
    {
        
        if (getTabCount() > 0)
        {
            setSelectedTab(d_tabContentPane->getChildAtIdx(0)->getName());
        }
    }

    performChildWindowLayout();

    requestRedraw();

}

void TabControl::addButtonForTabContent(Window* wnd)
{
    
    TabButton* tb = createTabButton(makeButtonName(wnd));
    
    tb->setFont(getFont());
    
    tb->setTargetWindow(wnd);
    
    tb->setTabIndex(d_nextTabIndex++);
    
    d_tabButtonIndexMap.insert(
        TabButtonIndexMap::value_type(tb->getTabIndex(), tb));
    
    d_tabButtonPane->addChildWindow(tb);
    
    tb->subscribeEvent(TabButton::EventClicked, 
        Event::Subscriber(&TabControl::handleTabButtonClicked, this));

}


TabButton* TabControl::getButtonForTabContents(Window* wnd) const
{
    TabButtonIndexMap::const_iterator i, iend;
    iend = d_tabButtonIndexMap.end();
    for (i = d_tabButtonIndexMap.begin(); i != iend; ++i)
    {
        
        TabButton* tb = i->second;
        Window* child = tb->getTargetWindow();
        if (child == wnd)
        {
			return tb;
        }
	}
	throw UnknownObjectException((utf8*)"TabControl::getButtonForTabContents - The Window object is not a tab contents.");
}

void TabControl::calculateTabButtonSizePosition(TabButton* btn, uint targetIndex)
{
    
    
    btn->setHeight(Relative, 1.0f);
    btn->setYPosition(Relative, 0.0f);
    
    if (targetIndex > 0)
    {
		TabButtonIndexMap::iterator iter = d_tabButtonIndexMap.begin();
		std::advance(iter, targetIndex - 1);
		Window* prevButton = iter->second;

		
        btn->setXPosition(Relative, 
            prevButton->getXPosition(Relative) 
            + prevButton->getWidth(Relative));
    }
    else
    {
        
        btn->setXPosition(Relative, 0);
    }
    
    const Font* fnt = btn->getFont();
    btn->setWidth(Absolute, 
        fnt->getTextExtent(btn->getText()) + getAbsoluteTabTextPadding()*2);
    btn->requestRedraw();
}

void TabControl::removeButtonForTabContent(Window* wnd)
{
    
    TabButton* tb = static_cast<TabButton*>(
        d_tabButtonPane->getChild(makeButtonName(wnd)));
    
    d_tabButtonIndexMap.erase(tb->getTabIndex());
    d_tabButtonPane->removeChildWindow(tb);
	
	WindowManager::getSingleton().destroyWindow(tb);
}

String TabControl::makeButtonName(Window* wnd)
{
    
    String buttonName = (utf8*)"__auto_btn";
    buttonName.append(wnd->getName());
    return buttonName;
}

void TabControl::selectTab_impl(Window* wnd)
{
    bool modified = false;
    bool foundSelected = false;
    
    TabButtonIndexMap::iterator i, iend;
    iend = d_tabButtonIndexMap.end();
    for (i = d_tabButtonIndexMap.begin(); i != iend; ++i)
    {
        
        TabButton* tb = i->second;
        Window* child = tb->getTargetWindow();
        
        bool selectThis = (child == wnd);
        
        modified = modified || (tb->isSelected() != selectThis);
        foundSelected = foundSelected || selectThis;
        
        tb->setSelected(selectThis);
        tb->setRightOfSelected(foundSelected);
        child->setVisible(selectThis);
    }
    
    if (modified)
    {
        WindowEventArgs args(this);
        onSelectionChanged(args);
    }
}

void TabControl::addTabControlProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( TabControl );
       CEGUI_ADD_STATICPROPERTY( &d_tabHeightProperty );
       CEGUI_ADD_STATICPROPERTY( &d_relativeTabHeightProperty );
       CEGUI_ADD_STATICPROPERTY( &d_absoluteTabHeightProperty );
       CEGUI_ADD_STATICPROPERTY( &d_tabTextPaddingProperty );
       CEGUI_ADD_STATICPROPERTY( &d_relativeTabTextPaddingProperty );
       CEGUI_ADD_STATICPROPERTY( &d_absoluteTabTextPaddingProperty );
	CEGUI_END_ADD_STATICPROPERTY
}

void TabControl::addChild_impl(Window* wnd)
{
    
    if (wnd->getName().find((const utf8*)"__auto_TabPane__") != String::npos)
    {
        
        Window::addChild_impl(wnd);
    }
    else
    {
        
        addTab(wnd);
    }
}

void TabControl::removeChild_impl(Window* wnd)
{
    
    if (!wnd) return;

    
    if (wnd->getName().find((const utf8*)"__auto_TabPane__") != String::npos)
    {
        
        Window::removeChild_impl(wnd);
    }
    else
    {
        
        removeTab(wnd->getName());
    }
}

void TabControl::onSelectionChanged(WindowEventArgs& e)
{
    requestRedraw();
    fireEvent(EventSelectionChanged, e, EventNamespace);
}

void TabControl::onFontChanged(WindowEventArgs& e)
{
    
    TabButtonIndexMap::iterator i, iend;
    iend = d_tabButtonIndexMap.end();
    for (i = d_tabButtonIndexMap.end(); i != iend; ++i)
    {
        i->second->setFont(getFont());
    }
}


void TabControl::performChildWindowLayout()
{
    Window::performChildWindowLayout();

    if (d_tabButtonPane)
    {
        
        d_tabButtonPane->setSize(Relative, Size(1.0f, d_rel_tabHeight) );
        d_tabButtonPane->setPosition(Relative, Point(0.0f, 0.0f) );
        
        TabButtonIndexMap::iterator i, iend;
        iend = d_tabButtonIndexMap.end();
        uint x = 0;
        for (i = d_tabButtonIndexMap.begin(); i != iend; ++i, ++x)
        {
            TabButton* btn = i->second;
            calculateTabButtonSizePosition(btn, x);
        }
    }
    if (d_tabContentPane)
    {
        
        d_tabContentPane->setSize(Relative, Size(1.0f, 1.0f - d_rel_tabHeight) );
        d_tabContentPane->setPosition(Relative, Point(0.0f, d_rel_tabHeight) );
    }

}

Window*	TabControl::createTabButtonPane(const String& name) const
{
	return WindowManager::getSingleton().createWindow(GUISheet::WidgetTypeName, name);
}

bool TabControl::handleContentWindowTextChanged(const EventArgs& args)
{
    
    const WindowEventArgs& wargs = static_cast<const WindowEventArgs&>(args);
    Window* tabButton = d_tabButtonPane->getChild(
        makeButtonName(wargs.window));
    tabButton->setText(wargs.window->getText());
    
    performChildWindowLayout();
	requestRedraw();

	return true;
}

bool TabControl::handleTabButtonClicked(const EventArgs& args)
{
    const WindowEventArgs& wargs = static_cast<const WindowEventArgs&>(args);
    TabButton* tabButton = static_cast<TabButton*>(wargs.window);
    setSelectedTab(tabButton->getTargetWindow()->getName());

	return true;
}

int TabControl::writeChildWindowsXML(OutStream& out_stream) const
{
    int childOutputCount = Window::writeChildWindowsXML(out_stream);

    
    
    
    for (uint i = 0; i < getTabCount(); ++i)
    {
        getTabContentsAtIndex(i)->writeXMLToStream(out_stream);
        ++childOutputCount;
    }

    return childOutputCount;
}

} 
