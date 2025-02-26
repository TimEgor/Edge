#pragma once

#include "EdgeCommon/Assert/AssertCore.h"

namespace Edge
{
#pragma region Vector2Base
	template <typename T>
	Vector2Base<T>& Vector2Base<T>::operator=(const Vector2Base& vector)
	{
		m_x = vector.m_x;
		m_y = vector.m_y;

		return *this;
	}

	template <typename T>
	typename Vector2Base<T>::ValueType Vector2Base<T>::operator[](size_t index) const
	{
		return getElement(index);
	}

	template <typename T>
	typename Vector2Base<T>::ValueType& Vector2Base<T>::operator[](size_t index)
	{
		return getElement(index);
	}

	template <typename T>
	typename Vector2Base<T>::ValueType Vector2Base<T>::getElement(size_t index) const
	{
		EDGE_ASSERT(index < 2);
		return m_values[index];
	}

	template <typename T>
	typename Vector2Base<T>::ValueType& Vector2Base<T>::getElement(size_t index)
	{
		EDGE_ASSERT(index < 2);
		return m_values[index];
	}

	template <typename T>
	void Vector2Base<T>::setElement(size_t index, ValueType value)
	{
		ValueType& element = getElement(index);
		element = value;
	}
#pragma endregion

#pragma region Vector3Base
	template <typename T>
	Vector3Base<T>& Vector3Base<T>::operator=(const Vector2Base<ValueType>& vector)
	{
		m_x = vector.m_x;
		m_y = vector.m_y;
		m_z = vector.DefaultValue;

		return *this;
	}

	template <typename T>
	Vector3Base<T>& Vector3Base<T>::operator=(const Vector3Base& vector)
	{
		m_x = vector.m_x;
		m_y = vector.m_y;
		m_z = vector.m_z;

		return *this;
	}

	template <typename T>
	typename Vector3Base<T>::ValueType Vector3Base<T>::operator[](size_t index) const
	{
		return getElement(index);
	}

	template <typename T>
	typename Vector3Base<T>::ValueType& Vector3Base<T>::operator[](size_t index)
	{
		return getElement(index);
	}

	template <typename T>
	typename Vector3Base<T>::ValueType Vector3Base<T>::getElement(size_t index) const
	{
		EDGE_ASSERT(index < 3);
		return m_values[index];
	}

	template <typename T>
	typename Vector3Base<T>::ValueType& Vector3Base<T>::getElement(size_t index)
	{
		EDGE_ASSERT(index < 3);
		return m_values[index];
	}

	template <typename T>
	void Vector3Base<T>::setElement(size_t index, ValueType value)
	{
		ValueType& element = getElement(index);
		element = value;
	}
#pragma endregion

#pragma region Vector4Base
	template <typename T>
	Vector4Base<T>& Vector4Base<T>::operator=(const Vector2Base<ValueType>& vector)
	{
		m_x = vector.m_x;
		m_y = vector.m_y;
		m_z = DefaultValue;
		m_w = DefaultValue;

		return *this;
	}

	template <typename T>
	Vector4Base<T>& Vector4Base<T>::operator=(const Vector3Base<ValueType>& vector)
	{
		m_x = vector.m_x;
		m_y = vector.m_y;
		m_z = vector.m_z;
		m_w = DefaultValue;

		return *this;
	}

	template <typename T>
	Vector4Base<T>& Vector4Base<T>::operator=(const Vector4Base& vector)
	{
		m_x = vector.m_x;
		m_y = vector.m_y;
		m_z = vector.m_z;
		m_w = vector.m_w;

		return *this;
	}

	template <typename T>
	typename Vector4Base<T>::ValueType Vector4Base<T>::operator[](size_t index) const
	{
		return getElement(index);
	}

	template <typename T>
	typename Vector4Base<T>::ValueType& Vector4Base<T>::operator[](size_t index)
	{
		return getElement(index);
	}

	template <typename T>
	typename Vector4Base<T>::ValueType Vector4Base<T>::getElement(size_t index) const
	{
		EDGE_ASSERT(index < 4);
		return m_values[index];
	}

	template <typename T>
	typename Vector4Base<T>::ValueType& Vector4Base<T>::getElement(size_t index)
	{
		EDGE_ASSERT(index < 4);
		return m_values[index];
	}

	template <typename T>
	void Vector4Base<T>::setElement(size_t index, ValueType value)
	{
		ValueType& element = getElement(index);
		element = value;
	}
#pragma endregion
}
