#pragma once

#include "WindowEvents.h"

namespace TS
{
	class Window;

	struct WindowActivationEvent final : public WindowEventBase
	{
		bool m_isActive = false;

		WindowActivationEvent(WindowHandleReference& window, bool isActive)
			: WindowEventBase(window), m_isActive(isActive) {}

		TS_EVENT_TYPE(TS_WINDOW_ACTIVATION_EVENT);
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
