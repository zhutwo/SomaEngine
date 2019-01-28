
#include "AppLayer.h"

#define MEGABYTE 1048576
AppLayer *g_pApp = NULL;
static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("SomaEngine");

AppLayer::AppLayer()
{
	g_pApp = this;

	m_bIsRunning = false;
}

bool AppLayer::InitInstance(HINSTANCE hInstance, LPWSTR lpCmdLine, HWND hWnd, int screenWidth, int screenHeight)
{
	
	if (!Init::IsOnlyInstance(szTitle))
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

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MsgProc;
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

		return false;
	}

	m_hInstance = hInstance;

	if (hWnd == NULL)
	{
		m_hWnd = CreateWindow(
			szWindowClass,
			szTitle,
			WS_OVERLAPPEDWINDOW,
			0, 0,
			screenWidth, screenHeight,
			NULL,
			NULL,
			hInstance,
			NULL
		);

		DWORD Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
		m_sfView = CreateWindow(
			_T("STATIC"), 
			NULL, 
			Style, 
			0, 0,
			screenWidth, screenHeight, 
			m_hWnd, 
			NULL, 
			hInstance, 
			NULL);
	}
	
	if (m_hWnd == NULL)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("SomaEngine"),
			NULL);

		return 0;
	}

	m_sfWindow.create(m_sfView);

	m_bIsRunning = true;

	return TRUE;
}

void AppLayer::MainLoop()
{
	/*
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
	*/

	MSG Message;
	Message.message = ~WM_QUIT;
	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			// If a message was waiting in the message queue, process it
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			// SFML rendering code goes here
		}
	}
}

void AppLayer::ShutDown()
{
	// Destroy the main window
	DestroyWindow(m_hWnd);

	// Don't forget to unregister the window class
	UnregisterClass(szWindowClass, m_hInstance);
}

LRESULT CALLBACK AppLayer::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}