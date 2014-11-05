#include "Model.h"
#include "Canvas.h"
#include "MainWindow.h"
#include "Resource.h"
#include "WinMaker.h"
#include "Controller.h"
#include <exception>

LRESULT CALLBACK WndProc (HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam) {

	//get the right window controller
	Controller * pController = WinGetLong<Controller *>(windowHandle); 
	
	//redirect windows signals to our methods
	switch(msg) {
	case WM_CREATE:
		try {
			pController = new Controller (windowHandle, reinterpret_cast<CREATESTRUCT *> (lParam));
			WinSetLong<Controller *>(windowHandle, pController);
		}
		//new controller could fail
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
	case WM_SIZE:
		pController->Resize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_PAINT:
		pController->Paint();
		return 0;
	case WM_COMMAND:
		pController->Command(LOWORD(wParam));
		return 0;
	case WM_DESTROY:
		WinSetLong<Controller *>(windowHandle, 0);
		delete pController;
		return 0;
	}

	return DefWindowProc(windowHandle, msg, wParam, lParam);
}

Controller::Controller(HWND pWindowHandle, CREATESTRUCT * pCreate) {
	windowHandle = pWindowHandle;
	model("Generic");
}

Controller::~Controller() {
	PostQuitMessage(0); //controller in charge of posting quit message
}

void Controller::Resize(int x, int y) {
	view.SetSize(x, y);
}

void Controller::Paint() {
	//prepare the canvas and let the view do the rest
	PaintCanvas canvas(windowHandle);
	view.Paint(canvas, model);
}

//this is for windows menu command processing - eg File/About/Help etc
void Controller::Command(int cmd) {
	//we have IDM_EXIT, IDM_HELP and IDM_ABOUT as possible windows signals
	switch(cmd) {
	case IDM_EXIT:
		SendMessage(windowHandle, WM_CLOSE, 0, 0L);
		break;
	case IDM_HELP:
		MessageBox(windowHandle, L"TODO!", L"Generic", MB_ICONINFORMATION | MB_OK);
		break;
	case IDM_ABOUT:
		HINSTANCE hInst = WinGetLong<HINSTANCE>(windowHandle, GWL_HINSTANCE);
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), windowHandle, AboutDlgProc);
		break;
	}
}

BOOL CALLBACK AboutDlgProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD (wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog (windowHandle, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}