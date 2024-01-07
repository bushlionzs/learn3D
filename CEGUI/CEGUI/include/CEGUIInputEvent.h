

#ifndef _CEGUIInputEvent_h_
#define _CEGUIInputEvent_h_

#include "CEGUIBase.h"
#include "CEGUIEventArgs.h"
#include "CEGUIString.h"
#include "CEGUIVector.h"



namespace CEGUI
{

struct CEGUIEXPORT Key
{
	
	enum Scan
    {
        Escape          =0x01,
        One             =0x02,
        Two             =0x03,
        Three           =0x04,
        Four            =0x05,
        Five            =0x06,
        Six             =0x07,
        Seven           =0x08,
        Eight           =0x09,
        Nine            =0x0A,
        Zero            =0x0B,
        Minus           =0x0C,    
        Equals			=0x0D,
        Backspace		=0x0E,    
        Tab				=0x0F,
        Q               =0x10,
        W               =0x11,
        E               =0x12,
        R               =0x13,
        T               =0x14,
        Y               =0x15,
        U               =0x16,
        I               =0x17,
        O               =0x18,
        P               =0x19,
        LeftBracket     =0x1A,
        RightBracket    =0x1B,
        Return			=0x1C,    
        LeftControl		=0x1D,
        A               =0x1E,
        S               =0x1F,
        D               =0x20,
        F               =0x21,
        G               =0x22,
        H               =0x23,
        J               =0x24,
        K               =0x25,
        L               =0x26,
        Semicolon       =0x27,
        Apostrophe		=0x28,
        Grave           =0x29,    
        LeftShift       =0x2A,
        Backslash       =0x2B,
        Z               =0x2C,
        X               =0x2D,
        C               =0x2E,
        V               =0x2F,
        B               =0x30,
        N               =0x31,
        M               =0x32,
        Comma           =0x33,
        Period          =0x34,    
        Slash           =0x35,    
        RightShift      =0x36,
        Multiply        =0x37,    
        LeftAlt        =0x38,    
        Space           =0x39,
        Capital         =0x3A,
        F1              =0x3B,
        F2              =0x3C,
        F3              =0x3D,
        F4              =0x3E,
        F5              =0x3F,
        F6              =0x40,
        F7              =0x41,
        F8              =0x42,
        F9              =0x43,
        F10             =0x44,
        NumLock         =0x45,
        ScrollLock      =0x46,    
        Numpad7         =0x47,
        Numpad8         =0x48,
        Numpad9         =0x49,
        Subtract        =0x4A,    
        Numpad4         =0x4B,
        Numpad5         =0x4C,
        Numpad6         =0x4D,
        Add				=0x4E,    
        Numpad1         =0x4F,
        Numpad2         =0x50,
        Numpad3         =0x51,
        Numpad0         =0x52,
        Decimal			=0x53,    
        OEM_102         =0x56,    
        F11             =0x57,
        F12             =0x58,
        F13             =0x64,    
        F14             =0x65,    
        F15             =0x66,    
        Kana            =0x70,    
        ABNT_C1         =0x73,    
        Convert         =0x79,    
        NoConvert       =0x7B,    
        Yen             =0x7D,    
        ABNT_C2         =0x7E,    
        NumpadEquals    =0x8D,    
        PrevTrack       =0x90,    
        At              =0x91,    
        Colon           =0x92,    
        Underline       =0x93,    
        Kanji           =0x94,    
        Stop            =0x95,    
        AX              =0x96,    
        Unlabeled       =0x97,    
        NextTrack       =0x99,    
        NumpadEnter     =0x9C,    
        RightControl    =0x9D,
        Mute            =0xA0,    
        Calculator      =0xA1,    
        PlayPause       =0xA2,    
        MediaStop       =0xA4,    
        VolumeDown      =0xAE,    
        VolumeUp        =0xB0,    
        WebHome         =0xB2,    
        NumpadComma     =0xB3,    
        Divide          =0xB5,    
        SysRq           =0xB7,
        RightAlt        =0xB8,    
        Pause           =0xC5,    
        Home            =0xC7,    
        ArrowUp         =0xC8,    
        PageUp          =0xC9,    
        ArrowLeft       =0xCB,    
        ArrowRight      =0xCD,    
        End             =0xCF,    
        ArrowDown       =0xD0,    
        PageDown		=0xD1,    
        Insert          =0xD2,    
        Delete          =0xD3,    
        LeftWindows     =0xDB,    
        RightWindow     =0xDC,    
        RightWindows    =0xDC,    
        AppMenu         =0xDD,    
        Power           =0xDE,    
        Sleep           =0xDF,    
        Wake			=0xE3,    
        WebSearch		=0xE5,    
        WebFavorites	=0xE6,    
        WebRefresh		=0xE7,    
        WebStop			=0xE8,    
        WebForward		=0xE9,    
        WebBack			=0xEA,    
        MyComputer		=0xEB,    
        Mail			=0xEC,    
        MediaSelect		=0xED     
    };

};



enum MouseButton
{
	LeftButton,
	RightButton,
	MiddleButton,
	X1Button,
	X2Button,
	MouseButtonCount,		
	NoButton				
};



enum SystemKey
{
	LeftMouse		= 0x0001,			
	RightMouse		= 0x0002,			
	Shift			= 0x0004,			
	Control			= 0x0008,			
	MiddleMouse		= 0x0010,			
	X1Mouse			= 0x0020,			
	X2Mouse			= 0x0040,			
	Alt				= 0x0080			
};



class CEGUIEXPORT WindowEventArgs : public EventArgs
{
public:
	WindowEventArgs(Window* wnd) : window(wnd) {}
	
	virtual bool isKindOf(const String& strClassName) const 
	{ 
		return strClassName=="Window" ? true : EventArgs::isKindOf(strClassName);
	}

	Window*	window;		
};

class CEGUIEXPORT HyperLinkEventArgs : public EventArgs
{
public:
	HyperLinkEventArgs(const String& winName, const String& hyperName) : windowName(winName), hyperLinkName(hyperName) {}
	
	virtual bool isKindOf(const String& strClassName) const 
	{ 
		return strClassName=="HyperLink" ? true: EventArgs::isKindOf(strClassName);
	}

	String	windowName;
	String	hyperLinkName;
};


class CEGUIEXPORT MouseEventArgs : public WindowEventArgs
{
public:
	MouseEventArgs(Window* wnd) : WindowEventArgs(wnd) {}
	
	virtual bool isKindOf(const String& strClassName) const 
	{ 
		return strClassName=="Mouse" ? true : WindowEventArgs::isKindOf(strClassName);
	}

	Point		position;		
	Vector2		moveDelta;		
	MouseButton	button;			
	uint		sysKeys;		
	float		wheelChange;	
	uint        clickCount;     
};



class CEGUIEXPORT MouseCursorEventArgs : public EventArgs
{
public:
	MouseCursorEventArgs(MouseCursor* cursor) : mouseCursor(cursor) {}
	
	virtual bool isKindOf(const String& strClassName) const 
	{ 
		return strClassName=="MouseCursor" ? true : EventArgs::isKindOf(strClassName);
	}

	MouseCursor* mouseCursor;	
	const Image* image;			
};



class CEGUIEXPORT KeyEventArgs : public WindowEventArgs
{
public:
	KeyEventArgs(Window* wnd) : WindowEventArgs(wnd) {}
	
	virtual bool isKindOf(const String& strClassName) const 
	{ 
		return strClassName=="Key" ? true : WindowEventArgs::isKindOf(strClassName);
	}

	utf32		codepoint;		
	Key::Scan	scancode;		
	uint		sysKeys;		
};



class CEGUIEXPORT ActivationEventArgs : public WindowEventArgs
{
public:
	ActivationEventArgs(Window* wnd) : WindowEventArgs(wnd) {}
	
	virtual bool isKindOf(const String& strClassName) const 
	{ 
		return strClassName=="Activation" ? true : WindowEventArgs::isKindOf(strClassName);
	}

	Window*	otherWindow;	
};


class CEGUIEXPORT DragDropEventArgs : public WindowEventArgs
{
public:
	DragDropEventArgs(Window* wnd) : WindowEventArgs(wnd) {}
	
	virtual bool isKindOf(const String& strClassName) const 
	{ 
		return strClassName=="DragDrop" ? true : WindowEventArgs::isKindOf(strClassName);
	}

	DragContainer*	dragDropItem; 
};

} 


#endif	
