#pragma once


class ApplicationWindow
{
public:
	ApplicationWindow();
	~ApplicationWindow();

	bool createWindow(int32_t width, int32_t height);
	HWND getWnd()
	{
		return mWnd;
	}
private:
	HWND mWnd;
	HINSTANCE m_hInstance;
	int32_t mWidth, mHeight;
};