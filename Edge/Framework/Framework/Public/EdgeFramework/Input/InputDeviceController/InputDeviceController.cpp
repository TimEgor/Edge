#include "InputDeviceController.h"

#include "EdgeCommon/Multithreading/LockGuard.h"

#include "EdgeFramework/FrameworkCore.h"

#include <cassert>

#include "EdgeFramework/WindowController/WindowEventController.h"

void Edge::InputDeviceController::clearDeviceCollection()
{
	m_devices = DeviceCollection();
}

void Edge::InputDeviceController::findDevices()
{
	for (auto& findIter : m_finders)
	{
		assert(findIter.second);
		findIter.second->findDevices(*this);
	}
}

bool Edge::InputDeviceController::init()
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

void Edge::InputDeviceController::release()
{
	UniqueLockGuard locker(m_mutex);

	m_devices = DeviceCollection();
	m_finders = FinderCollection();

	if (m_windowActivationEventDispatcher != InvalidEventDispatcherID)
	{
		FrameworkCore::getInstance().getApplication().getEventController().removeEventDispatcher(m_windowActivationEventDispatcher);
	}
}

void Edge::InputDeviceController::update()
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

void Edge::InputDeviceController::setWindowForAllDevices(const Window& window, bool exclusiveUsing)
{
	UniqueLockGuard locker(m_mutex);

	for (auto& deviceIter : m_devices)
	{
		deviceIter.second->setWindow(window, exclusiveUsing);
	}
}

void Edge::InputDeviceController::acquireWindowDevices(const Window& window)
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

void Edge::InputDeviceController::unacquireWindowDevices(const Window& window)
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

Edge::InputDeviceController::FinderID Edge::InputDeviceController::addDeviceFinder(FinderPointer&& finder)
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

void Edge::InputDeviceController::removeDeviceFinder(FinderID finderID)
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

Edge::InputDeviceController::DeviceID Edge::InputDeviceController::addDevice(DevicePointer&& device)
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

void Edge::InputDeviceController::removeDevice(DeviceID deviceID)
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

void Edge::InputDeviceController::removeDevices(InputDeviceType type)
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

void Edge::InputDeviceController::removeDevices()
{
	UniqueLockGuard locker(m_mutex);

	clearDeviceCollection();
}

void Edge::InputDeviceController::refindDevices()
{
	{
		UniqueLockGuard locker(m_mutex);
		clearDeviceCollection();
	}

	findDevices();
}

void Edge::InputDeviceController::visitDevice(DeviceID deviceID, const DeviceVisitorFunctionPtr& visitorFunction) const
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

void Edge::InputDeviceController::visitReadonlyDevice(DeviceID deviceID, const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const
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

void Edge::InputDeviceController::visitFirstDevice(InputDeviceType type, const DeviceVisitorFunctionPtr& visitorFunction) const
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

void Edge::InputDeviceController::visitFirstReadonlyDevice(InputDeviceType type, const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const
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

void Edge::InputDeviceController::visitDevices(InputDeviceType type, const DeviceVisitorFunctionPtr& visitorFunction) const
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

void Edge::InputDeviceController::visitReadonlyDevices(InputDeviceType type, const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const
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

void Edge::InputDeviceController::visitDevices(const DeviceVisitorFunctionPtr& visitorFunction) const
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
void Edge::InputDeviceController::visitReadonlyDevices(const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const
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

bool Edge::InputDeviceController::isFinderValid(FinderID finderID) const
{
	UniqueLockGuard locker(m_mutex);

	auto findFinderIter = m_finders.find(finderID);
	return findFinderIter != m_finders.end();
}

bool Edge::InputDeviceController::isDeviceValid(DeviceID deviceID) const
{
	UniqueLockGuard locker(m_mutex);

	auto findDeviceIter = m_devices.find(deviceID);
	return findDeviceIter != m_devices.end();
}

const Edge::InputDeviceKeyCache::DeviceKeyCache* Edge::InputDeviceController::getDeviceKeyCache(InputDeviceType type) const
{
	SharedLockGuard locker(m_mutex);
	return m_keyCache.getCacheData(type);
}
