
#include "AppLayer.h"
#include <iostream>

#define MEGABYTE 1048576

//AppLayer *g_pApp = NULL;

AppLayer::AppLayer()
{
	//g_pApp = this;

	m_bIsRunning = false;
}
/*
HWND AppLayer::GetHwnd()
{
	return DXUTGetHWND();
}
*/
bool AppLayer::InitInstance(HINSTANCE hInstance, LPWSTR lpCmdLine, HWND hWnd, int screenWidth, int screenHeight)
{
	std::cout << "Checking for existing instance..." << std::endl;
	if (!Init::IsOnlyInstance(GetGameTitle()))
	{
		std::cout << "FAIL! Duplicate instance detected." << std::endl;
		return false;
	}
	std::cout << "PASS! No duplicate instance detected." << std::endl << std::endl;

	bool resourceCheck = false;
	while (!resourceCheck)
	{
		//const DWORDLONG physicalRAM = 512 * MEGABYTE;
		//const DWORDLONG virtualRAM = 1024 * MEGABYTE;
		const DWORDLONG diskSpace = 300 * MEGABYTE;

		std::cout << "Checking for sufficient disk space (" << diskSpace << " bytes)..." << std::endl;
		if (!Init::CheckStorage(diskSpace))
		{
			std::cout << "FAIL! Insufficient disk space (" << (unsigned int)Init::GetStorage() << " bytes available)." << std::endl;
			return false;
		}
		std::cout << "PASS! " << (unsigned int)Init::GetStorage() << " bytes available." << std::endl << std::endl;

		std::cout << "Checking available memory..." << std::endl;
		std::cout << "Virtual: " << (unsigned int)Init::GetVirtualMemory << " bytes available." << std::endl;
		std::cout << "RAM: " << (unsigned int)Init::GetPhysicalMemory << " bytes available." << std::endl << std::endl;

		std::cout << "Verifying CPU..." << std::endl;
		std::wcout << Init::GetCPUType() << std::endl;
		std::cout << (unsigned int)Init::ReadCPUSpeed() << "Mhz" << std::endl << std::endl;

		resourceCheck = true;
	}

	m_hInstance = hInstance;

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