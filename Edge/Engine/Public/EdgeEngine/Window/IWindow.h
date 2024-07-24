#pragma once

#include "EdgeEngine/Core/HashedType.h"
#include "EdgeEngine/Core/Math/Vector.h"

#include "EdgeEngine/Event/IEventController.h"

namespace Edge
{
	using WindowSize = UInt16Vector2;
	constexpr WindowSize DefaultWindowSize = UInt16Vector2Zero;

	struct WindowArea final
	{
		using ValueType = uint16_t;
		using VectorValueType = Vector4Base<ValueType>;

		union
		{
			VectorValueType m_vector;

			struct
			{
				ValueType m_top;
				ValueType m_bottom;
				ValueType m_right;
				ValueType m_left;
			};
		};

		constexpr WindowArea() = default;
		constexpr WindowArea(const VectorValueType& vector)
			: m_vector(vector) {}
		constexpr WindowArea(ValueType top, ValueType bottom, ValueType right, ValueType left)
			: m_top(top), m_bottom(bottom), m_right(right), m_left(left) {}

		constexpr WindowArea(const WindowArea& area)
			: m_vector(area.m_vector) {}

		WindowArea& operator=(const WindowArea& area)
		{
			m_vector = area.m_vector;
			return *this;
		}
	};

	constexpr WindowArea DefaultWindowArea = WindowArea(0, 0, 0, 0);

	using WindowID = uint32_t;
	constexpr WindowID InvalidWindowID = 0;

	using WindowType = HashedType::Type;

	class IWindow : public HashedType
	{
	public:
		IWindow() = default;
		virtual ~IWindow() = default;

		virtual bool init(const char* title, const WindowSize& size) = 0;
		virtual void release() = 0;

		virtual bool isValid() const = 0;

		virtual void show() = 0;
		virtual void hide() = 0;
		virtual bool isShown() const = 0;

		virtual bool isStable() const = 0;

		virtual const WindowSize& getWindowSize() const = 0;
		virtual const WindowSize& getClientAreaSize() const = 0;
		virtual const WindowArea& getCutoutsArea() const = 0;

		virtual WindowID getID() const = 0;

		virtual InstancedEventID getSizeEventID() const = 0;

		virtual void* getNativeHandle() const = 0;

		virtual WindowType getType() const = 0;
	};

}

#define EDGE_WINDOW_TYPE(WINDOW_TYPE) EDGE_HASH_TYPE(#WINDOW_TYPE, Edge::WindowType, Window)