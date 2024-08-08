#pragma once

#include "EdgeFramework/EventController/Event.h"

#include "WindowHandle.h"

namespace Edge
{
	struct WindowEventBase : public Event
	{
		WindowHandleReference m_window;

		WindowEventBase(WindowHandleReference& window) : m_window(window) {}
	};

	struct InstancedWindowEventBase : public InstancedEvent
	{
		WindowHandleReference m_window;

		InstancedWindowEventBase(WindowHandleReference& window) : m_window(window) {}
	};

	struct WindowSizeEvent final : public InstancedWindowEventBase
	{
		WindowSizeEvent(WindowHandleReference& window)
			: InstancedWindowEventBase(window) {}

		EDGE_INSTANCED_EVENT_TYPE(EDGE_WINDOW_SIZE_EVENT_TYPE);
	};
}
