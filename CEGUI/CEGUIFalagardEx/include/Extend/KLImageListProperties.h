#ifndef _FalImageListBoxProperties_h_
#define _FalImageListBoxProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{
	
	
	
	
	
	
	


	namespace KLImageListBoxProperties
	{
		
		class ImageNormal : public Property
		{
		public:
			ImageNormal() : Property(
				"ImageNormal",
				"Property to get/set ImageNormal .",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class ImageHorver : public Property
		{
		public:
			ImageHorver() : Property(
				"ImageHorver",
				"Property to get/set ImageNormal .",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class ImageChecked : public Property
		{
		public:
			ImageChecked() : Property(
				"ImageChecked",
				"Property to get/set ImageNormal .",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		class ImageDisable: public Property
		{
		public:
			ImageDisable() : Property(
				"ImageDisable",
				"Property to get/set ImageNormal .",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class AutoScale : public Property
		{
		public:
			AutoScale() : Property(
				"AutoScale",
				"Property to get/set checked status.",
				"Trye")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		
		class AddItem : public Property
		{
		public:
			AddItem() : Property(
				"AddItem",
				"Property to get/set KeyImageAnimation name status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	}
}

#endif  
