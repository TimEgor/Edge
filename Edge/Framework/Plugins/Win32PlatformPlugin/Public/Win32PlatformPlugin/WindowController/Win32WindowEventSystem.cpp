#include "Win32WindowEventSystem.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/WindowController/WindowController.h"

#include "Win32Window.h"

LRESULT EdgeWin32::Win32WindowEventController::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	const Edge::WindowID tsWindowID = GetWindowLong(hwnd, 0);

	if (tsWindowID != Edge::InvalidWindowID)
	{
		Edge::WindowHandleReference window = Edge::FrameworkCore::getInstance().getApplication().getWindowController().getWindow(tsWindowID);
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
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void EdgeWin32::Win32WindowEventController::updateWindowEventsInternal(HWND hWnd)
{
	MSG msg{ 0 };
	while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			Edge::FrameworkCore::getInstance().getApplication().stop();
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void EdgeWin32::Win32WindowEventController::updateWindowEvents(const Edge::Window& window)
{
	const Win32Window& win32Window = reinterpret_cast<const Win32Window&>(window);
	updateWindowEventsInternal(win32Window.getHWnd());
}

void EdgeWin32::Win32WindowEventController::updateProcessWindowsEvents()
{
	updateWindowEventsInternal(nullptr);
}
