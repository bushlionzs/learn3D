#pragma once

class ApplicationBase;
class ApplicationWindow
{
public:
	ApplicationWindow(ApplicationBase* app);
	~ApplicationWindow();

	bool createWindow(int32_t width, int32_t height);
	HWND getWnd()
	{
		return mWnd;
	}
	LRESULT WINAPI MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND mWnd;
	HINSTANCE m_hInstance;
	int32_t mWidth, mHeight;
	ApplicationBase* mApp;
};