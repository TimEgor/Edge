#pragma once

#include "EdgeCommon/PlatformMacros.h"
#include "EdgeFramework/WindowController/WindowEventController.h"

namespace Edge {
	class Window;
}

namespace EdgeWin32
{
	class Win32WindowEventController final : public Edge::WindowEventController
	{
	private:
		static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void updateWindowEventsInternal(HWND hWnd);

	public:
		Win32WindowEventController() = default;

		virtual void updateWindowEvents(const Edge::Window& window) override;
		virtual void updateProcessWindowsEvents() override;

		static WNDPROC getWndProcPtr() { return wndProc; }
	};
}
