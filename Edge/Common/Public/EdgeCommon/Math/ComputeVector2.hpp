namespace Edge
{
	template <typename T>
	ComputeVector2Base<T>& ComputeVector2Base<T>::operator=(const ComputeVector2Base& vector)
	{
		m_vector = vector.m_vector;

		return *this;
	}

	template <typename T>
	ComputeVector2Base<T>& ComputeVector2Base<T>::operator+=(const ComputeVector2Base& vector)
	{
		m_vector.m_x += vector.m_vector.m_x;
		m_vector.m_y += vector.m_vector.m_y;

		return *this;
	}

	template <typename T>
	ComputeVector2Base<T>& ComputeVector2Base<T>::operator-=(const ComputeVector2Base& vector)
	{
		m_vector.m_x -= vector.m_vector.m_x;
		m_vector.m_y -= vector.m_vector.m_y;

		return *this;
	}

	template <typename T>
	ComputeVector2Base<T>& ComputeVector2Base<T>::operator*=(T value)
	{
		m_vector.m_x *= value;
		m_vector.m_y *= value;

		return *this;
	}

	template <typename T>
	ComputeVector2Base<T>& ComputeVector2Base<T>::operator/=(T value)
	{
		EDGE_ASSERT(std::abs(value) > Math::TypedEpsilon<T>());

		m_vector.m_x /= value;
		m_vector.m_y /= value;

		return *this;
	}

	template <typename T>
	bool ComputeVector2Base<T>::operator==(const ComputeVector2Base<T>& vector) const
	{
		return isEqual(vector);
	}

	template <typename T>
	bool ComputeVector2Base<T>::operator!=(const ComputeVector2Base<T>& vector) const
	{
		return !operator==(vector);
	}

	template <typename T>
	FloatVector2 ComputeVector2Base<T>::getFloatVector2() const
	{
		FloatVector2 result;
		getFloatVector2(result);

		return result;
	}

	template <typename T>
	void ComputeVector2Base<T>::getFloatVector2(FloatVector2& out) const
	{
		out = FloatVector2(float(m_vector.m_x), float(m_vector.m_y));
	}

	template <typename T>
	T ComputeVector2Base<T>::getLength() const
	{
		return sqrt(getLengthSqr());
	}

	template <typename T>
	T ComputeVector2Base<T>::getLengthSqr() const
	{
		return dot(*this);
	}

	template <typename T>
	ComputeVector2Base<T>& ComputeVector2Base<T>::negate()
	{
		m_vector.m_x = -m_vector.m_x;
		m_vector.m_y = -m_vector.m_y;

		return *this;
	}

	template <typename T>
	ComputeVector2Base<T> ComputeVector2Base<T>::getUnit() const
	{
		ComputeVector2Base vector(*this);
		return vector.normalize();
	}

	template <typename T>
	ComputeVector2Base<T>& ComputeVector2Base<T>::normalize()
	{
		const T length = getLength();
		if (length <= Math::TypedEpsilon<T>())
		{
			return *this;
		}

		return operator/=(length);
	}

	template <typename T>
	T ComputeVector2Base<T>::dot(const ComputeVector2Base& vector) const
	{
		return
			m_vector.m_x * vector.m_vector.m_x +
			m_vector.m_y * vector.m_vector.m_y;
	}

	template <typename T>
	bool ComputeVector2Base<T>::isEqual(const ComputeVector2Base& vector, T epsilon) const
	{
		return
			Math::IsApproxEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxEqual(m_vector.m_y, vector.m_vector.m_y, epsilon);
	}

	template <typename T>
	bool ComputeVector2Base<T>::isLess(const ComputeVector2Base& vector, T epsilon) const
	{
		return
			Math::IsApproxLess(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxLess(m_vector.m_y, vector.m_vector.m_y, epsilon);
	}

	template <typename T>
	bool ComputeVector2Base<T>::isLessOrEqual(const ComputeVector2Base& vector, T epsilon) const
	{
		return
			Math::IsApproxLessOrEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxLessOrEqual(m_vector.m_y, vector.m_vector.m_y, epsilon);
	}

	template <typename T>
	bool ComputeVector2Base<T>::isGreater(const ComputeVector2Base& vector, T epsilon) const
	{
		return
			Math::IsApproxGreater(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxGreater(m_vector.m_y, vector.m_vector.m_y, epsilon);
	}

	template <typename T>
	bool ComputeVector2Base<T>::isGreaterOrEqual(const ComputeVector2Base& vector, T epsilon) const
	{
		return
			Math::IsApproxGreaterOrEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxGreaterOrEqual(m_vector.m_y, vector.m_vector.m_y, epsilon);
	}

	template <typename T>
	bool ComputeVector2Base<T>::isUnit() const
	{
		return Math::IsApproxEqual(getLengthSqr(), T(1.0));
	}

	template <typename T>
	bool ComputeVector2Base<T>::isZero() const
	{
		return Math::IsApproxEqual(getLengthSqr(), T(0.0));
	}

	template <typename T>
	ComputeVector2Base<T> operator+(const ComputeVector2Base<T>& vector1, const ComputeVector2Base<T>& vector2)
	{
		ComputeVector2Base<T> result(vector1);
		return result += vector2;
	}

	template <typename T>
	ComputeVector2Base<T> operator-(const ComputeVector2Base<T>& vector1, const ComputeVector2Base<T>& vector2)
	{
		ComputeVector2Base<T> result(vector1);
		return result -= vector2;
	}

	template <typename T>
	ComputeVector2Base<T> operator-(const ComputeVector2Base<T>& vector)
	{
		ComputeVector2Base<T> result(vector);
		return result.negate();
	}

	template <typename T>
	ComputeVector2Base<T> operator*(const ComputeVector2Base<T>& vector, T value)
	{
		ComputeVector2Base<T> result(vector);
		return result *= value;
	}

	template <typename T>
	ComputeVector2Base<T> operator*(T value, const ComputeVector2Base<T>& vector)
	{
		return operator*(vector, value);
	}

	template <typename T>
	ComputeVector2Base<T> operator/(const ComputeVector2Base<T>& vector, T value)
	{
		ComputeVector2Base result(vector);
		return result /= value;
	}

	template <typename T>
	ComputeVector2Base<T> operator/(T value, const ComputeVector2Base<T>& vector)
	{
		return operator/(vector, value);
	}

	template <typename T>
	T DotComputeVector2(const ComputeVector2Base<T>& vector1, const ComputeVector2Base<T>& vector2)
	{
		ComputeVector2Base<T> result(vector1);
		return result.dot(vector2);
	}
}
