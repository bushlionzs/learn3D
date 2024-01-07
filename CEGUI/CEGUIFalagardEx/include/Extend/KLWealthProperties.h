#ifndef _FalMoneyProperties_h_
#define _FalMoneyProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{
	
	namespace KLWealthProperties
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

		
		class MoneyNumber : public Property
		{
		public:
			MoneyNumber() : Property(
				"MoneyNumber",
				"Property to get/set Money Number.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};


		
		class GoldIcon : public Property
		{
		public:
			GoldIcon() : Property(
				"GoldIcon",
				"Property to get/set Gold Icon.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class SilverIcon : public Property
		{
		public:
			SilverIcon() : Property(
				"SilverIcon",
				"Property to get/set Silver Icon.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class CopperIcon : public Property
		{
		public:
			CopperIcon() : Property(
				"CopperIcon",
				"Property to get/set Copper Icon.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

	}
}

#endif