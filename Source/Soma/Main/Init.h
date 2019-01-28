/*
Soma Initialization
*/

#pragma once

#include <crtdbg.h>
#include <direct.h>
#include <string>
#include "SomaStd.h"
#include "AppLayerStd.h"

class Init
{
public:
	// Check for only one instance of game running
	static bool IsOnlyInstance(LPCTSTR gameTitle);
	// Check for sufficient disk space
	static bool CheckStorage(const DWORDLONG diskSpaceNeeded);
	// Check for sufficient memory
	static bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	// Check CPU speed
	static bool CheckCPUSpeed(const DWORD minCPUSpeed);

	// Just for Lab 2
	static std::wstring GetCPUType();
	static DWORDLONG GetStorage();
	static DWORDLONG GetPhysicalMemory();
	static DWORDLONG GetVirtualMemory();
};