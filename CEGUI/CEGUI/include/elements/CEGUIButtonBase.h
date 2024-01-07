

#ifndef _CEGUIButtonBase_h_
#define _CEGUIButtonBase_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIButtonBaseProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT ButtonBase : public Window
{
public:
	
	
	static const colour		DefaultNormalLabelColour;		
	static const colour		DefaultHoverLabelColour;		
	static const colour		DefaultPushedLabelColour;		
	static const colour		DefaultDisabledLabelColour;		


	
	
	bool	isHovering(void) const			
	{
		return d_hovering;
	}
	virtual bool	setHovering(bool state)			
	{
		return d_hovering = state;
	}


	
	bool	isPushed(void) const			{return d_pushed;}
	virtual bool	setPushed(bool state)			{return d_pushed = state;}


	
	colour	getNormalTextColour(void) const			{return d_normalColour;}


	
	colour	getHoverTextColour(void) const			{return d_hoverColour;}


	
	colour	getPushedTextColour(void) const			{return d_pushedColour;}


	
	colour	getDisabledTextColour(void) const		{return d_disabledColour;}

	
	
	void	setNormalTextColour(const colour& colour);


	
	void	setHoverTextColour(const colour& colour);


	
	void	setPushedTextColour(const colour& colour);

	
	
	void	setDisabledTextColour(const colour& colour);

	void	setStayHover(bool show);

	
	
	ButtonBase(const String& type, const String& name);


	
	virtual ~ButtonBase(void);


protected:
	
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onMouseButtonUp(MouseEventArgs& e);
	virtual void	onCaptureLost(WindowEventArgs& e);
	virtual void	onMouseLeaves(MouseEventArgs& e);
	
	
	


	
	
	void	updateInternalState(const Point& mouse_pos);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"ButtonBase")	return true;
		return Window::testClassName_impl(class_name);
	}


	
	
	virtual	void	drawSelf(float z);


	
	virtual void	drawNormal(float z)		= 0;


	
	virtual void	drawHover(float z)			{drawNormal(z);}


	
	virtual void	drawPushed(float z)		{drawNormal(z);}


	
	virtual void	drawDisabled(float z)		{drawNormal(z);}


	
	bool	d_pushed;			
	bool	d_hovering;			
	bool	d_isInWindow;
	bool	d_stayHover;

	
	colour	d_normalColour;					
	colour	d_hoverColour;					
	colour	d_pushedColour;					
	colour	d_disabledColour;				

private:
	
	static ButtonBaseProperties::NormalTextColour	d_normalTextColourProperty;
	static ButtonBaseProperties::HoverTextColour	d_hoverTextColourProperty;
	static ButtonBaseProperties::PushedTextColour	d_pushedTextColourProperty;
	static ButtonBaseProperties::DisabledTextColour	d_disabledTextColourProperty;

	
	void	addButtonBaseProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
