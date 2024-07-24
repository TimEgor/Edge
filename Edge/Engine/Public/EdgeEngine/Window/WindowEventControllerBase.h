#pragma once

#include "IWindowEventController.h"

namespace Edge
{
	class IEventController;

	class WindowEventControllerBase : public IWindowEventController
	{
	protected:
		void initWindowContextEvent();
		void releaseWindowContextEvent();

		static void onWindowActivate(const WindowHandleReference& window, bool isActive);
		static void onWindowClose(const WindowHandleReference& window);
		static void onWindowSizeChange(const WindowHandleReference& window);

	public:
		WindowEventControllerBase();
		virtual ~WindowEventControllerBase();

		virtual void updateWindowEvents(const IWindow& window) = 0;
		virtual void updateProcessWindowsEvents() = 0;
	};
}
