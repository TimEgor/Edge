#include "Win32WindowEventSystem.h"

#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Engine/IEngine.h"
#include "EdgeEngine/Window/IWindowController.h"

#include "Win32Window.h"

LRESULT Edge_WIN32::Win32WindowEventController::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	const Edge::WindowHandleReference window = getWindowFromHWnd(hwnd);
	if (window && window->getWindow().isValid())
	{
		Win32Window& win32Window = window->getWindowCast<Win32Window>();

		switch (msg)
		{
		case WM_DESTROY:
		{
			win32Window.invalidate();
			PostQuitMessage(0);

			return 0;
		}

		case WM_ENTERSIZEMOVE:
		{
			win32Window.setSizeStable(false);
			break;
		}

		case WM_EXITSIZEMOVE:
		{
			win32Window.setSizeStable(true);
			break;
		}
		case WM_SIZE:
		{
			win32Window.updateSize();
			onWindowSizeChange(window);
			break;
		}
		case WM_ACTIVATE:
		{
			const bool activationState = LOWORD(wParam);
			onWindowActivate(window, activationState);
			break;
		}
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Edge_WIN32::Win32WindowEventController::updateWindowEventsInternal(HWND hWnd)
{
	MSG msg{ 0 };
	while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			const Edge::WindowHandleReference window = getWindowFromHWnd(hWnd);

			onWindowClose(window);
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

Edge::WindowHandleReference Edge_WIN32::Win32WindowEventController::getWindowFromHWnd(HWND hwnd)
{
	const Edge::WindowID windowID = GetWindowLong(hwnd, 0);

	if (windowID == Edge::InvalidWindowID)
	{
		return nullptr;
	}

	return Edge::EngineCore::getInstance().getEngine().getWindowController().getWindow(windowID);
}

void Edge_WIN32::Win32WindowEventController::updateWindowEvents(const Edge::IWindow& window)
{
	const Win32Window& win32Window = reinterpret_cast<const Win32Window&>(window);
	updateWindowEventsInternal(win32Window.getHWnd());
}

void Edge_WIN32::Win32WindowEventController::updateProcessWindowsEvents()
{
	updateWindowEventsInternal(nullptr);
}
