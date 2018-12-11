/*
Soma Application Layer
*/

#pragma once

#include "Init.h"
#include "dxut.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

class AppLayer
{
protected:
	HINSTANCE m_hInstance;
	bool m_bIsRunning;

	// remove after engine complete
	LPCTSTR m_cGameTitle = L"SomaEngine";

public:

	AppLayer();

	// change to virtual after engine complete
	LPCTSTR GetGameTitle() { return m_cGameTitle; }

	//HWND GetHwnd();
	HINSTANCE GetInstance() { return m_hInstance; }
	bool InitInstance(HINSTANCE hInstance, LPWSTR lpCmdLine, HWND hWnd = NULL, int screenWidth = SCREEN_WIDTH, int screenHeight = SCREEN_HEIGHT);

	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool IsRunning() { return m_bIsRunning; }
};