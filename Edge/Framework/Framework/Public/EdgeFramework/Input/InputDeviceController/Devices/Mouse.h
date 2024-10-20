#pragma once

#include "InputDevice.h"

#define EDGE_INPUT_DEVICE_TYPE_MOUSE

namespace Edge
{
	using MouseKey = InputDeviceKeyData::KeyIndex;
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

	inline MouseKey GetMouseKey(MouseKeys key) { return static_cast<MouseKey>(key); }

	class MouseInputDevice : public InputDevice
	{
	public:
		MouseInputDevice() = default;

		EDGE_INPUT_DEVICE_TYPE(EDGE_INPUT_DEVICE_TYPE_MOUSE)
	};
}