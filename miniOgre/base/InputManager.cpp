#include "OgreHeader.h"
#include "InputManager.h"



template<> InputManager* Ogre::Singleton< InputManager >::msSingleton = NULL;

LRESULT InputManager::msOldWindowProc = NULL;

bool InputManager::msSkipMove = false;

int VirtualKeyToText(WPARAM _virtualKey)
{
	static WCHAR deadKey = 0;

	BYTE keyState[256];
	HKL  layout = GetKeyboardLayout(0);
	if (GetKeyboardState(keyState) == 0)
		return 0;

	WCHAR buff[3] = { 0, 0, 0 };
	int ascii = ToUnicodeEx((UINT)_virtualKey, 0, keyState, buff, 3, 0, layout);
	if (ascii == 1 && deadKey != '\0')
	{
		// A dead key is stored and we have just converted a character key
		// Combine the two into a single character
		WCHAR wcBuff[3] = { buff[0], deadKey, '\0' };
		WCHAR out[3];

		deadKey = '\0';
		if (FoldStringW(MAP_PRECOMPOSED, (LPWSTR)wcBuff, 3, (LPWSTR)out, 3))
			return out[0];
	}
	else if (ascii == 1)
	{
		// We have a single character
		deadKey = '\0';
		return buff[0];
	}
	else if (ascii == 2)
	{
		// Convert a non-combining diacritical mark into a combining diacritical mark
		// Combining versions range from 0x300 to 0x36F; only 5 (for French) have been mapped below
		// http://www.fileformat.info/info/unicode/block/combining_diacritical_marks/images.htm
		switch (buff[0])
		{
		case 0x5E: // Circumflex accent: §Ó
			deadKey = 0x302;
			break;
		case 0x60: // Grave accent: §Ñ
			deadKey = 0x300;
			break;
		case 0xA8: // Diaeresis: §î
			deadKey = 0x308;
			break;
		case 0xB4: // Acute accent: §Û
			deadKey = 0x301;
			break;
		case 0xB8: // Cedilla: §Ù
			deadKey = 0x327;
			break;
		default:
			deadKey = buff[0];
			break;
		}
	}
	return 0;
}

static int ScanCodeToText(int _scanCode)
{
	HKL  layout = GetKeyboardLayout(0);
	unsigned int vk = MapVirtualKeyEx((UINT)_scanCode, 3, layout);
	if (vk == 0)
		return 0;

	return VirtualKeyToText(vk);
}

bool gUseMouseMessage = true;

LRESULT CALLBACK InputManager::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#define __WM_REALMOUSELAST WM_MOUSEWHEEL
#else
#define __WM_REALMOUSELAST WM_MOUSELAST
#endif // WM_MOUSEWHEEL

#define GET_HIWORD(param) ((short)HIWORD(param))
#define GET_LOWORD(param) ((short)LOWORD(param))

	if (WM_DROPFILES == uMsg)
	{
		HDROP hDrop = (HDROP)wParam;
		wchar_t buff[MAX_PATH] = { 0 };
		UINT fcount = DragQueryFileW(hDrop, 0xFFFFFFFF, NULL, 0);

		for (UINT index = 0; index < fcount; ++index)
		{
			DragQueryFileW(hDrop, index, buff, MAX_PATH);
			InputManager::getSingleton().onFileDrop(buff);
		}

		DragFinish(hDrop);
		return 0;
	}
	else if (WM_SETCURSOR == uMsg)
	{
		InputManager::getSingleton().onMouseCursor();
		return TRUE;
	}
	else if (WM_CLOSE == uMsg)
	{
		if (!InputManager::getSingleton().onWindowClose((size_t)hWnd))
			return 0;
	}
	else if ((uMsg >= WM_MOUSEFIRST) && (uMsg <= __WM_REALMOUSELAST))
	{
		if (gUseMouseMessage)
		{
			static int old_x = 0;
			static int old_y = 0;
			static int old_z = 0;
			static bool left_button = false;
			static bool right_button = false;

			switch (uMsg)
			{
			case WM_MOUSEMOVE:
			{
				int x = GET_LOWORD(lParam);
				int y = GET_HIWORD(lParam);

				if (x < 0) x = 0;
				else if (x > InputManager::getSingleton().mWidth) x = InputManager::getSingleton().mWidth;
				if (y < 0) y = 0;
				else if (y > InputManager::getSingleton().mHeight) y = InputManager::getSingleton().mHeight;

				old_x = x;
				old_y = y;

				if (msSkipMove)
					msSkipMove = false;
				else
					InputManager::getSingleton().mouseMove(old_x, old_y, old_z);
				break;
			}
			case WM_MOUSEWHEEL:
				old_z = GET_HIWORD(wParam);
				InputManager::getSingleton().mouseWheel(old_z);
				break;

			case WM_LBUTTONDOWN:
				left_button = true;
				if (!right_button)
					::SetCapture(hWnd);
				InputManager::getSingleton().mousePress(old_x, old_y, OIS::MouseButtonID::MB_Left);
				break;


			case WM_LBUTTONDBLCLK:
				left_button = true;
				if (!right_button)
					::SetCapture(hWnd);
				InputManager::getSingleton().mousePress(old_x, old_y, OIS::MouseButtonID::MB_Left);
				break;

			case WM_RBUTTONDOWN:
			{
				right_button = true;
				if (!left_button)
					::SetCapture(hWnd);
				int x = GET_LOWORD(lParam);
				int y = GET_HIWORD(lParam);
				InputManager::getSingleton().mousePress(x, y, OIS::MouseButtonID::MB_Right);
				break;
			}
			case WM_RBUTTONDBLCLK:
				right_button = true;
				if (!left_button)
					::SetCapture(hWnd);
				InputManager::getSingleton().mousePress(old_x, old_y, OIS::MouseButtonID::MB_Right);
				break;

			case WM_MBUTTONDOWN:
				InputManager::getSingleton().mousePress(old_x, old_y, OIS::MouseButtonID::MB_Middle);
				break;

			case WM_LBUTTONUP:
				InputManager::getSingleton().mouseRelease(old_x, old_y, OIS::MouseButtonID::MB_Left);
				left_button = false;
				if (!right_button)
					::SetCapture(0);
				break;
			case WM_RBUTTONUP:
				right_button = false;
				if (!left_button)
					::SetCapture(0);
				InputManager::getSingleton().mouseRelease(old_x, old_y, OIS::MouseButtonID::MB_Right);
				break;
			case WM_MBUTTONUP:
				InputManager::getSingleton().mouseRelease(old_x, old_y, OIS::MouseButtonID::MB_Middle);
				break;
			}
		}
	}


	return CallWindowProc((WNDPROC)msOldWindowProc, hWnd, uMsg, wParam, lParam);
}

InputManager::InputManager() :
	mInputManager(nullptr),
	mKeyboard(nullptr),
	mMouse(nullptr),
	mHwnd(0),
	mMouseX(0),
	mMouseY(0),
	mMouseZ(0),
	mMouseMove(false)
{
	
}

InputManager::~InputManager()
{
	
}

void InputManager::createInput(size_t _handle)
{
	mHwnd = (HWND)_handle;


	if (!msOldWindowProc)
	{
		msOldWindowProc = GetWindowLongPtr(mHwnd, GWLP_WNDPROC);
		SetWindowLongPtr(mHwnd, GWLP_WNDPROC, (LONG_PTR)windowProc);
	}


	LONG_PTR style = GetWindowLongPtr(mHwnd, GWL_EXSTYLE);
	SetWindowLongPtr(mHwnd, GWL_EXSTYLE, style | WS_EX_ACCEPTFILES);

	std::ostringstream windowHndStr;
	windowHndStr << _handle;

	OIS::ParamList pl;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mKeyboard->setEventCallback(this);

	if (!gUseMouseMessage)
	{
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
		mMouse->setEventCallback(this);
	}
	
}

void InputManager::destroyInput()
{
	if (msOldWindowProc)
	{
		SetWindowLongPtr((HWND)mHwnd, GWLP_WNDPROC, (LONG_PTR)msOldWindowProc);
		msOldWindowProc = 0;
	}

	if (mInputManager)
	{
		if (mKeyboard)
		{
			mInputManager->destroyInputObject(mKeyboard);
			mKeyboard = nullptr;
		}
		OIS::InputManager::destroyInputSystem(mInputManager);
		mInputManager = nullptr;
	}
}

void InputManager::captureInput()
{
	mKeyboard->capture();
	if (!gUseMouseMessage)
	{
		mMouse->capture();
	}
}

void InputManager::setInputViewSize(int _width, int _height)
{
	mWidth = _width;
	mHeight = _height;
}

void InputManager::onMouseCursor()
{
	for (auto listener : listeners)
	{
		listener->injectMouseCursor();
	}
}

void InputManager::setMousePosition(int _x, int _y)
{
	POINT point = { _x, _y };
	::ClientToScreen(mHwnd, &point);

	msSkipMove = true;
	::SetCursorPos(point.x, point.y);
}

void InputManager::updateCursorPosition()
{
}

void InputManager::addListener(InputListener* listener)
{
	listeners.push_back(listener);
}
void InputManager::removeListener(InputListener* listener)
{
	listeners.erase(std::find(listeners.begin(), listeners.end(), listener));
}

POINT InputManager::MouseGetPos()
{
	POINT pt;
	pt.x = mMouseX;
	pt.y = mMouseY;
	return pt;
}

bool InputManager::IsKeyDown(OIS::KeyCode key)
{
	return mKeyboard->isKeyDown(key);
}
//void InputManager::SetCaptureType(InputCaptureType type)
//{
//	mInputCaptureType = type;
//}
//
//InputCaptureType InputManager::GetCaptureType()
//{
//	return IC_GAME;
//}

extern int ScanCodeToText(int _scanCode);
bool InputManager::keyPressed(const OIS::KeyEvent& _arg)
{
	unsigned int text = _arg.text;
	KeyCode key = KeyCode::Enum(_arg.key);
	int scan_code = key.getValue();

	if (scan_code > 70 && scan_code < 84)
	{
		static unsigned int nums[13] = { 55, 56, 57, 45, 52, 53, 54, 43, 49, 50, 51, 48, 46 };
		text = nums[scan_code - 71];
	}
	else if (key == KeyCode::Divide)
	{
		text = '/';
	}
	else
	{
#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
		text = ScanCodeToText((int)key.getValue());
#endif
	}

	injectKeyPress(key, text);
	return true;
}

bool InputManager::keyReleased(const OIS::KeyEvent& _arg)
{
	injectKeyRelease(KeyCode::Enum(_arg.key));
	return true;
}



bool InputManager::mouseMoved(const OIS::MouseEvent& arg)
{
	injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
	return true;
}

bool InputManager::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	injectMousePress(arg.state.X.abs, arg.state.Y.abs, id);
	return true;
}
bool InputManager::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, id);
	return true;
}

void InputManager::frameEvent(float _time)
{
	computeMouseMove();
}

void InputManager::computeMouseMove()
{
	if (mMouseMove)
	{
		injectMouseMove(mMouseX, mMouseY, mMouseZ);
		mMouseMove = false;
	}
}

void InputManager::mouseWheel(int _absz)
{
	injectMouseWheel(_absz);
}

void InputManager::mouseMove(int _absx, int _absy, int _absz)
{
	injectMouseMove(_absx, _absy, _absz);
}

void InputManager::mousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
	injectMousePress(_absx, _absy, _id);
}

void InputManager::mouseRelease(int _absx, int _absy, OIS::MouseButtonID _id)
{
	injectMouseRelease(_absx, _absy, _id);
}

void InputManager::injectMouseWheel(int _absz)
{
	if (!mInputManager)
		return;

	/*for (auto listener : listeners)
	{
		listener->injectMouseWheel(_absz);
	}*/
}

void InputManager::injectMouseMove(int _absx, int _absy, int _absz)
{
	if (!mInputManager)
		return;

	for (auto listener : listeners)
	{
		listener->injectMouseMove(_absx, _absy, _absz);
	}
}

void InputManager::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
	if (!mInputManager)
		return;
	for (auto listener : listeners)
	{
		listener->injectMousePress(_absx, _absy, _id);
	}
}

void InputManager::injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id)
{
	if (!mInputManager)
		return;

	for (auto listener : listeners)
	{
		listener->injectMouseRelease(_absx, _absy, _id);
	}
}

void InputManager::injectKeyPress(KeyCode _key, uint32_t _text)
{

	if (!mInputManager)
		return;

	if (_key == KeyCode::Escape)
	{
		//mExit = true;
		return;
	}
	else if (_key == KeyCode::SysRq)
	{
		//makeScreenShot();
		return;
	}

	// change polygon mode
	// TODO: polygon mode require changes in platform
	else if (_key == KeyCode::F5)
	{
		//getCamera()->setPolygonMode(Ogre::PM_SOLID);
	}
	else if (_key == KeyCode::F6)
	{
		//getCamera()->setPolygonMode(Ogre::PM_WIREFRAME);
	}
	else if (_key == KeyCode::F7)
	{
		//getCamera()->setPolygonMode(Ogre::PM_POINTS);
	}

	for (auto listener : listeners)
	{
		listener->injectKeyPress(_key, _text);
	}
}

void InputManager::injectKeyRelease(KeyCode _key)
{
	if (!mInputManager)
		return;
	for (auto listener : listeners)
	{
		listener->injectKeyRelease(_key);
	}
}

