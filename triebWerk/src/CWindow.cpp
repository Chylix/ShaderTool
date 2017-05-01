#include <CWindow.h>
#include <Windows.h>
#include <iostream>

#include <Winuser.h>

triebWerk::CWindow::CWindow() : 
	m_Height(0),
	m_Width(0),
	m_IsFullscreen(false),
	m_ShowCursor(true),
	m_IsSizing(false)
{
}

triebWerk::CWindow::~CWindow()
{
	//If screen resolution is not user default, change it to user default before the engine started
	if (m_DefaultHeight != GetSystemMetrics(SM_CYSCREEN) || m_DefaultWidth != GetSystemMetrics(SM_CXSCREEN))
	{
		DEVMODE dmScreenSettings = { 0 };
		EnumDisplaySettings(NULL, 0, &dmScreenSettings);
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = static_cast<DWORD>(m_DefaultWidth);
		dmScreenSettings.dmPelsHeight = static_cast<DWORD>(m_DefaultHeight);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettingsEx(NULL, &dmScreenSettings, NULL, CDS_FULLSCREEN, NULL);
	}
}

bool triebWerk::CWindow::Initialize(const bool a_Fullscreen, const unsigned short a_ScreenWidth, const unsigned short a_ScreenHeight, const SWindowConfig& a_WindowConfig)
{
	if (a_WindowConfig.m_WindowStyle == 0)
	{
		WindowStyleWindowed = DefaultWindowStyleWindowed;
	}
	else
	{
		WindowStyleWindowed = a_WindowConfig.m_WindowStyle;
	}

	if (strlen(a_WindowConfig.m_WindowName) == 0)
	{
		CDebugLogfile::Instance().LogfText(CDebugLogfile::ELogType::Error, false, "Error: Empty window name not allowed!");
		return false;
	}

	//Get the default user screen resolution
	m_DefaultWidth = static_cast<unsigned short>(GetSystemMetrics(SM_CXSCREEN));
	m_DefaultHeight = static_cast<unsigned short>(GetSystemMetrics(SM_CYSCREEN));

	//Set initialize values
	m_Width = a_ScreenWidth;
	m_Height = a_ScreenHeight;
	m_IsFullscreen = a_Fullscreen;

	HMODULE hModule;

	hModule = GetModuleHandle(NULL);

	//window sytle
	WNDCLASSEX mainWindowDescription;
	ZeroMemory(&mainWindowDescription, sizeof(WNDCLASSEX));
	mainWindowDescription.cbSize = sizeof(WNDCLASSEX);
	mainWindowDescription.style = CS_HREDRAW | CS_VREDRAW;
	mainWindowDescription.lpfnWndProc = WindowProcedure;
	mainWindowDescription.hInstance = GetModuleHandle(NULL);
	mainWindowDescription.hCursor = LoadCursor(NULL, IDC_ARROW);
	mainWindowDescription.hbrBackground = (HBRUSH)COLOR_WINDOW;
	mainWindowDescription.lpszClassName = a_WindowConfig.m_WindowName;
	if(a_WindowConfig.m_IconID != 0)
	{
		mainWindowDescription.hIcon = LoadIcon(hModule, MAKEINTRESOURCE(a_WindowConfig.m_IconID));
		mainWindowDescription.hIconSm = mainWindowDescription.hIcon;
	}


	RegisterClassEx(&mainWindowDescription);

	//Adjust the window rect
	RECT windowRectangle = { 0, 0, static_cast<long>(a_ScreenWidth), static_cast<long>(a_ScreenHeight) };

	AdjustWindowRect(&windowRectangle, WindowStyleWindowed, FALSE);

	//Create window 
	m_WindowHandle = CreateWindowEx(NULL,
		a_WindowConfig.m_WindowName,
		a_WindowConfig.m_WindowName,
		WindowStyleWindowed,
		0,
		0,
		windowRectangle.right - windowRectangle.left,
		windowRectangle.bottom - windowRectangle.top,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		this);

	if (m_WindowHandle == NULL)
	{
		CDebugLogfile::Instance().LogfText(CDebugLogfile::ELogType::Error, false, "Error: Could not initialize a window instance");
		return false;
	}


	ShowWindow(m_WindowHandle, SW_SHOWDEFAULT);
	m_ShowCursor = true;

	//If fullscreen change normal "default" window above to fullscreen
	if (a_Fullscreen)
		ChangeWindowSettings(true, m_Width, m_Height);

	unsigned int a;
	unsigned int b;

	GetDPIFromDisplay(&a, &b);

	return true;
}

const MSG triebWerk::CWindow::GetWindowEvent()
{
	//Get the first message in queue and remove it from the queue
	MSG msg = m_MessageQueue.front();
	m_MessageQueue.pop();

	return msg;
}

size_t triebWerk::CWindow::GetWindowEventCount() const
{
    return m_MessageQueue.size();
}

LRESULT triebWerk::CWindow::WindowProcedure(HWND a_HWnd, UINT a_Message, WPARAM a_WParam, LPARAM a_LParam)
{
		CWindow *pThis = nullptr;

		//Handle messages with the class own function HandleMessage
		if (a_Message == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(a_LParam);
			pThis = reinterpret_cast<CWindow*>(pCreate->lpCreateParams);
			SetWindowLongPtr(a_HWnd, GWLP_USERDATA, (LONG_PTR)pThis);
	
			pThis->m_WindowHandle = a_HWnd;
		}
		else
		{
			pThis = reinterpret_cast<CWindow*>(GetWindowLongPtr(a_HWnd, GWLP_USERDATA));
		}
		if (pThis)
		{
			return pThis->HandleMessage(a_Message, a_WParam, a_LParam);
		}
		else
		{
			return DefWindowProc(a_HWnd, a_Message, a_WParam, a_LParam);
		}
}

LRESULT triebWerk::CWindow::HandleMessage(UINT a_Message, WPARAM wParam, LPARAM lParam)
{
	//Handle all windows messages
	switch (a_Message)
	{
	case WM_SIZE:
	{
		MSG msg = { 0 };
		msg.message = a_Message;
		msg.lParam = lParam;
		msg.wParam = wParam;
		m_MessageQueue.push(msg);

		if (wParam == SIZE_MAXIMIZED)
		{
			MSG msgMax = { 0 };
			msgMax.message = WM_EXITSIZEMOVE;
			msgMax.lParam = lParam;
			msgMax.wParam = wParam;
			m_MessageQueue.push(msg);
		}
	}break;
	
	case WM_SIZING:
	{
		m_IsSizing = true;
	}break;

	case WM_EXITSIZEMOVE:
	{
		if (m_IsSizing)
		{
			MSG msg = { 0 };
			msg.message = a_Message;
			msg.lParam = lParam;
			msg.wParam = wParam;
			m_MessageQueue.push(msg);

			m_IsSizing = false;
		}

	}break;
	
	case WM_DESTROY:
	{
		//Quit window
		PostQuitMessage(0);
		return 0;
	}break;

	default:
		return DefWindowProc(m_WindowHandle, a_Message, wParam, lParam);
	}

	return true;
}

HWND& triebWerk::CWindow::GetWindowHandle()
{
	return m_WindowHandle;
}

unsigned short triebWerk::CWindow::GetScreenWidth() const
{
	return m_Width;
}

unsigned short triebWerk::CWindow::GetScreenHeight() const
{
	return m_Height;
}

bool triebWerk::CWindow::IsWindowFullscreen()
{
	return m_IsFullscreen;
}

void triebWerk::CWindow::UpdateWindow()
{
    BOOL newMessage = FALSE;
    do
    {
        MSG msg = { 0 };
        newMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
        if (newMessage)
        {
            TranslateMessage(&msg);
            m_MessageQueue.push(msg);

            DispatchMessage(&msg);
        }
    }while (newMessage == TRUE);
}

void triebWerk::CWindow::GetDPIFromDisplay(unsigned int* a_OutDPIX, unsigned int* a_OutDPIY)
{
	//HRESULT hResult;

	//auto monitor = MonitorFromWindow(m_WindowHandle, MONITOR_DEFAULTTONEAREST);

	//hResult = GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, a_OutDPIX, a_OutDPIY);
	//if (FAILED(hResult))
	//{
	//	DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Could not read dpi from monitor!");
	//	*a_OutDPIX = 0;
	//	*a_OutDPIY = 0;
	//	return;
	//}

    *a_OutDPIX = 0;
    *a_OutDPIY = 0;
}

int triebWerk::CWindow::GetMaximalDisplayWidth()
{
	DEVMODE dmScreenSettings;
	EnumDisplaySettings(NULL, 0, &dmScreenSettings);
	return dmScreenSettings.dmPelsWidth;
}

int triebWerk::CWindow::GetMaximalDisplayHeight()
{
	DEVMODE dmScreenSettings;
	EnumDisplaySettings(NULL, 0, &dmScreenSettings);
	return dmScreenSettings.dmPelsHeight;
}

void triebWerk::CWindow::ChangeWindowSettings(const bool a_IsFullscreen, const unsigned short a_ScreenWidth, const unsigned short a_ScreenHeight)
{
	//Set new values
	m_IsFullscreen = a_IsFullscreen;
	m_Width = a_ScreenWidth;
	m_Height = a_ScreenHeight;

	//Set window rect
	RECT windowRectangle = { 0, 0, a_ScreenWidth ,a_ScreenHeight };

	DEVMODE dmScreenSettings;
	EnumDisplaySettings(NULL, 0, &dmScreenSettings);
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);

	//If Fullscreen set target resolution if not set "normal" resolution
	if (a_IsFullscreen)
	{
		dmScreenSettings.dmPelsWidth = a_ScreenWidth;
		dmScreenSettings.dmPelsHeight = a_ScreenHeight;
	}
	else
	{
		dmScreenSettings.dmPelsWidth = static_cast<DWORD>(m_DefaultWidth);
		dmScreenSettings.dmPelsHeight = static_cast<DWORD>(m_DefaultHeight);
	}
	dmScreenSettings.dmBitsPerPel = 32;
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	long error = ChangeDisplaySettingsEx(NULL, &dmScreenSettings, NULL, CDS_FULLSCREEN, NULL);
	if (error != DISP_CHANGE_SUCCESSFUL)
	{
		//Make error
	}

	//Set the style for fullscreen or window
	if(a_IsFullscreen)
		SetWindowLongPtr(m_WindowHandle, GWL_STYLE, WindowStyleFullscreen);
	else
		SetWindowLongPtr(m_WindowHandle, GWL_STYLE, WindowStyleWindowed);

	//If window calculate correct client space
	if (!a_IsFullscreen)
		AdjustWindowRect(&windowRectangle, WindowStyleWindowed, FALSE);

	//Resize the window and draw it new
	SetWindowPos(m_WindowHandle, NULL, 0, 0, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_SHOWWINDOW);

	//Sadly the ShowCursor parameter is a incrementing bool  
	//Disable Cursor if Fullscreen enable if window
	if (m_ShowCursor == true && a_IsFullscreen)
	{
		ShowCursor(false);
		m_ShowCursor = false;
	}
	else if(m_ShowCursor == false && !a_IsFullscreen)
	{
		ShowCursor(true);
		m_ShowCursor = true;
	}
}