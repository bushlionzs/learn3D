/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "MyGUI_Precompiled.h"
#include "MyGUI_Timer.h"
#include "time_util.h"


namespace MyGUI
{

	Timer::Timer() :
		mTimeStart(0)
	{
	}

	void Timer::reset()
	{
		mTimeStart = getCurrentMilliseconds();
	}

	unsigned long Timer::getMilliseconds() const
	{
		return getCurrentMilliseconds() - mTimeStart;
	}

	unsigned long Timer::getCurrentMilliseconds() const
	{
		return get_tick_count();
	}

} // namespace MyGUI
