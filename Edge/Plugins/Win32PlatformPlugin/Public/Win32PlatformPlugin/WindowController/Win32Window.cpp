#include "Win32Window.h"

#include "EdgeEngine/Core/UtilsMacros.h"
#include "EdgeEngine/Core/Multithreading/LockGuard.h"

#include "Win32PlatformPlugin/Win32PlatformUtils.h"

void Edge_WIN32::Win32Window::updateSizeInternal()
{
	RECT clientSize;
	GetClientRect(m_hWnd, &clientSize);
	m_clientAreaSize.m_x = static_cast<uint16_t>(clientSize.right - clientSize.left);
	m_clientAreaSize.m_y = static_cast<uint16_t>(clientSize.bottom - clientSize.top);

	m_cutoutsArea.m_top = static_cast<Edge::WindowArea::ValueType>(clientSize.top);
	m_cutoutsArea.m_bottom = static_cast<Edge::WindowArea::ValueType>(m_windowSize.m_y - clientSize.bottom);
	m_cutoutsArea.m_right = static_cast<Edge::WindowArea::ValueType>(m_windowSize.m_x - clientSize.right);
	m_cutoutsArea.m_left = static_cast<Edge::WindowArea::ValueType>(clientSize.left);
}

bool Edge_WIN32::Win32Window::init(const char* title, const Edge::WindowSize& size)
{

	const Win32Platform& win32Platform = getWin32FrameworkPlatform();

	Edge::LockGuard locker(m_mutex);

	EDGE_CHECK_INITIALIZATION(initWindowInstancedEvents());

	m_windowSize = size;

	m_hWnd = CreateWindow(EDGE_WIN32_WND_CLASS_NAME, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		m_windowSize.m_x, m_windowSize.m_y, NULL, NULL, win32Platform.getHInstance(), NULL);

	if (!m_hWnd)
	{
		return false;
	}

	ShowCursor(true);

	m_isShown = true;

	ShowWindow(m_hWnd, SW_NORMAL);
	UpdateWindow(m_hWnd);

	SetWindowLong(m_hWnd, 0, getID());

	updateSizeInternal();

    return true;
}

void Edge_WIN32::Win32Window::release()
{
	Edge::LockGuard locker(m_mutex);

	releaseWindowInstancedEvents();

	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
	}
}

bool Edge_WIN32::Win32Window::isValid() const
{
	Edge::SharedLockGuard locker(m_mutex);

	return m_hWnd;
}

void Edge_WIN32::Win32Window::invalidate()
{
	Edge::LockGuard locker(m_mutex);

	m_hWnd = nullptr;
}

void Edge_WIN32::Win32Window::show()
{
	Edge::LockGuard locker(m_mutex);

	ShowWindow(m_hWnd, SW_NORMAL);

	m_isShown = true;
}

void Edge_WIN32::Win32Window::hide()
{
	Edge::LockGuard locker(m_mutex);

	ShowWindow(m_hWnd, SW_HIDE);

	m_isShown = false;
}

bool Edge_WIN32::Win32Window::isStable() const
{
	Edge::SharedLockGuard locker(m_mutex);

	return m_sizeStable;
}

const Edge::WindowSize& Edge_WIN32::Win32Window::getClientAreaSize() const
{
	Edge::SharedLockGuard locker(m_mutex);

	return m_clientAreaSize;
}

const Edge::WindowArea& Edge_WIN32::Win32Window::getCutoutsArea() const
{
	Edge::SharedLockGuard locker(m_mutex);

	return m_cutoutsArea;
}

const Edge::WindowSize& Edge_WIN32::Win32Window::getWindowSize() const
{
	Edge::SharedLockGuard locker(m_mutex);

	return m_windowSize;
}

bool Edge_WIN32::Win32Window::isShown() const
{
	Edge::SharedLockGuard locker(m_mutex);

	return m_isShown;
}

void Edge_WIN32::Win32Window::setSizeStable(bool state)
{
	Edge::LockGuard locker(m_mutex);

	m_sizeStable = state;
}

void Edge_WIN32::Win32Window::updateSize()
{
	Edge::LockGuard locker(m_mutex);

	updateSizeInternal();
}