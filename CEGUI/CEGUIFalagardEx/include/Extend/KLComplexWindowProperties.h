#ifndef _FalagardComplexWindowProperties_h_
#define _FalagardComplexWindowProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

	namespace KLComplexWindowProperties
	{
	
		
		class ActionButtonSize: public Property
		{
			public:
			ActionButtonSize() : Property(
				"ActionButtonSize",
				"Property to get/set ComplexWindow name status.",
				"w=0 h=0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		
		
		class TextColour: public Property
		{
		public: 
			TextColour():Property(
				"TextColour",
				"Property to get/set ComplexWindow TextColour",
				"FFFFFFFF"	)
			{}
			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		class NormalTextColour:public Property
		{
		public: 
			NormalTextColour():Property("NormalTextColour", "Property to get/set ComplexWindow NormalTextColour", "FFFFFFFF"){}
			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		class HoverTextColour:public Property
		{
		public: 
			HoverTextColour():Property("HoverTextColour", "Property to get/set ComplexWindow HoverTextColour", "FFFFFFFF"){}
			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		class PushedTextColour:public Property
		{
		public: 
			PushedTextColour():Property("PushedTextColour", "Property to get/set ComplexWindow PushedTextColour", "FFFFFFFF"){}
			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		




		
		class ActionButtonDistance: public Property
		{
			public:
			ActionButtonDistance() : Property(
				"ActionButtonDistance",
				"Property to get/set ComplexWindow name status.",
				"w=0 h=0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class OptionButtonSize: public Property
		{
		public:
			OptionButtonSize() : Property(
				"OptionButtonSize",
				"Property to get/set ComplexWindow name status.",
				"w=0 h=0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};


		class TextAniName : public Property
		{
		public:
			TextAniName() : Property(
				"TextAniName",
				"Use to set text item's bkg img",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
		class TextFixedValue: public Property
		{
		public:
			TextFixedValue() : Property(
				"TextFixedValue",
				"Property to get/set ComplexWindow name status.",
				"1.0f")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	};
};

#endif  
