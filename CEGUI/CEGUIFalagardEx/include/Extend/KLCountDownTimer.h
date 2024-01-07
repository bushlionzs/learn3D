#ifndef _FalagardCountDownTimer_h_
#define _FalagardCountDownTimer_h_


#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLCountDownTimerProperties.h"
#include "KLSimpleText.h"


namespace CEGUI
{

    class FALAGARDBASE_API KLCountDownTimer :	public KLSimpleText
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        KLCountDownTimer(const String& type, const String& name);

        
        ~KLCountDownTimer();

		
		void	setStep(int step);
		int		getStep(void) const { return d_timeStep; }

		void	setTimer(int time);
		
		int		getTimer(void) const { return int(f_currentTime); }

    protected:
        

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLCountDownTimer")	return true;
			return Window::testClassName_impl(class_name);
		}

		virtual void	updateSelf(float elapsed);

		String	getTimeText(int currTime);

		
		float			f_lastSecond;				
		int				d_timeStep;
		float			f_currentTime;
		int             f_currentTimeInt;

	private:
        
		static KLCountDownTimerProperties::Step			d_stepProperty;
		static KLCountDownTimerProperties::Timer			d_timeProperty;

        

        
        void addStopWatchProperties(void);

    };

    
    class FALAGARDBASE_API KLCountDownTimerFactory : public WindowFactory
    {
    public:
        KLCountDownTimerFactory(void) : WindowFactory(KLCountDownTimer::WidgetTypeName) { }
        ~KLCountDownTimerFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}



#endif