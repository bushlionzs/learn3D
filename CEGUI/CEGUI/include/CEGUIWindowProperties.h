

#ifndef _CEGUIWindowProperties_h_
#define _CEGUIWindowProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{



namespace WindowProperties
{

class RelativeMinSize : public Property
{
public:
	RelativeMinSize() : Property(
		"RelativeMinSize",
		"Property to get/set the minimum size for the Window.  Value is \"w:[float] h:[float]\" using relative metrics (this setting is relative to the display size).",
		"w:0.000000 h:0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RelativeMaxSize : public Property
{
public:
	RelativeMaxSize() : Property(
		"RelativeMaxSize",
		"Property to get/set the maximum size for the Window.  Value is \"w:[float] h:[float]\" using relative metrics (this setting is relative to the display size).",
		"w:1.000000 h:1.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AbsoluteMinSize : public Property
{
public:
	AbsoluteMinSize() : Property(
		"AbsoluteMinSize",
		"Property to get/set the minimum size for the Window.  Value is \"w:[float] h:[float]\" using absolute (pixel) metrics.",
		"w:0.000000 h:0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AbsoluteMaxSize : public Property
{
public:
	AbsoluteMaxSize() : Property(
		"AbsoluteMaxSize",
		"Property to get/set the maximum size for the Window.  Value is \"w:[float] h:[float]\" using absolute (pixel) metrics.",
		"", false)
		{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);

	
	bool	isDefault(const PropertyReceiver* receiver) const;
	String	getDefault(const PropertyReceiver* receiver) const;
};



class MetricsMode : public Property
{
public:
	MetricsMode() : Property(
		"MetricsMode",
		"Property to get/set the metrics mode for the Window.  Value is \"Relative\", \"Absolute\", or \"Inherited\".",
		"Relative")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class ID : public Property
{
public:
	ID() : Property(
		"ID",
		"Property to get/set the ID value of the Window.  Value is an unsigned integer number.",
		"0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class Alpha : public Property
{
public:
	Alpha() : Property(
		"Alpha",
		"Property to get/set the alpha value of the Window.  Value is floating point number.",
		"1.000000") 
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class Font : public Property
{
public:
	Font() : Property(
		"Font",
		"Property to get/set the font for the Window.  Value is the name of the font to use (must be loaded already).",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
	bool	isDefault(const PropertyReceiver* receiver) const;
};


class MouseHollow : public Property
{
public:
	MouseHollow() : Property(
		"MouseHollow", 
        "Property to get/set whether the window will ignore all mouse input events.  Value is either \"True\" or \"False\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};
class MouseMoveHollow : public Property
{
public:
	MouseMoveHollow() : Property(
		"MouseMoveHollow", 
        "Property to get/set whether the window will ignore all mouse input events.  Value is either \"True\" or \"False\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

class MouseLButtonHollow : public Property
{
public:
	MouseLButtonHollow() : Property(
		"MouseLButtonHollow", 
        "Property to get/set whether the window will ignore all mouse l-button input events.  Value is either \"True\" or \"False\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class MouseRButtonHollow : public Property
{
public:
	MouseRButtonHollow() : Property(
		"MouseRButtonHollow", 
        "Property to get/set whether the window will ignore all mouse r-button input events.  Value is either \"True\" or \"False\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class TextOriginal : public Property
{
public:
	TextOriginal() : Property(
		"TextOriginal", 
		"Property to get/set the text / caption for the Window.  Value is the text string to use.",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

class Text : public Property
{
public:
	Text() : Property(
		"Text", 
		"Property to get/set the text / caption for the Window.  Value is the text string to use.",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class MouseCursorImage : public Property
{
public:
	MouseCursorImage() : Property(
		"MouseCursorImage",
		"Property to get/set the mouse cursor image for the Window.  Value should be \"set:<imageset name> image:<image name>\".",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
	bool	isDefault(const PropertyReceiver* receiver) const;
};



class ClippedByParent : public Property
{
public:
	ClippedByParent() : Property(
		"ClippedByParent",
		"Property to get/set the 'clipped by parent' setting for the Window.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class InheritsAlpha : public Property
{
public:
	InheritsAlpha() : Property(
		"InheritsAlpha",
		"Property to get/set the 'inherits alpha' setting for the Window.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AlwaysOnTop : public Property
{
public:
	AlwaysOnTop() : Property(
		"AlwaysOnTop",
		"Property to get/set the 'always on top' setting for the Window.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class WindowLayOutNum : public Property
{
public:
	WindowLayOutNum() : Property(
		"WindowLayOutNum",
		"Property to get/set the 'Window Lay Outp' setting for the Window.  Value is Number between the 0--99",
		"50")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class Disabled : public Property
{
public:
	Disabled() : Property(
		"Disabled",
		"Property to get/set the 'disabled state' setting for the Window.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
	bool	isDefault(const PropertyReceiver* receiver) const;
};



class Visible : public Property
{
public:
	Visible() : Property(
		"Visible",
		"Property to get/set the 'visible state' setting for the Window.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
	bool	isDefault(const PropertyReceiver* receiver) const;
};



class RestoreOldCapture : public Property
{
public:
	RestoreOldCapture() : Property(
		"RestoreOldCapture",
		"Property to get/set the 'restore old capture' setting for the Window.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class DestroyedByParent : public Property
{
public:
	DestroyedByParent() : Property(
		"DestroyedByParent",
		"Property to get/set the 'destroyed by parent' setting for the Window.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class Width : public Property
{
public:
	Width() : Property(
		"Width",
		"Property to get/set the width of the Window.  Value is floating point using the active metrics mode.",
		"0.000000", false) {}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RelativeWidth : public Property
{
public:
	RelativeWidth() : Property(
		"RelativeWidth",
		"Property to get/set the width of the Window.  Value is floating point using relative metrics.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AbsoluteWidth: public Property
{
public:
	AbsoluteWidth() : Property(
		"AbsoluteWidth",
		"Property to get/set the width of the Window.  Value is floating point using absolute metrics.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class Height : public Property
{
public:
	Height() : Property(
		"Height",
		"Property to get/set the height of the Window.  Value is floating point using the active metrics mode.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RelativeHeight : public Property
{
public:
	RelativeHeight() : Property(
		"RelativeHeight",
		"Property to get/set the height of the Window.  Value is floating point using relative metrics.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AbsoluteHeight : public Property
{
public:
	AbsoluteHeight() : Property(
		"AbsoluteHeight",
		"Property to get/set the height of the Window.  Value is floating point using absolute metrics.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class Size : public Property
{
public:
	Size() : Property(
		"Size",
		"Property to get/set the size of the Window.  Value is \"w:[float] h:[float]\" using the active metrics mode.",
		"w:0.000000 h:0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RelativeSize : public Property
{
public:
	RelativeSize() : Property(
		"RelativeSize",
		"Property to get/set the size of the Window.  Value is \"w:[float] h:[float]\" using relative metrics.",
		"w:0.000000 h:0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AbsoluteSize : public Property
{
public:
	AbsoluteSize() : Property(
		"AbsoluteSize",
		"Property to get/set the size of the Window.  Value is \"w:[float] h:[float]\" using absolute metrics.",
		"w:0.000000 h:0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class XPosition : public Property
{
public:
	XPosition() : Property(
		"XPosition",
		"Property to get/set the x co-ordinate position of the Window.  Value is a floating point number using the active metrics mode.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RelativeXPosition : public Property
{
public:
	RelativeXPosition() : Property(
		"RelativeXPosition",
		"Property to get/set the x co-ordinate position of the Window.  Value is a floating point number using relative metrics.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AbsoluteXPosition : public Property
{
public:
	AbsoluteXPosition() : Property(
		"AbsoluteXPosition",
		"Property to get/set the x co-ordinate position of the Window.  Value is a floating point number using absolute metrics.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class YPosition : public Property
{
public:
	YPosition() : Property(
		"YPosition",
		"Property to get/set the y co-ordinate position of the Window.  Value is a floating point number using the active metrics mode.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RelativeYPosition : public Property
{
public:
	RelativeYPosition() : Property(
		"RelativeYPosition",
		"Property to get/set the y co-ordinate position of the Window.  Value is a floating point number using relative metrics.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AbsoluteYPosition : public Property
{
public:
	AbsoluteYPosition() : Property(
		"AbsoluteYPosition",
		"Property to get/set the y co-ordinate position of the Window.  Value is a floating point number using absolute metrics.",
		"0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class Position : public Property
{
public:
	Position() : Property(
		"Position",
		"Property to get/set the position of the Window.  Value is \"x:[float] y:[float]\" using the active metrics mode.",
		"x:0.000000 y:0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RelativePosition : public Property
{
public:
	RelativePosition() : Property(
		"RelativePosition",
		"Property to get/set the position of the Window.  Value is \"x:[float] y:[float]\" using relative metrics.",
		"x:0.000000 y:0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AbsolutePosition : public Property
{
public:
	AbsolutePosition() : Property(
		"AbsolutePosition",
		"Property to get/set the position of the Window.  Value is \"x:[float] y:[float]\" using absolute metrics.",
		"x:0.000000 y:0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class Rect : public Property
{
public:
	Rect() : Property(
		"Rect",
		"Property to get/set the area rectangle of the Window.  Value is \"l:[float] t:[float] r:[float] b:[float]\" (where l is left, t is top, r is right, and b is bottom) using the active metrics system.",
		"l:0.000000 t:0.000000 r:0.000000 b:0.000000", false)
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class RelativeRect : public Property
{
public:
	RelativeRect() : Property(
		"RelativeRect",
		"Property to get/set the area rectangle of the Window.  Value is \"l:[float] t:[float] r:[float] b:[float]\" (where l is left, t is top, r is right, and b is bottom) using relative metrics.",
		"l:0.000000 t:0.000000 r:0.000000 b:0.000000", false) 
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class AbsoluteRect : public Property
{
public:
	AbsoluteRect() : Property(
		"AbsoluteRect",
		"Property to get/set the area rectangle of the Window.  Value is \"l:[float] t:[float] r:[float] b:[float]\" (where l is left, t is top, r is right, and b is bottom) using absolute metrics.",
		"l:0.000000 t:0.000000 r:0.000000 b:0.000000", false) 
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class ZOrderChangeEnabled : public Property
{
public:
	ZOrderChangeEnabled() : Property(
		"ZOrderChangeEnabled",
		"Property to get/set the 'z-order changing enabled' setting for the Window.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class WantsMultiClickEvents : public Property
{
public:
    WantsMultiClickEvents() : Property(
        "WantsMultiClickEvents",
        "Property to get/set whether the window will receive double-click and triple-click events.  Value is either \"True\" or \"False\".",
        "True")
    {}

    String	get(const PropertyReceiver* receiver) const;
    void	set(PropertyReceiver* receiver, const String& value);
};



class MouseButtonDownAutoRepeat : public Property
{
public:
    MouseButtonDownAutoRepeat() : Property(
        "MouseButtonDownAutoRepeat",
        "Property to get/set whether the window will receive autorepeat mouse button down events.  Value is either \"True\" or \"False\".",
        "False")
    {}

    String  get(const PropertyReceiver* receiver) const;
    void    set(PropertyReceiver* receiver, const String& value);
};



class AutoRepeatDelay : public Property
{
public:
    AutoRepeatDelay() : Property(
        "AutoRepeatDelay",
        "Property to get/set the autorepeat delay.  Value is a floating point number indicating the delay required in seconds.",
        "0.300000")
    {}

    String  get(const PropertyReceiver* receiver) const;
    void    set(PropertyReceiver* receiver, const String& value);
};



class AutoRepeatRate : public Property
{
public:
    AutoRepeatRate() : Property(
        "AutoRepeatRate",
        "Property to get/set the autorepeat rate.  Value is a floating point number indicating the rate required in seconds.",
        "0.060000")
    {}

    String  get(const PropertyReceiver* receiver) const;
    void    set(PropertyReceiver* receiver, const String& value);
};


class DistributeCapturedInputs : public Property
{
public:
	DistributeCapturedInputs() : Property(
		"DistributeCapturedInputs",
		"Property to get/set whether captured inputs are passed to child windows.  Value is either \"True\" or \"False\".",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};


class CustomTooltipType : public Property
{
public:
    CustomTooltipType() : Property(
    "CustomTooltipType",
    "Property to get/set the custom tooltip for the window.  Value is the type name of the custom tooltip.",
    "")
    {}

    String  get(const PropertyReceiver* receiver) const;
    void    set(PropertyReceiver* receiver, const String& value);
};


class Tooltip : public Property
{
public:
    Tooltip() : Property(
    "Tooltip",
    "Property to get/set the tooltip text for the window.  Value is the tooltip text for the window.",
    "")
    {}

    String  get(const PropertyReceiver* receiver) const;
    void    set(PropertyReceiver* receiver, const String& value);
};


class InheritsTooltipText : public Property
{
public:
    InheritsTooltipText() : Property(
        "InheritsTooltipText",
        "Property to get/set whether the window inherits its parents tooltip text when it has none of its own.  Value is either \"True\" or \"False\".",
        "False")
    {}

    String  get(const PropertyReceiver* receiver) const;
    void    set(PropertyReceiver* receiver, const String& value);
};



class RiseOnClick : public Property
{
public:
    RiseOnClick() : Property(
		"RiseOnClick",
		"Property to get/set whether the window will come tot he top of the z order hwn clicked.  Value is either \"True\" or \"False\".",
		"True")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};



class VerticalAlignment : public Property
{
    public:
        VerticalAlignment() : Property(
        "VerticalAlignment",
        "Property to get/set the windows vertical alignment.  Value is one of \"Top\", \"Centre\" or \"Bottom\".",
        "Top")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
};



class HorizontalAlignment : public Property
{
    public:
        HorizontalAlignment() : Property(
        "HorizontalAlignment",
        "Property to get/set the windows horizontal alignment.  Value is one of \"Left\", \"Centre\" or \"Right\".",
        "Left")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
};



class UnifiedAreaRect : public Property
{
	public:
		UnifiedAreaRect() : Property(
		"UnifiedAreaRect",
		"Property to get/set the windows unified area rectangle.  Value is a \"URect\".",
		"{{0.000000,0.000000},{0.000000,0.000000},{0.000000,0.000000},{0.000000,0.000000}}")
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};



class UnifiedPosition : public Property
{
	public:
		UnifiedPosition() : Property(
		"UnifiedPosition",
		"Property to get/set the windows unified position.  Value is a \"UVector2\".",
		"{{0.000000,0.000000},{0.000000,0.000000}}", false)
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};



class UnifiedXPosition : public Property
{
	public:
		UnifiedXPosition() : Property(
		"UnifiedXPosition",
		"Property to get/set the windows unified position x-coordinate.  Value is a \"UDim\".",
		"{0.000000,0.000000}", false)
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};



class UnifiedYPosition : public Property
{
	public:
		UnifiedYPosition() : Property(
		"UnifiedYPosition",
		"Property to get/set the windows unified position y-coordinate.  Value is a \"UDim\".",
		"{0.000000,0.000000}", false)
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};



class UnifiedSize : public Property
{
	public:
		UnifiedSize() : Property(
		"UnifiedSize",
		"Property to get/set the windows unified size.  Value is a \"UVector2\".",
		"{{0.000000,0.000000},{0.000000,0.000000}}", false)
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};



class UnifiedWidth : public Property
{
	public:
		UnifiedWidth() : Property(
		"UnifiedWidth",
		"Property to get/set the windows unified width.  Value is a \"UDim\".",
		"{0.000000,0.000000}", false)
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};



class UnifiedHeight : public Property
{
	public:
		UnifiedHeight() : Property(
		"UnifiedHeight",
		"Property to get/set the windows unified height.  Value is a \"UDim\".",
		"{0.000000,0.000000}", false)
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};



class UnifiedMinSize : public Property
{
	public:
		UnifiedMinSize() : Property(
		"UnifiedMinSize",
		"Property to get/set the windows unified minimum size.  Value is a \"UVector2\".",
		"{{0.000000,0.000000},{0.000000,0.000000}}")
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};



class UnifiedMaxSize : public Property
{
	public:
		UnifiedMaxSize() : Property(
		"UnifiedMaxSize",
		"Property to get/set the windows unified maximum size.  Value is a \"UVector2\".",
		"{{0.000000,0.000000},{0.000000,0.000000}}")
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};

class ZoomMode : public Property
{
	public:
		ZoomMode() : Property(
		"ZoomMode",
		"Property to get/set the windows unified maximum size.  Value is a \"UVector2\".",
		"Relative")
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};

class HookPosition: public Property
{
	public:
		HookPosition() : Property(
		"HookPosition",
		"Property to get/set the windows unified maximum size.  Value is a \"UVector2\".",
		"x:0 y:0")
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};

class HookMode: public Property
{
	public:
		HookMode() : Property(
		"HookMode",
		"Property to get/set the windows unified maximum size.  Value is a \"UVector2\".",
		"x:0 y:0")
		{}

		String	get(const PropertyReceiver* receiver) const;
		void	set(PropertyReceiver* receiver, const String& value);
};

class StepShowTime: public Property
{
public:
	StepShowTime() : Property(
		"StepShowTime",
		"Property to get/set the windows show and hide mode",
		"0.0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

class NeedRealTimeUpdate: public Property
{
public:
	NeedRealTimeUpdate() : Property(
		"NeedRealTimeUpdate",
		"Property to get/set the windows show and hide mode",
		"0.0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

class ExtendTooltip: public Property
{
public:
	ExtendTooltip() : Property(
		"ExtendTooltip",
		"Property to get/set the windows ExtendTooltip",
		"false")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

class GroupWindow: public Property
{
public:
	GroupWindow() : Property(
		"GroupWindow",
		"Property to get/set the windows show and hide mode",
		"0.0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

class BaseTop: public Property
{
public:
	BaseTop() : Property(
		"BaseTop",
		"Property to get/set the windows show and hide mode",
		"0.0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

class BaseHorizon: public Property
{
public:
	BaseHorizon() : Property(
		"BaseHorizon",
		"Property to get/set the windows show and hide mode",
		"0.0")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

class SpecialModal: public Property
{
public:
	SpecialModal() : Property(
		"SpecialModal",
		"Property to get/set the windows show and hide mode",
		"False")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};

class HyperLinkColorDefault : public Property
{
public:
	HyperLinkColorDefault() : Property(
		"HyperLinkColorDefault",
		"Property to get/set the windows HyperLinkColorDefault",
		"")
	{}

	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};
class HyperLinkColorActive : public Property
{
public:
	HyperLinkColorActive() : Property(
		"HyperLinkColorActive",
		"Property to get/set the windows HyperLinkColorActive",
		"")
	{}
	String	get(const PropertyReceiver* receiver) const;
	void	set(PropertyReceiver* receiver, const String& value);
};
} 


} 

#endif	
