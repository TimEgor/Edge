#pragma once

#include "WindowEvents.h"

namespace Edge
{
	class IWindow;

	struct WindowActivationEvent final : public InstancedWindowEventBase
	{
		bool m_isActive = false;

		WindowActivationEvent(const WindowHandleReference& window, bool isActive)
			: InstancedWindowEventBase(window), m_isActive(isActive) {}

		EDGE_EVENT_TYPE(EDGE_WINDOW_ACTIVATION_EVENT);
	};

	struct WindowClosingEvent final : public InstancedWindowEventBase
	{
		WindowClosingEvent(const WindowHandleReference& window)
			: InstancedWindowEventBase(window) {}

		EDGE_EVENT_TYPE(EDGE_WINDOW_ACTIVATION_EVENT);
	};

	class IWindowEventController
	{
	public:
		IWindowEventController() = default;
		virtual ~IWindowEventController() = default;

		virtual void updateWindowEvents(const IWindow& window) = 0;
		virtual void updateProcessWindowsEvents() = 0;
	};
}
