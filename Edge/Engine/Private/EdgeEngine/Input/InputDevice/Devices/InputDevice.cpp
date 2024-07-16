#include "InputDevice.h"

void TS::InputDevice::setWindow(const Window& window, bool exclusiveUsing)
{
	m_windowId = window.getID();
	onWindowSet(window, exclusiveUsing);
}
