#include "InputDevice.h"

void Edge::InputDevice::setWindow(const Window& window, bool exclusiveUsing)
{
	m_windowId = window.getID();
	onWindowSet(window, exclusiveUsing);
}
