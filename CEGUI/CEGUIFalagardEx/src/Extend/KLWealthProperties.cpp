#include "KLWealthProperties.h"
#include "KLWealth.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{
namespace KLWealthProperties
{

	
	String	HorzFormatting::get(const PropertyReceiver* receiver) const
	{
		switch(static_cast<const KLWealth*>(receiver)->getHorizontalFormatting())
		{
		case KLWealth::RightAligned:
			return String((utf8*)"RightAligned");
			break;

		default:
			return String((utf8*)"LeftAligned");
			break;
		}
	}


	void	HorzFormatting::set(PropertyReceiver* receiver, const String& value)
	{
		KLWealth::HorzFormatting fmt;

		if (value == (utf8*)"RightAligned")
		{
			fmt = KLWealth::RightAligned;
		}
		else
		{
			fmt = KLWealth::LeftAligned;
		}

		static_cast<KLWealth*>(receiver)->setHorizontalFormatting(fmt);
	}

	

	String MoneyNumber::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::intToString(static_cast<const KLWealth*>(receiver)->getMoneyNumber());
    }

    void MoneyNumber::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<KLWealth*>(receiver)->setMoneyNumber(PropertyHelper::stringToInt(value));
    }

	

	String GoldIcon::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::imageToString(static_cast<const KLWealth*>(receiver)->getGoldIcon());
    }

    void GoldIcon::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<KLWealth*>(receiver)->setGoldIcon(PropertyHelper::stringToImage(value));
    }


	

	String SilverIcon::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::imageToString(static_cast<const KLWealth*>(receiver)->getSilverIcon());
    }

    void SilverIcon::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<KLWealth*>(receiver)->setSilverIcon(PropertyHelper::stringToImage(value));
    }

	

	String CopperIcon::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::imageToString(static_cast<const KLWealth*>(receiver)->getCopperIcon());
    }

    void CopperIcon::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<KLWealth*>(receiver)->setCopperIcon(PropertyHelper::stringToImage(value));
    }


}
}