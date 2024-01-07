#include "KLTextChatHistoryProperties.h"
#include "KLTextChatHistory.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{

	
	namespace KLTextChatHistoryProperties
	{
		

		String ChatBoardNumber::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::intToString(static_cast<const KLTextChatHistory*>(receiver)->getChatBoardNumber());
		}

		void ChatBoardNumber::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextChatHistory*>(receiver)->setChatBoardNumber(PropertyHelper::stringToInt(value));
		}

		String	FadeEnabled::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void	FadeEnabled::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextChatHistory*>(receiver)->setFadeEnabled(PropertyHelper::stringToBool(value));
		}

		String FadeShowTime::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::floatToString(static_cast<const KLTextChatHistory*>(receiver)->getFadeShowTime());
		}

		void FadeShowTime::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextChatHistory*>(receiver)->setFadeShowTime(PropertyHelper::stringToFloat(value));
		}

	}
}