

#ifndef _CEGUIMenuItem_h_
#define _CEGUIMenuItem_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUITextItem.h"
#include "elements/CEGUIMenuItemProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT MenuItem : public TextItem
{
public:
	static const String EventNamespace;				

	
	
	
	static const colour		DefaultHoverColour;			
	static const colour		DefaultPushedColour;		
	static const colour		DefaultOpenedColour;		
	static const colour		DefaultNormalTextColour;	
	static const colour		DefaultDisabledTextColour;	


	
	
	static const String EventClicked;					


	
	
	bool	isHovering(void) const			{return d_hovering;}


	
	bool	isPushed(void) const			{return d_pushed;}


	
	colour	getHoverColour(void) const			{return d_hoverColour;}


	
	colour	getPushedColour(void) const			{return d_pushedColour;}


	
	colour	getOpenedColour(void) const			{return d_openedColour;}


	
	colour	getNormalTextColour(void) const			{return d_normalTextColour;}


	
	colour	getDisabledTextColour(void) const		{return d_disabledTextColour;}


	
	PopupMenu*	getPopupMenu(void) const			{return d_popup;}


	
	
	void	setHoverColour(const colour& colour);


	
	void	setPushedColour(const colour& colour);


	
	void	setOpenedColour(const colour& colour);


	
	void	setNormalTextColour(const colour& colour);


	
	void	setDisabledTextColour(const colour& colour);


	
	void	setPopupMenu(PopupMenu* popup);


	
	void	openPopupMenu(void);


	
	void	closePopupMenu(bool notify=true);


	
	bool	togglePopupMenu(void);


	
	
	MenuItem(const String& type, const String& name);


	
	virtual ~MenuItem(void);


protected:
	
	
	virtual void	onClicked(WindowEventArgs& e);


	
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onMouseButtonUp(MouseEventArgs& e);
	virtual void	onCaptureLost(WindowEventArgs& e);
	virtual void	onMouseLeaves(MouseEventArgs& e);


	
	
	void	updateInternalState(const Point& mouse_pos);


	
	void	closeAllMenuItemPopups();


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"MenuItem")	return true;
		return TextItem::testClassName_impl(class_name);
	}


	

	
	bool	d_pushed;			
	bool	d_hovering;			
	bool	d_opened;			

	
	colour	d_hoverColour;					
	colour	d_pushedColour;					
	colour	d_openedColour;					
	colour	d_normalTextColour;				
	colour	d_disabledTextColour;			

	PopupMenu* d_popup;						

	bool	d_popupWasClosed;				

private:
	
	static MenuItemProperties::HoverColour			d_hoverColourProperty;
	static MenuItemProperties::PushedColour			d_pushedColourProperty;
	static MenuItemProperties::OpenedColour			d_openedColourProperty;
	static MenuItemProperties::NormalTextColour		d_normalTextColourProperty;
	static MenuItemProperties::DisabledTextColour	d_disabledTextColourProperty;


	
	void addMenuItemProperties(void);


	
	virtual void	addChild_impl(Window* wnd);
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif


#endif	
