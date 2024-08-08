#pragma once

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Application/Application.h"
#include "EdgeFramework/Platform/Platform.h"

#include "Win32Platform.h"

#include <cassert>

namespace EdgeWin32
{
	inline Win32Platform& getWin32FrameworkPlatform()
	{
		Edge::Platform& platform = Edge::FrameworkCore::getInstance().getApplication().getPlatform();
		assert(platform.getType() == Win32Platform::getPlatformType());

		return reinterpret_cast<Win32Platform&>(platform);
	}
}