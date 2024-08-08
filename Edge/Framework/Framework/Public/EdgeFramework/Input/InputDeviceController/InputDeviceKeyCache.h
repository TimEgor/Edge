#pragma once

#include <unordered_map>

#include "Devices/InputDevice.h"

namespace Edge
{
	class InputDeviceKeyCache final
	{
	public:
		struct DeviceKeyCache final
		{
			InputDeviceKeyData m_currentKeyData;
			InputDeviceKeyData m_prevKeyData;
		};

	private:
		struct DeviceKeyCacheData final
		{
			DeviceKeyCache m_cache;
			bool isUpdated = false;
		};

		using DeviceKeyCacheCollection = std::unordered_map<InputDeviceType, DeviceKeyCacheData>;

		DeviceKeyCacheCollection m_keyCaches;

	public:
		InputDeviceKeyCache() = default;

		const DeviceKeyCache* getCacheData(InputDeviceType deviceType) const;

		void updateCacheData();
		void releaseUselessCacheData();
		void addData(InputDeviceType deviceType, const InputDeviceKeyData& data);
	};
}
