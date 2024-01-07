

#ifndef _CEGUISlider_h_
#define _CEGUISlider_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUISliderProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT Slider : public Window
{
public:
	static const String EventNamespace;				


	
	static const String EventValueChanged;		
	static const String EventThumbTrackStarted;	
	static const String EventThumbTrackEnded;		


	
	
	float	getCurrentValue(void) const			{return d_value;}


	
	float	getMaxValue(void) const				{return d_maxValue;}


	
	float	getClickStep(void) const		{return d_step;}


	
	
	virtual	void	initialise(void);


	
	void	setMaxValue(float maxVal);


	
	void	setCurrentValue(float value);


	
	void	setClickStep(float step)		{d_step = step;}


	
	
	Slider(const String& type, const String& name);


	
	virtual ~Slider(void);


protected:
	

	
	virtual Thumb*	createThumb(const String& name) const		= 0;


	
	virtual void	updateThumb(void)	= 0;


	
	virtual float	getValueFromThumb(void) const	= 0;


	
	virtual float	getAdjustDirectionFromPoint(const Point& pt) const	= 0;


	
	bool	handleThumbMoved(const EventArgs& e);


	
	bool	handleThumbTrackStarted(const EventArgs& e);


	
	bool	handleThumbTrackEnded(const EventArgs& e);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Slider")	return true;
		return Window::testClassName_impl(class_name);
	}


	
	
	virtual void	onValueChanged(WindowEventArgs& e);


	
	virtual void	onThumbTrackStarted(WindowEventArgs& e);


	
	virtual void	onThumbTrackEnded(WindowEventArgs& e);


	
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual	void	onMouseWheel(MouseEventArgs& e);


	
	float	d_value;		
	float	d_maxValue;		
	float	d_step;			

	
	Thumb*	d_thumb;		


private:
	
	static SliderProperties::CurrentValue	d_currentValueProperty;
	static SliderProperties::MaximumValue	d_maximumValueProperty;
	static SliderProperties::ClickStepSize	d_clickStepSizeProperty;


	
	void	addSliderProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
