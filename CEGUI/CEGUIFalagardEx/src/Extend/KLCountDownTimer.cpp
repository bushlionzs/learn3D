
#include "KLCountDownTimer.h"



namespace CEGUI
{
	
	
	
	
	
    const utf8  KLCountDownTimer::WidgetTypeName[] = "Falagard/CountDownTimer";

	KLCountDownTimerProperties::Step			KLCountDownTimer::d_stepProperty;
	KLCountDownTimerProperties::Timer			KLCountDownTimer::d_timeProperty;

    KLCountDownTimer::KLCountDownTimer(const String& type, const String& name) :
        KLSimpleText(type, name),
		f_currentTime(0.f),
		d_timeStep(-1)
    {
        addStopWatchProperties();

		//f_lastSecond = System::getSingleton().getCurTimeElapsed();
		setNeedRealTimeUpdate(true);
    }

    KLCountDownTimer::~KLCountDownTimer()
    {
    }

	void KLCountDownTimer::addStopWatchProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( KLCountDownTimer )
		   CEGUI_ADD_STATICPROPERTY( &d_stepProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_timeProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	void KLCountDownTimer::setStep(int step)
	{
		d_timeStep = step;
		
		String value = getTimeText(int(f_currentTime));
		setText(value.c_str());
		requestRedraw();
	}

	void KLCountDownTimer::setTimer(int time)
	{
		f_currentTime = (float)(time);
		f_currentTimeInt = -1;
		//f_lastSecond = System::getSingleton().getCurTimeElapsed();

		
		String value = getTimeText(time);
		

		setText(value.c_str());
		requestRedraw();
	}

	String KLCountDownTimer::getTimeText(int currTime)
	{
		char value[128] = {0};

		int day;
		int hour;
		int minute;
		int second;
		float tmpNum;

		day		= currTime / (3600 * 24);
		if( day > 0 )
		{
			tmpNum = float(currTime * 1.0f / ( 3600 * 24) );
			day = int( ceil( int(tmpNum * 100) * 0.01f ) );
		}

		hour = (currTime % (3600 * 24)) / 3600;
		if( hour > 0 )
		{
			tmpNum = float((currTime % (3600 * 24)) * 1.0f / 3600);
			hour = int( ceil( int(tmpNum * 100) * 0.01f ) );
		}
		if( day == 0 && hour > 23 )
			day = 1;

		minute = (currTime %  3600) / 60;
		if( minute > 0 )
		{
			tmpNum = float((currTime %  3600) * 1.0f / 60);
			minute = int( ceil( int(tmpNum * 100) * 0.01f ) );
		}
		if( day == 0 && hour == 0 && minute > 59 )
			hour = 1;

		second = currTime % 60;
		

		if( day == 0 )
		{
			if( hour == 0 )
			{
				if( minute == 0 )
				{
					
					if( second != 0 )
						_snprintf(value, 128, "%ds", second);
				}
				else
					_snprintf(value, 128, "%dm", minute);
			}
			else
			{
				_snprintf(value, 128, "%dh", hour);
			}
		}
		else
		{
			_snprintf(value, 128, "%dd", day);
		}
		return value;
	}

	void KLCountDownTimer::updateSelf(float elapsed)
	{
		if(f_currentTime == 0.f || f_currentTime < -1.f) 
		{
			setText("");
			requestRedraw();		
			return;
		}
		if(f_currentTime <= -1.f )
		{
			setText("N/A");
			requestRedraw();
			return;
		}
		//float fNowTime = System::getSingleton().getCurTimeElapsed();
		
		//float fElapsed = fNowTime - f_lastSecond;
		//if( fElapsed >= 1.f )
		{
			f_currentTime -= elapsed;
			if (f_currentTime < 0.f)
				f_currentTime = 0.f;

			//f_lastSecond = fNowTime;

			int n = int( ceil(f_currentTime) );
			if( n != 0 && n != f_currentTimeInt )
			{
				f_currentTimeInt = n;

				String value = getTimeText(n);	
				
				setText(value.c_str());

				requestRedraw();
			}
		}

		KLSimpleText::updateSelf(elapsed);
	}

    
    
    
    Window* KLCountDownTimerFactory::createWindow(const String& name)
    {
        return new KLCountDownTimer(d_type, name);
    }

    void KLCountDownTimerFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}