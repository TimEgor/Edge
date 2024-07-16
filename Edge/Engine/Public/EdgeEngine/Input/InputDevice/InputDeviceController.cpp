#include "InputDeviceController.h"

#include "TinySimCommon/Multithreading/LockGuard.h"

#include "TinySimFramework/FrameworkCore.h"

#include <cassert>

#include "TinySimFramework/WindowController/WindowEventController.h"

void TS::InputDeviceController::clearDeviceCollection()
{
	m_devices = DeviceCollection();
}

void TS::InputDeviceController::findDevices()
{
	for (auto& findIter : m_finders)
	{
		assert(findIter.second);
		findIter.second->findDevices(*this);
	}
}

bool TS::InputDeviceController::init()
{
	findDevices();

	{
		UniqueLockGuard locker(m_mutex);

		m_windowActivationEventDispatcher = FrameworkCore::getInstance().getApplication().getEventController().addEventDispatcher(WindowActivationEvent::getEventType(),
			[this](const Event& event)
			{
				const WindowActivationEvent& windowActivationEvent = static_cast<const WindowActivationEvent&>(event);
				if (!windowActivationEvent.m_window)
				{
					return;
				}

				if (windowActivationEvent.m_isActive)
				{
					acquireWindowDevices(windowActivationEvent.m_window->getWindow());
				}
				else
				{
					unacquireWindowDevices(windowActivationEvent.m_window->getWindow());
				}
			});
	}

	return true;
}

void TS::InputDeviceController::release()
{
	UniqueLockGuard locker(m_mutex);

	m_devices = DeviceCollection();
	m_finders = FinderCollection();

	if (m_windowActivationEventDispatcher != InvalidEventDispatcherID)
	{
		FrameworkCore::getInstance().getApplication().getEventController().removeEventDispatcher(m_windowActivationEventDispatcher);
	}
}

void TS::InputDeviceController::update()
{
	UniqueLockGuard locker(m_mutex);

	m_keyCache.updateCacheData();

	for (auto& deviceIter : m_devices)
	{
		DevicePointer& device = deviceIter.second;

		device->update();
		m_keyCache.addData(device->getType(), device->getKeyData());
	}

	m_keyCache.releaseUselessCacheData();
}

void TS::InputDeviceController::setWindowForAllDevices(const Window& window, bool exclusiveUsing)
{
	UniqueLockGuard locker(m_mutex);

	for (auto& deviceIter : m_devices)
	{
		deviceIter.second->setWindow(window, exclusiveUsing);
	}
}

void TS::InputDeviceController::acquireWindowDevices(const Window& window)
{
	UniqueLockGuard locker(m_mutex);

	WindowID windowID = window.getID();

	for (auto& deviceIter : m_devices)
	{
		DevicePointer& device = deviceIter.second;
		if (device->getWindowID() == windowID)
		{
			device->acquire();
		}
	}
}

void TS::InputDeviceController::unacquireWindowDevices(const Window& window)
{
	UniqueLockGuard locker(m_mutex);

	WindowID windowID = window.getID();

	for (auto& deviceIter : m_devices)
	{
		DevicePointer& device = deviceIter.second;
		if (device->getWindowID() == windowID)
		{
			device->unacquire();
		}
	}
}

TS::InputDeviceController::FinderID TS::InputDeviceController::addDeviceFinder(FinderPointer&& finder)
{
	if (!finder)
	{
		assert(false && "Finder is null.");
		return InvalidFinderID;
	}

	UniqueLockGuard locker(m_mutex);

	FinderID finderID = ++m_lastFinderID;
	assert(finderID != InvalidFinderID);

	auto newFinderIter = m_finders.emplace(finderID, std::move(finder));
	assert(newFinderIter.second);

	return finderID;
}

void TS::InputDeviceController::removeDeviceFinder(FinderID finderID)
{
	UniqueLockGuard locker(m_mutex);

	auto findFinderIter = m_finders.find(finderID);
	if (findFinderIter == m_finders.end())
	{
		assert(false && "Invalid finder ID.");
		return;
	}

	m_finders.erase(findFinderIter);
}

TS::InputDeviceController::DeviceID TS::InputDeviceController::addDevice(DevicePointer&& device)
{
	if (!device)
	{
		assert(false && "Device is null.");
		return InvalidDeviceID;
	}

	UniqueLockGuard locker(m_mutex);

	DeviceID deviceID = ++m_lastDeviceID;
	assert(deviceID != InvalidDeviceID);

	auto newFinderIter = m_devices.emplace(deviceID, std::move(device));
	assert(newFinderIter.second);

	return deviceID;
}

void TS::InputDeviceController::removeDevice(DeviceID deviceID)
{
	UniqueLockGuard locker(m_mutex);

	auto findDeviceIter = m_devices.find(deviceID);
	if (findDeviceIter == m_devices.end())
	{
		assert(false && "Invalid device ID.");
		return;
	}

	m_devices.erase(findDeviceIter);
}

void TS::InputDeviceController::removeDevices(InputDeviceType type)
{
	UniqueLockGuard locker(m_mutex);

	for (auto deviceIter = m_devices.begin(); deviceIter != m_devices.end();)
	{
		assert(deviceIter->second);

		if (deviceIter->second->getType() == type)
		{
			deviceIter = m_devices.erase(deviceIter);
		}
		else
		{
			++deviceIter;
		}
	}
}

void TS::InputDeviceController::removeDevices()
{
	UniqueLockGuard locker(m_mutex);

	clearDeviceCollection();
}

void TS::InputDeviceController::refindDevices()
{
	{
		UniqueLockGuard locker(m_mutex);
		clearDeviceCollection();
	}

	findDevices();
}

void TS::InputDeviceController::visitDevice(DeviceID deviceID, const DeviceVisitorFunctionPtr& visitorFunction) const
{
	if (!visitorFunction)
	{
		assert(false && "Visitor function is null.");
		return;
	}

	UniqueLockGuard locker(m_mutex);

	auto findDeviceIter = m_devices.find(deviceID);
	if (findDeviceIter != m_devices.end())
	{
		InputDevice* device = findDeviceIter->second.get();
		visitorFunction(*device);
	}
}

void TS::InputDeviceController::visitReadonlyDevice(DeviceID deviceID, const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const
{
	if (!visitorFunction)
	{
		assert(false && "Visitor function is null.");
		return;
	}

	SharedLockGuard locker(m_mutex);

	auto findDeviceIter = m_devices.find(deviceID);
	if (findDeviceIter != m_devices.end())
	{
		const InputDevice* device = findDeviceIter->second.get();
		visitorFunction(*device);
	}
}

void TS::InputDeviceController::visitFirstDevice(InputDeviceType type, const DeviceVisitorFunctionPtr& visitorFunction) const
{
	if (!visitorFunction)
	{
		assert(false && "Visitor function is null.");
		return;
	}

	UniqueLockGuard locker(m_mutex);

	for (auto& deviceIter : m_devices)
	{
		InputDevice* device = deviceIter.second.get();

		if (device->getType() == type)
		{
			visitorFunction(*device);
			break;
		}
	}
}

void TS::InputDeviceController::visitFirstReadonlyDevice(InputDeviceType type, const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const
{
	if (!visitorFunction)
	{
		assert(false && "Visitor function is null.");
		return;
	}

	SharedLockGuard locker(m_mutex);

	for (auto& deviceIter : m_devices)
	{
		const InputDevice* device = deviceIter.second.get();

		if (device->getType() == type)
		{
			visitorFunction(*device);
			break;
		}
	}
}

void TS::InputDeviceController::visitDevices(InputDeviceType type, const DeviceVisitorFunctionPtr& visitorFunction) const
{
	if (!visitorFunction)
	{
		assert(false && "Visitor function is null.");
		return;
	}

	UniqueLockGuard locker(m_mutex);

	for (auto& deviceIter : m_devices)
	{
		InputDevice* device = deviceIter.second.get();

		if (device->getType() == type)
		{
			visitorFunction(*device);
		}
	}
}

void TS::InputDeviceController::visitReadonlyDevices(InputDeviceType type, const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const
{
	if (!visitorFunction)
	{
		assert(false && "Visitor function is null.");
		return;
	}

	SharedLockGuard locker(m_mutex);

	for (auto& deviceIter : m_devices)
	{
		const InputDevice* device = deviceIter.second.get();

		if (device->getType() == type)
		{
			visitorFunction(*device);
		}
	}
}

void TS::InputDeviceController::visitDevices(const DeviceVisitorFunctionPtr& visitorFunction) const
{
	if (!visitorFunction)
	{
		assert(false && "Visitor function is null.");
		return;
	}

	UniqueLockGuard locker(m_mutex);

	for (auto& deviceIter : m_devices)
	{
		InputDevice* device = deviceIter.second.get();
		visitorFunction(*device);
	}
}
void TS::InputDeviceController::visitReadonlyDevices(const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const
{
	if (!visitorFunction)
	{
		assert(false && "Visitor function is null.");
		return;
	}

	SharedLockGuard locker(m_mutex);

	for (auto& deviceIter : m_devices)
	{
		const InputDevice* device = deviceIter.second.get();
		visitorFunction(*device);
	}
}

bool TS::InputDeviceController::isFinderValid(FinderID finderID) const
{
	UniqueLockGuard locker(m_mutex);

	auto findFinderIter = m_finders.find(finderID);
	return findFinderIter != m_finders.end();
}

bool TS::InputDeviceController::isDeviceValid(DeviceID deviceID) const
{
	UniqueLockGuard locker(m_mutex);

	auto findDeviceIter = m_devices.find(deviceID);
	return findDeviceIter != m_devices.end();
}

const TS::InputDeviceKeyCache::DeviceKeyCache* TS::InputDeviceController::getDeviceKeyCache(InputDeviceType type) const
{
	SharedLockGuard locker(m_mutex);
	return m_keyCache.getCacheData(type);
}
