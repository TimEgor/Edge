#include "InputDeviceKeyUtils.h"

#include "EdgeCommon/Math/ComputeMath.h"

bool Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(const InputDeviceKeyData& data, InputDeviceKeyData::KeyIndex key)
{
	return data.m_values[key] > Math::Epsilon;
}
