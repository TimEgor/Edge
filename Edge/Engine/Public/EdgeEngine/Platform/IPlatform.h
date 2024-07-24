#pragma once

#include "EdgeEngine/Core/HashedType.h"
#include "EdgeEngine/Window/IWindow.h"

#include "MonitorInfo.h"

#include <cstdint>

namespace Edge
{
	class IWindowEventController;

	using PlatformType = HashedType::Type;

	class IPlatform : public HashedType
	{
	public:
		IPlatform() = default;
		virtual ~IPlatform() = default;

		virtual bool init() = 0;
		virtual void release() = 0;

		virtual void* getNativeHandle() const = 0;

		virtual IWindow* createWindow(WindowID windowID) const = 0;
		virtual const IWindowEventController& getWindowEventController() const = 0;
		virtual IWindowEventController& getWindowEventController() = 0;

		virtual uint32_t getMonitorCount() const = 0;
		virtual const MonitorInfo& getMonitorInfo(uint32_t index) const = 0;

		virtual PlatformType getType() const = 0;
	};
}

#define EDGE_PLATFORM_TYPE(PLATFORM_TYPE) EDGE_HASH_TYPE(#PLATFORM_TYPE, Edge::PlatformType, Platform)