#if !defined CONTROLLER_H
#define CONTROLLER_H

#include "view.h"
#include "model.h"
#include <windows.h>

class Controller {
public:
	Controller(HWND windowHandle, CREATESTRUCT * pCreate);
	~Controller();
	void Resize(int x, int y);
	void Paint();
	void Command(int cmd);

private:
	HWND windowHandle;
	Model model;
	View view;
};

#endif