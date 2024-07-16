#pragma once

#include "TinySimCommon/Multithreading/Mutex.h"

#include "Window.h"
#include "WindowHandle.h"

#include <unordered_map>

namespace TS
{
	class WindowEventController;

	class WindowController final
	{
	private:
		using WindowContainer = std::unordered_map<WindowID, WindowHandle>;

		mutable SharedMutex m_mutex;

		WindowContainer m_windows;

		WindowID m_lastWindowID = InvalidWindowID;

		static void updateWindowEvents(const Window& window);

	public:
		WindowController() = default;
		~WindowController();

		WindowHandleReference createWindow(const char* title, const WindowSize& size);
		WindowHandleReference getWindow(WindowID windowID) const;
		void destroyWindow(WindowHandle* windowHandle);

		void updateAllWindowsEvents() const;
		void updateWindowEvents(WindowHandleReference& window) const;
	};
}
