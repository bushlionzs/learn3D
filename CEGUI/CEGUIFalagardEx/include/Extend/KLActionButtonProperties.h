#ifndef _FalActionButtonProperties_h_
#define _FalActionButtonProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{
	
	namespace KLActionButtonProperties
	{
		
		class Empty : public Property
		{
		public:
			Empty() : Property(
				"Empty",
				"Property to get/set empty status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		
		class Checked : public Property
		{
		public:
			Checked() : Property(
				"Checked",
				"Property to get/set checked status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class Default : public Property
		{
		public:
			Default() : Property(
				"Default",
				"",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		
		class Gloom : public Property
		{
		public:
			Gloom() : Property(
				"Gloom",
				"Property to get/set Gloom status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class CornerChar : public Property
		{
		public:
			CornerChar() : Property(
				"CornerChar",
				"Property to get/set Corner Character.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		
		class DraggingEnabled : public Property
		{
		public:
			DraggingEnabled() : Property(
				"DraggingEnabled",
				"Property to get/set the state of the dragging enabled setting for the DragContainer.  Value is either \"True\" or \"False\".",
				"True")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		
		class DragThreshold : public Property
		{
		public:
			DragThreshold() : Property(
				"DragThreshold",
				"Property to get/set the dragging threshold value.  Value is a float.",
				"8.000000")
			{}

			String get(const PropertyReceiver* receiver) const;
			void set(PropertyReceiver* receiver, const String& value);
		};

		class DragAcceptName : public Property
		{
		public:
			DragAcceptName() : Property(
				"DragAcceptName",
				"Property to get/set the drag accept name.  Value is a String.",
				"")
			{}

			String get(const PropertyReceiver* receiver) const;
			void set(PropertyReceiver* receiver, const String& value);
		};
	}
}

#endif  
