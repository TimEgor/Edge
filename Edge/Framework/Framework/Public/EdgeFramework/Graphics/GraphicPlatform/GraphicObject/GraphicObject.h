#pragma once

namespace Edge
{
	class GraphicObject
	{
	public:
		GraphicObject() = default;
		virtual ~GraphicObject() = default;

		virtual void* getNativeHandle() const = 0;

		template<typename T>
		T* getNativeHandleCast() const { return reinterpret_cast<T*>(getNativeHandle()); }

		virtual void setName(const char* name) = 0;
	};
}