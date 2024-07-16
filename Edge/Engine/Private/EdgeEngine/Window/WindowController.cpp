#include "WindowController.h"

#include "TinySimCommon/Core/UtilsMacros.h"
#include "TinySimCommon/Multithreading/LockGuard.h"

#include "WindowEventController.h"
#include "TinySimFramework/FrameworkCore.h"
#include "TinySimFramework/Platform/Platform.h"

#include <cassert>

TS::WindowController::~WindowController()
{
	LockGuard locker(m_mutex);

	assert(m_windows.empty());
}

TS::WindowHandleReference TS::WindowController::createWindow(const char* title, const WindowSize& size)
{
	LockGuard locker(m_mutex);

	WindowID windowID = ++m_lastWindowID;

	Window* window = FrameworkCore::getInstance().getApplication().getPlatform().createWindow(windowID);
	if (!window->init(title, size))
	{
		TS_SAFE_DESTROY(window);
		return nullptr;
	}

	auto newWindowIter = m_windows.emplace(windowID, window);

	return &newWindowIter.first->second;
}

TS::WindowHandleReference TS::WindowController::getWindow(WindowID windowID) const
{
	SharedLockGuard locker(m_mutex);

	auto findWindowIter = m_windows.find(windowID);
	if (findWindowIter != m_windows.end())
	{
		return const_cast<WindowHandle*>(&findWindowIter->second);
	}

	return nullptr;
}

void TS::WindowController::destroyWindow(WindowHandle* windowHandle)
{
	assert(windowHandle);
	assert(windowHandle->getReferenceCount() == 0);

	Window* window = &windowHandle->getWindow();
	assert(window);

	WindowID windowID = window->getID();

	TS_SAFE_DESTROY_WITH_RELEASING(window);

	LockGuard lock(m_mutex);

	m_windows.erase(windowID);
}

void TS::WindowController::updateWindowEvents(const Window& window)
{
	FrameworkCore::getInstance().getApplication().getPlatform().getWindowEventController().updateWindowEvents(window);
}

void TS::WindowController::updateAllWindowsEvents() const
{
	SharedLockGuard locker(m_mutex);

	for (auto& windowIter : m_windows)
	{
		updateWindowEvents(windowIter.second.getWindow());
	}
}

void TS::WindowController::updateWindowEvents(WindowHandleReference& window) const
{
	SharedLockGuard locker(m_mutex);

	if (window)
	{
		updateWindowEvents(window->getWindow());
	}
}
