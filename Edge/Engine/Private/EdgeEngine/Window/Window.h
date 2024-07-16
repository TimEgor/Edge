#pragma once

#include "TinySimCommon/Core/HashedType.h"
#include "TinySimCommon/Math/Vector.h"
#include "TinySimCommon/Multithreading/Mutex.h"

#include "TinySimFramework/EventController/EventController.h"

namespace TS
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

	class Window : public HashedType
	{
	protected:
		mutable SharedMutex m_mutex;

		WindowSize m_windowSize = DefaultWindowSize;
		WindowSize m_clientAreaSize = DefaultWindowSize;
		WindowArea m_cutoutsArea = DefaultWindowArea;

		const WindowID m_windowID = InvalidWindowID;

		InstancedEventID m_sizeEventID = InvalidInstancedEventID;

		bool m_isShown = false;

		bool initWindowInstancedEvents();
		void releaseWindowInstancedEvents();

		void onSizeChanged();

	public:
		Window(WindowID windowID)
			: m_windowID(windowID) {}
		virtual ~Window() = default;

		virtual bool init(const char* title, const WindowSize& size) = 0;
		virtual void release() = 0;

		virtual bool isValid() const = 0;

		virtual void show() = 0;
		virtual void hide() = 0;
		bool isShown() const;

		virtual bool isStable() const = 0;

		const WindowSize& getWindowSize() const;
		const WindowSize& getClientAreaSize() const;
		const WindowArea& getCutoutsArea() const;

		WindowID getID() const { return m_windowID; }

		InstancedEventID getSizeEventID() const;

		virtual void* getNativeHandle() const = 0;

		virtual WindowType getType() const = 0;
	};

}

#define TS_WINDOW_TYPE(WINDOW_TYPE) TS_HASH_TYPE(#WINDOW_TYPE, TS::WindowType, Window)