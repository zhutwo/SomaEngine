
#include "AppLayer.h"
#include "SomaStd.h"

#define MEGABYTE 1048576

AppLayer *g_pApp = NULL;
static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("SomaEngine");

AppLayer::AppLayer()
{
	g_pApp = this;

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

	ShowWindow(m_hWnd,
		nCmdShow);
	UpdateWindow(m_hWnd);

	m_bIsRunning = true;

	return TRUE;
}

LRESULT CALLBACK AppLayer::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}