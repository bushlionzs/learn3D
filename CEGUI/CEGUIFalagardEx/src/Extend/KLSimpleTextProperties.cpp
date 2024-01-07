
#include "KLSimpleTextProperties.h"
#include "KLSimpleText.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{
	namespace KLSimpleTextProperties
	{
		String	HorzFormatting::get(const PropertyReceiver* receiver) const
		{
			switch(static_cast<const KLSimpleText*>(receiver)->getHorizontalFormatting())
			{
			case KLSimpleText::RightAligned:
				return String((utf8*)"RightAligned");
				break;

			case KLSimpleText::HorzCentred:
				return String((utf8*)"HorzCentred");
				break;

			case KLSimpleText::HorzJustified:
				return String((utf8*)"HorzJustified");
				break;

			case KLSimpleText::WordWrapLeftAligned:
				return String((utf8*)"WordWrapLeftAligned");
				break;

			case KLSimpleText::WordWrapRightAligned:
				return String((utf8*)"WordWrapRightAligned");
				break;

			case KLSimpleText::WordWrapCentred:
				return String((utf8*)"WordWrapCentred");
				break;

			case KLSimpleText::WordWrapJustified:
				return String((utf8*)"WordWrapJustified");
				break;

			default:
				return String((utf8*)"LeftAligned");
				break;
			}
		}


		void	HorzFormatting::set(PropertyReceiver* receiver, const String& value)
		{
			KLSimpleText::HorzFormatting fmt;

			if (value == (utf8*)"RightAligned")
			{
				fmt = KLSimpleText::RightAligned;
			}
			else if (value == (utf8*)"HorzCentred")
			{
				fmt = KLSimpleText::HorzCentred;
			}
			else if (value == (utf8*)"HorzJustified")
			{
				fmt = KLSimpleText::HorzJustified;
			}
			else if (value == (utf8*)"WordWrapLeftAligned")
			{
				fmt = KLSimpleText::WordWrapLeftAligned;
			}
			else if (value == (utf8*)"WordWrapRightAligned")
			{
				fmt = KLSimpleText::WordWrapRightAligned;
			}
			else if (value == (utf8*)"WordWrapCentred")
			{
				fmt = KLSimpleText::WordWrapCentred;
			}
			else if (value == (utf8*)"WordWrapJustified")
			{
				fmt = KLSimpleText::WordWrapJustified;
			}
			else
			{
				fmt = KLSimpleText::LeftAligned;
			}

			static_cast<KLSimpleText*>(receiver)->setHorizontalFormatting(fmt);
		}


		String	VertFormatting::get(const PropertyReceiver* receiver) const
		{
			switch(static_cast<const KLSimpleText*>(receiver)->getVerticalFormatting())
			{
			case KLSimpleText::BottomAligned:
				return String((utf8*)"BottomAligned");
				break;

			case KLSimpleText::VertCentred:
				return String((utf8*)"VertCentred");
				break;

			default:
				return String((utf8*)"TopAligned");
				break;
			}
		}


		void	VertFormatting::set(PropertyReceiver* receiver, const String& value)
		{
			KLSimpleText::VertFormatting fmt;

			if (value == (utf8*)"BottomAligned")
			{
				fmt = KLSimpleText::BottomAligned;
			}
			else if (value == (utf8*)"VertCentred")
			{
				fmt = KLSimpleText::VertCentred;
			}
			else
			{
				fmt = KLSimpleText::TopAligned;
			}

			static_cast<KLSimpleText*>(receiver)->setVerticalFormatting(fmt);
		}

		
		String	TextScale::get(const PropertyReceiver* receiver) const
		{
			return "";
		}


		void	TextScale::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSimpleText*>(receiver)->setTextScale(PropertyHelper::stringToSize(value));
		}

		String	TextColor::get(const PropertyReceiver* receiver) const
		{
			return "";
		}


		void	TextColor::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSimpleText*>(receiver)->setTextColor( PropertyHelper::stringToColour(value));
		}
	}
}