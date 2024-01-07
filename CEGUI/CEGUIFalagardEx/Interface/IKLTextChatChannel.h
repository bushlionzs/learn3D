

#ifndef IFALCHATCHANNEL_H
#define IFALCHATCHANNEL_H

namespace CEGUI
{
	class IKLTextChatChannel
	{
	public:		
		virtual void clearAllChannel(void) = 0;
		virtual void addChannel(const String& strType, const String& strNormal, const String& strHover, const String& strPushed, const String& strName) = 0;
	};
}

#endif 