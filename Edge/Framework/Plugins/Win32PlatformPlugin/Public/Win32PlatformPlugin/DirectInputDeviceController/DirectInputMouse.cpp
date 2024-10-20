#include "DirectInputMouse.h"

#include "EdgeCommon/UtilsMacros.h"

bool EdgeWin32::DirectInputMouse::init()
{
	EDGE_CHECK_INITIALIZATION(initDevice());

	getDirectInputDevice()->SetDataFormat(&c_dfDIMouse2);

	return true;
}

void EdgeWin32::DirectInputMouse::release()
{
	releaseDevice();
}

void EdgeWin32::DirectInputMouse::update()
{
	m_keyData.reset();

	DIMOUSESTATE2 deviceState;

	const HRESULT result = getDirectInputDevice()->GetDeviceState(sizeof(DIMOUSESTATE2), &deviceState);
	if (result != DI_OK)
	{
		return;
	}

	for (uint32_t keyIndex = 0; keyIndex < 8; ++keyIndex)
	{
		m_keyData.m_values[GetMouseKey(Edge::MouseKeys::FIRST_BUTTON) + keyIndex] = (static_cast<float>(deviceState.rgbButtons[keyIndex] > 0)) ? 1.0f : 0.0f;
	}

	m_keyData.m_values[GetMouseKey(Edge::MouseKeys::X)] = static_cast<float>(deviceState.lX);
	m_keyData.m_values[GetMouseKey(Edge::MouseKeys::Y)] = static_cast<float>(deviceState.lY);
	m_keyData.m_values[GetMouseKey(Edge::MouseKeys::Z)] = static_cast<float>(deviceState.lZ);
}

void EdgeWin32::DirectInputMouse::onWindowSet(const Edge::Window& window, bool exclusiveUsing)
{
	setDeviceCooperativeLevel(window, exclusiveUsing);
}

void EdgeWin32::DirectInputMouse::acquire()
{
	acquireDevice();
}

void EdgeWin32::DirectInputMouse::unacquire()
{
	unacquireDevice();
}
