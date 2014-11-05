#include "WinClass.h"

SimpleWinClass::SimpleWinClass(wchar_t const  * pName, HINSTANCE hInst) {
	name = pName;
	hInstance = hInst;
}

SimpleWinClass::SimpleWinClass(int resId, HINSTANCE hInst) {
	ResString resStr(hInst, resId);
	name = resStr;
	hInstance = hInst;
}

HWND SimpleWinClass::GetRunningWindow() {
	//returns the most recent window handle or
	//returns 0 when no other instance is running
	HWND hwnd = FindWindow(GetName(), 0);
	if (IsWindow(hwnd)) {
		HWND hwndPopup = GetLastActivePopup (hwnd);
		if (IsWindow (hwndPopup)) {
			hwnd = hwndPopup;
		}
	}
	else {
		hwnd = 0;
	}
	return hwnd;
}

//winclass constructor
WinClass::WinClass(wchar_t const * className, HINSTANCE hInst, WNDPROC winProc) 
	: SimpleWinClass(className, hInst) {
		windowStyle.lpfnWndProc = winProc;
		SetDefaults();

}

WinClass::WinClass(int resId, HINSTANCE hInst, WNDPROC winProc) 
	: SimpleWinClass(resId, hInst) {
		windowStyle.lpfnWndProc = winProc;
		SetDefaults();

}

void WinClass::SetDefaults() {
	windowStyle.style = 0;
	windowStyle.cbClsExtra = 0;
	windowStyle.cbWndExtra = 0;
	windowStyle.lpszClassName = GetName ();
	windowStyle.hInstance = GetInstance ();

	windowStyle.hIcon = 0;
	windowStyle.lpszMenuName = 0;

	windowStyle.hCursor = ::LoadCursor(0, IDC_ARROW);
	windowStyle.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

	//windowStyle.lpfnWndProc    = winProc; // window procedure
	//_class.cbSize = sizeof(WNDCLASSEX);
	//_class.style          = CS_HREDRAW | CS_VREDRAW;
	//_class.hIcon          = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));
	//_class.hIconSm        = LoadIcon(_class.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
}

void WinClass::SetResIcons(int resId) {
	//TODO
}

void WinClass::Register() {
	if (RegisterClassEx(&windowStyle) == 0) {
		throw std::runtime_error("Class registration failed");
	}
}

TopWindowClass::TopWindowClass(int resId, HINSTANCE hInst, WNDPROC winProc)
	: WinClass(resId, hInst, winProc) {
	
}

ResString::ResString (HINSTANCE hInst, int resId)
{
	if (!::LoadString (hInst, resId, _buf, MAX_RESSTRING + 1)) {
		throw std::runtime_error("Load String failed");
	}
}