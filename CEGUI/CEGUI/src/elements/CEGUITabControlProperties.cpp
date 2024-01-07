

#include "elements/CEGUITabControlProperties.h"
#include "elements/CEGUITabControl.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{


namespace TabControlProperties
{
String	AbsoluteTabHeight::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::floatToString(static_cast<const TabControl*>(receiver)->getAbsoluteTabHeight());
}


void	AbsoluteTabHeight::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<TabControl*>(receiver)->setAbsoluteTabHeight(PropertyHelper::stringToFloat(value));
}

String	RelativeTabHeight::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::floatToString(static_cast<const TabControl*>(receiver)->getRelativeTabHeight());
}

bool	AbsoluteTabHeight::isDefault(const PropertyReceiver* receiver) const
{
	return static_cast<const TabControl*>(receiver)->getRelativeTabHeight() == 0.05f;
}

String	AbsoluteTabHeight::getDefault(const PropertyReceiver* receiver) const
{
	float defval = 0;
	Window* par = static_cast<const TabControl*>(receiver)->getParent();

	if (par != 0)
	{
		defval = par->relativeToAbsoluteY(0.05f);
	}

	return PropertyHelper::floatToString(defval);
}


void	RelativeTabHeight::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<TabControl*>(receiver)->setRelativeTabHeight(PropertyHelper::stringToFloat(value));
}


String	TabHeight::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::floatToString(static_cast<const TabControl*>(receiver)->getTabHeight());
}


void	TabHeight::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<TabControl*>(receiver)->setTabHeight(PropertyHelper::stringToFloat(value));
}

bool TabHeight::isDefault(const PropertyReceiver* receiver) const
{
	if (static_cast<const TabControl*>(receiver)->getMetricsMode() == Relative)
	{
		return static_cast<const TabControl*>(receiver)->isPropertyDefault("RelativeTabHeight");
	}
	else
	{
		return static_cast<const TabControl*>(receiver)->isPropertyDefault("AbsoluteTabHeight");
	}
}

String TabHeight::getDefault(const PropertyReceiver* receiver) const
{
	if (static_cast<const TabControl*>(receiver)->getMetricsMode() == Relative)
	{
		return static_cast<const TabControl*>(receiver)->getPropertyDefault("RelativeTabHeight");
	}
	else
	{
		return static_cast<const TabControl*>(receiver)->getPropertyDefault("AbsoluteTabHeight");
	}
}



String	AbsoluteTabTextPadding::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::floatToString(static_cast<const TabControl*>(receiver)->getAbsoluteTabTextPadding());
}


void	AbsoluteTabTextPadding::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<TabControl*>(receiver)->setAbsoluteTabTextPadding(PropertyHelper::stringToFloat(value));
}

String	RelativeTabTextPadding::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::floatToString(static_cast<const TabControl*>(receiver)->getRelativeTabTextPadding());
}


void	RelativeTabTextPadding::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<TabControl*>(receiver)->setRelativeTabTextPadding(PropertyHelper::stringToFloat(value));
}

bool	RelativeTabTextPadding::isDefault(const PropertyReceiver* receiver) const
{
	return static_cast<const TabControl*>(receiver)->getAbsoluteTabTextPadding() == 5.0f;
}

String	RelativeTabTextPadding::getDefault(const PropertyReceiver* receiver) const
{
	float defval = 0;
	Window* par = static_cast<const TabControl*>(receiver)->getParent();

	if (par != 0)
	{
		defval = par->absoluteToRelativeY(5.0f);
	}

	return PropertyHelper::floatToString(defval);
}



String	TabTextPadding::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::floatToString(static_cast<const TabControl*>(receiver)->getTabTextPadding());
}


void	TabTextPadding::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<TabControl*>(receiver)->setTabTextPadding(PropertyHelper::stringToFloat(value));
}

bool	TabTextPadding::isDefault(const PropertyReceiver* receiver) const
{
	if (static_cast<const TabControl*>(receiver)->getMetricsMode() == Relative)
	{
		return static_cast<const TabControl*>(receiver)->isPropertyDefault("RelativeTabTextPadding");
	}
	else
	{
		return static_cast<const TabControl*>(receiver)->isPropertyDefault("AbsoluteTabTextPadding");
	}
}

String	TabTextPadding::getDefault(const PropertyReceiver* receiver) const
{
	if (static_cast<const TabControl*>(receiver)->getMetricsMode() == Relative)
	{
		return static_cast<const TabControl*>(receiver)->getPropertyDefault("RelativeTabTextPadding");
	}
	else
	{
		return static_cast<const TabControl*>(receiver)->getPropertyDefault("AbsoluteTabTextPadding");
	}
}





} 

} 
