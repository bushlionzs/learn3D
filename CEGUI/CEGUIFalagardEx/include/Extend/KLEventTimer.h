#pragma once

#include "falmodule.h"
#include "ceguiwindowfactory.h"
#include "IKLEventTimer.h"
#include "KLSimpleText.h"

namespace CEGUI
{

	namespace KLEventTimerProperties
	{
		class FalagardEventTimerTotalTime : public Property
		{
		public:
			FalagardEventTimerTotalTime() : Property("TotalTime","Property to get/set TotalTime.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};		
		class FalagardEventTimerEventTime: public Property
		{
		public:
			FalagardEventTimerEventTime() : Property("EventTime","Property to get/set EventTime.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};	

		class FalagardEventTimerTextColor : public Property
		{
		public:
			FalagardEventTimerTextColor() : Property("EventTimerTextColor","Property to get/set text color.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};	
		class FalagardEventTimerTextBlink : public Property
		{
		public:
			FalagardEventTimerTextBlink() : Property("EventTimerTextBlink","Property to get/set text color.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};	
	}

	class  KLEventTimer :	public KLSimpleText, public IKLEventTimer
	{
	public:
		
		static const String EventNamespace;				
		static const String EventTimerOK;

		static KLEventTimerProperties::FalagardEventTimerTotalTime		mEventTimerTotalTimeProperty;		
		static KLEventTimerProperties::FalagardEventTimerEventTime		mEventTimerEventTimeProperty;		
		static KLEventTimerProperties::FalagardEventTimerTextColor		mEventTimerTextColorProperty;	
		static KLEventTimerProperties::FalagardEventTimerTextBlink		mEventTimerTextBlinkProperty;	

		static const utf8   WidgetTypeName[]; 
		KLEventTimer( const String& type, const String& name );
		virtual ~KLEventTimer();

		
		virtual void onTimerOK(WindowEventArgs& e);

		virtual void setTotalTime(size_t t);
		virtual void setEventTime(size_t t);
		virtual void setTimerTextColor( const colour& col );
		virtual void setTimerBlink(bool flag);
		virtual void resetEventState();
		virtual void resetState();
		virtual void updateSelf(float elapsed);

		virtual void enableEvent(bool flag);
		virtual void enableTimer(bool flag);

		virtual bool	testClassName_impl(const String& class_name) const;

	private:
		
		size_t	mTotalTime;
		size_t	mEventTime;
		colour	mTimerTextColor;
		bool	mEnableEvent;
		bool	mEnableTimer;
		bool	mTextBlink;
		size_t	mCurrentEventTime;
		size_t	mCurrentTotalTime;
		float	mCurTotalElapsed;
		float	mCurEventElapsed;
	};

	class FALAGARDBASE_API KLEventTimerFactory : public WindowFactory
    {
    public:
        KLEventTimerFactory(void) : WindowFactory(KLEventTimer::WidgetTypeName) { }
        ~KLEventTimerFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
};