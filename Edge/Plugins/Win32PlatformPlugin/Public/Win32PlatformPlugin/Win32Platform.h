#pragma once

#include "EdgeEngine/Core/PlatformMacros.h"
#include "EdgeEngine/Platform/IPlatform.h"

#include "WindowController/Win32WindowEventSystem.h"

//#include "DirectInputDeviceController/DirectInputDeviceController.h"

#include <vector>

#define EDGE_PLARFORM_WIN32_TYPE

namespace Edge_WIN32
{
	class Win32Platform final : public Edge::IPlatform
	{
		using MonitorInfoCollection = std::vector<Edge::MonitorInfo>;

	private:
		Win32WindowEventController m_windowEventController;

		MonitorInfoCollection m_monitorInfos;

		//DirectInputDeviceController m_directInputDeviceController;

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

		virtual Edge::IWindow* createWindow(Edge::WindowID windowID) const override;
		virtual const Edge::IWindowEventController& getWindowEventController() const override;
		virtual Edge::IWindowEventController& getWindowEventController() override;

		virtual uint32_t getMonitorCount() const override { return static_cast<uint32_t>(m_monitorInfos.size()); }
		virtual const Edge::MonitorInfo& getMonitorInfo(uint32_t index) const override { return m_monitorInfos[index]; }

		EDGE_PLATFORM_TYPE(EDGE_PLARFORM_WIN32_TYPE)
	};
}