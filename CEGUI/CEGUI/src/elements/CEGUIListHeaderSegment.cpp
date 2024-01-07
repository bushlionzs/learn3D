

#include "elements/CEGUIListHeaderSegment.h"
#include "CEGUIMouseCursor.h"



namespace CEGUI
{
const String ListHeaderSegment::EventNamespace("ListHeaderSegment");


ListHeaderSegmentProperties::Clickable		ListHeaderSegment::d_clickableProperty;
ListHeaderSegmentProperties::Dragable		ListHeaderSegment::d_dragableProperty;
ListHeaderSegmentProperties::Sizable		ListHeaderSegment::d_sizableProperty;
ListHeaderSegmentProperties::SortDirection	ListHeaderSegment::d_sortDirectionProperty;




const String ListHeaderSegment::EventSegmentClicked( (utf8*)"SegmentClicked" );
const String ListHeaderSegment::EventSplitterDoubleClicked( (utf8*)"SplitterDoubleClicked" );
const String ListHeaderSegment::EventSizingSettingChanged( (utf8*)"SizingSettingChanged" );
const String ListHeaderSegment::EventSortDirectionChanged( (utf8*)"SortDirectionChanged" );
const String ListHeaderSegment::EventMovableSettingChanged( (utf8*)"MovableSettingChanged" );
const String ListHeaderSegment::EventSegmentDragStart( (utf8*)"SegmentDragStart" );
const String ListHeaderSegment::EventSegmentDragStop( (utf8*)"SegmentDragStop" );
const String ListHeaderSegment::EventSegmentDragPositionChanged( (utf8*)"SegmentDragPositionChanged" );
const String ListHeaderSegment::EventSegmentSized( (utf8*)"SegmentSized" );
const String ListHeaderSegment::EventClickableSettingChanged( (utf8*)"ClickableSettingChanged" );


const float	ListHeaderSegment::DefaultSizingArea	= 8.0f;
const float	ListHeaderSegment::SegmentMoveThreshold	= 12.0f;



ListHeaderSegment::ListHeaderSegment(const String& type, const String& name) :
	Window(type, name),
	d_sizingMouseCursor(NULL),
	d_movingMouseCursor(NULL),
	d_splitterSize(DefaultSizingArea),
	d_splitterHover(false),
	d_dragSizing(false),
	d_sortDir(None),
	d_segmentHover(false),
	d_segmentPushed(false),
	d_sizingEnabled(false),
	d_movingEnabled(false),
	d_dragMoving(false),
	d_allowClicks(true)
{
	addHeaderSegmentProperties();
}



ListHeaderSegment::~ListHeaderSegment(void)
{
}



void ListHeaderSegment::setSizingEnabled(bool setting)
{
	if (d_sizingEnabled != setting)
	{
		d_sizingEnabled = setting;

		
		if (!d_sizingEnabled && d_dragSizing)
		{
			releaseInput();
		}

		WindowEventArgs args(this);
		onSizingSettingChanged(args);
	}

}



void ListHeaderSegment::setSortDirection(SortDirection sort_dir)
{
	if (d_sortDir != sort_dir)
	{
		d_sortDir = sort_dir;

		WindowEventArgs args(this);
		onSortDirectionChanged(args);

		requestRedraw();
	}

}



void ListHeaderSegment::setDragMovingEnabled(bool setting)
{
	if (d_movingEnabled != setting)
	{
		d_movingEnabled = setting;

		WindowEventArgs args(this);
		onMovableSettingChanged(args);
	}

}



void ListHeaderSegment::setClickable(bool setting)
{
	if (d_allowClicks != setting)
	{
		d_allowClicks = setting;

		WindowEventArgs args(this);
		onClickableSettingChanged(args);
	}

}



void ListHeaderSegment::onSegmentClicked(WindowEventArgs& e)
{
	fireEvent(EventSegmentClicked, e, EventNamespace);
}



void ListHeaderSegment::onSplitterDoubleClicked(WindowEventArgs& e)
{
	fireEvent(EventSplitterDoubleClicked, e, EventNamespace);
}



void ListHeaderSegment::onSizingSettingChanged(WindowEventArgs& e)
{
	fireEvent(EventSizingSettingChanged, e, EventNamespace);
}



void ListHeaderSegment::onSortDirectionChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventSortDirectionChanged, e, EventNamespace);
}



void ListHeaderSegment::onMovableSettingChanged(WindowEventArgs& e)
{
	fireEvent(EventMovableSettingChanged, e, EventNamespace);
}



void ListHeaderSegment::onSegmentDragStart(WindowEventArgs& e)
{
	fireEvent(EventSegmentDragStart, e, EventNamespace);
}



void ListHeaderSegment::onSegmentDragStop(WindowEventArgs& e)
{
	fireEvent(EventSegmentDragStop, e, EventNamespace);
}



void ListHeaderSegment::onSegmentDragPositionChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventSegmentDragPositionChanged, e, EventNamespace);
}



void ListHeaderSegment::onSegmentSized(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventSegmentSized, e, EventNamespace);
}



void ListHeaderSegment::onClickableSettingChanged(WindowEventArgs& e)
{
	fireEvent(EventClickableSettingChanged, e, EventNamespace);
}



void ListHeaderSegment::doDragSizing(const Point& local_mouse)
{
    float delta = local_mouse.d_x - d_dragPoint.d_x;

    
    float orgWidth = getAbsoluteWidth();

    
    
    
    
    
    float maxWidth(d_maxSize.d_x.asAbsolute(System::getSingleton().getRenderer()->getWidth()));
    float minWidth(d_minSize.d_x.asAbsolute(System::getSingleton().getRenderer()->getWidth()));
    float newWidth = orgWidth + delta;

    if (newWidth > maxWidth)
        delta = maxWidth - orgWidth;
    else if (newWidth < minWidth)
        delta = minWidth - orgWidth;
    
    
    URect area(d_area.d_min.d_x, d_area.d_min.d_y, d_area.d_max.d_x + UDim(0,PixelAligned(delta)), d_area.d_max.d_y);
    setWindowArea_impl(area.d_min, area.getSize());

    
    d_dragPoint.d_x += getAbsoluteWidth() - orgWidth;

    WindowEventArgs args(this);
    onSegmentSized(args);
}



void ListHeaderSegment::doDragMoving(const Point& local_mouse)
{
	
	float	deltaX = local_mouse.d_x - d_dragPoint.d_x;
	float	deltaY = local_mouse.d_y - d_dragPoint.d_y;

	
	d_dragPosition.d_x += deltaX;
	d_dragPosition.d_y += deltaY;

	
	d_dragPoint.d_x += deltaX;
	d_dragPoint.d_y += deltaY;

	WindowEventArgs args(this);
	onSegmentDragPositionChanged(args);
}



void ListHeaderSegment::initDragMoving(void)
{
	if (d_movingEnabled)
	{
		
		d_dragMoving = true;
		d_segmentPushed = false;
		d_segmentHover = false;
		d_dragPosition.d_x = 0.0f;
		d_dragPosition.d_y = 0.0f;

		
		MouseCursor::getSingleton().setImage(d_movingMouseCursor);

		
		WindowEventArgs args(this);
		onSegmentDragStart(args);
	}

}



void ListHeaderSegment::initSizingHoverState(void)
{
	
	if (!d_splitterHover  && !d_segmentPushed)
	{
		d_splitterHover = true;

		
		MouseCursor::getSingleton().setImage(d_sizingMouseCursor);

		
		requestRedraw();
	}

	
	if (d_segmentHover)
	{	
		d_segmentHover = false;
		requestRedraw();
	}

}



void ListHeaderSegment::initSegmentHoverState(void)
{
	
	if (d_splitterHover)
	{
		d_splitterHover = false;
		MouseCursor::getSingleton().setImage(getMouseCursor());
		requestRedraw();
	}

	
	if ((!d_segmentHover) && isClickable())
	{
		d_segmentHover = true;
		requestRedraw();
	}
}



bool ListHeaderSegment::isDragMoveThresholdExceeded(const Point& local_mouse)
{
	
	
	float	deltaX = local_mouse.d_x - d_dragPoint.d_x;
	float	deltaY = local_mouse.d_y - d_dragPoint.d_y;

	if ((deltaX > SegmentMoveThreshold) || (deltaX < -SegmentMoveThreshold) ||
		(deltaY > SegmentMoveThreshold) || (deltaY < -SegmentMoveThreshold))
	{
		return true;
	}
	else
	{
		return false;
	}

}



void ListHeaderSegment::onMouseMove(MouseEventArgs& e)
{
	
	Window::onMouseMove(e);

	
	
	
	Point localMousePos(screenToWindow(e.position));

	if (getMetricsMode() == Relative)
	{
		localMousePos = relativeToAbsolute(localMousePos);
	}

	
	if (d_dragSizing)
	{
		doDragSizing(localMousePos);
	}
	
	else if (d_dragMoving)
	{
		doDragMoving(localMousePos);
	}
	
	else if (isHit(e.position))
	{
		
		if ((localMousePos.d_x > (getAbsoluteWidth() - d_splitterSize)) && d_sizingEnabled)
		{
			initSizingHoverState();
		}
		
		else
		{
			initSegmentHoverState();

			
			if (d_segmentPushed && !d_dragMoving)
			{
				if (isDragMoveThresholdExceeded(localMousePos))
				{
					initDragMoving();
				}

			}

		}

	}
	
	else
	{
		
		if (d_splitterHover)
		{
			d_splitterHover = false;
			MouseCursor::getSingleton().setImage(getMouseCursor());
			requestRedraw();
		}

		
		if (d_segmentHover)
		{	
			d_segmentHover = false;
			requestRedraw();
		}

	}

	e.handled = true;
}



void ListHeaderSegment::onMouseButtonDown(MouseEventArgs& e)
{
	
	Window::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		
		if (captureInput())
		{
			
			Point localPos(screenToWindow(e.position));

			if (getMetricsMode() == Relative)
			{
				localPos = relativeToAbsolute(localPos);
			}

			
			d_dragPoint = localPos;

			
			if (d_splitterHover)
			{
				if (isSizingEnabled())
				{
					
					d_dragSizing = true;
				}

			}
			else
			{
				d_segmentPushed = true;
			}

		}

		e.handled = true;
	}

}



void ListHeaderSegment::onMouseButtonUp(MouseEventArgs& e)
{
	
	Window::onMouseButtonUp(e);

	if (e.button == LeftButton)
	{
		
		if (d_segmentPushed && d_segmentHover)
		{
			WindowEventArgs args(this);
			onSegmentClicked(args);
		}
		else if (d_dragMoving)
		{
			MouseCursor::getSingleton().setImage(getMouseCursor());
			
			WindowEventArgs args(this);
			onSegmentDragStop(args);
		}

		
		releaseInput();
		e.handled = true;
	}

}



void ListHeaderSegment::onMouseDoubleClicked(MouseEventArgs& e)
{
	
	Window::onMouseDoubleClicked(e);

	
	if ((e.button == LeftButton) && d_splitterHover)
	{
		WindowEventArgs args(this);
		onSplitterDoubleClicked(args);

		e.handled = true;
	}

}



void ListHeaderSegment::onMouseLeaves(MouseEventArgs& e)
{
	
	Window::onMouseLeaves(e);

	d_splitterHover = false;
	d_dragSizing = false;
	d_segmentHover = false;
	requestRedraw();
}



void ListHeaderSegment::onCaptureLost(WindowEventArgs& e)
{
	
	Window::onCaptureLost(e);

	
	d_dragSizing = false;
	d_segmentPushed = false;
	d_dragMoving = false;

	e.handled = true;
}


void ListHeaderSegment::addHeaderSegmentProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( ListHeaderSegment );
	   CEGUI_ADD_STATICPROPERTY( &d_clickableProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_sizableProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_dragableProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_sortDirectionProperty );
	CEGUI_END_ADD_STATICPROPERTY
}



} 
