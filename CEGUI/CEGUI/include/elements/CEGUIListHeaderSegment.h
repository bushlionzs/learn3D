

#ifndef _CEGUIListHeaderSegment_h_
#define _CEGUIListHeaderSegment_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIListHeaderSegmentProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT ListHeaderSegment : public Window
{
public:
	static const String EventNamespace;				


	
	
	static const String EventSegmentClicked;				
	static const String EventSplitterDoubleClicked;		
	static const String EventSizingSettingChanged;		
	static const String EventSortDirectionChanged;		
	static const String EventMovableSettingChanged;		
	static const String EventSegmentDragStart;			
	static const String EventSegmentDragStop;				
	static const String EventSegmentDragPositionChanged;	
	static const String EventSegmentSized;				
	static const String EventClickableSettingChanged;		

	
	static const float	DefaultSizingArea;		
	static const float	SegmentMoveThreshold;	


	
	
	enum SortDirection
	{
		None,		
		Ascending,	
		Descending	
	};


	
	
	bool	isSizingEnabled(void) const			{return d_sizingEnabled;}


	
	SortDirection	getSortDirection(void) const	{return d_sortDir;}


	
	bool	isDragMovingEnabled(void) const		{return d_movingEnabled;}


	
	const Point&	getDragMoveOffset(void) const	{return d_dragPosition;}


	
	bool	isClickable(void) const		{return d_allowClicks;}


	
	
	void	setSizingEnabled(bool setting);


	
	void	setSortDirection(SortDirection sort_dir);


	
	void	setDragMovingEnabled(bool setting);


	
	void setClickable(bool setting);


	
	
	ListHeaderSegment(const String& type, const String& name);


	
	virtual ~ListHeaderSegment(void);


protected:
	

	
	void	doDragSizing(const Point& local_mouse);


	
	void	doDragMoving(const Point& local_mouse);


	
	void	initDragMoving(void);


	
	void	initSizingHoverState(void);


	
	void	initSegmentHoverState(void);


			
	bool	isDragMoveThresholdExceeded(const Point& local_mouse);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"ListHeaderSegment")	return true;
		return Window::testClassName_impl(class_name);
	}


	
	
	virtual void	onSegmentClicked(WindowEventArgs& e);


	
	virtual void	onSplitterDoubleClicked(WindowEventArgs& e);


	
	virtual void	onSizingSettingChanged(WindowEventArgs& e);


	
	virtual void	onSortDirectionChanged(WindowEventArgs& e);


	
	virtual void	onMovableSettingChanged(WindowEventArgs& e);


	
	virtual void	onSegmentDragStart(WindowEventArgs& e);


	
	virtual void	onSegmentDragStop(WindowEventArgs& e);


	
	virtual void	onSegmentDragPositionChanged(WindowEventArgs& e);


	
	virtual void	onSegmentSized(WindowEventArgs& e);


	
	virtual void	onClickableSettingChanged(WindowEventArgs& e);


	
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onMouseButtonUp(MouseEventArgs& e);
	virtual void	onMouseDoubleClicked(MouseEventArgs& e);
	virtual void	onMouseLeaves(MouseEventArgs& e);
	virtual void	onCaptureLost(WindowEventArgs& e);


	
	const Image*	d_sizingMouseCursor;	
	const Image*	d_movingMouseCursor;	

	float	d_splitterSize;		
	bool	d_splitterHover;	

	bool	d_dragSizing;		
	Point	d_dragPoint;		

	SortDirection	d_sortDir;	

	bool	d_segmentHover;		
	bool	d_segmentPushed;	
	bool	d_sizingEnabled;	
	bool	d_movingEnabled;	
	bool	d_dragMoving;		
	Point	d_dragPosition;		
	bool	d_allowClicks;		


private:
	
	static ListHeaderSegmentProperties::Clickable		d_clickableProperty;
	static ListHeaderSegmentProperties::Dragable		d_dragableProperty;
	static ListHeaderSegmentProperties::Sizable			d_sizableProperty;
	static ListHeaderSegmentProperties::SortDirection	d_sortDirectionProperty;


	
	void	addHeaderSegmentProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
