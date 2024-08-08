#pragma once

#include "WindowEvents.h"

namespace Edge
{
	class Window;

	struct WindowActivationEvent final : public WindowEventBase
	{
		bool m_isActive = false;

		WindowActivationEvent(WindowHandleReference& window, bool isActive)
			: WindowEventBase(window), m_isActive(isActive) {}

		EDGE_EVENT_TYPE(EDGE_WINDOW_ACTIVATION_EVENT);
	};

	class WindowEventController
	{
	protected:
		void initWindowContextEvent();
		void releaseWindowContextEvent();

		static void onWindowActivate(WindowHandleReference& window, bool isActive);
		static void onWindowSizeChange(WindowHandleReference& window);

	public:
		WindowEventController();
		virtual ~WindowEventController();

		virtual void updateWindowEvents(const Window& window) = 0;
		virtual void updateProcessWindowsEvents() = 0;
	};
}
