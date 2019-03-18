/*
Soma Application Layer
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Init.h"
#include "SomaStd.h"
#include "../TestGame/TestGame.cpp"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

class SomaApp
{
protected:
	sf::RenderWindow*				m_renderWindow;
	HWND							m_hWnd;
	HINSTANCE						m_hInstance;
	bool							m_bIsRunning;
	sf::Clock						m_clock;
	sf::Time						m_fixedFrameTime;
	bool							m_isLimitingFrameRate;
	
	// remove after engine complete
	//LPCTSTR m_cGameTitle = L"SomaEngine";

public:

	SomaApp();

	// change to virtual after engine complete
	//LPCTSTR GetGameTitle() { return m_cGameTitle; }
	sf::RenderWindow* GetSfWindow() { return m_renderWindow; }
	HWND GetHwnd() { return m_hWnd; }
	HINSTANCE GetInstance() { return m_hInstance; }
	bool IsRunning() { return m_bIsRunning; }

	bool InitInstance(HINSTANCE hInstance, LPWSTR lpCmdLine, HWND hWnd = NULL, int screenWidth = SCREEN_WIDTH, int screenHeight = SCREEN_HEIGHT);
	bool CheckResources();
	void MainLoop();
	void ShutDown();
	void ShowSplash();

	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

extern SomaApp *g_pApp;