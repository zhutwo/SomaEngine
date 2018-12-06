/*
All work no play makes Jack a dull boy.
*/

#pragma once

#include "Init.h"
#include "AppLayer.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>

AppLayer g_testApp;

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	// enable console functionality
	AllocConsole();
	HANDLE stdHandle;
	int hConsole;
	FILE* fp;
	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
	fp = _fdopen(hConsole, "w");
	freopen_s(&fp, "CONOUT$", "w", stdout);

	// initialize game instance
	if (!g_testApp.InitInstance(hInstance, lpCmdLine, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return FALSE;
	}
	
	std::system("PAUSE");

	//DXUTMainLoop();
	//DXUTShutdown();

	return 0;
}