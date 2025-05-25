namespace Edge
{
	template <typename T>
	ComputeVector4Base<T>& ComputeVector4Base<T>::operator=(const ComputeVector4Base<T>& vector)
	{
		m_vector = vector.m_vector;

		return *this;
	}

	template <typename T>
	ComputeVector4Base<T>& ComputeVector4Base<T>::operator+=(const ComputeVector4Base<T>& vector)
	{
		m_vector.m_x += vector.m_vector.m_x;
		m_vector.m_y += vector.m_vector.m_y;
		m_vector.m_z += vector.m_vector.m_z;
		m_vector.m_w += vector.m_vector.m_w;

		return *this;
	}

	template <typename T>
	ComputeVector4Base<T>& ComputeVector4Base<T>::operator-=(const ComputeVector4Base<T>& vector)
	{
		m_vector.m_x -= vector.m_vector.m_x;
		m_vector.m_y -= vector.m_vector.m_y;
		m_vector.m_z -= vector.m_vector.m_z;
		m_vector.m_w -= vector.m_vector.m_w;

		return *this;
	}

	template <typename T>
	ComputeVector4Base<T>& ComputeVector4Base<T>::operator*=(T value)
	{
		m_vector.m_x *= value;
		m_vector.m_y *= value;
		m_vector.m_z *= value;
		m_vector.m_w *= value;

		return *this;
	}

	template <typename T>
	ComputeVector4Base<T>& ComputeVector4Base<T>::operator/=(T value)
	{
		EDGE_ASSERT(std::abs(value) > Math::Epsilon);

		m_vector.m_x /= value;
		m_vector.m_y /= value;
		m_vector.m_z /= value;
		m_vector.m_w /= value;

		return *this;
	}

	template <typename T>
	bool ComputeVector4Base<T>::operator==(const ComputeVector4Base<T>& vector) const
	{
		return isEqual(vector);
	}

	template <typename T>
	bool ComputeVector4Base<T>::operator!=(const ComputeVector4Base<T>& vector) const
	{
		return !operator==(vector);
	}

	template <typename T>
	FloatVector4 ComputeVector4Base<T>::getFloatVector4() const
	{
		FloatVector4 result;
		getFloatVector4(result);

		return result;
	}

	template <typename T>
	void ComputeVector4Base<T>::getFloatVector4(FloatVector4& out) const
	{
		out = FloatVector4(float(m_vector.m_x), float(m_vector.m_y), float(m_vector.m_z), float(m_vector.m_w));
	}

	template <typename T>
	T ComputeVector4Base<T>::getLength() const
	{
		return sqrt(getLengthSqr());
	}

	template <typename T>
	T ComputeVector4Base<T>::getLengthSqr() const
	{
		return dot(*this);
	}

	template <typename T>
	ComputeVector4Base<T>& ComputeVector4Base<T>::negate()
	{
		m_vector.m_x = -m_vector.m_x;
		m_vector.m_y = -m_vector.m_y;
		m_vector.m_z = -m_vector.m_z;
		m_vector.m_w = -m_vector.m_w;

		return *this;
	}

	template <typename T>
	ComputeVector4Base<T> ComputeVector4Base<T>::getUnit() const
	{
		ComputeVector4Base<T> vector(*this);
		return vector.normalize();
	}

	template <typename T>
	ComputeVector4Base<T>& ComputeVector4Base<T>::normalize()
	{
		const T length = getLength();
		if (length <= Math::TypedEpsilon<T>())
		{
			return *this;
		}

		return operator/=(length);
	}

	template <typename T>
	T ComputeVector4Base<T>::dot(const ComputeVector4Base<T>& vector) const
	{
		return
			m_vector.m_x * vector.m_vector.m_x +
			m_vector.m_y * vector.m_vector.m_y +
			m_vector.m_z * vector.m_vector.m_z +
			m_vector.m_w * vector.m_vector.m_w;
	}

	template <typename T>
	bool ComputeVector4Base<T>::isEqual(const ComputeVector4Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxEqual(m_vector.m_y, vector.m_vector.m_y, epsilon) &&
			Math::IsApproxEqual(m_vector.m_z, vector.m_vector.m_z, epsilon) &&
			Math::IsApproxEqual(m_vector.m_w, vector.m_vector.m_w, epsilon);
	}

	template <typename T>
	bool ComputeVector4Base<T>::isLess(const ComputeVector4Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxLess(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxLess(m_vector.m_y, vector.m_vector.m_y, epsilon) &&
			Math::IsApproxLess(m_vector.m_z, vector.m_vector.m_z, epsilon) &&
			Math::IsApproxLess(m_vector.m_w, vector.m_vector.m_w, epsilon);
	}

	template <typename T>
	bool ComputeVector4Base<T>::isLessOrEqual(const ComputeVector4Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxLessOrEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxLessOrEqual(m_vector.m_y, vector.m_vector.m_y, epsilon) &&
			Math::IsApproxLessOrEqual(m_vector.m_z, vector.m_vector.m_z, epsilon) &&
			Math::IsApproxLessOrEqual(m_vector.m_w, vector.m_vector.m_w, epsilon);
	}

	template <typename T>
	bool ComputeVector4Base<T>::isGreater(const ComputeVector4Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxGreater(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxGreater(m_vector.m_y, vector.m_vector.m_y, epsilon) &&
			Math::IsApproxGreater(m_vector.m_z, vector.m_vector.m_z, epsilon) &&
			Math::IsApproxGreater(m_vector.m_w, vector.m_vector.m_w, epsilon);
	}

	template <typename T>
	bool ComputeVector4Base<T>::isGreaterOrEqual(const ComputeVector4Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxGreaterOrEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxGreaterOrEqual(m_vector.m_y, vector.m_vector.m_y, epsilon) &&
			Math::IsApproxGreaterOrEqual(m_vector.m_z, vector.m_vector.m_z, epsilon) &&
			Math::IsApproxGreaterOrEqual(m_vector.m_w, vector.m_vector.m_w, epsilon);
	}

	template <typename T>
	bool ComputeVector4Base<T>::isUnit() const
	{
		return Math::IsApproxEqual(getLengthSqr(), T(1.0));
	}

	template <typename T>
	bool ComputeVector4Base<T>::isZero() const
	{
		return Math::IsApproxEqual(getLengthSqr(), T(0.0));
	}

	template <typename T>
	ComputeVector4Base<T> operator+(const ComputeVector4Base<T>& vector1, const ComputeVector4Base<T>& vector2)
	{
		ComputeVector4Base<T> result(vector1);
		return result += vector2;
	}

	template <typename T>
	ComputeVector4Base<T> operator-(const ComputeVector4Base<T>& vector1, const ComputeVector4Base<T>& vector2)
	{
		ComputeVector4Base<T> result(vector1);
		return result -= vector2;
	}

	template <typename T>
	ComputeVector4Base<T> operator-(const ComputeVector4Base<T>& vector)
	{
		ComputeVector4Base<T> result(vector);
		return result.negate();
	}

	template <typename T>
	ComputeVector4Base<T> operator*(const ComputeVector4Base<T>& vector, T value)
	{
		ComputeVector4Base<T> result(vector);
		return result *= value;
	}

	template <typename T>
	ComputeVector4Base<T> operator*(T value, const ComputeVector4Base<T>& vector)
	{
		return operator*(vector, value);
	}

	template <typename T>
	ComputeVector4Base<T> operator/(const ComputeVector4Base<T>& vector, T value)
	{
		ComputeVector4Base<T> result(vector);
		return result /= value;
	}

	template <typename T>
	ComputeVector4Base<T> operator/(T value, const ComputeVector4Base<T>& vector)
	{
		return operator/(vector, value);
	}

	template <typename T>
	ComputeVector4Base<T> ComputeVector4FromPoint(const ComputeVector3Base<T>& vector)
	{
		return ComputeVector4Base<T>(vector, T(1.0));
	}

	template <typename T>
	T DotComputeVector4(const ComputeVector4Base<T>& vector1, const ComputeVector4Base<T>& vector2)
	{
		ComputeVector4Base<T> result(vector1);
		return result.dot(vector2);
	}
}