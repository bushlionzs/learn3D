#ifndef _FalChatChannelProperties_h_
#define _FalChatChannelProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{
	namespace KLTextChatChannelProperties
	{
		
		class ButtonSize : public Property
		{
		public:
			ButtonSize() : Property(
				"ButtonSize",
				"",
				"w:0.0 h:0.0")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};


		class TextSize : public Property
		{
		public:
			TextSize() : Property(
				"TextSize",
				"",
				"w:0.0 h:0.0")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};


		
		class ButtonPosition : public Property
		{
		public:
			ButtonPosition() : Property(
				"ButtonPosition",
				"",
				"x:0.0 y:0.0")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		
		class HoverChannel : public Property
		{
		public:
			HoverChannel() : Property(
				"HoverChannel",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		
		class HoverChannelName : public Property
		{
		public:
			HoverChannelName() : Property(
				"HoverChannelName",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		class ChannelBkg : public Property
		{
		public:
			ChannelBkg() : Property(
				"ChannelBkg",
				"Use to set channel item's bkg img",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		class BkgSize : public Property
		{
		public:
			BkgSize() : Property(
				"BkgSize",
				"",
				"w:0.0 h:0.0")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		class BkgPosition : public Property
		{
		public:
			BkgPosition() : Property(
				"BkgPosition",
				"",
				"x:0.0 y:0.0")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

	}
}


#endif
