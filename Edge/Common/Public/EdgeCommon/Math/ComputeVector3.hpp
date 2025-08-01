namespace Edge
{
	template <typename T>
	ComputeVector3Base<T>& ComputeVector3Base<T>::operator=(const ComputeVector3Base<T>& vector)
	{
		m_vector = vector.m_vector;

		return *this;
	}

	template <typename T>
	ComputeVector3Base<T>& ComputeVector3Base<T>::operator+=(const ComputeVector3Base<T>& vector)
	{
		m_vector.m_x += vector.m_vector.m_x;
		m_vector.m_y += vector.m_vector.m_y;
		m_vector.m_z += vector.m_vector.m_z;

		return *this;
	}

	template <typename T>
	ComputeVector3Base<T>& ComputeVector3Base<T>::operator-=(const ComputeVector3Base<T>& vector)
	{
		m_vector.m_x -= vector.m_vector.m_x;
		m_vector.m_y -= vector.m_vector.m_y;
		m_vector.m_z -= vector.m_vector.m_z;

		return *this;
	}

	template <typename T>
	ComputeVector3Base<T>& ComputeVector3Base<T>::operator*=(T value)
	{
		m_vector.m_x *= value;
		m_vector.m_y *= value;
		m_vector.m_z *= value;

		return *this;
	}

	template <typename T>
	ComputeVector3Base<T>& ComputeVector3Base<T>::operator/=(T value)
	{
		EDGE_ASSERT(std::abs(value) > Math::TypedEpsilon<T>());

		m_vector.m_x /= value;
		m_vector.m_y /= value;
		m_vector.m_z /= value;

		return *this;
	}

	template <typename T>
	bool ComputeVector3Base<T>::operator==(const ComputeVector3Base<T>& vector) const
	{
		return isEqual(vector);
	}

	template <typename T>
	bool ComputeVector3Base<T>::operator!=(const ComputeVector3Base<T>& vector) const
	{
		return !operator==(vector);
	}

	template <typename T>
	FloatVector3 ComputeVector3Base<T>::getFloatVector3() const
	{
		FloatVector3 result;
		getFloatVector3(result);

		return result;
	}

	template <typename T>
	void ComputeVector3Base<T>::getFloatVector3(FloatVector3& out) const
	{
		out = FloatVector3(float(m_vector.m_x), float(m_vector.m_y), float(m_vector.m_z));
	}

	template <typename T>
	T ComputeVector3Base<T>::getLength() const
	{
		return sqrt(getLengthSqr());
	}

	template <typename T>
	T ComputeVector3Base<T>::getLengthSqr() const
	{
		return dot(*this);
	}

	template <typename T>
	ComputeVector3Base<T>& ComputeVector3Base<T>::negate()
	{
		m_vector.m_x = -m_vector.m_x;
		m_vector.m_y = -m_vector.m_y;
		m_vector.m_z = -m_vector.m_z;

		return *this;
	}

	template <typename T>
	ComputeVector3Base<T>& ComputeVector3Base<T>::computeReciprocal()
	{
		m_vector.m_x = T(1.0) / m_vector.m_x;
		m_vector.m_y = T(1.0) / m_vector.m_y;
		m_vector.m_z = T(1.0) / m_vector.m_z;

		return *this;
	}

	template <typename T>
	ComputeVector3Base<T>& ComputeVector3Base<T>::multiplyElements(const ComputeVector3Base<T>& vector)
	{
		m_vector.m_x *= vector.m_vector.m_x;
		m_vector.m_y *= vector.m_vector.m_y;
		m_vector.m_z *= vector.m_vector.m_z;

		return *this;
	}

	template <typename T>
	ComputeVector3Base<T> ComputeVector3Base<T>::getUnit() const
	{
		ComputeVector3Base<T> result;
		getUnit(result);

		return result;
	}

	template <typename T>
	void ComputeVector3Base<T>::getUnit(ComputeVector3Base<T>& out) const
	{
		ComputeVector3Base<T> result(*this);
		out = result.normalize();
	}

	template <typename T>
	ComputeVector3Base<T>& ComputeVector3Base<T>::normalize()
	{
		const T length = getLength();
		if (length <= Math::TypedEpsilon<T>())
		{
			return *this;
		}

		return operator/=(length);
	}

	template <typename T>
	ComputeVector3Base<T> ComputeVector3Base<T>::getOrthogonal() const
	{
		ComputeVector3Base<T> result;
		getOrthogonal(result);

		return result;
	}

	template <typename T>
	void ComputeVector3Base<T>::getOrthogonal(ComputeVector3Base<T>& out) const
	{
		if (abs(m_vector.m_x) > abs(m_vector.m_y))
		{
			out.m_vector.m_x = m_vector.m_z;
			out.m_vector.m_y = T(0.0);
			out.m_vector.m_z = -m_vector.m_x;
		}
		else
		{
			out.m_vector.m_x = T(0.0);
			out.m_vector.m_y = m_vector.m_z;
			out.m_vector.m_z = -m_vector.m_y;
		}
	}

	template <typename T>
	ComputeVector3Base<T> ComputeVector3Base<T>::getAbs() const
	{
		ComputeVector3Base<T> result;
		getAbs(result);

		return result;
	}

	template <typename T>
	void ComputeVector3Base<T>::getAbs(ComputeVector3Base<T>& out) const
	{
		out.m_vector.m_x = abs(m_vector.m_x);
		out.m_vector.m_y = abs(m_vector.m_y);
		out.m_vector.m_z = abs(m_vector.m_z);
	}

	template <typename T>
	uint32_t ComputeVector3Base<T>::getMinElementIndex() const
	{
		return
			getX() < getY() ?
			getX() < getZ() ? 0 : 2 :
			getY() < getZ() ? 1 : 2;
	}

	template <typename T>
	uint32_t ComputeVector3Base<T>::getMaxElementIndex() const
	{
		return
			getX() > getY() ?
			getX() > getZ() ? 0 : 2 :
			getY() > getZ() ? 1 : 2;
	}

	template <typename T>
	T ComputeVector3Base<T>::dot(const ComputeVector3Base<T>& vector) const
	{
		return
			m_vector.m_x * vector.m_vector.m_x +
			m_vector.m_y * vector.m_vector.m_y +
			m_vector.m_z * vector.m_vector.m_z;
	}

	template <typename T>
	ComputeVector3Base<T> ComputeVector3Base<T>::cross(const ComputeVector3Base<T>& vector) const
	{
		return ComputeVector3Base<T>(
			m_vector.m_y * vector.m_vector.m_z - m_vector.m_z * vector.m_vector.m_y,
			m_vector.m_z * vector.m_vector.m_x - m_vector.m_x * vector.m_vector.m_z,
			m_vector.m_x * vector.m_vector.m_y - m_vector.m_y * vector.m_vector.m_x);
	}

	template <typename T>
	ComputeVector3Base<T> ComputeVector3Base<T>::swizzle(uint32_t index1, uint32_t index2, uint32_t index3) const
	{
		return ComputeVector3Base<T>(getElement(index1), getElement(index2), getElement(index3));
	}

	template <typename T>
	bool ComputeVector3Base<T>::isEqual(const ComputeVector3Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxEqual(m_vector.m_y, vector.m_vector.m_y, epsilon) &&
			Math::IsApproxEqual(m_vector.m_z, vector.m_vector.m_z, epsilon);
	}

	template <typename T>
	bool ComputeVector3Base<T>::isLess(const ComputeVector3Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxLess(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxLess(m_vector.m_y, vector.m_vector.m_y, epsilon) &&
			Math::IsApproxLess(m_vector.m_z, vector.m_vector.m_z, epsilon);
	}

	template <typename T>
	bool ComputeVector3Base<T>::isLessOrEqual(const ComputeVector3Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxLessOrEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxLessOrEqual(m_vector.m_y, vector.m_vector.m_y, epsilon) &&
			Math::IsApproxLessOrEqual(m_vector.m_z, vector.m_vector.m_z, epsilon);
	}

	template <typename T>
	bool ComputeVector3Base<T>::isGreater(const ComputeVector3Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxGreater(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxGreater(m_vector.m_y, vector.m_vector.m_y, epsilon) &&
			Math::IsApproxGreater(m_vector.m_z, vector.m_vector.m_z, epsilon);
	}

	template <typename T>
	bool ComputeVector3Base<T>::isGreaterOrEqual(const ComputeVector3Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxGreaterOrEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) &&
			Math::IsApproxGreaterOrEqual(m_vector.m_y, vector.m_vector.m_y, epsilon) &&
			Math::IsApproxGreaterOrEqual(m_vector.m_z, vector.m_vector.m_z, epsilon);
	}

	template <typename T>
	bool ComputeVector3Base<T>::isAnyLess(const ComputeVector3Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxLess(m_vector.m_x, vector.m_vector.m_x, epsilon) ||
			Math::IsApproxLess(m_vector.m_y, vector.m_vector.m_y, epsilon) ||
			Math::IsApproxLess(m_vector.m_z, vector.m_vector.m_z, epsilon);
	}

	template <typename T>
	bool ComputeVector3Base<T>::isAnyLessOrEqual(const ComputeVector3Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxLessOrEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) ||
			Math::IsApproxLessOrEqual(m_vector.m_y, vector.m_vector.m_y, epsilon) ||
			Math::IsApproxLessOrEqual(m_vector.m_z, vector.m_vector.m_z, epsilon);
	}

	template <typename T>
	bool ComputeVector3Base<T>::isAnyGreater(const ComputeVector3Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxGreater(m_vector.m_x, vector.m_vector.m_x, epsilon) ||
			Math::IsApproxGreater(m_vector.m_y, vector.m_vector.m_y, epsilon) ||
			Math::IsApproxGreater(m_vector.m_z, vector.m_vector.m_z, epsilon);
	}

	template <typename T>
	bool ComputeVector3Base<T>::isAnyGreaterOrEqual(const ComputeVector3Base<T>& vector, T epsilon) const
	{
		return
			Math::IsApproxGreaterOrEqual(m_vector.m_x, vector.m_vector.m_x, epsilon) ||
			Math::IsApproxGreaterOrEqual(m_vector.m_y, vector.m_vector.m_y, epsilon) ||
			Math::IsApproxGreaterOrEqual(m_vector.m_z, vector.m_vector.m_z, epsilon);
	}

	template <typename T>
	bool ComputeVector3Base<T>::isUnit() const
	{
		return Math::IsApproxEqual(getLengthSqr(), T(1.0));
	}

	template <typename T>
	bool ComputeVector3Base<T>::isZero() const
	{
		return Math::IsApproxEqual(getLengthSqr(), T(0.0));
	}

	template <typename T>
	ComputeVector3Base<T> operator+(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2)
	{
		ComputeVector3Base<T> result(vector1);
		return result += vector2;
	}

	template <typename T>
	ComputeVector3Base<T> operator-(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2)
	{
		ComputeVector3Base<T> result(vector1);
		return result -= vector2;
	}

	template <typename T>
	ComputeVector3Base<T> operator-(const ComputeVector3Base<T>& vector)
	{
		ComputeVector3Base<T> result(vector);
		return result.negate();
	}

	template <typename T>
	ComputeVector3Base<T> operator*(const ComputeVector3Base<T>& vector, T value)
	{
		ComputeVector3Base<T> result(vector);
		return result *= value;
	}

	template <typename T>
	ComputeVector3Base<T> operator*(T value, const ComputeVector3Base<T>& vector)
	{
		return operator*(vector, value);
	}

	template <typename T>
	ComputeVector3Base<T> operator/(const ComputeVector3Base<T>& vector, T value)
	{
		ComputeVector3Base<T> result(vector);
		return result /= value;
	}


	template <typename T>
	ComputeVector3Base<T> operator/(T value, const ComputeVector3Base<T>& vector)
	{
		return operator/(vector, value);
	}

	template <typename T>
	T DotComputeVector3(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2)
	{
		ComputeVector3Base<T> result(vector1);
		return result.dot(vector2);
	}

	template <typename T>
	ComputeVector3Base<T> CrossComputeVector3(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2)
	{
		return vector1.cross(vector2);
	}

	template <typename T>
	ComputeVector3Base<T> NegateComputeVector3(const ComputeVector3Base<T>& vector)
	{
		ComputeVector3Base<T> result(vector);
		return result.negate();
	}

	template <typename T>
	ComputeVector3Base<T> ComputeReciprocalComputeVector3(const ComputeVector3Base<T>& vector)
	{
		ComputeVector3Base<T> result(vector);
		return result.computeReciprocal();
	}

	template <typename T>
	ComputeVector3Base<T> NormalizeComputeVector3(const ComputeVector3Base<T>& vector)
	{
		ComputeVector3Base<T> result(vector);
		return result.normalize();
	}

	template <typename T>
	T LengthComputeVector3(const ComputeVector3Base<T>& vector)
	{
		return vector.getLength();
	}

	template <typename T>
	T LengthSqrComputeVector3(const ComputeVector3Base<T>& vector)
	{
		return vector.getLengthSqr();
	}

	template <typename T>
	ComputeVector3Base<T> MultiplyComputeVector3Elements(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2)
	{
		ComputeVector3Base<T> result(vector1);
		return result.multiplyElements(vector2);
	}

	template <typename T>
	ComputeVector3Base<T> MinComputeVector3(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2)
	{
		return ComputeVector3Base<T>(
			std::min(vector1.getX(), vector2.getX()),
			std::min(vector1.getY(), vector2.getY()),
			std::min(vector1.getZ(), vector2.getZ())
		);
	}

	template <typename T>
	ComputeVector3Base<T> MaxComputeVector3(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2)
	{
		return ComputeVector3Base<T>(
			std::max(vector1.getX(), vector2.getX()),
			std::max(vector1.getY(), vector2.getY()),
			std::max(vector1.getZ(), vector2.getZ())
		);
	}
}