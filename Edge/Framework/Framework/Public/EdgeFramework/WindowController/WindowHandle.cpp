#include "WindowHandle.h"

#include "EdgeFramework/FrameworkCore.h"

#include "WindowController.h"

#include <cassert>

void Edge::WindowHandle::selfDestroy()
{
	FrameworkCore::getInstance().getApplication().getWindowController().destroyWindow(this);
}

Edge::WindowHandle::WindowHandle(Window* window)
	: m_window(window)
{
	assert(m_window);
}

Edge::Window& Edge::WindowHandle::getWindow()
{
	assert(m_window);
	return *m_window;
}

const Edge::Window& Edge::WindowHandle::getWindow() const
{
	assert(m_window);
	return *m_window;
}
