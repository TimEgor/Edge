#pragma once

#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

namespace Edge
{
	class Window;
}

namespace EdgeWin32
{
	class DirectInputDevice
	{
	private:
		IDirectInput8* m_directInputInterface = nullptr;
		IDirectInputDevice8* m_directInputDevice = nullptr;
		DIDEVICEINSTANCE m_deviceInstance;

	public:
		DirectInputDevice(IDirectInput8* directInputInterface, const DIDEVICEINSTANCE& deviceInstance)
			: m_directInputInterface(directInputInterface), m_deviceInstance(deviceInstance) {}
		~DirectInputDevice() { releaseDevice(); }

		bool initDevice();
		void releaseDevice();

		void setDeviceCooperativeLevel(const Edge::Window& window, bool exclusiveUsing);
		void acquireDevice();
		void unacquireDevice();

		IDirectInputDevice8* getDirectInputDevice() const { return m_directInputDevice; }
	};
}
