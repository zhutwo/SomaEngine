
#include "Init.h"

bool Init::IsOnlyInstance(LPCTSTR gameTitle)
{
	// Find the window. If active, set and return false
	// Only one game instance may have this mutex at a time...
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);

	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(gameTitle, NULL);
		if (hWnd)
		{
			// An instance of your game is already running.
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			return false;
		}
	}
	return true;
}

bool Init::CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	// Check for enough free disk space on the current disk.
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const neededClusters =	diskSpaceNeeded / (diskfree.sectors_per_cluster * diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < neededClusters)
	{
		//DEBUG_ERROR(“CheckStorage Failure : Not enough physical storage.”);
		return false;
	}
	return true;
}

bool Init::CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	if (status.ullTotalPhys < physicalRAMNeeded)
	{
		//DEBUG_ERROR(“CheckMemory Failure : Not enough physical memory.”);
		return false;
	}
	// Check for enough free memory.
	if (status.ullAvailVirtual < virtualRAMNeeded)
	{
		//DEBUG_ERROR(“CheckMemory Failure : Not enough virtual memory.”);
		return false;
	}
	char *buff = DEBUG_NEW char[virtualRAMNeeded];
	if (buff)
	{
		delete[] buff;
	}
	else
	{
		// even though there is enough memory, it isn’t available in one block.
		//DEBUG_ERROR(“CheckMemory Failure : Not enough contiguous memory.”);
		return false;
	}
	return true;
}

DWORD Init::ReadCPUSpeed()
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;
	// open the key where the proc speed is hidden:
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS)
	{
		// query the key:
		RegQueryValueEx(hKey, L"~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
	}
	return dwMHz;
}

// For Lab 2 only
std::wstring Init::GetCPUType()
{
	DWORD dataSize{};
	LONG retCode = RegGetValue(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", L"ProcessorNameString", RRF_RT_REG_SZ, nullptr, nullptr, &dataSize);
	std::wstring data;
	data.resize(dataSize / sizeof(wchar_t));
	retCode = RegGetValue(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", L"ProcessorNameString", RRF_RT_REG_SZ, nullptr, &data[0], &dataSize);
	DWORD stringLengthInWchars = dataSize / sizeof(wchar_t);
	stringLengthInWchars--;
	data.resize(stringLengthInWchars);
	return data;
}

DWORDLONG Init::GetStorage()
{
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	return diskfree.avail_clusters * diskfree.sectors_per_cluster * diskfree.bytes_per_sector;
}

DWORDLONG Init::GetPhysicalMemory()
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys;
}

DWORDLONG Init::GetVirtualMemory()
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	return status.ullAvailVirtual;
}