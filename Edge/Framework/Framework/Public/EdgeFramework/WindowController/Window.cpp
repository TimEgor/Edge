#include "Window.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Multithreading/LockGuard.h"

#include "EdgeFramework/FrameworkCore.h"

#include "WindowEvents.h"

bool Edge::Window::initWindowInstancedEvents()
{
	EventController& eventController = FrameworkCore::getInstance().getApplication().getEventController();

	m_sizeEventID = eventController.registerInstancedEvent(WindowSizeEvent::getInstancedEventsType());
	EDGE_CHECK_RETURN_FALSE(m_sizeEventID != InvalidInstancedEventID);

	return true;
}

void Edge::Window::releaseWindowInstancedEvents()
{
	EventController& eventController = FrameworkCore::getInstance().getApplication().getEventController();

	if (m_sizeEventID != InvalidInstancedEventID)
	{
		eventController.unregisterInstancedEvent(m_sizeEventID);
		m_sizeEventID = InvalidInstancedEventID;
	}
}

bool Edge::Window::isShown() const
{
	SharedLockGuard locker(m_mutex);

	return m_isShown;
}

const Edge::WindowSize& Edge::Window::getWindowSize() const
{
	SharedLockGuard locker(m_mutex);

	return m_windowSize;
}

const Edge::WindowSize& Edge::Window::getClientAreaSize() const
{
	SharedLockGuard locker(m_mutex);

	return m_clientAreaSize;
}

const Edge::WindowArea& Edge::Window::getCutoutsArea() const
{
	SharedLockGuard locker(m_mutex);

	return m_cutoutsArea;
}

Edge::InstancedEventID Edge::Window::getSizeEventID() const
{
	SharedLockGuard locker(m_mutex);

	return m_sizeEventID;
}
