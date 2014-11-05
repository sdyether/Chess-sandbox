#if !defined WINMAKER_H
#define WINMAKER_H

#include <windows.h>

//wrap the window creation


class WinMaker {

public:

	WinMaker(WinClass &winClass);
	HWND getWindowHandle() { return windowHandle; }

	void AddCaption (wchar_t const * caption) {
		windowName = caption;
	}

	void AddSysMenu ()    { style |= WS_SYSMENU; }
	void AddVScrollBar () { style |= WS_VSCROLL; }
	void AddHScrollBar () { style |= WS_HSCROLL; }
	void Create ();
	void Show (int nCmdShow = SW_SHOWNORMAL);

	//getters and setters
	int getWidth() { 
		return width; 
	}

	int getHeight() { 
		return height; 
	}


	void setWidth(int pWidth) { 
		width = pWidth; 
	}

	void setHeight(int pHeight) { 
		height = pHeight; 
	}

protected:
	HWND windowHandle;
	WinClass &_class;

	int width; //window sizes and positions
	int height;
	int xPos;
	int yPos;
	
	DWORD exStyle; //extended window style
	DWORD style; //window style
	wchar_t const * windowName; //pointer to window name
	HWND parentHandle; //handle to owner window
	HMENU menuHandle; //handle to menu
	void * data; //pointer to window creation data
};

//extend top window with caption
class TopWinMaker : public WinMaker {
public:
	TopWinMaker(WinClass &winClass, wchar_t const * caption);
};

//use this to manage the appropriate controller for the window we want
template <class T>
inline T WinGetLong (HWND windowHandle, int which = GWL_USERDATA)
{
	return reinterpret_cast<T> (::GetWindowLong (windowHandle, which));
}

template <class T>
inline void WinSetLong (HWND windowHandle, T value, int which = GWL_USERDATA)
{
	::SetWindowLong (windowHandle, which, reinterpret_cast<long> (value));
}

#endif
