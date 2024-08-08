#pragma once

namespace Edge
{
	class InputDeviceController;

	class InputDeviceFinder
	{
	public:
		InputDeviceFinder() = default;
		virtual ~InputDeviceFinder() = default;

		virtual void findDevices(InputDeviceController& deviceController) = 0;
	};
}
