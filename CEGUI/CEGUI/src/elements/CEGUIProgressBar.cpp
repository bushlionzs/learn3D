

#include "elements/CEGUIProgressBar.h"


namespace CEGUI
{
const String ProgressBar::EventNamespace("ProgressBar");


ProgressBarProperties::CurrentProgress	ProgressBar::d_currentProgressProperty;
ProgressBarProperties::StepSize			ProgressBar::d_stepSizeProperty;



const String ProgressBar::EventProgressChanged( (utf8*)"ProgressChanged" );
const String ProgressBar::EventProgressDone( (utf8*)"ProgressDone" );



ProgressBar::ProgressBar(const String& type, const String& name) :
	Window(type, name),
	d_progress(0),
	d_step(0.01f)
{
	addProgressBarProperties();
}



ProgressBar::~ProgressBar(void)
{
}



void ProgressBar::setProgress(float progress)
{
	
	progress = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;

	if (progress != d_progress)
	{
		
		d_progress = progress;
		WindowEventArgs args(this);
		onProgressChanged(args);

		
		if (d_progress == 1.0f)
		{
			onProgressDone(args);
		}

	}

}


void ProgressBar::onProgressChanged(WindowEventArgs& e)
{
	requestRedraw();

	fireEvent(EventProgressChanged, e, EventNamespace);
}



void ProgressBar::onProgressDone(WindowEventArgs& e)
{
	fireEvent(EventProgressDone, e, EventNamespace);
}


void ProgressBar::addProgressBarProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( ProgressBar );
	   CEGUI_ADD_STATICPROPERTY( &d_stepSizeProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_currentProgressProperty );
	CEGUI_END_ADD_STATICPROPERTY
}


} 
