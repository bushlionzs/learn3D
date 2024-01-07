

#include "elements/CEGUIListHeader.h"
#include "CEGUIExceptions.h"

#include <sstream>



namespace CEGUI
{
const String ListHeader::EventNamespace("ListHeader");


ListHeaderProperties::SortSettingEnabled	ListHeader::d_sortSettingProperty;
ListHeaderProperties::ColumnsSizable		ListHeader::d_sizableProperty;
ListHeaderProperties::ColumnsMovable		ListHeader::d_movableProperty;
ListHeaderProperties::SortColumnID			ListHeader::d_sortColumnIDProperty;
ListHeaderProperties::SortDirection			ListHeader::d_sortDirectionProperty;




const String ListHeader::EventSortColumnChanged( (utf8*)"SortColumnChanged" );
const String ListHeader::EventSortDirectionChanged( (utf8*)"SortDirectionChanged" );
const String ListHeader::EventSegmentSized( (utf8*)"SegmentSized" );
const String ListHeader::EventSegmentClicked( (utf8*)"SegmentClicked" );
const String ListHeader::EventSplitterDoubleClicked( (utf8*)"SplitterDoubleClicked" );
const String ListHeader::EventSegmentSequenceChanged( (utf8*)"SegmentSequenceChanged" );
const String ListHeader::EventSegmentAdded( (utf8*)"SegmentAdded" );
const String ListHeader::EventSegmentRemoved( (utf8*)"SegmentRemoved" );
const String ListHeader::EventSortSettingChanged( (utf8*)"SortSettingChanged" );
const String ListHeader::EventDragMoveSettingChanged( (utf8*)"DragMoveSettingChanged" );
const String ListHeader::EventDragSizeSettingChanged( (utf8*)"DragSizeSettingChanged" );
const String ListHeader::EventSegmentRenderOffsetChanged( (utf8*)"SegmentOffsetChanged" );


const float	ListHeader::ScrollSpeed	= 8.0f;
const float	ListHeader::MinimumSegmentPixelWidth	= 20.0f;



ListHeader::ListHeader(const String& type, const String& name) :
	Window(type, name),
	d_sortSegment(NULL),
	d_sizingEnabled(true),
	d_sortingEnabled(true),
	d_movingEnabled(true),
	d_uniqueIDNumber(0),
	d_segmentOffset(0.0f),
	d_sortDir(ListHeaderSegment::None)
{
	addHeaderProperties();
}



ListHeader::~ListHeader(void)
{
}



uint ListHeader::getColumnCount(void) const
{
	return (uint)d_segments.size();
}



ListHeaderSegment& ListHeader::getSegmentFromColumn(uint column) const
{
	if (column >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"ListHeader::getSegmentFromColumn - requested column index is out of range for this ListHeader.");
	}
	else
	{
		return *d_segments[column];
	}

}



ListHeaderSegment& ListHeader::getSegmentFromID(uint id) const
{
	for (uint i = 0; i < getColumnCount(); ++i)
	{
		if (d_segments[i]->getID() == id)
		{
			return *d_segments[i];
		}

	}

	
	throw InvalidRequestException((utf8*)"ListHeader::getSegmentFromID - no segment with the requested ID is attached to this ListHeader.");
}



ListHeaderSegment& ListHeader::getSortSegment(void) const
{
	if (d_sortSegment == NULL)
	{
		throw	InvalidRequestException((utf8*)"ListHeader::getSortSegment - Sort segment was NULL!  (No segments are attached to the ListHeader?)");
	}
	else
	{
		return *d_sortSegment;
	}

}



uint ListHeader::getColumnFromSegment(const ListHeaderSegment& segment) const
{
	for (uint i = 0; i < getColumnCount(); ++i)
	{
		if (d_segments[i] == &segment)
		{
			return i;
		}

	}

	
	throw InvalidRequestException((utf8*)"ListHeader::getColumnFromSegment - the given ListHeaderSegment is not attached to this ListHeader.");
}



uint ListHeader::getColumnFromID(uint id) const
{
	for (uint i = 0; i < getColumnCount(); ++i)
	{
		if (d_segments[i]->getID() == id)
		{
			return i;
		}

	}

	
	throw InvalidRequestException((utf8*)"ListHeader::getColumnFromID - no column with the requested ID is available on this ListHeader.");
}



uint ListHeader::getSortColumn(void) const
{
	return getColumnFromSegment(getSortSegment());
}



uint ListHeader::getColumnWithText(const String& text) const
{
	for (uint i = 0; i < getColumnCount(); ++i)
	{
		if (d_segments[i]->getText() == text)
		{
			return i;
		}

	}

	
	throw InvalidRequestException((utf8*)"ListHeader::getColumnWithText - no column with the text '" + text + "' is attached to this ListHeader.");
}



float ListHeader::getPixelOffsetToSegment(const ListHeaderSegment& segment) const
{
	float offset = 0.0f;

	for (uint i = 0; i < getColumnCount(); ++i)
	{
		if (d_segments[i] == &segment)
		{
			return offset;
		}

		offset += d_segments[i]->getAbsoluteWidth();
	}

	
	throw InvalidRequestException((utf8*)"ListHeader::getPixelOffsetToSegment - the given ListHeaderSegment is not attached to this ListHeader.");
}



float ListHeader::getPixelOffsetToColumn(uint column) const
{
	if (column >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"ListHeader::getPixelOffsetToColumn - requested column index is out of range for this ListHeader.");
	}
	else
	{
		float offset = 0.0f;

		for (uint i = 0; i < column; ++i)
		{
			offset += d_segments[i]->getAbsoluteWidth();
		}

		return offset;
	}

}



float ListHeader::getTotalSegmentsPixelExtent(void) const
{
	float extent = 0.0f;

	for (uint i = 0; i < getColumnCount(); ++i)
	{
		extent += d_segments[i]->getAbsoluteWidth();
	}

	return extent;
}



float ListHeader::getColumnPixelWidth(uint column) const
{
	if (column >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"ListHeader::getColumnPixelWidth - requested column index is out of range for this ListHeader.");
	}
	else
	{
		return d_segments[column]->getAbsoluteWidth();
	}

}



ListHeaderSegment::SortDirection ListHeader::getSortDirection(void) const
{
	return d_sortDir;
}



bool ListHeader::isSortingEnabled(void) const
{
	return d_sortingEnabled;
}



bool ListHeader::isColumnSizingEnabled(void) const
{
	return d_sizingEnabled;
}



bool ListHeader::isColumnDraggingEnabled(void) const
{
	return d_movingEnabled;
}



void ListHeader::setSortingEnabled(bool setting)
{
	if (d_sortingEnabled != setting)
	{
		d_sortingEnabled = setting;

		
		for (uint i = 0; i <getColumnCount(); ++i)
		{
			d_segments[i]->setClickable(d_sortingEnabled);
		}

		
		WindowEventArgs args(this);
		onSortSettingChanged(args);
	}

}



void ListHeader::setSortDirection(ListHeaderSegment::SortDirection direction)
{
	if (d_sortDir != direction)
	{
		d_sortDir = direction;

		
		if (d_sortSegment != NULL)
		{
			d_sortSegment->setSortDirection(direction);
		}

		
		WindowEventArgs args(this);
		onSortDirectionChanged(args);
	}

}



void ListHeader::setSortSegment(const ListHeaderSegment& segment)
{
	setSortColumn(getColumnFromSegment(segment));
}



void ListHeader::setSortColumn(uint column)
{
	if (column >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"ListHeader::setSortColumn - specified column index is out of range for this ListHeader.");
	}
	else
	{
		
		if (d_sortSegment != d_segments[column])
		{
			
			if (d_sortSegment != NULL)
			{
				d_sortSegment->setSortDirection(ListHeaderSegment::None);
			}

			
			d_sortSegment = d_segments[column];
			d_sortSegment->setSortDirection(d_sortDir);

			
			WindowEventArgs args(this);
			onSortColumnChanged(args);
		}

	}

}



void ListHeader::setSortColumnFromID(uint id)
{
	setSortSegment(getSegmentFromID(id));
}



void ListHeader::setColumnSizingEnabled(bool setting)
{
	if (d_sizingEnabled != setting)
	{
		d_sizingEnabled = setting;

		
		for (uint i = 0; i <getColumnCount(); ++i)
		{
			d_segments[i]->setSizingEnabled(d_sizingEnabled);
		}

		
		WindowEventArgs args(this);
		onDragSizeSettingChanged(args);
	}

}



void ListHeader::setColumnDraggingEnabled(bool setting)
{
	if (d_movingEnabled != setting)
	{
		d_movingEnabled = setting;

		
		for (uint i = 0; i <getColumnCount(); ++i)
		{
			d_segments[i]->setDragMovingEnabled(d_movingEnabled);
		}

		
		WindowEventArgs args(this);
		onDragMoveSettingChanged(args);
	}

}



void ListHeader::addColumn(const String& text, uint id, float width)
{
	
	insertColumn(text, id, width, getColumnCount());
}



void ListHeader::insertColumn(const String& text, uint id, float width, uint position)
{
	
	if (position > getColumnCount())
	{
		position = getColumnCount();
	}

	ListHeaderSegment* seg = createInitialisedSegment(text, id, width);
	d_segments.insert((d_segments.begin() + position), seg);

	
	addChildWindow(seg);

	layoutSegments();

	
	WindowEventArgs args(this);
	onSegmentAdded(args);

	
	if (d_sortSegment == NULL)
	{
		setSortColumn(position);
	}
}



void ListHeader::removeColumn(uint column)
{
	if (column >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"ListHeader::removeColumn - specified column index is out of range for this ListHeader.");
	}
	else
	{
		ListHeaderSegment* seg = d_segments[column];

		
		d_segments.erase(d_segments.begin() + column);

		
		if (d_sortSegment == seg)
		{
			
			if (getColumnCount() > 0)
			{
				
				d_sortDir = ListHeaderSegment::None;
				setSortColumn(0);
			}
			
			else
			{
				d_sortSegment = NULL;
			}

		}

		
		removeChildWindow(seg);

		
		destroyListSegment(seg);

		layoutSegments();

		
		WindowEventArgs args(this);
		onSegmentRemoved(args);
	}

}



void ListHeader::moveColumn(uint column, uint position)
{
	if (column >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"ListHeader::moveColumn - specified column index is out of range for this ListHeader.");
	}
	else
	{
		
		if (position >= getColumnCount())
		{
			position = getColumnCount() - 1;
		}

		ListHeaderSegment* seg = d_segments[column];

		
		d_segments.erase(d_segments.begin() + column);

		
		d_segments.insert(d_segments.begin() + position, seg);

		
		HeaderSequenceEventArgs args(this, column, position);
		onSegmentSequenceChanged(args);

		layoutSegments();
	}

}



void ListHeader::insertColumn(const String& text, uint id, float width, const ListHeaderSegment& position)
{
	insertColumn(text, id, width, getColumnFromSegment(position));
}



void ListHeader::removeSegment(const ListHeaderSegment& segment)
{
	removeColumn(getColumnFromSegment(segment));
}



void ListHeader::moveColumn(uint column, const ListHeaderSegment& position)
{
	moveColumn(column, getColumnFromSegment(position));
}



void ListHeader::moveSegment(const ListHeaderSegment& segment, uint position)
{
	moveColumn(getColumnFromSegment(segment), position);
}



void ListHeader::moveSegment(const ListHeaderSegment& segment, const ListHeaderSegment& position)
{
	moveColumn(getColumnFromSegment(segment), getColumnFromSegment(position));
}



void ListHeader::setSegmentOffset(float offset)
{
	if (d_segmentOffset != offset)
	{
		d_segmentOffset = offset;
		layoutSegments();
		requestRedraw();
	
		
		WindowEventArgs args(this);
		onSegmentOffsetChanged(args);
	}

}



void ListHeader::setColumnPixelWidth(uint column, float width)
{
	if (column >= getColumnCount())
	{
		throw InvalidRequestException((utf8*)"ListHeader::setColumnPixelWidth - specified column index is out of range for this ListHeader.");
	}
	else
	{
		d_segments[column]->setWidth(Absolute, width);

		layoutSegments();

		
		WindowEventArgs args(d_segments[column]);
		onSegmentSized(args);
	}

}



ListHeaderSegment* ListHeader::createInitialisedSegment(const String& text, uint id, float width)
{
	
	std::stringstream name;
	name << getName().c_str() << "__auto_seg_" << d_uniqueIDNumber;

	
	ListHeaderSegment* newseg = createNewSegment(name.str());
	d_uniqueIDNumber++;

	
	newseg->setMetricsMode(Relative);
	newseg->setSize(Size(width, 1.0f));
	newseg->setMinimumSize(absoluteToRelative_impl(NULL, Size(MinimumSegmentPixelWidth, 0.0f)));
	newseg->setText(text);
	newseg->setID(id);

	
	newseg->subscribeEvent(ListHeaderSegment::EventSegmentSized, Event::Subscriber(&CEGUI::ListHeader::segmentSizedHandler, this));
	newseg->subscribeEvent(ListHeaderSegment::EventSegmentDragStop, Event::Subscriber(&CEGUI::ListHeader::segmentMovedHandler, this));
	newseg->subscribeEvent(ListHeaderSegment::EventSegmentClicked, Event::Subscriber(&CEGUI::ListHeader::segmentClickedHandler, this));
	newseg->subscribeEvent(ListHeaderSegment::EventSplitterDoubleClicked, Event::Subscriber(&CEGUI::ListHeader::segmentDoubleClickHandler, this));
	newseg->subscribeEvent(ListHeaderSegment::EventSegmentDragPositionChanged, Event::Subscriber(&CEGUI::ListHeader::segmentDragHandler, this));

	return newseg;
}



void ListHeader::layoutSegments(void)
{
	Point pos(-d_segmentOffset, 0.0f);

	for (uint i = 0; i < getColumnCount(); ++i)
	{
		d_segments[i]->setPosition(pos);
		pos.d_x += d_segments[i]->getWidth();
	}

}



void ListHeader::onSortColumnChanged(WindowEventArgs& e)
{
	fireEvent(EventSortColumnChanged, e, EventNamespace);
}



void ListHeader::onSortDirectionChanged(WindowEventArgs& e)
{
	fireEvent(EventSortDirectionChanged, e, EventNamespace);
}



void ListHeader::onSegmentSized(WindowEventArgs& e)
{
	fireEvent(EventSegmentSized, e, EventNamespace);
}



void ListHeader::onSegmentClicked(WindowEventArgs& e)
{
	fireEvent(EventSegmentClicked, e, EventNamespace);
}



void ListHeader::onSplitterDoubleClicked(WindowEventArgs& e)
{
	fireEvent(EventSplitterDoubleClicked, e, EventNamespace);
}



void ListHeader::onSegmentSequenceChanged(WindowEventArgs& e)
{
	fireEvent(EventSegmentSequenceChanged, e, EventNamespace);
}



void ListHeader::onSegmentAdded(WindowEventArgs& e)
{
	fireEvent(EventSegmentAdded, e, EventNamespace);
}



void ListHeader::onSegmentRemoved(WindowEventArgs& e)
{
	fireEvent(EventSegmentRemoved, e, EventNamespace);
}



void ListHeader::onSortSettingChanged(WindowEventArgs& e)
{
	fireEvent(EventSortSettingChanged, e, EventNamespace);
}



void ListHeader::onDragMoveSettingChanged(WindowEventArgs& e)
{
	fireEvent(EventDragMoveSettingChanged, e, EventNamespace);
}



void ListHeader::onDragSizeSettingChanged(WindowEventArgs& e)
{
	fireEvent(EventDragSizeSettingChanged, e, EventNamespace);
}



void ListHeader::onSegmentOffsetChanged(WindowEventArgs& e)
{
	fireEvent(EventSegmentRenderOffsetChanged, e, EventNamespace);
}



bool ListHeader::segmentSizedHandler(const EventArgs& e)
{
	layoutSegments();

	
	WindowEventArgs args(((WindowEventArgs&)e).window);
	onSegmentSized(args);

	return true;
}



bool ListHeader::segmentMovedHandler(const EventArgs& e)
{
	Point mousePos(MouseCursor::getSingleton().getPosition());

	
	if (isHit(mousePos))
	{
		
		Point localMousePos(screenToWindow(mousePos));

		
		float currwidth = -d_segmentOffset;

		
		if (getMetricsMode() == Relative)
		{
			localMousePos = relativeToAbsolute(localMousePos);
			currwidth = relativeToAbsoluteX(currwidth);
		}

		
        uint col;
		for (col = 0; col < getColumnCount(); ++col)
		{
			currwidth += d_segments[col]->getAbsoluteWidth();

			if (localMousePos.d_x < currwidth)
			{
				
				break;
			}

		}

		
		ListHeaderSegment* seg = ((ListHeaderSegment*)((WindowEventArgs&)e).window);
		uint curcol = getColumnFromSegment(*seg);

		
		moveColumn(curcol, col);
	}

	return true;
}



bool ListHeader::segmentClickedHandler(const EventArgs& e)
{
	
	if (d_sortingEnabled)
	{
		ListHeaderSegment* seg = ((ListHeaderSegment*)((WindowEventArgs&)e).window);

		
		if (d_sortSegment != seg)
		{
			
			setSortSegment(*seg);
		}
		
		else if (d_sortSegment != NULL)
		{
			ListHeaderSegment::SortDirection currDir = d_sortSegment->getSortDirection();

			
			switch (currDir)
			{
			case ListHeaderSegment::None:
				setSortDirection(ListHeaderSegment::None);
				
				break;

			case ListHeaderSegment::Ascending:
				setSortDirection(ListHeaderSegment::Descending);
				break;

			case ListHeaderSegment::Descending:
				setSortDirection(ListHeaderSegment::Ascending);
				break;
			}

		}

		
		WindowEventArgs args(((WindowEventArgs&)e).window);
		onSegmentClicked(args);
	}

	return true;
}



bool ListHeader::segmentDoubleClickHandler(const EventArgs& e)
{
	WindowEventArgs args(((WindowEventArgs&)e).window);
	onSplitterDoubleClicked(args);

	return true;
}



bool ListHeader::segmentDragHandler(const EventArgs& e)
{
	

	
	Point localMousePos(screenToWindow(MouseCursor::getSingleton().getPosition()));

	MetricsMode mmode = getMetricsMode();

	
	if (mmode == Relative)
	{
		localMousePos = relativeToAbsolute(localMousePos);
	}

	
	if (localMousePos.d_x < 0.0f)
	{
		if (d_segmentOffset > 0.0f)
		{
			float adjust = ScrollSpeed;
			
			if (mmode == Relative)
			{
				adjust = absoluteToRelativeX(adjust);
			}
			
			setSegmentOffset(std::max(0.0f, d_segmentOffset - adjust));
		}

	}
	
	else if (localMousePos.d_x >= getAbsoluteWidth())
	{
		float adjust	= ScrollSpeed;
		float pixOffset = d_segmentOffset;
		float maxOffset = std::max(0.0f, getTotalSegmentsPixelExtent() - getAbsoluteWidth());

		
		if (mmode == Relative)
		{
			maxOffset = absoluteToRelativeX(maxOffset);
			pixOffset = relativeToAbsoluteX(pixOffset);
			adjust = absoluteToRelativeX(adjust);
		}

		
		if (d_segmentOffset < maxOffset)
		{
			
			setSegmentOffset(std::min(maxOffset, d_segmentOffset + adjust));
		}

	}

	return true;
}


void ListHeader::addHeaderProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( ListHeader );
	   CEGUI_ADD_STATICPROPERTY( &d_sizableProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_movableProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_sortSettingProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_sortColumnIDProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_sortDirectionProperty );
	CEGUI_END_ADD_STATICPROPERTY
}


} 
