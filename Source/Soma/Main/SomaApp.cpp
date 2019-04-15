
#include "SomaApp.h"
#include <future>

#define MEGABYTE 1048576
SomaApp *g_pApp = NULL;
static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("SomaEngine");

SomaApp::SomaApp()
{
	g_pApp = this;
	m_bIsRunning = false;
}

bool SomaApp::InitInstance(HINSTANCE hInstance, LPWSTR lpCmdLine, HWND hWnd, int screenWidth, int screenHeight)
{
	if (!Init::IsOnlyInstance(szTitle))
	{
		return false;
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
	}
	
	if (m_hWnd == NULL)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("SomaEngine"),
			NULL);

		return 0;
	}

	m_renderWindow = new sf::RenderWindow(m_hWnd);

	auto checkFuture = std::async(std::launch::async,&SomaApp::CheckResources,this);
	//ShowSplash();
	
	bool passed = checkFuture.get();
	if (!passed)
	{
		return false;
	}
	m_bIsRunning = true;

	return TRUE;
}

bool SomaApp::CheckResources()
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
		return true;
}

void SomaApp::ShowSplash()
{
	sf::Texture splashImage;
	if (!splashImage.loadFromFile("BNS.png"))
	{
		MessageBox(NULL,
			_T("Failed to load splash screen"),
			_T("SomaEngine"),
			NULL);
	}
	sf::Sprite splashSprite(splashImage);

	float opacity = 0.0f;
	float time = 0.0f;
	float fadeInTime = 2.0f;
	float fadeOutAtTime = 3.0f;
	float fadeOutTime = 1.0f;
	float waitTime = 5.0f;
	m_clock.restart();

	while (true)
	{
		time = m_clock.getElapsedTime().asSeconds();
		if (time < fadeInTime)
		{
			opacity = time / fadeInTime;
		}
		else if (time >= fadeOutAtTime)
		{
			opacity = 1.0f - ((time - fadeOutAtTime)/ fadeOutTime);
		}
		else
		{
			opacity = 1.0f;
		}
		if (opacity > 1.0f)
		{
			opacity = 1.0f;
		}
		else if (opacity < 0.0f)
		{
			opacity = 0.0f;
		}
		opacity *= opacity;
		sf::Color color = splashSprite.getColor();
		color.a = opacity * 255.0f;
		splashSprite.setColor(color);
		m_renderWindow->clear();
		m_renderWindow->draw(splashSprite);
		m_renderWindow->display();
		if (time > waitTime)
		{
			break;
		}
	}
}

void SomaApp::MainLoop()
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
	TestGame test;
	test.BuildSceneJSON();
	//test.testScene.Start();

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	m_fixedFrameTime = sf::seconds(1.0f / 60.0f);
	m_isLimitingFrameRate = true;
	m_clock.restart();

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
			sf::Time dt = m_clock.restart();
			if (m_isLimitingFrameRate)
			{
				timeSinceLastUpdate += dt;
				while (timeSinceLastUpdate > m_fixedFrameTime)
				{
					timeSinceLastUpdate -= m_fixedFrameTime;

					test.testScene.Update(m_fixedFrameTime);

					m_renderWindow->clear();
					test.testScene.Render(*m_renderWindow);
					m_renderWindow->display();
				}
			}
			else
			{
				test.testScene.Update(dt);

				m_renderWindow->clear();
				test.testScene.Render(*m_renderWindow);
				m_renderWindow->display();
			}

		}
	}
}

void SomaApp::ShutDown()
{
	// Destroy the main window
	DestroyWindow(m_hWnd);

	// Don't forget to unregister the window class
	UnregisterClass(szWindowClass, m_hInstance);
}

LRESULT CALLBACK SomaApp::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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