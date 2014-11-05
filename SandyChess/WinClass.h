#if !defined WINCLASS_H
#define WINCLASS_H

#include <windows.h>
#include <string>

class ResString
{
	enum { MAX_RESSTRING = 255 };
public:
	ResString (HINSTANCE hInst, int resId);
	operator wchar_t const * () { return _buf; } //overload for easy string grabbing
private:
	wchar_t _buf [MAX_RESSTRING + 1];
};

class SimpleWinClass {
public:
	SimpleWinClass(wchar_t const  * pName, HINSTANCE hInst);
	SimpleWinClass(int resId, HINSTANCE hInst);

	wchar_t const * GetName() const { 
		return name;
	}

	HINSTANCE GetInstance () const {
		return hInstance;
	}

	HWND GetRunningWindow();

protected:
	HINSTANCE hInstance;
	wchar_t const  * name;
};

//program creates windows of this class
class WinClass: public SimpleWinClass {

public:

	WinClass(wchar_t const * className, HINSTANCE hInst, WNDPROC winProc);
	WinClass(int resId, HINSTANCE hInst, WNDPROC winProc);

	void SetBackgroundColour(int colour) {
		windowStyle.hbrBackground = reinterpret_cast<HBRUSH>(colour + 1);
	}

	void SetResIcons(int resId);

	void Register ();


protected:
	void SetDefaults();
	WNDCLASSEX windowStyle;

};

//the primary window
class TopWindowClass : public WinClass {
public:
	TopWindowClass(int resId, HINSTANCE hInst, WNDPROC winProc);
};

#endif