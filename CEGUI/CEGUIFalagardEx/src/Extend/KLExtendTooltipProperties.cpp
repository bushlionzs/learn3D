
#include "KLExtendTooltipProperties.h"
#include "KLExtendTooltip.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{
	
	namespace KLResizeTextProperties
	{
		

		String	TopFrame::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::imageToString((static_cast<const KLExtendTooltip::ResizeText*>(receiver)->getTopFrame()));
		}

		void TopFrame::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLExtendTooltip::ResizeText*>(receiver)->setTopFrame(PropertyHelper::stringToImage(value));
		}

		

		String	MiddleFrame::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::imageToString((static_cast<const KLExtendTooltip::ResizeText*>(receiver)->getMiddleFrame()));
		}

		void MiddleFrame::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLExtendTooltip::ResizeText*>(receiver)->setMiddleFrame(PropertyHelper::stringToImage(value));
		}

		

		String	BottomFrame::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::imageToString((static_cast<const KLExtendTooltip::ResizeText*>(receiver)->getBottomFrame()));
		}

		void BottomFrame::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLExtendTooltip::ResizeText*>(receiver)->setBottomFrame(PropertyHelper::stringToImage(value));
		}
		

		String	TextArea::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::urectToString((static_cast<const KLExtendTooltip::ResizeText*>(receiver)->getTextArea()));
		}

		void TextArea::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLExtendTooltip::ResizeText*>(receiver)->setTextArea(PropertyHelper::stringToURect(value));
		}
	}

	
	namespace FalagardExtendTooltipProperties
	{
		

		String	PageElements::get(const PropertyReceiver* receiver) const
		{
			return (static_cast<const KLExtendTooltip*>(receiver)->getPageElementsName());
		}

		void PageElements::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLExtendTooltip*>(receiver)->setPageElementsName(value);
		}

		String	PageBak::get(const PropertyReceiver* receiver) const
		{
			return (static_cast<const KLExtendTooltip*>(receiver)->getPageBakName());
		}

		void PageBak::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLExtendTooltip*>(receiver)->setPageBakName(value);
		}

		String	PageClose::get(const PropertyReceiver* receiver) const
		{
			return (static_cast<const KLExtendTooltip*>(receiver)->getPageCloseName());
		}

		void PageClose::set(PropertyReceiver* receiver, const String& value)
		{
			size_t wstart = value.find("c:");
			size_t idstart = value.find("w:");

			String caption(value.substr(0, wstart));
			caption = caption.substr(caption.find_first_of(":") + 1);

			String condition(value.substr(wstart, idstart-1));
			condition = condition.substr(condition.find_first_of(":") + 1);

			String width(value.substr(idstart));
			width = width.substr(width.find_first_of(":") + 1);
			float iWidth = PropertyHelper::stringToFloat(width); 

			static_cast<KLExtendTooltip*>(receiver)->setPageCloseName(condition, iWidth);
		}

		String	ResizeMaxWidth::get(const PropertyReceiver* receiver) const
		{
			return String("");
		}

		void ResizeMaxWidth::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLExtendTooltip*>(receiver)->setDefaultWidth(PropertyHelper::stringToFloat(value));
		}

		String ConditionWidth::get(const PropertyReceiver* receiver) const
		{
			return String("");
		}

		void ConditionWidth::set(PropertyReceiver* receiver, const String& value)
		{
			size_t wstart = value.find("c:");
			size_t idstart = value.find("w:");

			String caption(value.substr(0, wstart));
			caption = caption.substr(caption.find_first_of(":") + 1);

			String condition(value.substr(wstart, idstart-1));
			condition = condition.substr(condition.find_first_of(":") + 1);
			int iCondition = PropertyHelper::stringToInt(condition);

			String width(value.substr(idstart));
			width = width.substr(width.find_first_of(":") + 1);
			float iWidth = PropertyHelper::stringToFloat(width); 

			static_cast<KLExtendTooltip*>(receiver)->setConditionWidth(iCondition, iWidth);
		}
	}

}
