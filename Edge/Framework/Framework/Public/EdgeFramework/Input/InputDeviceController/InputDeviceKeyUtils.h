#pragma once
#include "Devices/InputDeviceKeyData.h"

namespace Edge
{
	struct InputDeviceKeyData;

	namespace InputDeviceKeyUtils
	{
		bool IsInputDeviceKeyPressed(const InputDeviceKeyData& data, InputDeviceKeyData::KeyIndex key);
	}
}
