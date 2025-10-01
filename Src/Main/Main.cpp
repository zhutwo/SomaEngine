/*
All work no play makes Jack a dull boy.
*/

#pragma once

#include "SomaApp.h"

SomaApp g_testApp;

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) 
{
	if (!g_pApp->InitInstance(hInstance, lpCmdLine, NULL, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return FALSE;
	}

	g_pApp->MainLoop();
	g_pApp->ShutDown();

	return 0;
}