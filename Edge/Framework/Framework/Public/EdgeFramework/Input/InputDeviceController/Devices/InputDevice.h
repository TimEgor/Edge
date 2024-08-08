#pragma once

#include "EdgeCommon/HashedType.h"

#include "EdgeFramework/WindowController/Window.h"

#include "InputDeviceKeyData.h"

namespace Edge
{
	class Window;

	using InputDeviceType = HashedType::Type;
	constexpr InputDeviceType InvalidInputDeviceType = 0;

	class InputDevice : public HashedType
	{
		WindowID m_windowId = InvalidWindowID;
		bool m_isEnable = true;

	protected:
		InputDeviceKeyData m_keyData;

		virtual void onWindowSet(const Window& window, bool exclusiveUsing = false) = 0;

	public:
		InputDevice() = default;
		virtual ~InputDevice() = default;

		virtual bool init() = 0;
		virtual void release() = 0;

		virtual void update() = 0;

		void setWindow(const Window& window, bool exclusiveUsing = false);
		WindowID getWindowID() const { return m_windowId; }

		virtual void acquire() = 0;
		virtual void unacquire() = 0;


		void setEnable(bool state) { m_isEnable = state; }
		bool isEnable() const { return m_isEnable; }

		const InputDeviceKeyData& getKeyData() const { return m_keyData; }

		virtual InputDeviceType getType() const = 0;
	};
}

#define EDGE_INPUT_DEVICE_TYPE(DEVICE_TYPE) EDGE_HASH_TYPE(#DEVICE_TYPE, Edge::InputDeviceType, Device)