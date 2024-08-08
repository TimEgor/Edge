#pragma once

#include "EdgeCommon/HashedType.h"
#include "EdgeFramework/WindowController/Window.h"

#include "MonitorInfo.h"

#include <cstdint>

namespace Edge
{
	class WindowEventController;

	using PlatformType = HashedType::Type;

	class Platform : public HashedType
	{
	public:
		Platform() = default;
		virtual ~Platform() = default;

		virtual bool init() = 0;
		virtual void release() = 0;

		virtual void* getNativeHandle() const = 0;

		virtual Window* createWindow(WindowID windowID) const = 0;
		virtual const WindowEventController& getWindowEventController() const = 0;
		virtual WindowEventController& getWindowEventController() = 0;

		virtual uint32_t getMonitorCount() const = 0;
		virtual const MonitorInfo& getMonitorInfo(uint32_t index) const = 0;

		virtual PlatformType getType() const = 0;
	};
}

#define EDGE_PLATFORM_TYPE(PLATFORM_TYPE) EDGE_HASH_TYPE(#PLATFORM_TYPE, Edge::PlatformType, Platform)