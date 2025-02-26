#pragma once

#include <type_traits>
#include <vector>

namespace Edge
{
	template <typename T>
	class DynamicVectorBase final
	{
	public:
		using ValueType = T;
		using ValueContainer = std::vector<ValueType>;

		static_assert(std::is_arithmetic_v<ValueType>);

		static constexpr ValueType DefaultValue = 0;

	private:
		ValueContainer m_values;

	public:
		DynamicVectorBase() = default;
		DynamicVectorBase(size_t dimension);
		DynamicVectorBase(ValueContainer&& values);
		DynamicVectorBase(const DynamicVectorBase& vector);
		DynamicVectorBase(DynamicVectorBase&& vector);

		DynamicVectorBase& operator=(const DynamicVectorBase& vector);
		DynamicVectorBase& operator=(DynamicVectorBase&& vector);
		ValueType operator[](size_t index) const;
		ValueType& operator[](size_t index);

		ValueType getElement(size_t index) const;
		ValueType& getElement(size_t index);

		void setElement(size_t index, ValueType value);

		void reset();

		uint32_t getElementCount() const;
	};

	using FloatDynamicVector = DynamicVectorBase<float>;
}

#include "DynamicVector.hpp"