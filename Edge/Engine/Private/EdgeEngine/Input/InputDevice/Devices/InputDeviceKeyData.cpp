#include "InputDeviceKeyData.h"

#include <cmath>
#include <cstring>

void TS::InputDeviceKeyData::copyFrom(const InputDeviceKeyData& keyData)
{
	memcpy(m_values, keyData.m_values, sizeof(m_values));
}

void TS::InputDeviceKeyData::reset()
{
	memset(m_values, 0, sizeof(m_values));
}

void TS::InputDeviceKeyData::combine(const InputDeviceKeyData& keyData)
{
	for (KeyIndex index = 0; index < KeyCount; ++index)
	{
		if (abs(keyData.m_values[index]) > abs(m_values[index]))
		{
			m_values[index] = keyData.m_values[index];
		}
	}
}
