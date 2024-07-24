#pragma once

#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Engine/IEngine.h"
#include "EdgeEngine/Platform/IPlatform.h"

#include "Win32Platform.h"

#include <cassert>

namespace Edge_WIN32
{
	inline Win32Platform& getWin32FrameworkPlatform()
	{
		Edge::IPlatform& platform = Edge::EngineCore::getInstance().getEngine().getPlatform();
		assert(platform.getType() == Win32Platform::getPlatformType());

		return reinterpret_cast<Win32Platform&>(platform);
	}
}