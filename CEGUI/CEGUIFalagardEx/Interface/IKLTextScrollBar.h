#pragma once

namespace CEGUI
{
	class IKLTextScrollBar
	{
	public:
		virtual void setScrollText(  const String& str) = 0;
		virtual void setScrollSpeed( float speed ) = 0;
		virtual void setScrollDirection( int direction ) = 0;
		virtual void resetState(const String &str) = 0;
		virtual void setLoop(bool ) = 0; 
		virtual void setLoopTimes(size_t num) = 0;
		virtual void setTextColor(colour) = 0;
		virtual void updateSelf(float elapsed) = 0;

		
		virtual void setQueueMode(bool bQueueMode) = 0;
		virtual void pushText(const String& str) = 0;
		virtual void setStringSpace(size_t space) = 0;
		virtual void clearAllText() = 0;
	};
};