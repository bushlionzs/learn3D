

#ifndef _CEGUIFrameWindow_h_
#define _CEGUIFrameWindow_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIFrameWindowProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT FrameWindow : public Window
{
public:
	static const String EventNamespace;				


	
	
	static const String EventRollupToggled;		
	static const String EventCloseClicked;		

	
	static const float	DefaultSizingBorderSize;	


	
	enum SizingLocation {
		SizingNone,			
		SizingTopLeft,		
		SizingTopRight,		
		SizingBottomLeft,	
		SizingBottomRight,	
		SizingTop,			
		SizingLeft,			
		SizingBottom,		
		SizingRight         
	};

	
	virtual void	initialise(void);
	
	
	
	bool	isSizingEnabled(void) const					{return d_sizingEnabled && isFrameEnabled();}


	
	bool	isFrameEnabled(void) const					{return d_frameEnabled;}


		
	bool	isTitleBarEnabled(void) const				{return (d_titlebar != NULL) && !((Window*)d_titlebar)->isDisabled();}


	
	bool	isCloseButtonEnabled(void) const			{return (d_closeButton != NULL) && !((Window*)d_closeButton)->isDisabled();}


	
	bool	isRollupEnabled(void) const					{return d_rollupEnabled;}


	
	bool	isRolledup(void) const						{return d_rolledup;}


	
	float	getSizingBorderThickness(void) const		{return d_borderSize;}


	
	void	setSizingEnabled(bool setting);


	
	void	setFrameEnabled(bool setting);


	
	void	setTitleBarEnabled(bool setting);


	
	void	setCloseButtonEnabled(bool setting);


	
	void	setRollupEnabled(bool setting);


	
	void	toggleRollup(void);


	
	void	setSizingBorderThickness(float pixels)		{d_borderSize = pixels;}


	
	void	setTitlebarFont(const String& name);


	
	void	setTitlebarFont(Font* font);


	
	void	offsetPixelPosition(const Vector2& offset);


	
	bool	isDragMovingEnabled(void) const		{return d_dragMovable;}


	
	void	setDragMovingEnabled(bool setting);


	
	const Font*	getTitlebarFont(void) const;


	
	colour	getCaptionColour(void) const;


	
	void	setCaptionColour(colour col);

    
    const Image* getNSSizingCursorImage() const;

    
    const Image* getEWSizingCursorImage() const;

    
    const Image* getNWSESizingCursorImage() const;

    
    const Image* getNESWSizingCursorImage() const;

    
    void setNSSizingCursorImage(const Image* image);

    
    void setEWSizingCursorImage(const Image* image);

    
    void setNWSESizingCursorImage(const Image* image);

    
    void setNESWSizingCursorImage(const Image* image);

    
    void setNSSizingCursorImage(const String& imageset, const String& image);

    
    void setEWSizingCursorImage(const String& imageset, const String& image);

    
    void setNWSESizingCursorImage(const String& imageset, const String& image);

    
    void setNESWSizingCursorImage(const String& imageset, const String& image);

    
    bool    isHit(const Point& position) const      { return Window::isHit(position) && !d_rolledup; }


	
	
	FrameWindow(const String& name, const String& type);

	
	virtual ~FrameWindow(void);


protected:
	
	
	virtual Titlebar*	createTitlebar(const String& name) const		= 0;


	
	virtual PushButton*	createCloseButton(const String& name) const	= 0;


	
	void	moveLeftEdge(float delta);


	
	void	moveRightEdge(float delta);


	
	void	moveTopEdge(float delta);


	
	void	moveBottomEdge(float delta);


	
	SizingLocation	getSizingBorderAtPoint(const Point& pt) const;

 
	
	bool	isLeftSizingLocation(SizingLocation loc) const			{return ((loc == SizingLeft) || (loc == SizingTopLeft) || (loc == SizingBottomLeft));}


	
	bool	isRightSizingLocation(SizingLocation loc) const			{return ((loc == SizingRight) || (loc == SizingTopRight) || (loc == SizingBottomRight));}


	
	bool	isTopSizingLocation(SizingLocation loc) const			{return ((loc == SizingTop) || (loc == SizingTopLeft) || (loc == SizingTopRight));}


	
	bool	isBottomSizingLocation(SizingLocation loc) const		{return ((loc == SizingBottom) || (loc == SizingBottomLeft) || (loc == SizingBottomRight));}

	
	bool	closeClickHandler(const EventArgs& e);


	
	void	setCursorForPoint(const Point& pt) const;


	
	virtual	Rect	getSizingRect(void) const		{return Rect(0, 0, getAbsoluteWidth(), getAbsoluteHeight());}


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"FrameWindow")	return true;
		return Window::testClassName_impl(class_name);
	}


	
	
	virtual void	onRollupToggled(WindowEventArgs& e);


	
	virtual void	onCloseClicked(WindowEventArgs& e);


	
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onMouseButtonUp(MouseEventArgs& e);
	virtual void	onCaptureLost(WindowEventArgs& e);
	virtual void    onTextChanged(WindowEventArgs& e);
	virtual void	onActivated(ActivationEventArgs& e);
	virtual void	onDeactivated(ActivationEventArgs& e);


	
	
	bool	d_frameEnabled;		

	
	bool	d_rollupEnabled;	
	bool	d_rolledup;			

	
	bool	d_sizingEnabled;	
	bool	d_beingSized;		
	float	d_borderSize;		
	Point	d_dragPoint;		

	
	Titlebar*	d_titlebar;				
	PushButton*	d_closeButton;			

	
	const Image*	d_nsSizingCursor;		
	const Image*	d_ewSizingCursor;		
	const Image*	d_nwseSizingCursor;		
	const Image*	d_neswSizingCursor;		

	bool	d_dragMovable;		


private:
	
	static FrameWindowProperties::SizingEnabled		d_sizingEnabledProperty;
	static FrameWindowProperties::FrameEnabled		d_frameEnabledProperty;
	static FrameWindowProperties::TitlebarEnabled	d_titlebarEnabledProperty;
	static FrameWindowProperties::CloseButtonEnabled d_closeButtonEnabledProperty;
	static FrameWindowProperties::RollUpState		d_rollUpStateProperty;
	static FrameWindowProperties::RollUpEnabled		d_rollUpEnabledProperty;
	static FrameWindowProperties::DragMovingEnabled	d_dragMovingEnabledProperty;
	static FrameWindowProperties::SizingBorderThickness d_sizingBorderThicknessProperty;
	static FrameWindowProperties::TitlebarFont		d_titlebarFontProperty;
	static FrameWindowProperties::CaptionColour		d_captionColourProperty;
    static FrameWindowProperties::NSSizingCursorImage   d_nsSizingCursorProperty;
    static FrameWindowProperties::EWSizingCursorImage   d_ewSizingCursorProperty;
    static FrameWindowProperties::NWSESizingCursorImage d_nwseSizingCursorProperty;
    static FrameWindowProperties::NESWSizingCursorImage d_neswSizingCursorProperty;


	
	void	addFrameWindowProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
