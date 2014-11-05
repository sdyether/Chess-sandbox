#if !defined CANVAS_H
#define CANVAS_H

#include <windows.h>

class Canvas {

public:
	operator HDC() { return hdc; }

	void Line(int x1, int y1, int x2, int y2) {
		MoveToEx(hdc, x1, y2, 0);
		LineTo(hdc, x2, y2);
	}

	void Text(int x, int y, char const * buf, int cBuf) {
		TextOut(hdc, x, y, buf, cBuf);
	}

	void Char(int x, int y, char c) {
		TextOut(hdc, x, y, &c, 1);
	}

protected:
	Canvas(HDC pHdc) { hdc = pHdc; }

	HDC hdc;
};

//create this object after WM_PAINT message
class PaintCanvas: public Canvas {
public:
	//beginpaint gives the canvas the device context
	PaintCanvas(HWND pWindowHandle) : Canvas(BeginPaint(windowHandle, &paint)) { 
		windowHandle = pWindowHandle; }

	//endpaint releases the device context
	~PaintCanvas() {
		EndPaint(windowHandle, &paint);
	}

protected:
	PAINTSTRUCT paint;
	HWND windowHandle;
};

#endif