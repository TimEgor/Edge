#pragma once

#include "IWindow.h"
#include "WindowHandle.h"

namespace Edge
{
	class WindowEventController;

	class IWindowController
	{
	public:
		IWindowController() = default;
		virtual ~IWindowController() = default;

		virtual WindowHandleReference createWindow(const char* title, const WindowSize& size) = 0;
		virtual WindowHandleReference getWindow(WindowID windowID) const = 0;
		virtual void destroyWindow(WindowHandle* windowHandle) = 0;

		virtual void updateAllWindowsEvents() const = 0;
		virtual void updateWindowEvents(WindowHandleReference& window) const = 0;
	};
}
