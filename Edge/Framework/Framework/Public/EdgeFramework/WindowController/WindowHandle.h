#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"
#include "EdgeCommon/Reference/MTReference.h"

namespace Edge
{
	class Window;

	class WindowHandle final : public MTCountableObjectBase, public NonCopyable
	{
	private:
		Window* m_window = nullptr;

		virtual void selfDestroy() override;

	public:
		WindowHandle(Window* window);

		Window& getWindow();
		const Window& getWindow() const;

		template <typename WindowType>
		WindowType& getWindowCast()
		{
			static_assert(std::is_base_of_v<Window, WindowType>);
			return reinterpret_cast<WindowType&>(getWindow());
		}

		template <typename WindowType>
		const WindowType& getWindowCast() const
		{
			static_assert(std::is_base_of_v<Window, WindowType>);
			return reinterpret_cast<const WindowType&>(getWindow());
		}
	};

	EDGE_MT_REFERENCE(WindowHandle);
}
