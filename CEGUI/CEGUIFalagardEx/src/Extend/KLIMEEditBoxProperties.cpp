#include "KLIMEEditBoxProperties.h"
#include "KLIMEEditBox.h"
#include "CEGUIPropertyHelper.h"
#include "CEGUIInputMethodEditor.h"


namespace CEGUI
{
	
	namespace KLIMEEditBoxProperties
	{
		String	DefaultEditBox::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::boolToString(ImeModule::GetActiveIMEEditBox() == static_cast<const Window*>(receiver));
		}

		void DefaultEditBox::set(PropertyReceiver* receiver, const String& value)
		{
			Window* old = static_cast<Window*>(ImeModule::GetActiveIMEEditBox());

			ImeModule::SetActiveIMEEditBox(static_cast<Window*>(receiver), PropertyHelper::stringToBool(value));

			if(ImeModule::GetActiveIMEEditBox() == receiver)
			{
				static_cast<KLIMEEditBox*>(ImeModule::GetActiveIMEEditBox())->resetCaretBlink();
			}
			if(old)
			{
				old->requestRedraw();
			}
		}
	}
}