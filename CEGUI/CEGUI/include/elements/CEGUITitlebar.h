

#ifndef _CEGUITitlebar_h_
#define _CEGUITitlebar_h_

#include "CEGUIWindow.h"
#include "elements/CEGUITitlebarProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT Titlebar : public Window
{
public:
	static const String EventNamespace;				


	
	bool	isDraggingEnabled(void) const;


	
	void	setDraggingEnabled(bool setting);


	
	colour	getCaptionColour(void) const;


	
	void	setCaptionColour(const colour& col);


	
	
	Titlebar(const String& type, const String& name);


	
	virtual ~Titlebar(void);


protected:
	
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onMouseButtonUp(MouseEventArgs& e);
	virtual void	onMouseDoubleClicked(MouseEventArgs& e);
	virtual void	onCaptureLost(WindowEventArgs& e);
	virtual void	onFontChanged(WindowEventArgs &e);


	
	
	virtual void	onDraggingModeChanged(WindowEventArgs& e) {}


	
	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Titlebar")	return true;
		return Window::testClassName_impl(class_name);
	}


	
	bool	d_dragging;			
	Point	d_dragPoint;		
	bool	d_dragEnabled;		

	Rect	d_oldCursorArea;	

	colour	d_captionColour;	


private:
	
	static TitlebarProperties::DraggingEnabled	d_dragEnabledProperty;
	static TitlebarProperties::CaptionColour	d_captionColourProperty;


	
	void	addTitlebarProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
