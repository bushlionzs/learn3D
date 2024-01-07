

#ifndef _CEGUITabControl_h_
#define _CEGUITabControl_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUITabControlProperties.h"
#include "elements/CEGUITabPane.h"
#include <vector>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

    
    class TabButton;


class CEGUIEXPORT TabControl : public Window
{
public:
	static const String EventNamespace;				


	
	
	static const String EventSelectionChanged;			


	
	
	uint	getTabCount(void) const;


    
    void    setSelectedTab(const String &name);

    
    void    setSelectedTab(uint ID);

    
    void    setSelectedTabAtIndex(uint index);

    
    Window*	getTabContentsAtIndex(uint index) const;

    
    Window*	getTabContents(const String& name) const;

    
    Window*	getTabContents(uint ID) const;

    
    bool	isTabContentsSelected(Window* wnd) const;

    
    uint	getSelectedTabIndex() const;
	
    
    float getRelativeTabHeight(void) const { return d_rel_tabHeight; }
    
    float getAbsoluteTabHeight(void) const { return d_abs_tabHeight; }
    
    float getTabHeight(void) const;
    
    float getTabTextPadding(void) const;
    
    float getRelativeTabTextPadding(void) const { return d_rel_tabPadding; }
    
    float getAbsoluteTabTextPadding(void) const { return d_abs_tabPadding; }


    
	
	virtual void	initialise(void);

    
    void setRelativeTabHeight(float height);
    
    void setAbsoluteTabHeight(float height);
    
    void setTabHeight(float height);

    
    void setTabTextPadding(float);
    
    void setRelativeTabTextPadding(float);
    
    void setAbsoluteTabTextPadding(float);
    
    void addTab(Window* wnd);
    
    void removeTab(const String& name);
    
    void removeTab(uint ID);


	
	
	TabControl(const String& type, const String& name);


	
	virtual ~TabControl(void);


protected:

	
    
    virtual	void	drawSelf(float z) {  }

    
    virtual void addButtonForTabContent(Window* wnd);
    
    virtual void removeButtonForTabContent(Window* wnd);
    
	TabButton* getButtonForTabContents(Window* wnd) const;
    
    String makeButtonName(Window* wnd);
    
    
    virtual void selectTab_impl(Window* wnd);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"TabControl")	return true;
		return Window::testClassName_impl(class_name);
	}

	void performChildWindowLayout();
    int writeChildWindowsXML(OutStream& out_stream) const;

	

	
	virtual	void	onSelectionChanged(WindowEventArgs& e);

	
	virtual void	onFontChanged(WindowEventArgs& e);

	
    Window*     d_tabButtonPane;    
    TabPane*    d_tabContentPane;   
    float       d_abs_tabHeight;    
    float       d_rel_tabHeight;    
    float       d_abs_tabPadding;    
    float       d_rel_tabPadding;    
    uint        d_nextTabIndex;     
    typedef std::map<uint, TabButton*> TabButtonIndexMap; 
    TabButtonIndexMap d_tabButtonIndexMap;  
    
    
    virtual TabPane*	createTabContentPane(const String& name) const		= 0;

    
    virtual Window*	createTabButtonPane(const String& name) const;

    
    virtual TabButton*	createTabButton(const String& name) const		= 0;

    
    void calculateTabButtonSizePosition(TabButton* btn, uint targetIndex);

protected:
	
	static TabControlProperties::TabHeight			d_tabHeightProperty;
    static TabControlProperties::AbsoluteTabHeight	d_absoluteTabHeightProperty;
    static TabControlProperties::RelativeTabHeight	d_relativeTabHeightProperty;

    static TabControlProperties::TabTextPadding			d_tabTextPaddingProperty;
    static TabControlProperties::AbsoluteTabTextPadding	d_absoluteTabTextPaddingProperty;
    static TabControlProperties::RelativeTabTextPadding	d_relativeTabTextPaddingProperty;
	
	void	addTabControlProperties(void);

    void    addChild_impl(Window* wnd);
    void    removeChild_impl(Window* wnd);

    
    bool handleContentWindowTextChanged(const EventArgs& args);
    bool handleTabButtonClicked(const EventArgs& args);
};



} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
