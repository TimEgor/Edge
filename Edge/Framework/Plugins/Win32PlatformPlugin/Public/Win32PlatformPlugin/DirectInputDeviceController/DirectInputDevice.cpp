#include "DirectInputDevice.h"

#include "EdgeCommon/UtilsMacros.h"

#include "EdgeFramework/WindowController/Window.h"

#include <cassert>

bool EdgeWin32::DirectInputDevice::initDevice()
{
	assert(m_directInputInterface);

	EDGE_CHECK_CALL(SUCCEEDED(m_directInputInterface->CreateDevice(m_deviceInstance.guidInstance, &m_directInputDevice, nullptr)), releaseDevice());

	return true;
}

void EdgeWin32::DirectInputDevice::releaseDevice()
{
	if (m_directInputDevice)
	{
		m_directInputDevice->Unacquire();
		m_directInputDevice->Release();
		m_directInputDevice = nullptr;
	}
}

void EdgeWin32::DirectInputDevice::setDeviceCooperativeLevel(const Edge::Window& window, bool exclusiveUsing)
{
	assert(m_directInputDevice);

	const HWND hWnd = static_cast<HWND>(window.getNativeHandle());

	if (exclusiveUsing)
	{
		m_directInputDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	}
	else
	{
		m_directInputDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	}
}

void EdgeWin32::DirectInputDevice::acquireDevice()
{
	assert(m_directInputDevice);
	m_directInputDevice->Acquire();
}

void EdgeWin32::DirectInputDevice::unacquireDevice()
{
	assert(m_directInputDevice);
	m_directInputDevice->Unacquire();
}
