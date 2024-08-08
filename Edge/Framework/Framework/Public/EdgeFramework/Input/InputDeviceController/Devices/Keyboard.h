#pragma once

#include <cassert>
#include <memory>

#include "InputDevice.h"
#include "KeyboardKeys.h"

#define EDGE_INPUT_DEVICE_TYPE_KEYBOARD

namespace Edge
{
	class KeyboardInputDevice : public InputDevice
	{
	public:
		KeyboardInputDevice() = default;

		EDGE_INPUT_DEVICE_TYPE(EDGE_INPUT_DEVICE_TYPE_KEYBOARD)
	};
}
