#pragma once

#include "TinySimCommon/Multithreading/Mutex.h"

#include "TinySimFramework/EventController/EventController.h"

#include "InputDeviceFinder.h"
#include "InputDeviceKeyCache.h"
#include "Devices/InputDevice.h"

#include <functional>
#include <memory>

namespace TS
{
	class InputDeviceController final
	{
	public:
		using FinderPointer = std::unique_ptr<InputDeviceFinder>;
		using DevicePointer = std::unique_ptr<InputDevice>;

		using FinderID = uint16_t;
		using DeviceID = uint16_t;

		static constexpr FinderID InvalidFinderID = 0;
		static constexpr DeviceID InvalidDeviceID = 0;

		using DeviceVisitorFunctionPtr = std::function<void(InputDevice&)>;
		using DeviceReadOnlyVisitorFunctionPtr = std::function<void(const InputDevice&)>;

	private:
		using DeviceCollection = std::unordered_map<DeviceID, DevicePointer>;
		using FinderCollection = std::unordered_map<FinderID, FinderPointer>;

		mutable SharedMutex m_mutex;

		InputDeviceKeyCache m_keyCache;

		DeviceCollection m_devices;
		FinderCollection m_finders;

		FinderID m_lastFinderID = InvalidFinderID;
		DeviceID m_lastDeviceID = InvalidDeviceID;

		EventDispatcherID m_windowActivationEventDispatcher = InvalidInstancedEventID;

		void clearDeviceCollection();
		void findDevices();

	public:
		InputDeviceController() = default;

		bool init();
		void release();

		void update();

		void setWindowForAllDevices(const Window& window, bool exclusiveUsing = false);
		void acquireWindowDevices(const Window& window);
		void unacquireWindowDevices(const Window& window);

		FinderID addDeviceFinder(FinderPointer&& finder);
		void removeDeviceFinder(FinderID finderID);

		DeviceID addDevice(DevicePointer&& device);
		void removeDevice(DeviceID deviceID);

		void removeDevices(InputDeviceType type);
		void removeDevices();

		void refindDevices();

		void visitDevice(DeviceID deviceID, const DeviceVisitorFunctionPtr& visitorFunction) const;
		void visitReadonlyDevice(DeviceID deviceID, const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const;

		void visitFirstDevice(InputDeviceType type, const DeviceVisitorFunctionPtr& visitorFunction) const;
		void visitFirstReadonlyDevice(InputDeviceType type, const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const;

		void visitDevices(InputDeviceType type, const DeviceVisitorFunctionPtr& visitorFunction) const;
		void visitReadonlyDevices(InputDeviceType type, const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const;

		void visitDevices(const DeviceVisitorFunctionPtr& visitorFunction) const;
		void visitReadonlyDevices(const DeviceReadOnlyVisitorFunctionPtr& visitorFunction) const;

		bool isFinderValid(FinderID finderID) const;
		bool isDeviceValid(DeviceID deviceID) const;

		const InputDeviceKeyCache::DeviceKeyCache* getDeviceKeyCache(InputDeviceType type) const;
	};
}
