/*
All work no play makes Jack a dull boy.
*/

#pragma once

#include "AppLayer.h"

AppLayer g_testApp;

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) 
{
	if (!g_testApp.InitInstance(hInstance, lpCmdLine, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return FALSE;
	}

	ShowWindow(g_testApp.GetHwnd(),
		nCmdShow);
	UpdateWindow(g_testApp.GetHwnd());

	g_testApp.MainLoop();
	g_testApp.ShutDown();

	return 0;
}