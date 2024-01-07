
#include "KLComplexWindowProperties.h"
#include "KLComplexWindow.h"
#include "CEGUIPropertyHelper.h"
#include <stdio.h>


namespace CEGUI
{
	namespace KLComplexWindowProperties
	{

		String ActionButtonSize::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::sizeToString( static_cast<const KLComplexWindow*>(receiver)->getActionButtonSize() );
		}

		void ActionButtonSize::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLComplexWindow*>(receiver)->setActionButtonSize( PropertyHelper::stringToSize(value) );
		}

		
		
		String TextColour::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::colourToString( static_cast<const KLComplexWindow*>(receiver)->getTextColor() );
		}
		void TextColour::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLComplexWindow*>(receiver)->setTextColor( PropertyHelper::stringToColour(value) );
		}
		
		String NormalTextColour::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::colourToString( static_cast<const KLComplexWindow*>(receiver)->getOptionNormalTextColour() );
		}
		void NormalTextColour::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLComplexWindow*>(receiver)->setOptionNormalTextColour( PropertyHelper::stringToColour(value) );
		}
		
		String HoverTextColour::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::colourToString( static_cast<const KLComplexWindow*>(receiver)->getOptionHoverTextColour() );
		}
		void HoverTextColour::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLComplexWindow*>(receiver)->setOptionHoverTextColour( PropertyHelper::stringToColour(value) );
		}
		
		String PushedTextColour::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::colourToString( static_cast<const KLComplexWindow*>(receiver)->getOptionPushedTextColour() );
		}
		void PushedTextColour::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLComplexWindow*>(receiver)->setOptionPushedTextColour( PropertyHelper::stringToColour(value) );
		}
		


		String ActionButtonDistance::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::sizeToString( static_cast<const KLComplexWindow*>(receiver)->getActionButtonDistance() );
		}

		void ActionButtonDistance::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLComplexWindow*>(receiver)->setActionButtonDistance( PropertyHelper::stringToSize(value) );
		}

		String OptionButtonSize::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::sizeToString( static_cast<const KLComplexWindow*>(receiver)->getOptionButtonSize() );
		}

		void OptionButtonSize::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLComplexWindow*>(receiver)->setOptionButtonSize( PropertyHelper::stringToSize(value) );
		}

		
		String TextAniName::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void TextAniName::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLComplexWindow*>(receiver)->setTextItemAni(value);	
		}

		String TextFixedValue::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::floatToString( static_cast<const KLComplexWindow*>(receiver)->getTextFixedValue() );
		}

		void TextFixedValue::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLComplexWindow*>(receiver)->setTextFixedValue( PropertyHelper::stringToFloat(value) );
		}
	};
}
