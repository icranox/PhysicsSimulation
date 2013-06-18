
#include"main.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmdLine, int cmdShow) {
	MSG msg;
	bool done = false;
	hInstance = hInst;
	wnd = WindowClass(100, 100, scrX, scrY);
	wnd.RegisterWin(className, WndProc, hInstance);
	wnd.SetdwStyles(WS_OVERLAPPEDWINDOW, NULL, false);
	wnd.CreateWin(windowName, className, hWnd, hInstance);
	gl = glClass();
	gl.SetPFD();
	gl.glSetup(hWnd, hDC, glRC, scrX, scrY, 80.0, 0.1,100.0);
	gl.InitGL(false);
	
	ShowWindow(hWnd, SW_SHOW);


	while(!done) {
		if (PeekMessage(&msg, NULL, 0,0,PM_REMOVE))
		{
			switch (msg.message)
			{
			case WM_QUIT:
				done = true;
				break;
			default:
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				break;
			}
		}

		glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		SwapBuffers(hDC);
	}


	return 0;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);

}



