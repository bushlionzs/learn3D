#ifndef _FalagardTextChatHistoryProperties_h_
#define _FalagardTextChatHistoryProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{

	namespace KLTextChatHistoryProperties
	{
		
		class ChatBoardNumber : public Property
		{
		public:
			ChatBoardNumber() : Property(
				"ChatBoardNumber",
				"Property to get/set ChatBoard Number.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};


		
		class FadeEnabled : public Property
		{
		public:
			FadeEnabled() : Property(
				"FadeEnabled",
				"Property to get/set the state of the fade show setting for the Static widget.  Value is either \"True\" or \"False\".",
				"False")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		class FadeShowTime : public Property
		{
		public:
			FadeShowTime() : Property(
				"FadeShowTime",
				"Property to get/set ChatBoard Fade Time.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	}
}


#endif