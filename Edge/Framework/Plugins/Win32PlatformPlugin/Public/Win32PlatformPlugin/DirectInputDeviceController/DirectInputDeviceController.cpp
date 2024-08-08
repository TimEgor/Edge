#include "DirectInputDeviceController.h"

#include "EdgeCommon/UtilsMacros.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Platform/Platform.h"

#include "DirectInputKeyboard.h"
#include "DirectInputMouse.h"

BOOL EdgeWin32::DirectInputDeviceFinder::directInputKeyboardEnumerator(LPCDIDEVICEINSTANCE deviceInstance, LPVOID param)
{
	if (!param)
	{
		return DIENUM_STOP;
	}

	const DeviceEnumerationContext& enumerationContext = *static_cast<DeviceEnumerationContext*>(param);
	if (!enumerationContext.isValid())
	{
		return DIENUM_STOP;
	}

	const BYTE deviceType = GET_DIDEVICE_TYPE(deviceInstance->dwDevType);

	if (deviceType == DI8DEVTYPE_KEYBOARD)
	{
		Edge::InputDeviceController::DevicePointer keyboardDevice(new DirectInputKeyboard(enumerationContext.m_directInputInterface, *deviceInstance));
		if (keyboardDevice->init())
		{
			enumerationContext.m_deviceController->addDevice(std::move(keyboardDevice));
		}
	}

	return DIENUM_CONTINUE;
}

BOOL EdgeWin32::DirectInputDeviceFinder::directInputMouseEnumerator(LPCDIDEVICEINSTANCE deviceInstance, LPVOID param)
{
	if (!param)
	{
		return DIENUM_STOP;
	}

	const DeviceEnumerationContext& enumerationContext = *static_cast<DeviceEnumerationContext*>(param);
	if (!enumerationContext.isValid())
	{
		return DIENUM_STOP;
	}

	const BYTE deviceType = GET_DIDEVICE_TYPE(deviceInstance->dwDevType);

	if (deviceType == DI8DEVTYPE_MOUSE)
	{
		Edge::InputDeviceController::DevicePointer mouseDevice(new DirectInputMouse(enumerationContext.m_directInputInterface, *deviceInstance));
		if (mouseDevice->init())
		{
			enumerationContext.m_deviceController->addDevice(std::move(mouseDevice));
		}
	}

	return DIENUM_CONTINUE;
}

void EdgeWin32::DirectInputDeviceFinder::findDevices(Edge::InputDeviceController& deviceController)
{
	if (!m_directInputInterface)
	{
		return;
	}

	DeviceEnumerationContext enumerationContext(m_directInputInterface, &deviceController);

	m_directInputInterface->EnumDevices(DI8DEVCLASS_KEYBOARD, directInputKeyboardEnumerator, &enumerationContext, DIEDFL_ATTACHEDONLY);
	m_directInputInterface->EnumDevices(DI8DEVCLASS_POINTER, directInputMouseEnumerator, &enumerationContext, DIEDFL_ATTACHEDONLY);
}

bool EdgeWin32::DirectInputDeviceController::init()
{
	if (FAILED(DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&m_directInputInterface), 0)))
	{
		return false;
	}

	Edge::InputDeviceController::FinderPointer directInputDeviceFinder(new DirectInputDeviceFinder(m_directInputInterface));
	Edge::InputDeviceController& inputDeviceController = Edge::FrameworkCore::getInstance().getApplication().getInputDeviceController();
	m_directInputDeviceFinderId = inputDeviceController.addDeviceFinder(std::move(directInputDeviceFinder));
	EDGE_CHECK_INITIALIZATION(m_directInputDeviceFinderId != Edge::InputDeviceController::InvalidFinderID);

	return true;
}

void EdgeWin32::DirectInputDeviceController::release()
{
	if (m_directInputDeviceFinderId != Edge::InputDeviceController::InvalidFinderID)
	{
		Edge::InputDeviceController& inputDeviceController = Edge::FrameworkCore::getInstance().getApplication().getInputDeviceController();
		inputDeviceController.removeDeviceFinder(m_directInputDeviceFinderId);
	}

	if (m_directInputInterface)
	{
		m_directInputInterface->Release();
		m_directInputInterface = nullptr;
	}
}
