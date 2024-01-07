

#include "elements/CEGUISlider.h"
#include "elements/CEGUIThumb.h"


namespace CEGUI
{
const String Slider::EventNamespace("Slider");


SliderProperties::CurrentValue	Slider::d_currentValueProperty;
SliderProperties::MaximumValue	Slider::d_maximumValueProperty;
SliderProperties::ClickStepSize	Slider::d_clickStepSizeProperty;



const String Slider::EventValueChanged( (utf8*)"ValueChanged" );
const String Slider::EventThumbTrackStarted( (utf8*)"ThumbTrackStarted" );
const String Slider::EventThumbTrackEnded( (utf8*)"ThumbTrackEnded" );



Slider::Slider(const String& type, const String& name) :
	Window(type, name),
	d_value(0.0f),
	d_maxValue(1.0f),
	d_step(0.01f),
	d_thumb(NULL)
{
	addSliderProperties();
}



Slider::~Slider(void)
{
}



void Slider::initialise(void)
{
	
	d_thumb = createThumb(getName() + "__auto_thumb__");
	addChildWindow(d_thumb);

	
	d_thumb->subscribeEvent(Thumb::EventThumbPositionChanged, Event::Subscriber(&CEGUI::Slider::handleThumbMoved, this));
	d_thumb->subscribeEvent(Thumb::EventThumbTrackStarted, Event::Subscriber(&CEGUI::Slider::handleThumbTrackStarted, this));
	d_thumb->subscribeEvent(Thumb::EventThumbTrackEnded, Event::Subscriber(&CEGUI::Slider::handleThumbTrackEnded, this));

	performChildWindowLayout();
}



void Slider::setMaxValue(float maxVal)
{
	d_maxValue = maxVal;

	float oldval = d_value;

	
	if (d_value > d_maxValue) {
		d_value = d_maxValue;
	}

	updateThumb();

	
	if (d_value != oldval)
	{
		WindowEventArgs args(this);
		onValueChanged(args);
	}

}



void Slider::setCurrentValue(float value)
{
	float oldval = d_value;

	
	d_value = (value >= 0.0f) ? ((value <= d_maxValue) ? value : d_maxValue) : 0.0f;

	updateThumb();

	
	if (d_value != oldval)
	{
		WindowEventArgs args(this);
		onValueChanged(args);
	}

}


void Slider::onValueChanged(WindowEventArgs& e)
{
	fireEvent(EventValueChanged, e, EventNamespace);
}



void Slider::onThumbTrackStarted(WindowEventArgs& e)
{
	fireEvent(EventThumbTrackStarted, e, EventNamespace);
}



void Slider::onThumbTrackEnded(WindowEventArgs& e)
{
	fireEvent(EventThumbTrackEnded, e, EventNamespace);
}



void Slider::onMouseButtonDown(MouseEventArgs& e)
{
	
	Window::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		float adj = getAdjustDirectionFromPoint(e.position);

		
		if (adj != 0)
		{
			setCurrentValue(d_value + (adj * d_step));
		}

		e.handled = true;
	}

}



void Slider::onMouseWheel(MouseEventArgs& e)
{
	
	Window::onMouseWheel(e);

	
	setCurrentValue(d_value + d_step * -e.wheelChange);

	
	e.handled = true;
}



bool Slider::handleThumbMoved(const EventArgs& e)
{
	setCurrentValue(getValueFromThumb());

	return true;
}



bool Slider::handleThumbTrackStarted(const EventArgs& e)
{
	
	WindowEventArgs args(this);
	onThumbTrackStarted(args);

	return true;
}



bool Slider::handleThumbTrackEnded(const EventArgs& e)
{
	
	WindowEventArgs args(this);
	onThumbTrackEnded(args);

	return true;
}



void Slider::addSliderProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( Slider );
	   CEGUI_ADD_STATICPROPERTY( &d_currentValueProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_clickStepSizeProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_maximumValueProperty );
	CEGUI_END_ADD_STATICPROPERTY
}


} 
