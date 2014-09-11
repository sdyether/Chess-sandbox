#if !defined MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>

//our callback procedure
LRESULT CALLBACK WindowProcedure
	(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam);

//program creates windows of this class
class WinClass {

public:
	WinClass (WNDPROC winProc, wchar_t const * className, HINSTANCE hInst);
	void Register () {
		::RegisterClass(&_class);
	}

private:
	WNDCLASS _class;

};

//wrap the window creation
class WinMaker {

public:
	WinMaker (): _hwnd (0) {}
	WinMaker (wchar_t const * caption, wchar_t const * className, HINSTANCE hInstance);
	void Show (int cmdShow) {
		::ShowWindow(_hwnd, cmdShow);
		::UpdateWindow(_hwnd);
	}

protected:
	HWND _hwnd;

};

#endif