#pragma once

#include<Windows.h>


#include"Utility\glew.h"
#include"Utility\auxiliary.h"
#include"Math\myMath.h"
#include<gl\gl.h>
#pragma comment(lib, "Source\\Utility\\glew32.lib")
#pragma comment(lib, "opengl32.lib")

long scrX = 1024;
long scrY = 768;

HWND hWnd;
HINSTANCE hInstance;
HDC hDC;
HGLRC glRC;

WindowClass wnd;
glClass gl;

Mouse m;
Keyboard kb;

char *windowName = "Physics Simulation";
char *className = "PhysWndClass"; 

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmdLine, int cmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

