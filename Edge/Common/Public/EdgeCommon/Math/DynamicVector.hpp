#pragma once

#include "EdgeCommon/Assert/AssertCore.h"

namespace Edge
{
#pragma region DynamicVectorBase
	template <typename T>
	DynamicVectorBase<T>::DynamicVectorBase(size_t dimension)
		: m_values(dimension)
	{
		EDGE_ASSERT(dimension > 0);
	}

	template <typename T>
	DynamicVectorBase<T>::DynamicVectorBase(ValueContainer&& values)
		: m_values(std::move(values))
	{
		EDGE_ASSERT(getElementCount() > 0);
	}


	template <typename T>
	DynamicVectorBase<T>::DynamicVectorBase(const DynamicVectorBase& vector)
		: m_values(vector.m_values)
	{
		reset();
	}

	template <typename T>
	DynamicVectorBase<T>::DynamicVectorBase(DynamicVectorBase&& vector)
		: m_values(std::move(vector.m_values))
	{
	}

	template <typename T>
	DynamicVectorBase<T>& DynamicVectorBase<T>::operator=(const DynamicVectorBase& vector)
	{
		m_values = vector.m_values;
		return *this;
	}

	template <typename T>
	DynamicVectorBase<T>& DynamicVectorBase<T>::operator=(DynamicVectorBase&& vector)
	{
		m_values = std::move(vector.m_values);
		return *this;
	}

	template <typename T>
	typename DynamicVectorBase<T>::ValueType DynamicVectorBase<T>::operator[](size_t index) const
	{
		return getElement(index);
	}


	template <typename T>
	typename DynamicVectorBase<T>::ValueType& DynamicVectorBase<T>::operator[](size_t index)
	{
		return getElement(index);
	}

	template <typename T>
	typename DynamicVectorBase<T>::ValueType DynamicVectorBase<T>::getElement(size_t index) const
	{
		//EDGE_ASSERT(index < m_values.size());
		return m_values[index];
	}

	template <typename T>
	typename DynamicVectorBase<T>::ValueType& DynamicVectorBase<T>::getElement(size_t index)
	{
		//EDGE_ASSERT(index < m_values.size());
		return m_values[index];
	}

	template <typename T>
	void DynamicVectorBase<T>::setElement(size_t index, ValueType value)
	{
		ValueType& element = getElement(index);
		element = value;
	}

	template <typename T>
	void DynamicVectorBase<T>::reset()
	{
		std::fill(m_values.begin(), m_values.end(), DefaultValue);
	}

	template <typename T>
	uint32_t DynamicVectorBase<T>::getElementCount() const
	{
		return m_values.size();
	}

#pragma endregion
}
