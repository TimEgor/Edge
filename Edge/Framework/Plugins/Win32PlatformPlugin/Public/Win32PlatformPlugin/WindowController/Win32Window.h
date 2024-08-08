#pragma once

#include "EdgeCommon/PlatformMacros.h"
#include "EdgeFramework/WindowController/Window.h"

#define EDGE_WIN32_WND_CLASS_NAME "EdgeWindow"
#define EDGE_WINDOW_WIN32_TYPE

namespace EdgeWin32
{
	class Win32Window final : public Edge::Window
	{
	private:
		HWND m_hWnd = nullptr;

		bool m_sizeStable = true;

		void updateSizeInternal();

	public:
		Win32Window(Edge::WindowID windowID)
			: Window(windowID) {}
		~Win32Window() { release(); }

		virtual bool init(const char* title, const Edge::WindowSize& size) override;
		virtual void release() override;

		virtual bool isValid() const override;
		void invalidate();

		virtual void show() override;
		virtual void hide() override;

		virtual bool isStable() const override;

		void setSizeStable(bool state);
		void updateSize();

		virtual void* getNativeHandle() const override { return m_hWnd; }
		HWND getHWnd() const { return m_hWnd; }

		EDGE_WINDOW_TYPE(EDGE_WINDOW_WIN32_TYPE);
	};
}