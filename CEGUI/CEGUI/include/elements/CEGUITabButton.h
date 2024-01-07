

#ifndef _CEGUITabButton_h_
#define _CEGUITabButton_h_

#include "CEGUIBase.h"
#include "elements/CEGUIButtonBase.h"


namespace CEGUI
{

class CEGUIEXPORT TabButton : public ButtonBase
{
public:
	static const String EventNamespace;				


	
	
	static const String EventClicked;					

	
	
	TabButton(const String& type, const String& name);


	
	virtual ~TabButton(void);

    
    virtual void setSelected(bool selected) { d_selected = selected; requestRedraw(); }

    
    virtual void setRightOfSelected(bool isRight) { d_rightOfSelected = isRight; requestRedraw(); }

    
    bool isSelected(void) const { return d_selected; }


    
    void setTargetWindow(Window* wnd);
    
    Window* getTargetWindow(void) { return d_targetWindow; }

    
    void setTabIndex(uint idx) { d_tabIndex = idx; }

    
    uint getTabIndex(void) { return d_tabIndex; }
protected:
    
    bool    d_selected;             
    bool    d_rightOfSelected;      
    Window* d_targetWindow;         
    uint    d_tabIndex;             
	
	
	virtual void	onClicked(WindowEventArgs& e);


	
	virtual void	onMouseButtonUp(MouseEventArgs& e);


	
	
	void	drawSelf(float z);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"TabButton")	return true;
		return ButtonBase::testClassName_impl(class_name);
	}
};


} 


#endif	
