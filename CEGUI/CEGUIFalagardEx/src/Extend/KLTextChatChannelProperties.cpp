
#include "KLTextChatChannelProperties.h"
#include "KLTextChatChannel.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{
	namespace KLTextChatChannelProperties
	{

		
		String ButtonSize::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::sizeToString(static_cast<const KLTextChatChannel*>(receiver)->getButtonSize());
		}

		void ButtonSize::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextChatChannel*>(receiver)->setButttonSize(PropertyHelper::stringToSize(value));
		}

		
		String TextSize::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::sizeToString(static_cast<const KLTextChatChannel*>(receiver)->getTextSize());
		}

		void TextSize::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextChatChannel*>(receiver)->setTextSize(PropertyHelper::stringToSize(value));
		}

		
		String ButtonPosition::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::pointToString(static_cast<const KLTextChatChannel*>(receiver)->getButtonPosition());
		}

		void ButtonPosition::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextChatChannel*>(receiver)->setButtonPosition(PropertyHelper::stringToPoint(value));
		}

		
		String HoverChannel::get(const PropertyReceiver* receiver) const
		{
			return (static_cast<const KLTextChatChannel*>(receiver)->getHoverChannel());
		}

		void HoverChannel::set(PropertyReceiver* receiver, const String& value)
		{
			
		}
		
		String HoverChannelName::get(const PropertyReceiver* receiver) const
		{
			return (static_cast<const KLTextChatChannel*>(receiver)->getHoverChannelName());
		}

		void HoverChannelName::set(PropertyReceiver* receiver, const String& value)
		{
			
		}
		
		String ChannelBkg::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void ChannelBkg::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextChatChannel*>(receiver)->setItemBkg(value);		
		}

		
		String BkgSize::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::sizeToString(static_cast<const KLTextChatChannel*>(receiver)->getBkgSize());
		}

		void BkgSize::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextChatChannel*>(receiver)->setBkgSize(PropertyHelper::stringToSize(value));
		}


		
		String BkgPosition::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::pointToString(static_cast<const KLTextChatChannel*>(receiver)->getBkgPosition());
		}

		void BkgPosition::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextChatChannel*>(receiver)->setBkgPosition(PropertyHelper::stringToPoint(value));
		}
	}
}
