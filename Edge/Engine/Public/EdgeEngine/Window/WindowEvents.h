#pragma once

#include "EdgeEngine/Event/Event.h"

#include "WindowHandle.h"

namespace Edge
{
	struct WindowEventBase : public Event
	{
		WindowHandleReference m_window;

		WindowEventBase(const WindowHandleReference& window) : m_window(window) {}
	};

	struct InstancedWindowEventBase : public InstancedEvent
	{
		WindowHandleReference m_window;

		InstancedWindowEventBase(const WindowHandleReference& window) : m_window(window) {}
	};

	struct WindowSizeEvent final : public InstancedWindowEventBase
	{
		WindowSizeEvent(const WindowHandleReference& window)
			: InstancedWindowEventBase(window) {}

		EDGE_INSTANCED_EVENT_TYPE(EDGE_WINDOW_SIZE_EVENT_TYPE);
	};
}
