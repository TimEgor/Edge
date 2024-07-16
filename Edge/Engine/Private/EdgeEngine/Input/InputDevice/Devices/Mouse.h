#pragma once

#include "InputDevice.h"
#include "TinySimCommon/Math/Vector.h"

#define TS_INPUT_DEVICE_TYPE_MOUSE

namespace TS
{
	using MouseKey = uint8_t;
	enum class MouseKeys : MouseKey
	{
		Left,
		Right,
		Wheel,
		Additional_1,
		Additional_2,
		Additional_3,
		Additional_4,
		Additional_5,

		FIRST_BUTTON = Left,
		LAST_BUTTON = Additional_5,

		X,
		Y,
		Z,

		FIRST_AXLE = X,
		LAST_AXLE = Z,

		MAX_KEY = Z
	};

	class MouseInputDevice : public InputDevice
	{
	public:
		MouseInputDevice() = default;

		TS_INPUT_DEVICE_TYPE(TS_INPUT_DEVICE_TYPE_MOUSE)
	};
}