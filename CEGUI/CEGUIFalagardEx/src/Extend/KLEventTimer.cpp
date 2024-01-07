#include "KLEventTimer.h"
#include "ceguiPropertyHelper.h"
#include "ceguiimagesetmanager.h"
#include "ceguiimageset.h"
#include "CEGUIKeyImageAnimationManager.h"
#include "ceguiwindowmanager.h"
#include "ceguitexture.h"
#include "CEGUIExceptions.h"
#include "KLSimpleText.h"

namespace CEGUI
{
	const utf8 KLEventTimer::WidgetTypeName[] = "Falagard/EventTimer";

	KLEventTimerProperties::FalagardEventTimerTotalTime		KLEventTimer::mEventTimerTotalTimeProperty;		
	KLEventTimerProperties::FalagardEventTimerEventTime		KLEventTimer::mEventTimerEventTimeProperty;		
	KLEventTimerProperties::FalagardEventTimerTextColor		KLEventTimer::mEventTimerTextColorProperty;	
	KLEventTimerProperties::FalagardEventTimerTextBlink		KLEventTimer::mEventTimerTextBlinkProperty;	

	const String KLEventTimer::EventNamespace("Falagard/EventTimer");
	const String KLEventTimer::EventTimerOK((utf8*)"TimerOK");

	namespace KLEventTimerProperties
	{
		String   FalagardEventTimerTotalTime::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardEventTimerTotalTime::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLEventTimer*>(receiver)->setTotalTime(PropertyHelper::stringToUint(value));
		}


		String   FalagardEventTimerEventTime::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardEventTimerEventTime::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLEventTimer*>(receiver)->setEventTime(PropertyHelper::stringToUint(value));
		}


		String   FalagardEventTimerTextColor::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardEventTimerTextColor::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLEventTimer*>(receiver)->setTimerTextColor(PropertyHelper::stringToColour(value));
		}

		String   FalagardEventTimerTextBlink::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardEventTimerTextBlink::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLEventTimer*>(receiver)->setTimerBlink(PropertyHelper::stringToBool(value));
		}
	}

	KLEventTimer::KLEventTimer(const String& type, const String& name) :
		 KLSimpleText(type, name)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLEventTimer )
			CEGUI_ADD_STATICPROPERTY( &mEventTimerTotalTimeProperty );
			CEGUI_ADD_STATICPROPERTY( &mEventTimerEventTimeProperty );
			CEGUI_ADD_STATICPROPERTY( &mEventTimerTextColorProperty );
			CEGUI_ADD_STATICPROPERTY( &mEventTimerTextBlinkProperty );
		CEGUI_END_ADD_STATICPROPERTY

		mTotalTime = 0;
		mEventTime = 0;
		mTimerTextColor = colour(1.0f, 0.0f, 0.0f, 1.0f);
		mEnableEvent = false;
		mEnableTimer = false;
		mCurrentEventTime = 0;
		mCurrentTotalTime = 0;
		mCurTotalElapsed = 0.0f;
		mCurEventElapsed = 0.0f;
		mTextBlink = false;
		setVerticalFormatting(KLSimpleText::VertCentred);
		setHorizontalFormatting(KLSimpleText::HorzCentred);
		d_clippedByParent = false;
		setTextColor(mTimerTextColor);
		setNeedRealTimeUpdate(true);
	}

	KLEventTimer::~KLEventTimer()
	{
	}
	
	void KLEventTimer::enableEvent(bool flag)
	{
		mEnableEvent = flag;
	}

	void KLEventTimer::enableTimer(bool flag)
	{
		mEnableTimer = flag;
	}

	void KLEventTimer::setTotalTime(size_t t)
	{
		mCurTotalElapsed = 0.0f;
		mTotalTime = t;
		mCurrentTotalTime = mTotalTime;
	}

	void KLEventTimer::setEventTime(size_t t)
	{
		mCurEventElapsed = 0.0f;
		mEventTime = t;
		mCurrentEventTime = mEventTime;
	}

	void KLEventTimer::setTimerTextColor(const colour &c)
	{
		mTimerTextColor = c;
		setTextColor(mTimerTextColor);
	}

	void KLEventTimer::setTimerBlink(bool flag)
	{
		mTextBlink = flag;
	}

	void KLEventTimer::resetEventState()
	{
		mEnableEvent = true;
		mCurrentEventTime = mEventTime;
	}
	void KLEventTimer::resetState()
	{
		mEnableTimer = true;
		mCurrentTotalTime = mTotalTime;
		resetEventState();
	}

	void KLEventTimer::onTimerOK(WindowEventArgs& e)
	{
		fireEvent(EventTimerOK, e, EventNamespace);
	}

	void KLEventTimer::updateSelf(float elapsed)
	{
		float time_now = System::getSingleton().getCurTimeElapsed();
		if( mCurTotalElapsed == 0.0f )
			mCurTotalElapsed = time_now;

		if( mEnableEvent )
		{
			if( mCurEventElapsed == 0.0f )
				mCurEventElapsed = time_now;

			int curElapse = int(mCurrentEventTime - time_now + mCurEventElapsed);
			if( curElapse <= 0 )
			{
				mEnableEvent = false;
				WindowEventArgs args(this);
				onTimerOK(args);
			}
		}

		if( mEnableTimer )
		{
			int curElapse = int(mCurrentTotalTime - time_now + mCurTotalElapsed);
			if( curElapse >= 0 )
			{
				if( curElapse == 0 )
				{
					mCurrentTotalTime = 0;
					mCurTotalElapsed = 0.0f;
					mEnableTimer = false;
				}

				char value[128];
				int hour;
				int minute;
				int second;
				hour =  curElapse/3600;
				minute = (curElapse - 3600*hour)/60;
				second = (curElapse - 3600*hour - 60*minute);

				if( hour == 0 )
				{
					_snprintf(value, 128, "%d:%02d", minute,second);
				}
				else
				{
					_snprintf(value, 128, "%d:%d:%d", hour, minute,second);
				}

				String strOutUtf32;

				if(mTextBlink)
				{
					utf32 val = 0xE0000000;
					strOutUtf32 = val;

					String str32( value );
					strOutUtf32 +=str32;
					
					val = 0xE1000000;
					strOutUtf32 += val;
				}
				else
				{
					String str32( value );
					strOutUtf32 =str32;
				}

				setText(strOutUtf32);

				requestRedraw();
			}
			else
			{
				mCurrentTotalTime = 0;
				mEnableTimer = false;
			}
		}

		KLSimpleText::updateSelf(elapsed);
	}

	bool	KLEventTimer::testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Falagard/EventTimer")	return true;
		return Window::testClassName_impl(class_name);
	}
 
    Window* KLEventTimerFactory::createWindow(const String& name)
    {
        return new KLEventTimer(d_type, name);
    }

    void KLEventTimerFactory::destroyWindow(Window* window)
    {
            delete window;
    }
};