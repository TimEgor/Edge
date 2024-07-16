#pragma once

#include <cassert>
#include <memory>

#include "InputDevice.h"
#include "KeyboardKeys.h"

#define TS_INPUT_DEVICE_TYPE_KEYBOARD

namespace TS
{
	class KeyboardInputDevice : public InputDevice
	{
	public:
		KeyboardInputDevice() = default;

		TS_INPUT_DEVICE_TYPE(TS_INPUT_DEVICE_TYPE_KEYBOARD)
	};
}
