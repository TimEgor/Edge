#pragma once
#include <cstdint>

namespace Edge
{
	struct InputDeviceKeyData final
	{
		using KeyValue = float;

		using KeyIndex = uint16_t;
		static constexpr KeyIndex KeyCount = 256;

		KeyValue m_values[KeyCount];

		void copyFrom(const InputDeviceKeyData& keyData);
		void reset();

		void combine(const InputDeviceKeyData& keyData);
	};
}
