#include "MainWindow.h"

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrevInst, char * cmdParam, int cmdShow) {
	wchar_t className [] = L"Chess Sandbox";

	WinClass winClass (WindowProcedure, className, hInst);
	winClass.Register ();

	WinMaker win (L"Chess Sandbox", className, hInst);
	win.Show (cmdShow);

	MSG  msg;
	int status;

	while ((status = ::GetMessage (& msg, 0, 0, 0)) != 0)
	{
		if (status == -1)
			return -1;
		::DispatchMessage (& msg);
	}

	return msg.wParam;
}

WinClass::WinClass(WNDPROC winProc, wchar_t const * className, HINSTANCE hInst) {
	//_class.cbSize = sizeof(WNDCLASSEX);
	//_class.style          = CS_HREDRAW | CS_VREDRAW;
	_class.style		  = 0;
	_class.lpfnWndProc    = winProc; // window procedure
	_class.cbClsExtra     = 0;
	_class.cbWndExtra     = 0;
	_class.hInstance      = hInst; // owner of class
	//_class.hIcon          = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));
	_class.hIcon		  = 0;
	_class.hCursor        = ::LoadCursor(0, IDC_ARROW);
	_class.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	_class.lpszMenuName   = 0;
	_class.lpszClassName  = className;
	//_class.hIconSm        = LoadIcon(_class.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
}

WinMaker::WinMaker (wchar_t const * caption, wchar_t const * className, HINSTANCE hInstance) {
	_hwnd = ::CreateWindow(
		className,            // name of a registered window class
		caption,              // window caption
		WS_OVERLAPPEDWINDOW,  // window style
		CW_USEDEFAULT,        // x position
		CW_USEDEFAULT,        // y position
		CW_USEDEFAULT,        // witdh
		CW_USEDEFAULT,        // height
		0,                    // handle to parent window
		0,                    // handle to menu
		hInstance,            // application instance
		0);                   // window creation data
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
		case WM_DESTROY:
			::PostQuitMessage (0);
			return 0;

	}
	return ::DefWindowProc (hwnd, message, wParam, lParam );
}






















/*

#include <stdlib.h>
#include <string.h>
#include <tchar.h>
// globals

// The main window class name
static TCHAR szWindowClass[] = _T("chess_sandbox");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Toujou is Love, Toujou is Live");

HINSTANCE hInst;

*/

/*

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)
	
{

		

	if (!RegisterClassEx(&_class))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; //store instance handle in the global var

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
		_T("Call to CreateWindow failed!"),
		_T("Win32 Guided Tour"),
		NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;

}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World!");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

*/