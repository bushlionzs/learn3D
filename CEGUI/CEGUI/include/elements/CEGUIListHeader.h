

#ifndef _CEGUIListHeader_h_
#define _CEGUIListHeader_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIListHeaderSegment.h"
#include "elements/CEGUIListHeaderProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT HeaderSequenceEventArgs : public WindowEventArgs
{
public:
	HeaderSequenceEventArgs(Window* wnd, uint old_idx, uint new_idx) : WindowEventArgs(wnd), d_oldIdx(old_idx), d_newIdx(new_idx) {};

	uint d_oldIdx;		
	uint d_newIdx;		
};



class CEGUIEXPORT ListHeader : public Window
{
public:
	static const String EventNamespace;				


	
	
	static const String EventSortColumnChanged;			
	static const String EventSortDirectionChanged;		
	static const String EventSegmentSized;				
	static const String EventSegmentClicked;				
	static const String EventSplitterDoubleClicked;		
	static const String EventSegmentSequenceChanged;		
	static const String EventSegmentAdded;				
	static const String EventSegmentRemoved;				
	static const String EventSortSettingChanged;			
	static const String EventDragMoveSettingChanged;		
	static const String EventDragSizeSettingChanged;		
	static const String EventSegmentRenderOffsetChanged;	

	
	static const float	ScrollSpeed;				
	static const float	MinimumSegmentPixelWidth;	


	
	
	uint	getColumnCount(void) const;

	
	
	ListHeaderSegment&	getSegmentFromColumn(uint column) const;


	
	ListHeaderSegment&	getSegmentFromID(uint id) const;


	
	ListHeaderSegment&	getSortSegment(void) const;


	
	uint	getColumnFromSegment(const ListHeaderSegment& segment) const;


	
	uint	getColumnFromID(uint id) const;


	
	uint	getSortColumn(void) const;


	
	uint	getColumnWithText(const String& text) const;


	
	float	getPixelOffsetToSegment(const ListHeaderSegment& segment) const;


	
	float	getPixelOffsetToColumn(uint column) const;


	
	float	getTotalSegmentsPixelExtent(void) const;


	
	float	getColumnPixelWidth(uint column) const;


	
	ListHeaderSegment::SortDirection	getSortDirection(void) const;


	
	bool	isSortingEnabled(void) const;


	
	bool	isColumnSizingEnabled(void) const;


	
	bool	isColumnDraggingEnabled(void) const;


	
	float	getSegmentOffset(void) const	{return d_segmentOffset;}


	
	
	void	setSortingEnabled(bool setting);


	
	void	setSortDirection(ListHeaderSegment::SortDirection direction);


	
	void	setSortSegment(const ListHeaderSegment& segment);


	
	void	setSortColumn(uint column);


	
	void	setSortColumnFromID(uint id);


	
	void	setColumnSizingEnabled(bool setting);


	
	void	setColumnDraggingEnabled(bool setting);


	
	void	addColumn(const String& text, uint id, float width);


	
	void	insertColumn(const String& text, uint id, float width, uint position);


	
	void	insertColumn(const String& text, uint id, float width, const ListHeaderSegment& position);


	
	void	removeColumn(uint column);


	
	void	removeSegment(const ListHeaderSegment& segment);


	
	void	moveColumn(uint column, uint position);


	
	void	moveColumn(uint column, const ListHeaderSegment& position);


	
	void	moveSegment(const ListHeaderSegment& segment, uint position);


	
	void	moveSegment(const ListHeaderSegment& segment, const ListHeaderSegment& position);


	
	void	setSegmentOffset(float offset);


	
	void	setColumnPixelWidth(uint column, float width);


	
	
	ListHeader(const String& type, const String& name);


	
	virtual ~ListHeader(void);


protected:
	
	
	virtual ListHeaderSegment*	createNewSegment(const String& name) const	= 0;


	
	virtual void	destroyListSegment(ListHeaderSegment* segment) const = 0;


	
	
	ListHeaderSegment*	createInitialisedSegment(const String& text, uint id, float width);


	
	void	layoutSegments(void);

	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"ListHeader")	return true;
		return Window::testClassName_impl(class_name);
	}


	
	
	virtual	void	onSortColumnChanged(WindowEventArgs& e);


	
	virtual	void	onSortDirectionChanged(WindowEventArgs& e);


	
	virtual	void	onSegmentSized(WindowEventArgs& e);


	
	virtual	void	onSegmentClicked(WindowEventArgs& e);


	
	virtual	void	onSplitterDoubleClicked(WindowEventArgs& e);


	
	virtual	void	onSegmentSequenceChanged(WindowEventArgs& e);


	
	virtual	void	onSegmentAdded(WindowEventArgs& e);


	
	virtual	void	onSegmentRemoved(WindowEventArgs& e);


	
	virtual	void	onSortSettingChanged(WindowEventArgs& e);


	
	virtual	void	onDragMoveSettingChanged(WindowEventArgs& e);


	
	virtual	void	onDragSizeSettingChanged(WindowEventArgs& e);


	
	virtual	void	onSegmentOffsetChanged(WindowEventArgs& e);


	
	bool	segmentSizedHandler(const EventArgs& e);
	bool	segmentMovedHandler(const EventArgs& e);
	bool	segmentClickedHandler(const EventArgs& e);
	bool	segmentDoubleClickHandler(const EventArgs& e);
	bool	segmentDragHandler(const EventArgs& e);


	
	typedef	std::vector<ListHeaderSegment*>		SegmentList;
	SegmentList	d_segments;			
	ListHeaderSegment*	d_sortSegment;	
	bool	d_sizingEnabled;		
	bool	d_sortingEnabled;		
	bool	d_movingEnabled;		
	uint	d_uniqueIDNumber;		
	float	d_segmentOffset;		
	ListHeaderSegment::SortDirection	d_sortDir;		


private:
	
	static ListHeaderProperties::SortSettingEnabled		d_sortSettingProperty;
	static ListHeaderProperties::ColumnsSizable			d_sizableProperty;
	static ListHeaderProperties::ColumnsMovable			d_movableProperty;
	static ListHeaderProperties::SortColumnID			d_sortColumnIDProperty;
	static ListHeaderProperties::SortDirection			d_sortDirectionProperty;


	
	void	addHeaderProperties(void);
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
