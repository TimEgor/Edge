#pragma once

#include "EdgeFramework/Input/InputDeviceController/Devices/Mouse.h"

#include "DirectInputDevice.h"

namespace EdgeWin32
{
	class DirectInputMouse final : public Edge::MouseInputDevice, public DirectInputDevice
	{
	private:
		virtual void onWindowSet(const Edge::Window& window, bool exclusiveUsing) override;

	public:
		DirectInputMouse(IDirectInput8* directInputInterface, const DIDEVICEINSTANCE& deviceInstance)
			: DirectInputDevice(directInputInterface, deviceInstance) {}
		~DirectInputMouse() { release(); }

		virtual bool init() override;
		virtual void release() override;

		virtual void update() override;

		virtual void acquire() override;
		virtual void unacquire() override;
	};
}