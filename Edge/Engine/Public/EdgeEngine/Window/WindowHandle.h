#pragma once

#include "EdgeEngine/Core/Patterns/NonCopyable.h"
#include "EdgeEngine/Core/Reference/MTReference.h"

#include "IWindow.h"

namespace Edge
{
	class WindowHandle final : public MTCountableObjectBase, public NonCopyable
	{
	private:
		IWindow* m_window = nullptr;

		virtual void selfDestroy() override;

	public:
		WindowHandle(IWindow* window);

		IWindow& getWindow();
		const IWindow& getWindow() const;

		template <typename WindowType>
		WindowType& getWindowCast()
		{
			static_assert(std::is_base_of_v<IWindow, WindowType>);
			return reinterpret_cast<WindowType&>(getWindow());
		}

		template <typename WindowType>
		const WindowType& getWindowCast() const
		{
			static_assert(std::is_base_of_v<IWindow, WindowType>);
			return reinterpret_cast<const WindowType&>(getWindow());
		}
	};

	EDGE_MT_REFERENCE(WindowHandle);
}
