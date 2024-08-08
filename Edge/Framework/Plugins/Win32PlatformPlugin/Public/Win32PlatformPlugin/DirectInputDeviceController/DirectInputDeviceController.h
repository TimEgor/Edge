#pragma once

#include "EdgeFramework/Input/InputDeviceController/InputDeviceController.h"

#include "DirectInputDevice.h"

namespace EdgeWin32
{
	class DirectInputDeviceFinder final : public Edge::InputDeviceFinder
	{
		struct DeviceEnumerationContext final
		{
			IDirectInput8* m_directInputInterface = nullptr;
			Edge::InputDeviceController* m_deviceController = nullptr;

			DeviceEnumerationContext() = default;
			DeviceEnumerationContext(IDirectInput8* directInput, Edge::InputDeviceController* deviceController)
				: m_directInputInterface(directInput), m_deviceController(deviceController) {}

			const bool isValid() const { return m_directInputInterface && m_deviceController; }
		};

		static BOOL directInputKeyboardEnumerator(LPCDIDEVICEINSTANCE deviceInstance, LPVOID param);
		static BOOL directInputMouseEnumerator(LPCDIDEVICEINSTANCE deviceInstance, LPVOID param);

	private:
		IDirectInput8* m_directInputInterface = nullptr;

	public:
		DirectInputDeviceFinder(IDirectInput8* directInputInterface)
			: m_directInputInterface(directInputInterface) {}

		virtual void findDevices(Edge::InputDeviceController& deviceController) override;
	};

	class DirectInputDeviceController final
	{
	private:
		Edge::InputDeviceController::FinderID m_directInputDeviceFinderId = Edge::InputDeviceController::InvalidFinderID;

		IDirectInput8* m_directInputInterface = nullptr;

	public:
		DirectInputDeviceController() = default;

		bool init();
		void release();
	};
}
