#include "Win32Platform.h"

#include "EdgeEngine/Core/UtilsMacros.h"

#include "WindowController/Win32Window.h"
#include "WindowController/Win32WindowEventSystem.h"

#include <cassert>

bool Edge_WIN32::Win32Platform::initWindowClass()
{
	WNDCLASS wndClass{};
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = sizeof(Edge::WindowID);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	wndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wndClass.hInstance = m_hInstance;
	wndClass.lpfnWndProc = Win32WindowEventController::getWndProcPtr();
	wndClass.lpszClassName = EDGE_WIN32_WND_CLASS_NAME;
	wndClass.lpszMenuName = 0;
	wndClass.style = 0;

	if (!RegisterClass(&wndClass))
	{
		assert(false && "Win32WindowSystem::registerClass() : WNDCLASS registration failed.");
		return false;
	}

	return true;
}

void Edge_WIN32::Win32Platform::collectMonitorInfo()
{
	EnumDisplayMonitors(nullptr, nullptr, [](HMONITOR hMonitor, HDC hdc, LPRECT rect, LPARAM param)
		{
			MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
			if (GetMonitorInfo(hMonitor, &monitorInfo))
			{
				Edge::MonitorInfo& info = reinterpret_cast<MonitorInfoCollection*>(param)->emplace_back();

				info.m_resolution.m_x = static_cast<uint16_t>(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left);
				info.m_resolution.m_y = static_cast<uint16_t>(monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);

				info.m_basePos.m_x = static_cast<uint16_t>(monitorInfo.rcMonitor.left);
				info.m_basePos.m_y = static_cast<uint16_t>(monitorInfo.rcMonitor.top);
			}

			return TRUE;
		}, reinterpret_cast<LPARAM>(&m_monitorInfos));
}

bool Edge_WIN32::Win32Platform::init()
{
	EDGE_CHECK_INITIALIZATION(initWindowClass());

	collectMonitorInfo();

	//EDGE_CHECK_INITIALIZATION(m_directInputDeviceController.init());

	return true;
}

void Edge_WIN32::Win32Platform::release()
{
	//m_directInputDeviceController.release();
}

Edge::IWindow* Edge_WIN32::Win32Platform::createWindow(Edge::WindowID windowID) const
{
	return new Win32Window(windowID);
}

const Edge::IWindowEventController& Edge_WIN32::Win32Platform::getWindowEventController() const
{
	return m_windowEventController;
}

Edge::IWindowEventController& Edge_WIN32::Win32Platform::getWindowEventController()
{
	return m_windowEventController;
}
