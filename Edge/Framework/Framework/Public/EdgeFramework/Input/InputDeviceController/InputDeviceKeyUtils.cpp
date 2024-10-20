#include "InputDeviceKeyUtils.h"

#include "EdgeCommon/Math/Const.h"

bool Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(const InputDeviceKeyData& data, InputDeviceKeyData::KeyIndex key)
{
	return data.m_values[key] > EDGE_EPSILON;
}
