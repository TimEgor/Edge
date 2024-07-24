#pragma once

#include "IWindow.h"

namespace Edge
{
	class WindowBase : public IWindow
	{
	private:
		const WindowID m_id = InvalidWindowID;
		InstancedEventID m_sizeEventID = InvalidInstancedEventID;

	protected:
		bool initWindowInstancedEvents();
		void releaseWindowInstancedEvents();

	public:
		WindowBase(WindowID windowID)
			: m_id(windowID) {}

		virtual WindowID getID() const override { return m_id; }

		virtual InstancedEventID getSizeEventID() const override { return m_sizeEventID; }
	};
}
