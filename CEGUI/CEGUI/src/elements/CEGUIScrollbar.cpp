

#include "elements/CEGUIScrollbar.h"
#include "elements/CEGUIThumb.h"



namespace CEGUI
{
const String Scrollbar::EventNamespace("Scrollbar");


ScrollbarProperties::DocumentSize	Scrollbar::d_documentSizeProperty;
ScrollbarProperties::PageSize		Scrollbar::d_pageSizeProperty;
ScrollbarProperties::StepSize		Scrollbar::d_stepSizeProperty;
ScrollbarProperties::OverlapSize	Scrollbar::d_overlapSizeProperty;
ScrollbarProperties::ScrollPosition	Scrollbar::d_scrollPositionProperty;



const String Scrollbar::EventScrollPositionChanged( (utf8*)"ScrollPosChanged" );
const String Scrollbar::EventThumbTrackStarted( (utf8*)"ThumbTrackStarted" );
const String Scrollbar::EventThumbTrackEnded( (utf8*)"ThumbTrackEnded" );
const String Scrollbar::EventScrollConfigChanged( (utf8*)"ScrollConfigChanged" );



Scrollbar::Scrollbar(const String& type, const String& name) :
	Window(type, name),
	d_documentSize(1.0f),
	d_pageSize(0.0f),
	d_stepSize(1.0f),
	d_overlapSize(0.0f),
	d_position(0.0f),
	d_usedInCombobox(false),
	d_comboboxScrollbarMaxWidth(1000)
{
	addScrollbarProperties();
}



Scrollbar::~Scrollbar(void)
{
}



void Scrollbar::initialise(void)
{
	
	d_thumb = createThumb(getName() + "__auto_thumb__");
	addChildWindow(d_thumb);
	d_thumb->subscribeEvent(Thumb::EventThumbPositionChanged, Event::Subscriber(&CEGUI::Scrollbar::handleThumbMoved, this));
	d_thumb->subscribeEvent(Thumb::EventThumbTrackStarted, Event::Subscriber(&CEGUI::Scrollbar::handleThumbTrackStarted, this));
	d_thumb->subscribeEvent(Thumb::EventThumbTrackEnded, Event::Subscriber(&CEGUI::Scrollbar::handleThumbTrackEnded, this));

	
	d_increase = createIncreaseButton(getName() + "__auto_incbtn__");
	addChildWindow(d_increase);
	d_increase->subscribeEvent(PushButton::EventMouseButtonDown, Event::Subscriber(&CEGUI::Scrollbar::handleIncreaseClicked, this));
	d_increase->subscribeEvent(PushButton::EventMouseMultiDown, Event::Subscriber(&CEGUI::Scrollbar::handleUpButtonMouseMultiDown, this));

	
	d_decrease = createDecreaseButton(getName() + "__auto_decbtn__");
	addChildWindow(d_decrease);
	d_decrease->subscribeEvent(PushButton::EventMouseButtonDown, Event::Subscriber(&CEGUI::Scrollbar::handleDecreaseClicked, this));
	d_decrease->subscribeEvent(PushButton::EventMouseMultiDown, Event::Subscriber(&CEGUI::Scrollbar::handleDownButtonMouseMultiDown, this));
	
	performChildWindowLayout();
}

void Scrollbar::setUsedInCombobox(bool bUsedInCombobox)
{
	d_usedInCombobox = bUsedInCombobox;
}

void Scrollbar::setComboboxScrollbarMaxWidth(int maxWidth)
{
	d_comboboxScrollbarMaxWidth = maxWidth;
}

void Scrollbar::onParentSized(WindowEventArgs& e)
{
	if(getName() == "Chat_Frame_History__auto_vscrollbar__")
	{
		int k = 0;
	}

	Window::onParentSized(e);
}

void Scrollbar::onSized(WindowEventArgs& e)
{
	if(d_usedInCombobox)
	{
		if(getAbsoluteWidth() > d_comboboxScrollbarMaxWidth)
		{
			setWidth(Absolute, d_comboboxScrollbarMaxWidth);
		}
		
		if(getParent())
		{
			float y = getAbsolutePosition().d_y;
			
			
			Point pos(getParent()->getWidth(Absolute) - getWidth(Absolute), y);

			setPosition(Absolute, pos);
		}
	}

	Window::onSized(e);
}


void Scrollbar::setDocumentSize(float document_size)
{
	if (d_documentSize != document_size)
	{
		d_documentSize = document_size;
		updateThumb();

		WindowEventArgs args(this);
		onScrollConfigChanged(args);
	}

}



void Scrollbar::setPageSize(float page_size)
{
	if (d_pageSize != page_size)
	{
		d_pageSize = page_size;
		updateThumb();

		WindowEventArgs args(this);
		onScrollConfigChanged(args);
	}

}



void Scrollbar::setStepSize(float step_size)
{
	if (d_stepSize != step_size)
	{
		d_stepSize = step_size;

		WindowEventArgs args(this);
		onScrollConfigChanged(args);
	}

}



void Scrollbar::setOverlapSize(float overlap_size)
{
	if (d_overlapSize != overlap_size)
	{
		d_overlapSize = overlap_size;

		WindowEventArgs args(this);
		onScrollConfigChanged(args);
	}

}



void Scrollbar::setScrollPosition(float position)
{
	float old_pos = d_position;

	
	float max_pos = std::max((d_documentSize - d_pageSize), 0.0f);

	
	d_position = (position >= 0) ? ((position <= max_pos) ? position : max_pos) : 0.0f;

	updateThumb();

	
	if (d_position != old_pos)
	{
		WindowEventArgs args(this);
		onScrollPositionChanged(args);
	}

}


void Scrollbar::onScrollPositionChanged(WindowEventArgs& e)
{
	fireEvent(EventScrollPositionChanged, e, EventNamespace);
}



void Scrollbar::onThumbTrackStarted(WindowEventArgs& e)
{
	fireEvent(EventThumbTrackStarted, e, EventNamespace);
}



void Scrollbar::onThumbTrackEnded(WindowEventArgs& e)
{
	fireEvent(EventThumbTrackEnded, e, EventNamespace);
}



void Scrollbar::onScrollConfigChanged(WindowEventArgs& e)
{
	fireEvent(EventScrollConfigChanged, e, EventNamespace);
}




void Scrollbar::onMouseButtonDown(MouseEventArgs& e)
{
	
	Window::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		float adj = getAdjustDirectionFromPoint(e.position);

		
		if (adj != 0)
		{
			setScrollPosition(d_position + (d_stepSize * adj));
		}

		e.handled = true;
	}

}


void Scrollbar::onMouseMultiDown(MouseEventArgs& e)
{
	
	Window::onMouseMultiDown(e);

	if ( e.button == LeftButton )
	{

		float adj = getAdjustDirectionFromPoint(e.position);

		
		if (adj != 0)
		{
			setScrollPosition(d_position + (d_stepSize * adj));
		}

		e.handled = true;
	}

}


void Scrollbar::onMouseWheel(MouseEventArgs& e)
{
	
	Window::onMouseWheel(e);

	
	setScrollPosition(d_position + d_stepSize * -e.wheelChange);

	
	e.handled = true;
}

void Scrollbar::setSpecialModal(bool spModual)
{
	d_specialModal = spModual;

	if( d_thumb )
		d_thumb->setSpecialModal(spModual);

	if( d_increase )
		d_increase->setSpecialModal(spModual);

	if( d_decrease )
		d_decrease->setSpecialModal(spModual);
}


bool Scrollbar::handleThumbMoved(const EventArgs& e)
{
	
	setScrollPosition(getValueFromThumb());

	return true;
}



bool Scrollbar::handleIncreaseClicked(const EventArgs& e)
{
	if (((const MouseEventArgs&)e).button == LeftButton)
	{
		
		setScrollPosition(d_position + d_stepSize);

		return true;
	}
	else
	{
		return false;
	}

}



bool Scrollbar::handleDecreaseClicked(const EventArgs& e)
{
	if (((const MouseEventArgs&)e).button == LeftButton)
	{
		
		setScrollPosition(d_position - d_stepSize);

		return true;
	}
	else
	{
		return false;
	}
}
bool Scrollbar::handleUpButtonMouseMultiDown(const EventArgs& e)
{
	if (((const MouseEventArgs&)e).button == LeftButton)
	{
		
		setScrollPosition(d_position + d_stepSize);

		return true;
	}
	else
	{
		return false;
	}
}

bool Scrollbar::handleDownButtonMouseMultiDown(const EventArgs& e)
{
	if (((const MouseEventArgs&)e).button == LeftButton)
	{
		
		setScrollPosition(d_position - d_stepSize);

		return true;
	}
	else
	{
		return false;
	}
}


bool Scrollbar::handleThumbTrackStarted(const EventArgs& e)
{
	
	WindowEventArgs args(this);
	onThumbTrackStarted(args);

	return true;
}



bool Scrollbar::handleThumbTrackEnded(const EventArgs& e)
{
	
	WindowEventArgs args(this);
	onThumbTrackEnded(args);

	return true;
}



void Scrollbar::addScrollbarProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( Scrollbar );
	   CEGUI_ADD_STATICPROPERTY( &d_documentSizeProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_pageSizeProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_stepSizeProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_overlapSizeProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_scrollPositionProperty );
	CEGUI_END_ADD_STATICPROPERTY
}



} 
