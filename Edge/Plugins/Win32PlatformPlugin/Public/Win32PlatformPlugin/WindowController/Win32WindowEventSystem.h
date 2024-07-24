#pragma once

#include "EdgeEngine/Core/PlatformMacros.h"
#include "EdgeEngine/Window/WindowEventControllerBase.h"

namespace Edge {
	class IWindow;
}

namespace Edge_WIN32
{
	class Win32WindowEventController final : public Edge::WindowEventControllerBase
	{
	private:
		static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void updateWindowEventsInternal(HWND hWnd);

		static Edge::WindowHandleReference getWindowFromHWnd(HWND hwnd);

	public:
		Win32WindowEventController() = default;

		virtual void updateWindowEvents(const Edge::IWindow& window) override;
		virtual void updateProcessWindowsEvents() override;

		static WNDPROC getWndProcPtr() { return wndProc; }
	};
}
