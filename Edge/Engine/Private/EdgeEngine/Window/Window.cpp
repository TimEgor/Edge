#include "Window.h"

#include "TinySimCommon/Multithreading/LockGuard.h"

#include "TinySimFramework/FrameworkCore.h"

#include "WindowEvents.h"

bool TS::Window::initWindowInstancedEvents()
{
	EventController& eventController = FrameworkCore::getInstance().getApplication().getEventController();

	m_sizeEventID = eventController.registerInstancedEvent(WindowSizeEvent::getInstancedEventsType());
	TS_CHECK_RETURN_FALSE(m_sizeEventID != InvalidInstancedEventID);

	return true;
}

void TS::Window::releaseWindowInstancedEvents()
{
	EventController& eventController = FrameworkCore::getInstance().getApplication().getEventController();

	if (m_sizeEventID != InvalidInstancedEventID)
	{
		eventController.unregisterInstancedEvent(m_sizeEventID);
		m_sizeEventID = InvalidInstancedEventID;
	}
}

bool TS::Window::isShown() const
{
	SharedLockGuard locker(m_mutex);

	return m_isShown;
}

const TS::WindowSize& TS::Window::getWindowSize() const
{
	SharedLockGuard locker(m_mutex);

	return m_windowSize;
}

const TS::WindowSize& TS::Window::getClientAreaSize() const
{
	SharedLockGuard locker(m_mutex);

	return m_clientAreaSize;
}

const TS::WindowArea& TS::Window::getCutoutsArea() const
{
	SharedLockGuard locker(m_mutex);

	return m_cutoutsArea;
}

TS::InstancedEventID TS::Window::getSizeEventID() const
{
	SharedLockGuard locker(m_mutex);

	return m_sizeEventID;
}
