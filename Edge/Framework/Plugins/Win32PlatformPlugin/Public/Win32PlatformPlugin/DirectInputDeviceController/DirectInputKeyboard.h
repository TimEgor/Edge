#pragma once

#include "EdgeFramework/Input/InputDeviceController/Devices/Keyboard.h"

#include "DirectInputDevice.h"

namespace EdgeWin32
{
	class DirectInputKeyboard final : public Edge::KeyboardInputDevice, public DirectInputDevice
	{
	private:
		BYTE m_deviceKeys[256];

		virtual void onWindowSet(const Edge::Window& window, bool exclusiveUsing) override;

	public:
		DirectInputKeyboard(IDirectInput8* directInputInterface, const DIDEVICEINSTANCE& deviceInstance)
			: DirectInputDevice(directInputInterface, deviceInstance) {}
		~DirectInputKeyboard() { release(); }

		virtual bool init() override;
		virtual void release() override;

		virtual void update() override;

		virtual void acquire() override;
		virtual void unacquire() override;
	};
}