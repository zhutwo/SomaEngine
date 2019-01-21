
#include "AppLayer.h"
#include "SomaStd.h"

#define MEGABYTE 1048576

//AppLayer *g_pApp = NULL;
static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("SomaEngine");

AppLayer::AppLayer()
{
	//g_pApp = this;

	m_bIsRunning = false;
}

HWND AppLayer::GetHwnd()
{
	return m_hWnd;
}

bool AppLayer::InitInstance(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, HWND hWnd, int screenWidth, int screenHeight)
{
	
	if (!Init::IsOnlyInstance(GetGameTitle()))
	{
		return false;
	}

	bool resourceCheck = false;
	while (!resourceCheck)
	{
		const DWORDLONG physicalRAM = 512 * MEGABYTE;
		const DWORDLONG virtualRAM = 1024 * MEGABYTE;
		const DWORDLONG diskSpace = 300 * MEGABYTE;
		const DWORD minCPU = 1024;

		if (!Init::CheckStorage(diskSpace))
		{
			return false;
		}
		if (!Init::CheckMemory(physicalRAM, virtualRAM))
		{
			return false;
		}
		if (!Init::CheckCPUSpeed(minCPU))
		{
			return false;
		}

		resourceCheck = true;
	}

	m_hInstance = hInstance;

	// The parameters to CreateWindow explained:  
	// szWindowClass: the name of the application  
	// szTitle: the text that appears in the title bar  
	// WS_OVERLAPPEDWINDOW: the type of window to create  
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
	// 500, 100: initial size (width, length)  
	// NULL: the parent of this window  
	// NULL: this application does not have a menu bar  
	// hInstance: the first parameter from WinMain  
	// NULL: not used in this application  

	if (hWnd == NULL)
	{
		m_hWnd = CreateWindow(
			_T("win32app"),
			_T("SomaEngine"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			NULL,
			NULL,
			hInstance,
			NULL
		);
	}

	if (!m_hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("SomaEngine"),
			NULL);

		return 0;
	}

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(m_hWnd,
		nCmdShow);
	UpdateWindow(m_hWnd);

	/*
	DXUTInit(false, false, lpCmdLine, false);

	if (hWnd == NULL)
	{
		DXUTCreateWindow(GetGameTitle(), hInstance);
	}
	else
	{
		DXUTSetWindow(hWnd, hWnd, hWnd);
	}
	if (!GetHwnd())
	{
		return FALSE;
	}
	SetWindowText(GetHwnd(), GetGameTitle());
	*/

	m_bIsRunning = true;

	return TRUE;
}

LRESULT CALLBACK AppLayer::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}