#include "MainWindow.h"
#include "WinClass.h"
#include "WinMaker.h"
#include "resource.h"

#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <exception>


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, char * cmdParam, int cmdShow) {
	try {

		wchar_t className [] = L"Chess Sandbox";

		//create top window class
		TopWindowClass topWinClass(ID_MAIN, hInst, MainWndProc);

		//only allow a single instance of the program
		HWND otherInstance = topWinClass.GetRunningWindow();
		if (otherInstance != 0) {
			return 0;
		}

		topWinClass.Register();

		//create top window
		TopWinMaker topWin(topWinClass, className);
		topWin.Create();
		topWin.Show(cmdShow);

		/*
		//create and register the class
		WinClass winClass (WindowProcedure, className, hInst);
		winClass.Register ();

		//create and show the window
		WinMaker win (L"Chess Sandbox", className, hInst);
		win.Show (cmdShow);
		*/
		
		//main message loop
		MSG  msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);

			//send back to Windows
			DispatchMessage(&msg);
		}

		return (int) msg.wParam;

	}
	catch (std::exception& e) {
		wchar_t buf [100];
		wsprintf (buf, L"Exception Caught: %s", e.what());
		::MessageBox (0, buf, L"Exception", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}
	catch (...) {
		::MessageBox (0, L"Unknown", L"Exception", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	return 0;
}


//special method for callbacks
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	wchar_t greeting[] = L"Hello, World!";

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}

	return 0;
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