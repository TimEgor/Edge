#include "WindowHandle.h"

#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Engine/IEngine.h"

#include "IWindowController.h"

#include <cassert>

void Edge::WindowHandle::selfDestroy()
{
	GetEngine().getWindowController().destroyWindow(this);
}

Edge::WindowHandle::WindowHandle(IWindow* window)
	: m_window(window)
{
	assert(m_window);
}

Edge::IWindow& Edge::WindowHandle::getWindow()
{
	assert(m_window);
	return *m_window;
}

const Edge::IWindow& Edge::WindowHandle::getWindow() const
{
	assert(m_window);
	return *m_window;
}
