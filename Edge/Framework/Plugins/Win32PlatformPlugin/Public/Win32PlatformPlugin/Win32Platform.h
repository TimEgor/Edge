#pragma once

#include "EdgeCommon/PlatformMacros.h"
#include "EdgeFramework/Platform/Platform.h"

#include "WindowController/Win32WindowEventSystem.h"

#include "DirectInputDeviceController/DirectInputDeviceController.h"

#include <vector>

#include "Font/Win32PlatformFontProvider.h"

#define EDGE_PLARFORM_WIN32_TYPE

namespace EdgeWin32
{
	class Win32Platform final : public Edge::Platform
	{
		using MonitorInfoCollection = std::vector<Edge::MonitorInfo>;

	private:
		Win32WindowEventController m_windowEventController;
		Win32PlatformFontProvider m_fontProvider;

		MonitorInfoCollection m_monitorInfos;

		DirectInputDeviceController m_directInputDeviceController;

		HINSTANCE m_hInstance;

		bool initWindowClass();
		void collectMonitorInfo();

	public:
		Win32Platform(HINSTANCE hInstance)
			: m_hInstance(hInstance) {}

		virtual bool init() override;
		virtual void release() override;

		HINSTANCE getHInstance() const { return m_hInstance; }
		virtual void* getNativeHandle() const override { return m_hInstance; }

		virtual Edge::Window* createWindow(Edge::WindowID windowID) const override;
		virtual const Edge::WindowEventController& getWindowEventController() const override;
		virtual Edge::WindowEventController& getWindowEventController() override;

		virtual const Edge::FontProvider& getFontProvider() const override;
		virtual Edge::FontProvider& getFontProvider() override;

		virtual uint32_t getMonitorCount() const override { return static_cast<uint32_t>(m_monitorInfos.size()); }
		virtual const Edge::MonitorInfo& getMonitorInfo(uint32_t index) const override { return m_monitorInfos[index]; }

		EDGE_PLATFORM_TYPE(EDGE_PLARFORM_WIN32_TYPE)
	};
}