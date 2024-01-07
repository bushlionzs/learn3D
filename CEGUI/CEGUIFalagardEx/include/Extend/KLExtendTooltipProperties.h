#ifndef _FalagardExtendTooltipProperties_h_
#define _FalagardExtendTooltipProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{

	namespace KLResizeTextProperties
	{
		class TopFrame : public Property
		{
		public:
			TopFrame() : Property(
				"TopFrame",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};		
		class MiddleFrame : public Property
		{
		public:
			MiddleFrame() : Property(
				"MiddleFrame",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};	
		class BottomFrame : public Property
		{
		public:
			BottomFrame() : Property(
				"BottomFrame",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};	
		class TextArea : public Property
		{
		public:
			TextArea() : Property(
				"TextArea",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};	
	}

	namespace FalagardExtendTooltipProperties
	{
		
		class PageHeader : public Property
		{
		public:
			PageHeader() : Property(
				"PageHeader",
				"Property to get/set the PageHeader window name.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};		

		
		class PageFooter : public Property
		{
		public:
			PageFooter() : Property(
				"PageFooter",
				"Property to get/set the PageFooter window name.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};	


		
		class PageElements : public Property
		{
		public:
			PageElements() : Property(
				"PageElements",
				"Property to get/set the page elements window name.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};	

		
		class PageBak : public Property
		{
		public:
			PageBak() : Property(
				"PageBak",
				"Property to get/set the PageBak window name.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		
		
		class PageClose : public Property
		{
		public:
			PageClose() : Property(
				"PageClose",
				"Property to get/set the PageClose window name.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		
		
		class ResizeMaxWidth : public Property
		{
		public:
			ResizeMaxWidth() : Property(
				"ResizeMaxWidth",
				"Property to get/set the PageBak window name.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		
		
		class ConditionWidth : public Property
		{
		public:
			ConditionWidth() : Property(
				"ConditionWidth",
				"Property to get/set the PageBak window name.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
	}
}


#endif