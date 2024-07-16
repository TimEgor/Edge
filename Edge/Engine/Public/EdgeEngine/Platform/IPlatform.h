#pragma once

#include "EdgeEngine/Core/HashedType.h"
#include "EdgeEngine/Windows/Window.h"

#include "MonitorInfo.h"

#include <cstdint>

namespace Edge
{
	class WindowEventController;

	using PlatformType = HashedType::Type;

	class IPlatform : public HashedType
	{
	public:
		IPlatform() = default;
		virtual ~IPlatform() = default;

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

#define TS_PLATFORM_TYPE(PLATFORM_TYPE) TS_HASH_TYPE(#PLATFORM_TYPE, TS::PlatformType, Platform)