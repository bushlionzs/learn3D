

#ifndef _CEGUIProgressBar_h_
#define _CEGUIProgressBar_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIProgressBarProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT ProgressBar : public Window
{
public:
	static const String EventNamespace;				


	
	static const String EventProgressChanged;		
	static const String EventProgressDone;		


	
	
	float	getProgress(void) const		{return d_progress;}

	
	float	getStep(void) const			{return d_step;}


	
	
	void	setProgress(float progress);


	
	void	setStepSize(float step_val)		{d_step = step_val;}


	
	void	step(void)			{setProgress(d_progress + d_step);}


	
	void	adjustProgress(float delta)		{setProgress(d_progress + delta);}


	
	
	ProgressBar(const String& type, const String& name);


	
	virtual ~ProgressBar(void);


protected:
	

	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"ProgressBar")	return true;
		return Window::testClassName_impl(class_name);
	}


	
	
	virtual	void	onProgressChanged(WindowEventArgs& e);


	
	virtual void	onProgressDone(WindowEventArgs& e);


	
	float	d_progress;		
	float	d_step;			


private:
	
	static ProgressBarProperties::CurrentProgress	d_currentProgressProperty;
	static ProgressBarProperties::StepSize			d_stepSizeProperty;


	
	void	addProgressBarProperties(void);
};


} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
