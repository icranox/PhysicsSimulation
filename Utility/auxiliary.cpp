#include"auxiliary.h"

/*
Font print
*/
void Font::SetScrSize(GLdouble x, GLdouble y)
{
	scrX = x;
	scrY = y;
	scrSizeSet = true;
}

void Font::Begin()
{
	if ((scrSizeSet) && (!beginSet))
	{
		glLoadIdentity();
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, scrX, 0.0, scrY, 0.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		beginSet = true;
	}
}

void Font::End()
{
	if (beginSet)
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		beginSet = false;
	}
}


void Font::glPrint(const char *fmt, ...)		// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
		vsprintf_s(text, fmt, ap);
														// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(font - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}

void Font::BuildFont(HDC hDC)								// Build Our Bitmap Font
{
	HFONT	hFont;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	font = glGenLists(96);								// Storage For 96 Characters

	hFont = CreateFont(	height,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						weight,						// Font Weight
						italic,							// Italic
						underlined,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						fontname);					// Font Name

	oldfont = (HFONT)SelectObject(hDC, hFont);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, font);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(hFont);									// Delete The Font

}



void Font::KillFont()									// Delete The Font List
{
	glDeleteLists(font, 96);							// Delete All 96 Characters
}


Font::Font(int Height, DWORD Weight, DWORD Italic, DWORD Underlined, char *Fontname)
{
	height = Height;
	weight = Weight;
	italic = Italic;
	underlined = Underlined;
	fontname = Fontname;
	scrSizeSet = false;
	beginSet = false;
}
Font::Font()
{
	height = -20;
	weight = 700;
	italic = FALSE;
	underlined = FALSE;
	fontname = "Arial";
	scrSizeSet = false;
	beginSet = false;
}
void Font::SetFontname(char *Fontname)
{
	fontname = Fontname;
}

Font::~Font()
{
	KillFont();
}



/*
input mouse
*/


Mouse::Mouse()
{
	deltaPosX = deltaPosY = posX = posY = wheel = 0;
	left = right = middle = false;
}

//if check returns 'true' then a WM was handled, else it returns 'false'
bool Mouse::Check(MSG msg, HWND hWnd)
{
	switch (msg.message)
	{
	case WM_MOUSEMOVE:
		posX = GET_X_LPARAM(msg.lParam); 
		posY = GET_Y_LPARAM(msg.lParam);
		DeltaPos();
		return true;
	case WM_MOUSEWHEEL:
		wheel = (GET_WHEEL_DELTA_WPARAM(msg.wParam));
		return true;
	case WM_LBUTTONDOWN:
		SetCapture(hWnd);
		left = true;
		return true;
	case WM_RBUTTONDOWN:
		SetCapture(hWnd);
		right = true;
		return true;
	case WM_MBUTTONDOWN:
		SetCapture(hWnd);
		middle = true;
		return true;
	case WM_LBUTTONUP:
		ReleaseCapture();
		left = false;
		return true;
	case WM_RBUTTONUP:
		ReleaseCapture();
		right = false;
		return true;
	case WM_MBUTTONUP:
		ReleaseCapture();
		middle = false;
		return true;
	case WM_CAPTURECHANGED:
		return true;
	default:
		return false;
	}
	return false;
}

void Mouse::DeltaPos()
{
	deltaPosX = posX-lastPosX;
	deltaPosY = posY-lastPosY;
	lastPosX = posX;
	lastPosY = posY;
}


/*
input keyboard
*/
//if check returns 'true' then a WM was handled, else it returns 'false'
int Keyboard::Check(MSG msg)
{
	switch (msg.message)
	{	
	case WM_KEYUP:
		key[msg.wParam] = false;
		return true;
	case WM_KEYDOWN:
		key[msg.wParam] = true;
		if (!keyPressed[msg.wParam])
			keyPressed[msg.wParam] = true;
		return true;
	default:
		return false;
	}
	return false;
};


/*
Timer
*/
void Timer::CalcFPS()
{
	frames++;
	if(elapsedTime >= 1000)
	{
		FPS = (double)frames/(elapsedTime/1000.0);
		elapsedTime = 0;
		frames = 0;
	}
}

void Timer::CalcDeltaT()
{
	deltaTime = (double)delta/1000.0;
}

void Timer::Update(bool complete)
{
	//get current time since boot
	currentTime = timeGetTime();
	delta = currentTime - lastTime;
	elapsedTime += delta;
	lastTime = currentTime;
	if (complete)
	{
		CalcDeltaT();
		CalcFPS();
	}
}

/*
Window Class
*/
WindowClass::WindowClass()
{
	x = y = 0;
	height = width = 50;
	dwStyle = WS_OVERLAPPEDWINDOW;
	dwStyleEx = NULL;
	hasMenu = false;
}

WindowClass::WindowClass(long X, long Y, long Width, long Height)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
	dwStyle = WS_OVERLAPPEDWINDOW;
	dwStyleEx = NULL;
	hasMenu = false;
	SetCorrectionFactor();
	rect.bottom = height+scrCorrection.FactorY;
	rect.left = x;
	rect.right = width+scrCorrection.FactorX;
	rect.top = y;
	
}

void WindowClass::SetScreenSize(long X, long Y, long Width, long Height)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
	SetCorrectionFactor();
	rect.bottom = height+scrCorrection.FactorY;
	rect.left = x;
	rect.right = width+scrCorrection.FactorX;
	rect.top = y;
}


void WindowClass::SetdwStyles(DWORD _dwStyle, DWORD _dwStyleEx, BOOL menu)
{
	dwStyle = _dwStyle;
	dwStyleEx = _dwStyleEx;
	hasMenu = menu;
}

void WindowClass::SetCorrectionFactor()
{
	switch (dwStyle)
	{
	case WS_OVERLAPPEDWINDOW:
		scrCorrection.FactorX = scrCorrection.ws_overlappedWndX;
		scrCorrection.FactorY = scrCorrection.ws_overlappedWndY;
		break;
	case WS_OVERLAPPED:
		scrCorrection.FactorX = scrCorrection.ws_overlappedX;
		scrCorrection.FactorY = scrCorrection.ws_overlappedY;
		break;
	default:
		scrCorrection.FactorX = 0;
		scrCorrection.FactorY = 0;
		break;
	}
}

long WindowClass::GetX()
{
	return x;
}

long WindowClass::GetY()
{
	return y;
}

long WindowClass::GetWidth()
{
	return width;
}

long WindowClass::GetHeight()
{
	return height;
}



//don't forget to unregister your WindowClass and kill everything
WindowClass::~WindowClass()
{
}
/*
bool WindowClass::RegisterWin(char *className, WNDPROC WndProc, HINSTANCE &hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(GetModuleHandle(NULL),IDC_ICON);
	wc.hIconSm = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = className;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	if (!RegisterClassEx(&wc))
	{
		return false;
	}
	return true;
	
}
*/
bool WindowClass::RegisterWin(char *className, WNDPROC WndProc, HINSTANCE hInstance, char *menuName, LPSTR icon, LPSTR iconSm) {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), icon);
	wc.hIconSm = LoadIcon(GetModuleHandle(NULL), iconSm);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = className;
	wc.lpszMenuName = menuName;
	wc.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	if (!RegisterClassEx(&wc))
	{
		return false;
	}
	return true;
}

bool WindowClass::RegisterWin(char *menuName, char *className, HICON hIcon, HICON hIconSm, WNDPROC WndProc, HINSTANCE hInstance) {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = hIcon;
	wc.hIconSm = hIconSm;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = className;
	wc.lpszMenuName = menuName;
	wc.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	if (!RegisterClassEx(&wc))
	{
		return false;
	}
	return true;
}

bool WindowClass::CreateWin(char *windowName, char *className, HWND &hWnd, HINSTANCE hInstance, HWND hWndParent, HMENU hMenu) {
	AdjustWindowRectEx(&rect, dwStyle, false, dwStyleEx);
	if(hWnd = CreateWindowEx(dwStyleEx, className, windowName, dwStyle, rect.left, rect.top, rect.right, rect.bottom, hWndParent, hMenu, hInstance, 0))
	{
		return true;
	}
	return false;
}


//don't forget to unregister your WindowClass and kill everything
bool  WindowClass::UnregisterWin(char *className, HINSTANCE hInst) {
	if(UnregisterClass(className, hInst))
	{
		return true;
	}

	return false;
}

/*
glClass
*/
int glClass::SetPFD(BYTE cColorBits, BYTE cDepthBits, DWORD dwFlags, BYTE iLayerType, BYTE iPixelType, WORD nVersion) {	
	if (glSet)
	{
		return 0x01;
	}

	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	= nVersion;
	pfd.cColorBits	= cColorBits;
	pfd.cDepthBits	= cDepthBits;
	pfd.dwFlags		= dwFlags;
	pfd.iLayerType	= iLayerType;
	pfd.iPixelType	= iPixelType;

	pfdSet = true;
	return 0x00;
}

bool glClass::InitGL(bool texture) {
	if(texture)
	{
		glEnable(GL_TEXTURE_2D);
	}

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.5);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return true;
}

/*
//Execute after Pixelformat definition
int glClass::glSetup(HWND &hWnd, HDC &hDC, HGLRC &glRC) {
	if (!pfdSet)
	{
		return 0x01;
	}

	hDC=GetDC(hWnd);
	if (hDC == NULL)
	{
		return 0x02;
	}

	SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
	glRC=wglCreateContext(hDC);
	if (glRC == NULL)
	{
		return 0x03;
	}

	wglMakeCurrent(hDC, glRC);
	ShowWindow(hWnd, SW_SHOW);
	glSet = true;
	return 0x00;
}
*/
void glClass::glKill(HWND &hWnd, HDC &hDC, HGLRC &glRC) {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(glRC);
	glRC=NULL;
	DeleteDC(hDC);
	hDC=NULL;
	DestroyWindow(hWnd);
	hWnd=NULL;
}

glClass::glClass() {
	glSet = false;
	pfdSet = false;
}

//Execute after glSetup
void glClass::glResize(GLsizei width, GLsizei height, GLdouble fovy, GLdouble zNear, GLdouble zFar) {
	if (glSet)
	{
	glViewport(0,0,width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)width/height, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}
}

//Execute after SetPFD
int glClass::glSetup(HWND &hWnd, HDC &hDC, HGLRC &glRC, GLsizei width, GLsizei height, GLdouble fovy, GLdouble zNear, GLdouble zFar) {
	if (!pfdSet)
	{
		return 0x01;
	}

	hDC=GetDC(hWnd);
	if (hDC == NULL)
	{
		return 0x02;
	}

	SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
	glRC=wglCreateContext(hDC);
	if (glRC == NULL)
	{
		return 0x03;
	}

	wglMakeCurrent(hDC, glRC);
	ShowWindow(hWnd, SW_SHOW);
	glSet = true;

	glResize(width, height, fovy, zNear, zFar);

	return 0x00;
}


glClass::~glClass() {

}