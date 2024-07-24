#pragma once

#include "EdgeEngine/Core/PlatformMacros.h"
#include "EdgeEngine/Core/Multithreading/Mutex.h"

#include "EdgeEngine/Window/WindowBase.h"

#define EDGE_WIN32_WND_CLASS_NAME "Edge_Window"
#define EDGE_WINDOW_WIN32_TYPE

namespace Edge_WIN32
{
	class Win32Window final : public Edge::WindowBase
	{
	private:
		mutable Edge::SharedMutex m_mutex;

		Edge::WindowSize m_windowSize = Edge::DefaultWindowSize;
		Edge::WindowSize m_clientAreaSize = Edge::DefaultWindowSize;
		Edge::WindowArea m_cutoutsArea = Edge::DefaultWindowArea;

		HWND m_hWnd = nullptr;

		bool m_sizeStable = true;
		bool m_isShown = false;

		void updateSizeInternal();

	public:
		Win32Window(Edge::WindowID windowID)
			: WindowBase(windowID) {}
		~Win32Window() { release(); }

		virtual bool init(const char* title, const Edge::WindowSize& size) override;
		virtual void release() override;

		virtual bool isValid() const override;
		void invalidate();

		virtual void show() override;
		virtual void hide() override;

		virtual bool isStable() const override;

		virtual const Edge::WindowSize& getClientAreaSize() const override;
		virtual const Edge::WindowArea& getCutoutsArea() const override;
		virtual const Edge::WindowSize& getWindowSize() const override;
		virtual bool isShown() const override;

		void setSizeStable(bool state);
		void updateSize();

		virtual void* getNativeHandle() const override { return m_hWnd; }
		HWND getHWnd() const { return m_hWnd; }

		EDGE_WINDOW_TYPE(EDGE_WINDOW_WIN32_TYPE);
	};
}