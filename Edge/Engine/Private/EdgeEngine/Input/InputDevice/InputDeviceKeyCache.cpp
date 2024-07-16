#include "InputDeviceKeyCache.h"

const TS::InputDeviceKeyCache::DeviceKeyCache* TS::InputDeviceKeyCache::getCacheData(InputDeviceType deviceType) const
{
	auto findDataIter = m_keyCaches.find(deviceType);
	if (findDataIter != m_keyCaches.end())
	{
		return &findDataIter->second.m_cache;
	}

	return nullptr;
}

void TS::InputDeviceKeyCache::updateCacheData()
{
	for (auto& cacheIter : m_keyCaches)
	{
		DeviceKeyCache& cache = cacheIter.second.m_cache;
		cache.m_prevKeyData.copyFrom(cache.m_currentKeyData);
		cache.m_currentKeyData.reset();

		cacheIter.second.isUpdated = false;
	}
}

void TS::InputDeviceKeyCache::releaseUselessCacheData()
{
	for (auto cacheIter = m_keyCaches.begin(); cacheIter != m_keyCaches.end();)
	{
		if (!cacheIter->second.isUpdated)
		{
			cacheIter = m_keyCaches.erase(cacheIter);
			continue;
		}

		++cacheIter;
	}
}

void TS::InputDeviceKeyCache::addData(InputDeviceType deviceType, const InputDeviceKeyData& data)
{
	DeviceKeyCacheData& cacheData = m_keyCaches[deviceType];
	cacheData.m_cache.m_currentKeyData.combine(data);
	cacheData.isUpdated = true;
}
