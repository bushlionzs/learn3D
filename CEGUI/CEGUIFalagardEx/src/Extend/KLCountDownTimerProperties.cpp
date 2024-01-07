
#include "KLCountDownTimerProperties.h"
#include "KLCountDownTimer.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{

	
	namespace KLCountDownTimerProperties
	{
		

		String Step::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::intToString( static_cast<const KLCountDownTimer*>(receiver)->getStep() );
		}

		void Step::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLCountDownTimer*>(receiver)->setStep( PropertyHelper::stringToInt(value) );
		}

		

		String Timer::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::intToString( static_cast<const KLCountDownTimer*>(receiver)->getTimer() );
		}

		void Timer::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLCountDownTimer*>(receiver)->setTimer( PropertyHelper::stringToInt(value) );
		}

	}
}