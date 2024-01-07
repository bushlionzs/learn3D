#pragma once

namespace CEGUI
{
	class IKLEventTimer
	{
	public:
		virtual void setTotalTime(size_t t) = 0;
		virtual void setEventTime(size_t t) = 0;
		virtual void setTimerTextColor( const colour& col ) = 0;
		virtual void resetEventState() = 0;
		virtual void setTimerBlink(bool) = 0;
		virtual void enableEvent(bool flag) = 0;
		virtual void enableTimer(bool flag) = 0;
	};
};