#ifndef _FalSimpleTextProperties_h_
#define _FalSimpleTextProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{
	
	namespace KLSimpleTextProperties
	{
		
		class HorzFormatting : public Property
		{
		public:
			HorzFormatting() : Property(
				"HorzFormatting",
				"Property to get/set the horizontal formatting mode.  Value is one of the HorzFormatting strings.",
				"LeftAligned")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};


		
		class VertFormatting : public Property
		{
		public:
			VertFormatting() : Property(
				"VertFormatting",
				"Property to get/set the vertical formatting mode.  Value is one of the VertFormatting strings.",
				"VertCentred")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
		
		class TextScale: public Property
		{
		public:
			TextScale() : Property(
				"TextScale",
				"Property to get/set the text colours for the StaticText widget.  Value is \"tl:[aarrggbb] tr:[aarrggbb] bl:[aarrggbb] br:[aarrggbb]\".",
				"x:1 y:1")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
		
		class TextColor: public Property
		{
		public:
			TextColor() : Property(
				"TextColor",
				"Property to get/set the text colours for the StaticText widget.  Value is \"tl:[aarrggbb] tr:[aarrggbb] bl:[aarrggbb] br:[aarrggbb]\".",
				"x:1 y:1")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
	}
}

#endif