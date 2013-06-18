#include<Windows.h>
#include<stdarg.h>
#include<stdio.h>
//needed for mouse inputs
#include<windowsx.h>

#include<gl\GL.h>
#include<gl\GLU.h>

#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")
//needed for timer
#pragma comment(lib,"Winmm.lib")

#define AUXAPI _declspec(dllexport)

/*
Font print

NOTE:

When using glPrint, variables are deklared as followed:
glprint(base, "TEXT %1.2FORMAT TEXT %3.3FORMAT", VAR1, VAR2);
FORMAT: d == INT
		s == STRING
		c == CHAR
		f == FLOAT
		u == UNSIGNED
		e == double
%NUMBER1.NUMBER2 (optional)
		NUMBER1 == number of digits before decimal point
		NUMBER2 == number of digits after decimal point (not needed when using integer numbers)
		


*/

class AUXAPI Font {
public:	
	/*
	Fontnames
	Courier New
	Arial
	Comic Sans MS
	Cambria
	Calibri
	Corbel
	Courier Standard
	Terminal Standard
	System Fett
	*/
	Font(int Height, DWORD Weight, DWORD Italic, DWORD Underlined, char *Fontname);
	/*
	Fontnames
	Courier New
	Arial
	Comic Sans MS
	Cambria
	Calibri
	Corbel
	Courier Standard
	Terminal Standard
	System Fett
	*/
	Font();
	/*
	Fontnames
	Courier New
	Arial
	Comic Sans MS
	Cambria
	Calibri
	Corbel
	Courier Standard
	Terminal Standard
	System Fett
	*/
	void SetFontname(char *Fontname);
	void glPrint(const char *fmt, ...);		// Custom GL "Print" Routine
	void SetScrSize(GLdouble x, GLdouble y);
	void Begin();
	void End();
	void BuildFont(HDC hDC);				// Build Our Bitmap Font
	void KillFont();						// Delete The Font List
	~Font();
	
private:
	GLdouble scrX;
	GLdouble scrY;
	bool scrSizeSet;
	bool beginSet;
	
	int height;
	DWORD weight;							//the "boldness" of the font
	DWORD italic;
	DWORD underlined;
	GLuint font;
	char *fontname;
};


/*
input mouse
*/
struct AUXAPI Mouse
{
	short posX;
	short posY;
	short lastPosX;
	short lastPosY;
	short deltaPosX;
	short deltaPosY;
	int wheel;
	bool left;
	bool right;
	bool middle;
	Mouse();
	//if check returns 'true' then a WM was handled, else it returns 'false'
	bool Check(MSG msg, HWND hWnd);
	void DeltaPos();
};

/*
input keyboard
*/
struct AUXAPI Keyboard
{
	bool key[256];
	bool keyPressed[256];

	//if check returns 'true' then a WM was handled, else it returns 'false'
	int Check(MSG msg);
};


/*
Timer
*/
struct AUXAPI Timer
{
	long double deltaTime;
	DWORD delta;
	DWORD currentTime;
	DWORD lastTime;
	DWORD elapsedTime;
	double FPS;
	int frames;
	void Update(bool complete);	//call before any other Timer function
	void CalcFPS();	
	void CalcDeltaT();
};

/*
Window Class
*/
class AUXAPI WindowClass {
public:
	WindowClass();
	WindowClass(long x, long y, long width, long height);

	void SetdwStyles(DWORD dwStyle, DWORD dwStyleEx, BOOL menu);
	void SetScreenSize(long x, long y, long width, long height);

	long GetX();
	long GetY();
	long GetWidth();
	long GetHeight();

	//bool RegisterWin(char *className, WNDPROC wndProc, HINSTANCE &hInstance);
	bool RegisterWin(char *className, WNDPROC wndProc, HINSTANCE hInstance, char *menuName = NULL, LPSTR icon = NULL, LPSTR iconSm = NULL);
	bool RegisterWin(char *menuName, char *className, HICON hIcon, HICON hIconSm, WNDPROC wndProc, HINSTANCE hInstance);
	bool UnregisterWin(char *className, HINSTANCE hInst);
	bool CreateWin(char *windowName, char *className, HWND &hWnd, HINSTANCE hInstance, HWND hWndParent = NULL, HMENU hMenu = NULL);
	//bool CreateWin(char *windowName, char *className, HWND &hWnd, HINSTANCE &hInstance);
	
	~WindowClass(); 
private:
	//screenCorrection, when the windowRect is adjusted, the "usable" window isn't as big as you have declared it, so I am correcting this
	void SetCorrectionFactor();
	struct ScreenCorrection	{
		const static long ws_overlappedWndX=9;
		const static long ws_overlappedWndY=31;
		const static long ws_overlappedX=11;
		const static long ws_overlappedY=33;
		long FactorX;
		long FactorY;
		
		//void chooseFactor(DWORD dwStyle);
	}scrCorrection;

	RECT rect;

	BOOL hasMenu; //does the window have a menu?
	
	long x;
	long y;
	long width;
	long height;
	DWORD dwStyle;
	DWORD dwStyleEx;
	char *menuName;
	char *className;

};


class AUXAPI glClass {
public:
	glClass();
	int SetPFD(BYTE cColorBits = 16, BYTE cDepthBits = 16, DWORD dwFlags = PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER|PFD_DRAW_TO_WINDOW, BYTE iLayerType = PFD_MAIN_PLANE, BYTE iPixelType = PFD_TYPE_RGBA, WORD nVersion = 1);
	//int glSetup(HWND &hWnd, HDC &hDC, HGLRC &glRC);
	int glSetup(HWND &hWnd, HDC &hDC, HGLRC &glRC, GLsizei width, GLsizei height, GLdouble fovy, GLdouble zNear, GLdouble zFar);
	void glResize(GLsizei width, GLsizei height, GLdouble fovy, GLdouble zNear, GLdouble zFar);
	bool InitGL(bool texture);

	void glKill(HWND &hWnd, HDC &hDC, HGLRC &glRC);
	~glClass();

private:
	bool pfdSet;
	bool glSet;
	PIXELFORMATDESCRIPTOR pfd;

};