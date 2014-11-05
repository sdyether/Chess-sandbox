#if !defined VIEW_H
#define VIEW_H

#include <windows.h>

class Canvas;
class Model;

class View {
public:
	void SetSize(int pX, int pY) {
		x = pX;
		y = pY;
	}

	void Paint(Canvas & canvas, Model & model);

protected:
	int x;
	int y;
};

#endif