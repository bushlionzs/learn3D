#ifndef _FalagardCountDownTimerProperties_h_
#define _FalagardCountDownTimerProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{
	
	namespace KLCountDownTimerProperties
	{
		
		class Step: public Property	
		{
			public:
			Step() : Property(
				"Step",
				"Property to get/set StopWatch status.",
				"0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class Timer: public Property	
		{
			public:
			Timer() : Property(
				"Timer",
				"Property to get/set StopWatch status.",
				"0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	}
}

#endif