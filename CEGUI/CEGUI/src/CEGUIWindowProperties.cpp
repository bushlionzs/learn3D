

#include "CEGUIWindowProperties.h"
#include "CEGUIWindow.h"
#include "CEGUIFont.h"
#include "CEGUIPropertyHelper.h"
#include "CEGUIExceptions.h"
#include <cstdlib>
#include <cstdio>


namespace CEGUI
{

namespace WindowProperties
{

String RelativeMinSize::get(const PropertyReceiver* receiver) const
{
	CEGUI::Size msz(static_cast<const Window*>(receiver)->getMinimumSize());

	if (static_cast<const Window*>(receiver)->getMetricsMode() == Absolute)
	{
		CEGUI::Size dsz(System::getSingleton().getRenderer()->getSize());

		msz.d_width	 /= dsz.d_width;
		msz.d_height /= dsz.d_height;
	}

	return PropertyHelper::sizeToString(msz);
}


void RelativeMinSize::set(PropertyReceiver* receiver, const String& value)
{
	CEGUI::Size msz(PropertyHelper::stringToSize(value));

	if (static_cast<Window*>(receiver)->getMetricsMode() == Absolute)
	{
		CEGUI::Size dsz(System::getSingleton().getRenderer()->getSize());

		msz.d_width	 *= dsz.d_width;
		msz.d_height *= dsz.d_height;
	}

	static_cast<Window*>(receiver)->setMinimumSize(msz);
}


String RelativeMaxSize::get(const PropertyReceiver* receiver) const
{
	CEGUI::Size msz(static_cast<const Window*>(receiver)->getMaximumSize());

	if (static_cast<const Window*>(receiver)->getMetricsMode() == Absolute)
	{
		CEGUI::Size dsz(System::getSingleton().getRenderer()->getSize());

		msz.d_width	 /= dsz.d_width;
		msz.d_height /= dsz.d_height;
	}

	return PropertyHelper::sizeToString(msz);
}


void RelativeMaxSize::set(PropertyReceiver* receiver, const String& value)
{
	CEGUI::Size msz(PropertyHelper::stringToSize(value));

	if (static_cast<Window*>(receiver)->getMetricsMode() == Absolute)
	{
		CEGUI::Size dsz(System::getSingleton().getRenderer()->getSize());

		msz.d_width	 *= dsz.d_width;
		msz.d_height *= dsz.d_height;
	}

	static_cast<Window*>(receiver)->setMaximumSize(msz);
}


String AbsoluteMinSize::get(const PropertyReceiver* receiver) const
{
	CEGUI::Size msz(static_cast<const Window*>(receiver)->getMinimumSize());

	if (static_cast<const Window*>(receiver)->getMetricsMode() == Relative)
	{
		CEGUI::Size dsz(System::getSingleton().getRenderer()->getSize());

		msz.d_width	 *= dsz.d_width;
		msz.d_height *= dsz.d_height;
	}

	return PropertyHelper::sizeToString(msz);
}


void AbsoluteMinSize::set(PropertyReceiver* receiver, const String& value)
{
	CEGUI::Size msz(PropertyHelper::stringToSize(value));

	if (static_cast<Window*>(receiver)->getMetricsMode() == Relative)
	{
		CEGUI::Size dsz(System::getSingleton().getRenderer()->getSize());

		msz.d_width	 /= dsz.d_width;
		msz.d_height /= dsz.d_height;
	}

	static_cast<Window*>(receiver)->setMinimumSize(msz);
}


String AbsoluteMaxSize::get(const PropertyReceiver* receiver) const
{
	CEGUI::Size msz(static_cast<const Window*>(receiver)->getMaximumSize());

	if (static_cast<const Window*>(receiver)->getMetricsMode() == Relative)
	{
		CEGUI::Size dsz(System::getSingleton().getRenderer()->getSize());

		msz.d_width	 *= dsz.d_width;
		msz.d_height *= dsz.d_height;
	}

	return PropertyHelper::sizeToString(msz);
}


void AbsoluteMaxSize::set(PropertyReceiver* receiver, const String& value)
{
	CEGUI::Size msz(PropertyHelper::stringToSize(value));

	if (static_cast<Window*>(receiver)->getMetricsMode() == Relative)
	{
		CEGUI::Size dsz(System::getSingleton().getRenderer()->getSize());

		msz.d_width	 /= dsz.d_width;
		msz.d_height /= dsz.d_height;
	}

	static_cast<Window*>(receiver)->setMaximumSize(msz);
}

bool AbsoluteMaxSize::isDefault(const PropertyReceiver* receiver) const
{
	return get(receiver) == getDefault(receiver);
}

String	AbsoluteMaxSize::getDefault(const PropertyReceiver* receiver) const
{
	return PropertyHelper::sizeToString(System::getSingleton().getRenderer()->getSize());
}

String MetricsMode::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::metricsModeToString(static_cast<const Window*>(receiver)->getMetricsMode());
}


void MetricsMode::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setMetricsMode(PropertyHelper::stringToMetricsMode(value));
}


String ID::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<const Window*>(receiver)->getID());
}


void ID::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setID(PropertyHelper::stringToUint(value));
}


String Alpha::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getAlpha());
}


void Alpha::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setAlpha(PropertyHelper::stringToFloat(value));
}


String Font::get(const PropertyReceiver* receiver) const
{
	const CEGUI::Font* fnt = static_cast<const Window*>(receiver)->getFont();

	if (fnt != NULL)
	{
		return fnt->getName();
	}
	else
	{
		return String();
	}

}


void Font::set(PropertyReceiver* receiver, const String& value)
{
	try
	{
		if (value.empty())
		{
			static_cast<Window*>(receiver)->setFont(System::getSingleton().getDefaultFont());
		}
		else
		{
			static_cast<Window*>(receiver)->setFont(value);
		}
	}
	catch (UnknownObjectException)
	{ }
}

bool Font::isDefault(const PropertyReceiver* receiver) const
{
    return static_cast<const Window*>(receiver)->getFont(false) == 0;
}

String MouseHollow::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->getMouseHollow());
}

void MouseHollow::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setMouseHollow(PropertyHelper::stringToBool(value));
}

String MouseMoveHollow::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->getMouseMoveHollow());
}

void MouseMoveHollow::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setMouseMoveHollow(PropertyHelper::stringToBool(value));
}

String MouseLButtonHollow::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->getMouseLButtonHollow());
}

void MouseLButtonHollow::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setMouseLButtonHollow(PropertyHelper::stringToBool(value));
}

String MouseRButtonHollow::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->getMouseRButtonHollow());
}

void MouseRButtonHollow::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setMouseRButtonHollow(PropertyHelper::stringToBool(value));
}

String TextOriginal::get(const PropertyReceiver* receiver) const
{
	return static_cast<const Window*>(receiver)->getTextOriginal();
}

void TextOriginal::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setTextOriginal(value);
}

String Text::get(const PropertyReceiver* receiver) const
{
	return static_cast<const Window*>(receiver)->getText();
}


void Text::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setText(value);
}


String MouseCursorImage::get(const PropertyReceiver* receiver) const
{
	const Image* img = static_cast<const Window*>(receiver)->getMouseCursor();

	if (img != NULL)
	{
		return PropertyHelper::imageToString(img);
	}
	else
	{
		return String();
	}

}

void MouseCursorImage::set(PropertyReceiver* receiver, const String& value)
{
	if (!value.empty())
	{
		static_cast<Window*>(receiver)->setMouseCursor(PropertyHelper::stringToImage(value));
	}
}

bool MouseCursorImage::isDefault(const PropertyReceiver* receiver) const
{
    return static_cast<const Window*>(receiver)->getMouseCursor(false) == 0;
}


String ClippedByParent::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->isClippedByParent());
}


void ClippedByParent::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setClippedByParent(PropertyHelper::stringToBool(value));
}


String InheritsAlpha::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->inheritsAlpha());
}


void InheritsAlpha::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setInheritsAlpha(PropertyHelper::stringToBool(value));
}


String AlwaysOnTop::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->isAlwaysOnTop());
}


void AlwaysOnTop::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setAlwaysOnTop(PropertyHelper::stringToBool(value));
}

String WindowLayOutNum::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::intToString(static_cast<const Window*>(receiver)->getWindowLayOutNum());
}


void WindowLayOutNum::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setWindowLayOutNum(PropertyHelper::stringToInt(value));
}


String Disabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->isDisabled());
}


void Disabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setEnabled(!PropertyHelper::stringToBool(value));
}

bool Disabled::isDefault(const PropertyReceiver* receiver) const
{
    return !static_cast<const Window*>(receiver)->isDisabled(true);
}


String Visible::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->isVisible());
}


void Visible::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setVisible(PropertyHelper::stringToBool(value));
}

bool Visible::isDefault(const PropertyReceiver* receiver) const
{
    return static_cast<const Window*>(receiver)->isVisible(true);
}


String RestoreOldCapture::get(const PropertyReceiver* receiver) const
{
	return	PropertyHelper::boolToString(static_cast<const Window*>(receiver)->restoresOldCapture());
}


void RestoreOldCapture::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setRestoreCapture(PropertyHelper::stringToBool(value));
}


String DestroyedByParent::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->isDestroyedByParent());
}


void DestroyedByParent::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setDestroyedByParent(PropertyHelper::stringToBool(value));
}


String Width::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getWidth());
}


void Width::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setWidth(PropertyHelper::stringToFloat(value));
}


String RelativeWidth::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getRelativeWidth());
}


void RelativeWidth::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setWidth(Relative, PropertyHelper::stringToFloat(value));
}


String AbsoluteWidth::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getAbsoluteWidth());
}


void AbsoluteWidth::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setWidth(Absolute, PropertyHelper::stringToFloat(value));
}


String Height::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getHeight());
}


void Height::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setHeight(PropertyHelper::stringToFloat(value));
}


String RelativeHeight::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getRelativeHeight());
}


void RelativeHeight::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setHeight(Relative, PropertyHelper::stringToFloat(value));
}


String AbsoluteHeight::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getAbsoluteHeight());
}


void AbsoluteHeight::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setHeight(Absolute, PropertyHelper::stringToFloat(value));
}


String Size::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::sizeToString(static_cast<const Window*>(receiver)->getSize());
}


void Size::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setSize(PropertyHelper::stringToSize(value));
}


String RelativeSize::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::sizeToString(static_cast<const Window*>(receiver)->getRelativeSize());
}


void RelativeSize::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setSize(Relative, PropertyHelper::stringToSize(value));
}


String AbsoluteSize::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::sizeToString(static_cast<const Window*>(receiver)->getAbsoluteSize());
}


void AbsoluteSize::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setSize(Absolute, PropertyHelper::stringToSize(value));
}


String XPosition::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getXPosition());
}


void XPosition::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setXPosition(PropertyHelper::stringToFloat(value));
}


String RelativeXPosition::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getRelativeXPosition());
}


void RelativeXPosition::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setXPosition(Relative, PropertyHelper::stringToFloat(value));
}


String AbsoluteXPosition::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getAbsoluteXPosition());
}


void AbsoluteXPosition::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setXPosition(Absolute, PropertyHelper::stringToFloat(value));
}


String YPosition::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getYPosition());
}


void YPosition::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setYPosition(PropertyHelper::stringToFloat(value));
}


String RelativeYPosition::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getRelativeYPosition());
}


void RelativeYPosition::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setYPosition(Relative, PropertyHelper::stringToFloat(value));
}


String AbsoluteYPosition::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getAbsoluteYPosition());
}


void AbsoluteYPosition::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setYPosition(Absolute, PropertyHelper::stringToFloat(value));
}


String Position::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::pointToString(static_cast<const Window*>(receiver)->getPosition());
}


void Position::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setPosition(PropertyHelper::stringToPoint(value));
}


String RelativePosition::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::pointToString(static_cast<const Window*>(receiver)->getRelativePosition());
}


void RelativePosition::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setPosition(Relative, PropertyHelper::stringToPoint(value));
}


String AbsolutePosition::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::pointToString(static_cast<const Window*>(receiver)->getAbsolutePosition());
}


void AbsolutePosition::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setPosition(Absolute, PropertyHelper::stringToPoint(value));
}


String Rect::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::rectToString(static_cast<const Window*>(receiver)->getRect());
}


void Rect::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setAreaRect(PropertyHelper::stringToRect(value));
}


String RelativeRect::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::rectToString(static_cast<const Window*>(receiver)->getRelativeRect());
}


void RelativeRect::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setRect(Relative, PropertyHelper::stringToRect(value));
}


String AbsoluteRect::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::rectToString(static_cast<const Window*>(receiver)->getAbsoluteRect());
}


void AbsoluteRect::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setRect(Absolute, PropertyHelper::stringToRect(value));
}


String ZOrderChangeEnabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->isZOrderingEnabled());
}


void ZOrderChangeEnabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setZOrderingEnabled(PropertyHelper::stringToBool(value));
}


String WantsMultiClickEvents::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->wantsMultiClickEvents());
}


void WantsMultiClickEvents::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setWantsMultiClickEvents(PropertyHelper::stringToBool(value));
}


String MouseButtonDownAutoRepeat::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->isMouseAutoRepeatEnabled());
}


void MouseButtonDownAutoRepeat::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setMouseAutoRepeatEnabled(PropertyHelper::stringToBool(value));
}


String AutoRepeatDelay::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getAutoRepeatDelay());
}


void AutoRepeatDelay::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setAutoRepeatDelay(PropertyHelper::stringToFloat(value));
}


String AutoRepeatRate::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getAutoRepeatRate());
}


void AutoRepeatRate::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setAutoRepeatRate(PropertyHelper::stringToFloat(value));
}


String DistributeCapturedInputs::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->distributesCapturedInputs());
}


void DistributeCapturedInputs::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setDistributesCapturedInputs(PropertyHelper::stringToBool(value));
}


String CustomTooltipType::get(const PropertyReceiver* receiver) const
{
    return static_cast<const Window*>(receiver)->getTooltipType();
}


void CustomTooltipType::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setTooltipType(value);
}

String Tooltip::get(const PropertyReceiver* receiver) const
{
    const Window* wnd = static_cast<const Window*>(receiver);

    if (!wnd->getParent() || !wnd->inheritsTooltipText() || (wnd->getTooltipText() != wnd->getParent()->getTooltipText()))
    {
        return wnd->getTooltipText();
    }
    else
    {
        return String("");
    }
}


void Tooltip::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setTooltipText(value);
}


String InheritsTooltipText::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->inheritsTooltipText());
}


void InheritsTooltipText::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setInheritsTooltipText(PropertyHelper::stringToBool(value));
}


String RiseOnClick::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::boolToString(static_cast<const Window*>(receiver)->isRiseOnClickEnabled());
}


void RiseOnClick::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setRiseOnClickEnabled(PropertyHelper::stringToBool(value));
}


String VerticalAlignment::get(const PropertyReceiver* receiver) const
{
    switch(static_cast<const Window*>(receiver)->getVerticalAlignment())
    {
        case VA_CENTRE:
            return String("Centre");
            break;

        case VA_BOTTOM:
            return String("Bottom");
            break;

        default:
            return String("Top");
    }
}

void VerticalAlignment::set(PropertyReceiver* receiver, const String& value)
{
    CEGUI::VerticalAlignment align;

    if (value == "Centre")
    {
        align = VA_CENTRE;
    }
    else if (value == "Bottom")
    {
        align = VA_BOTTOM;
    }
    else
    {
        align = VA_TOP;
    }
    
    static_cast<Window*>(receiver)->setVerticalAlignment(align);
}


String HorizontalAlignment::get(const PropertyReceiver* receiver) const
{
    switch(static_cast<const Window*>(receiver)->getHorizontalAlignment())
    {
        case HA_CENTRE:
            return String("Centre");
            break;

        case HA_RIGHT:
            return String("Right");
            break;

        default:
            return String("Left");
    }
}

void HorizontalAlignment::set(PropertyReceiver* receiver, const String& value)
{
    CEGUI::HorizontalAlignment align;

    if (value == "Centre")
    {
        align = HA_CENTRE;
    }
    else if (value == "Right")
    {
        align = HA_RIGHT;
    }
    else
    {
        align = HA_LEFT;
    }
    
    static_cast<Window*>(receiver)->setHorizontalAlignment(align);
}


String UnifiedAreaRect::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::urectToString(static_cast<const Window*>(receiver)->getWindowArea());
}

void UnifiedAreaRect::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setWindowArea(PropertyHelper::stringToURect(value));
}


String UnifiedPosition::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::uvector2ToString(static_cast<const Window*>(receiver)->getWindowPosition());
}

void UnifiedPosition::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setWindowPosition(PropertyHelper::stringToUVector2(value));
}


String UnifiedXPosition::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::udimToString(static_cast<const Window*>(receiver)->getWindowXPosition());
}

void UnifiedXPosition::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setWindowXPosition(PropertyHelper::stringToUDim(value));
}


String UnifiedYPosition::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::udimToString(static_cast<const Window*>(receiver)->getWindowYPosition());
}

void UnifiedYPosition::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setWindowYPosition(PropertyHelper::stringToUDim(value));
}


String UnifiedSize::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::uvector2ToString(static_cast<const Window*>(receiver)->getWindowSize());
}

void UnifiedSize::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setWindowSize(PropertyHelper::stringToUVector2(value));
}


String UnifiedWidth::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::udimToString(static_cast<const Window*>(receiver)->getWindowWidth());
}

void UnifiedWidth::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setWindowWidth(PropertyHelper::stringToUDim(value));
}


String UnifiedHeight::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::udimToString(static_cast<const Window*>(receiver)->getWindowHeight());
}

void UnifiedHeight::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setWindowHeight(PropertyHelper::stringToUDim(value));
}


String UnifiedMinSize::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::uvector2ToString(static_cast<const Window*>(receiver)->getWindowMinSize());
}

void UnifiedMinSize::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setWindowMinSize(PropertyHelper::stringToUVector2(value));
}


String UnifiedMaxSize::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::uvector2ToString(static_cast<const Window*>(receiver)->getWindowMaxSize());
}

void UnifiedMaxSize::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setWindowMaxSize(PropertyHelper::stringToUVector2(value));
}


String ZoomMode::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::metricsModeToString(static_cast<const Window*>(receiver)->getZoomMode());
}


void ZoomMode::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setZoomMode(PropertyHelper::stringToMetricsMode(value));
}


String HookPosition::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::pointToString(static_cast<const Window*>(receiver)->getHookPosition());
}


void HookPosition::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setHookPosition(PropertyHelper::stringToPoint(value));
}

String HookMode::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::hookModeToString(static_cast<const Window*>(receiver)->getHookMode());
}


void HookMode::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setHookMode(PropertyHelper::stringToHookMode(value));
}


String StepShowTime::get(const PropertyReceiver* receiver) const
{
	 return PropertyHelper::floatToString(static_cast<const Window*>(receiver)->getStepShowTime());
}


void StepShowTime::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setStepShowTime(PropertyHelper::stringToFloat(value));
}

String NeedRealTimeUpdate::get(const PropertyReceiver* receiver) const
{
	return "";
}


void NeedRealTimeUpdate::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setNeedRealTimeUpdate(PropertyHelper::stringToBool(value));
}


String ExtendTooltip::get(const PropertyReceiver* receiver) const
{
	return "";
}


void ExtendTooltip::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setExtendTooltip(PropertyHelper::stringToBool(value));
}



String GroupWindow::get(const PropertyReceiver* receiver) const
{
	return "";
}


void GroupWindow::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setGroupWindow(PropertyHelper::stringToBool(value));
}

String BaseTop::get(const PropertyReceiver* receiver) const
{
	return "";
}


void BaseTop::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setBaseTop(PropertyHelper::stringToBool(value));
}

String BaseHorizon::get(const PropertyReceiver* receiver) const
{
	return "";
}


void BaseHorizon::set(PropertyReceiver* receiver, const String& value)
{
	if(value == "right")
		static_cast<Window*>(receiver)->setBaseLeft(BHE_RIGHT);
	else if(value == "center")
		static_cast<Window*>(receiver)->setBaseLeft(BHE_CENTER);
	else
		static_cast<Window*>(receiver)->setBaseLeft(BHE_LEFT);
}		

String SpecialModal::get(const PropertyReceiver* receiver) const
{
	return "";
}


void SpecialModal::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setSpecialModal(PropertyHelper::stringToBool(value));
}

String HyperLinkColorDefault::get(const PropertyReceiver* receiver) const
{
	return "";
}
void HyperLinkColorDefault::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setHyperLinkColorDefault( 
		PropertyHelper::stringToColour(value) );
}
String HyperLinkColorActive::get(const PropertyReceiver* receiver) const
{
	return "";
}
void HyperLinkColorActive::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Window*>(receiver)->setHyperLinkColorActive( 
		PropertyHelper::stringToColour(value) );
}
} 

} 
