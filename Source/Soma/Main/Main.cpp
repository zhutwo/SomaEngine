/*
All work no play makes Jack a dull boy.
*/

#pragma once

//#include "Init.h"
//#include "AppLayer.h"
#include "SomaStd.h"
#include "../Input/InputInterface.h"
//#include <iostream>
//#include <io.h>
//#include <fcntl.h>

//AppLayer g_testApp;

// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("SomaEngine");

HINSTANCE hInst;

LRESULT APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	// enable console functionality
	/*
	AllocConsole();
	HANDLE stdHandle;
	int hConsole;
	FILE* fp;
	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
	fp = _fdopen(hConsole, "w");
	freopen_s(&fp, "CONOUT$", "w", stdout);
	*/

	// initialize game instance
	/*
	if (!g_testApp.InitInstance(hInstance, lpCmdLine, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return FALSE;
	}
	*/
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("SomaEngine"),
			NULL);

		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("SomaEngine"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

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

TempKeyHandler keyHandler;
TempMouseHandler mouseHandler;



LRESULT APIENTRY WndProc(_In_ HWND   hWnd, _In_ UINT   uMsg,	_In_ WPARAM wParam,	_In_ LPARAM lParam)
{
	//Point pt;
	PAINTSTRUCT ps;
	HDC hdc;

	std::wstring text;
	TCHAR mouseX[] = _T("Mouse X: ");
	TCHAR mouseY[] = _T("Mouse Y: ");

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		Point pt = Point(LOWORD(lParam), HIWORD(lParam));
		mouseHandler.VOnPointerButtonDown(pt, _T("Left Click"));
		InvalidateRect(hWnd, 0, TRUE);
	}
	break;
	case WM_MBUTTONDOWN:
	{
		Point pt = Point(LOWORD(lParam), HIWORD(lParam));
		mouseHandler.VOnPointerButtonDown(pt, _T("Middle Click"));
		InvalidateRect(hWnd, 0, TRUE);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		Point pt = Point(LOWORD(lParam), HIWORD(lParam));
		mouseHandler.VOnPointerButtonDown(pt, _T("Right Click"));
		InvalidateRect(hWnd, 0, TRUE);
	}
		break;
	case WM_MOUSEMOVE:
	{
		Point pt = Point(LOWORD(lParam), HIWORD(lParam));
		mouseHandler.VOnPointerMove(pt);
		InvalidateRect(hWnd, 0, TRUE);
	}
		break;
	case WM_CHAR:
		text = wParam;
		keyHandler.OnCharInput(text);
		InvalidateRect(hWnd, 0, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 10, 10, mouseX, _tcslen(mouseX));
		TextOut(hdc, 100, 10, mouseHandler.x, _tcslen(mouseHandler.x));
		TextOut(hdc, 10, 30, mouseY, _tcslen(mouseY));
		TextOut(hdc, 100, 30, mouseHandler.y, _tcslen(mouseHandler.y));
		TextOut(hdc, 10, 70, mouseHandler.button, _tcslen(mouseHandler.button));
		TextOut(hdc, 10, 90, keyHandler.key, _tcslen(keyHandler.key));

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}