/*
All work no play makes Jack a dull boy.
*/

#pragma once

#include "AppLayer.h"
#include "SomaStd.h"

AppLayer g_testApp;

LRESULT APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	if (!g_testApp.InitInstance(hInstance, lpCmdLine, nCmdShow)) // pass in sys reqs here
	{
		return 0;
	}

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;

	//DXUTMainLoop();
	//DXUTShutdown();

	return 0;
}