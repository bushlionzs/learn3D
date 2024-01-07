

#include "elements/CEGUIThumb.h"


namespace CEGUI
{
const String Thumb::EventNamespace("Thumb");


ThumbProperties::HotTracked	Thumb::d_hotTrackedProperty;
ThumbProperties::VertFree	Thumb::d_vertFreeProperty;
ThumbProperties::HorzFree	Thumb::d_horzFreeProperty;
ThumbProperties::VertRange	Thumb::d_vertRangeProperty;
ThumbProperties::HorzRange	Thumb::d_horzRangeProperty;




const String Thumb::EventThumbPositionChanged( (utf8*)"ThumbPosChanged" );
const String Thumb::EventThumbTrackStarted( (utf8*)"ThumbTrackStarted" );
const String Thumb::EventThumbTrackEnded( (utf8*)"ThumbTrackEnded" );



Thumb::Thumb(const String& type, const String& name) :
	PushButton(type, name),
	d_hotTrack(true),
	d_vertFree(false),
	d_horzFree(false),
	d_vertMin(0.0f),
	d_vertMax(1.0f),
    d_horzMin(0.0f),
	d_horzMax(1.0f),
    d_beingDragged(false)
{
	addThumbProperties();
}



Thumb::~Thumb(void)
{
}



void Thumb::setVertRange(float min, float max)
{
	
	if (min > max)
	{
		float tmp = min;
		max = min;
		min = tmp;
	}

	d_vertMax = max;
	d_vertMin = min;

	
	float cp = getYPosition();

	if (cp < min)
	{
		setYPosition(min);
	}
	else if (cp > max)
	{
		setYPosition(max);
	}

}



void Thumb::setHorzRange(float min, float max)
{
	
	if (min > max)
	{
		float tmp = min;
		max = min;
		min = tmp;
	}

	d_horzMax = max;
	d_horzMin = min;

	
	float cp = getXPosition();

	if (cp < min)
	{
		setXPosition(min);
	}
	else if (cp > max)
	{
		setXPosition(max);
	}

}


void Thumb::onThumbPositionChanged(WindowEventArgs& e)
{
	fireEvent(EventThumbPositionChanged, e, EventNamespace);
}



void Thumb::onThumbTrackStarted(WindowEventArgs& e)
{
	fireEvent(EventThumbTrackStarted, e, EventNamespace);
}



void Thumb::onThumbTrackEnded(WindowEventArgs& e)
{
	fireEvent(EventThumbTrackEnded, e, EventNamespace);
}



void Thumb::onMouseMove(MouseEventArgs& e)
{
	
	PushButton::onMouseMove(e);

	
	if (d_beingDragged)
	{
		Vector2 delta;
		float hmin, hmax, vmin, vmax;

		
		if (getMetricsMode() == Relative)
		{
			delta = relativeToAbsolute(screenToWindow(e.position));

			hmax = relativeToAbsoluteX_impl(d_parent, d_horzMax);
			hmin = relativeToAbsoluteX_impl(d_parent, d_horzMin);
			vmax = relativeToAbsoluteY_impl(d_parent, d_vertMax);
			vmin = relativeToAbsoluteY_impl(d_parent, d_vertMin);
		}
		else
		{
			delta = screenToWindow(e.position);

			hmin = d_horzMin;
			hmax = d_horzMax;
			vmin = d_vertMin;
			vmax = d_vertMax;
		}

		
		delta -= d_dragPoint;

		
		
		
		Point newPos(getAbsolutePosition());

		if (d_horzFree)
		{
			newPos.d_x += delta.d_x;

			
			newPos.d_x = (newPos.d_x < hmin) ? hmin : (newPos.d_x > hmax) ? hmax : newPos.d_x;
		}

		if (d_vertFree)
		{
			newPos.d_y += delta.d_y;

			
			newPos.d_y = (newPos.d_y < vmin) ? vmin : (newPos.d_y > vmax) ? vmax : newPos.d_y;
		}

		
		if (newPos != getAbsolutePosition())
		{
			if (getMetricsMode() == Relative)
			{
				newPos = absoluteToRelative_impl(d_parent, newPos);
			}

			setPosition(newPos);

			
			if (d_hotTrack)
			{
				WindowEventArgs args(this);
				onThumbPositionChanged(args);
			}

		}

	}

	e.handled = true;
}



void Thumb::onMouseButtonDown(MouseEventArgs& e)
{
	
	PushButton::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		
		d_beingDragged = true;
		d_dragPoint = screenToWindow(e.position);

		if (getMetricsMode() == Relative)
		{
			d_dragPoint = relativeToAbsolute(d_dragPoint);
		}

		
		WindowEventArgs args(this);
		onThumbTrackStarted(args);

		e.handled = true;
	}

}



void Thumb::onCaptureLost(WindowEventArgs& e)
{
	
	PushButton::onCaptureLost(e);

	d_beingDragged = false;

	
	WindowEventArgs args(this);
	onThumbTrackEnded(args);

	
	onThumbPositionChanged(args);
}



std::pair<float, float>	Thumb::getVertRange(void) const
{
	return std::make_pair(d_vertMin, d_vertMax);
}



std::pair<float, float>	Thumb::getHorzRange(void) const
{
	return std::make_pair(d_horzMin, d_horzMax);
}



void Thumb::addThumbProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( Thumb );
	   CEGUI_ADD_STATICPROPERTY( &d_hotTrackedProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_vertFreeProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_horzFreeProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_vertRangeProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_horzRangeProperty );
	CEGUI_END_ADD_STATICPROPERTY
}


} 
