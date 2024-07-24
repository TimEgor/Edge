#pragma once

#include "EdgeEngine/Core/Multithreading/Mutex.h"

#include "EdgeEngine/Window/WindowHandle.h"
#include "EdgeEngine/Window/IWindowController.h"

#include <unordered_map>


namespace Edge
{
	class WindowEventController;

	class WindowController final : public IWindowController
	{
	private:
		using WindowContainer = std::unordered_map<WindowID, WindowHandle>;

		mutable SharedMutex m_mutex;

		WindowContainer m_windows;

		WindowID m_lastWindowID = InvalidWindowID;

		static void updateWindowEvents(const IWindow& window);

	public:
		WindowController() = default;
		~WindowController();

		virtual WindowHandleReference createWindow(const char* title, const WindowSize& size) override;
		virtual WindowHandleReference getWindow(WindowID windowID) const override;
		virtual void destroyWindow(WindowHandle* windowHandle) override;

		virtual void updateAllWindowsEvents() const override;
		virtual void updateWindowEvents(WindowHandleReference& window) const override;
	};
}
