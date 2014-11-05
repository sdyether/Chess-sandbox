#include "WinMaker.h"

//winmaker constructor
WinMaker::WinMaker (WinClass &winClass)
	: windowHandle(0),
	exStyle(0),
	windowName(0),
	style(WS_OVERLAPPED),
	xPos(CW_USEDEFAULT),
	yPos(0),
	parentHandle(0),
	menuHandle(0),
	data(0) {
setWidth(900);
setHeight(900);
}

void WinMaker::Create() {
	windowHandle = CreateWindowEx(
		exStyle, _class.getName(), windowName, style, xPos, yPos, width, height, 
		parentHandle, menuHandle, _class.getInstance(), data);
	if (windowHandle == 0) {
		throw std::runtime_error("Window creation failed");
	}
}

void WinMaker::Show(int nCmdShow) {
	ShowWindow(windowHandle, nCmdShow);
	UpdateWindow(windowHandle);
}

TopWinMaker::TopWinMaker(WinClass &winClass, wchar_t const * caption) : WinMaker(winClass) {
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	windowName = caption;
}