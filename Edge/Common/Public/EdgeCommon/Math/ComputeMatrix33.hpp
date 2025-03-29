#pragma once

namespace Edge
{
	template <typename T>
	ComputeMatrix3x3Base<T>& ComputeMatrix3x3Base<T>::operator=(const ComputeMatrix3x3Base<T>& matrix)
	{
		m_matrix = matrix.m_matrix;

		return *this;
	}

	template <typename T>
	ComputeMatrix3x3Base<T>& ComputeMatrix3x3Base<T>::operator+=(const ComputeMatrix3x3Base<T>& matrix)
	{
		m_column1 += matrix.m_column1;
		m_column2 += matrix.m_column2;
		m_column3 += matrix.m_column3;

		return *this;
	}

	template <typename T>
	ComputeMatrix3x3Base<T>& ComputeMatrix3x3Base<T>::operator-=(const ComputeMatrix3x3Base<T>& matrix)
	{
		m_column1 -= matrix.m_column1;
		m_column2 -= matrix.m_column2;
		m_column3 -= matrix.m_column3;

		return *this;
	}

	template <typename T>
	ComputeMatrix3x3Base<T>& ComputeMatrix3x3Base<T>::operator*=(const ComputeMatrix3x3Base<T>& matrix)
	{
		ComputeMatrix3x3Base<T> result;

		result.m_matrix[0][0] = m_matrix[0][0] * matrix.m_matrix[0][0] + m_matrix[1][0] * matrix.m_matrix[0][1] + m_matrix[2][0] * matrix.m_matrix[0][2];
		result.m_matrix[0][1] = m_matrix[0][1] * matrix.m_matrix[0][0] + m_matrix[1][1] * matrix.m_matrix[0][1] + m_matrix[2][1] * matrix.m_matrix[0][2];
		result.m_matrix[0][2] = m_matrix[0][2] * matrix.m_matrix[0][0] + m_matrix[1][2] * matrix.m_matrix[0][1] + m_matrix[2][2] * matrix.m_matrix[0][2];

		result.m_matrix[1][0] = m_matrix[0][0] * matrix.m_matrix[1][0] + m_matrix[1][0] * matrix.m_matrix[1][1] + m_matrix[2][0] * matrix.m_matrix[1][2];
		result.m_matrix[1][1] = m_matrix[0][1] * matrix.m_matrix[1][0] + m_matrix[1][1] * matrix.m_matrix[1][1] + m_matrix[2][1] * matrix.m_matrix[1][2];
		result.m_matrix[1][2] = m_matrix[0][2] * matrix.m_matrix[1][0] + m_matrix[1][2] * matrix.m_matrix[1][1] + m_matrix[2][2] * matrix.m_matrix[1][2];

		result.m_matrix[2][0] = m_matrix[0][0] * matrix.m_matrix[2][0] + m_matrix[1][0] * matrix.m_matrix[2][1] + m_matrix[2][0] * matrix.m_matrix[2][2];
		result.m_matrix[2][1] = m_matrix[0][1] * matrix.m_matrix[2][0] + m_matrix[1][1] * matrix.m_matrix[2][1] + m_matrix[2][1] * matrix.m_matrix[2][2];
		result.m_matrix[2][2] = m_matrix[0][2] * matrix.m_matrix[2][0] + m_matrix[1][2] * matrix.m_matrix[2][1] + m_matrix[2][2] * matrix.m_matrix[2][2];

		*this = result;
		return *this;
	}

	template <typename T>
	ComputeMatrix3x3Base<T>& ComputeMatrix3x3Base<T>::operator*=(T value)
	{
		m_column1 *= value;
		m_column2 *= value;
		m_column3 *= value;

		return *this;
	}

	template <typename T>
	ComputeMatrix3x3Base<T>& ComputeMatrix3x3Base<T>::operator/=(T value)
	{
		m_column1 /= value;
		m_column2 /= value;
		m_column3 /= value;

		return *this;
	}

	template <typename T>
	bool ComputeMatrix3x3Base<T>::operator==(const ComputeMatrix3x3Base<T>& matrix) const
	{
		return isEqual(matrix);
	}

	template <typename T>
	bool ComputeMatrix3x3Base<T>::operator!=(const ComputeMatrix3x3Base<T>& matrix) const
	{
		return !isEqual(matrix);
	}

	template <typename T>
	FloatMatrix3x3 ComputeMatrix3x3Base<T>::getFloatMatrix3x3() const
	{
		FloatMatrix3x3 result;
		getFloatMatrix3x3(result);

		return result;
	}

	template <typename T>
	const ComputeVector3Base<T>& ComputeMatrix3x3Base<T>::getColumn(uint32_t index) const
	{
		EDGE_ASSERT(index < 3);
		return m_columns[index];
	}

	template <typename T>
	ComputeVector3Base<T>& ComputeMatrix3x3Base<T>::getColumn(uint32_t index)
	{
		EDGE_ASSERT(index < 3);
		return m_columns[index];
	}

	template <typename T>
	ComputeVector3Base<T> ComputeMatrix3x3Base<T>::getRow(uint32_t index) const
	{
		return ComputeVector3(m_matrix.m_rows[0][index], m_matrix.m_rows[1][index], m_matrix.m_rows[2][index]);
	}

	template <typename T>
	void ComputeMatrix3x3Base<T>::setColumn(uint32_t index, const ComputeVector3Base<T>& column)
	{
		EDGE_ASSERT(index < 3);
		m_columns[index] = column;
	}

	template <typename T>
	void ComputeMatrix3x3Base<T>::setRow(uint32_t index, const ComputeVector3Base<T>& row)
	{
		EDGE_ASSERT(index < 3);

		m_matrix.m_rows[0][index] = row.getX();
		m_matrix.m_rows[1][index] = row.getY();
		m_matrix.m_rows[2][index] = row.getZ();
	}

	template <typename T>
	ComputeMatrix3x3Base<T>& ComputeMatrix3x3Base<T>::negate()
	{
		m_column1 = -m_column1;
		m_column2 = -m_column2;
		m_column3 = -m_column3;

		return *this;
	}

	template <typename T>
	ComputeMatrix3x3Base<T>& ComputeMatrix3x3Base<T>::transpose()
	{
		ComputeMatrix3x3Base<T> transposed;

		transposed.setColumn(0, getRow(0));
		transposed.setColumn(1, getRow(1));
		transposed.setColumn(2, getRow(2));

		*this = transposed;
		return *this;
	}

	template <typename T>
	T ComputeMatrix3x3Base<T>::getDeterminant() const
	{
		return
			m_matrix[0][0] * (m_matrix[1][1] * m_matrix[2][2] - m_matrix[2][1] * m_matrix[1][2]) -
			m_matrix[0][1] * (m_matrix[1][0] * m_matrix[2][2] - m_matrix[2][0] * m_matrix[1][2]) +
			m_matrix[0][2] * (m_matrix[1][0] * m_matrix[2][1] - m_matrix[2][0] * m_matrix[1][1]);
	}

	template <typename T>
	ComputeMatrix3x3Base<T>& ComputeMatrix3x3Base<T>::invert()
	{
		const ComputeValueType determinant = getDeterminant();

		EDGE_ASSERT(abs(determinant) > Math::Epsilon);

		ComputeVector3Base<T> column0(
			(m_matrix[1][1] * m_matrix[2][2] - m_matrix[2][1] * m_matrix[1][2]),
			-(m_matrix[0][1] * m_matrix[2][2] - m_matrix[2][1] * m_matrix[0][2]),
			(m_matrix[0][1] * m_matrix[1][2] - m_matrix[0][2] * m_matrix[1][1])
		);

		ComputeVector3Base<T> column1(
			-(m_matrix[1][0] * m_matrix[2][2] - m_matrix[2][0] * m_matrix[1][2]),
			(m_matrix[0][0] * m_matrix[2][2] - m_matrix[2][0] * m_matrix[0][2]),
			-(m_matrix[0][0] * m_matrix[1][2] - m_matrix[1][0] * m_matrix[0][2])
		);

		ComputeVector3Base<T> column2(
			(m_matrix[1][0] * m_matrix[2][1] - m_matrix[2][0] * m_matrix[1][1]),
			-(m_matrix[0][0] * m_matrix[2][1] - m_matrix[2][0] * m_matrix[0][1]),
			(m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0])
		);

		ComputeMatrix3x3Base<T> inverted(column0, column1, column2);
		inverted *= T(1.0) / determinant;

		*this = inverted;
		return *this;
	}

	template <typename T>
	ComputeVector3Base<T> ComputeMatrix3x3Base<T>::transform(const ComputeVector3Base<T>& vector) const
	{
		ComputeVector3 result;
		transform(vector, result);

		return result;
	}

	template <typename T>
	void ComputeMatrix3x3Base<T>::transform(const ComputeVector3Base<T>& vector, ComputeVector3Base<T>& out) const
	{
		out[0] = m_matrix[0][0] * vector[0] + m_matrix[1][0] * vector[1] + m_matrix[2][0] * vector[2];
		out[1] = m_matrix[0][1] * vector[0] + m_matrix[1][1] * vector[1] + m_matrix[2][1] * vector[2];
		out[2] = m_matrix[0][2] * vector[0] + m_matrix[1][2] * vector[1] + m_matrix[2][2] * vector[2];
	}

	template <typename T>
	bool ComputeMatrix3x3Base<T>::isEqual(const ComputeMatrix3x3Base<T>& matrix, T epsilon) const
	{
		if (m_column1.isEqual(matrix.m_column1, epsilon)) { return false; }
		if (m_column2.isEqual(matrix.m_column2, epsilon)) { return false; }
		if (m_column3.isEqual(matrix.m_column3, epsilon)) { return false; }

		return true;
	}

	template <typename T>
	ComputeMatrix3x3Base<T> operator+(const ComputeMatrix3x3Base<T>& matrix1, const ComputeMatrix3x3Base<T>& matrix2)
	{
		ComputeMatrix3x3Base<T> result(matrix1);
		return result += matrix2;
	}

	template <typename T>
	ComputeMatrix3x3Base<T> operator-(const ComputeMatrix3x3Base<T>& matrix1, const ComputeMatrix3x3Base<T>& matrix2)
	{
		ComputeMatrix3x3Base<T> matrix3(matrix1);
		return matrix3 -= matrix2;
	}

	template <typename T>
	ComputeMatrix3x3Base<T> operator-(const ComputeMatrix3x3Base<T>& matrix)
	{
		ComputeMatrix3x3Base<T> result(matrix);
		return result.negate();
	}

	template <typename T>
	ComputeMatrix3x3Base<T> operator*(const ComputeMatrix3x3Base<T>& matrix1, const ComputeMatrix3x3Base<T>& matrix2)
	{
		ComputeMatrix3x3Base<T> result(matrix1);
		return result *= matrix2;
	}

	template <typename T>
	ComputeMatrix3x3Base<T> operator*(const ComputeMatrix3x3Base<T>& matrix, T value)
	{
		ComputeMatrix3x3Base<T> result(matrix);
		return result *= value;
	}

	template <typename T>
	ComputeMatrix3x3Base<T> operator*(T value, const ComputeMatrix3x3Base<T>& matrix)
	{
		ComputeMatrix3x3Base<T> result(matrix);
		return result *= value;
	}

	template <typename T>
	ComputeMatrix3x3Base<T> operator/(const ComputeMatrix3x3Base<T>& matrix, T value)
	{
		ComputeMatrix3x3Base<T> result(matrix);
		return result /= value;
	}

	template <typename T>
	ComputeMatrix3x3Base<T> operator/(T value, const ComputeMatrix3x3Base<T>& matrix)
	{
		ComputeMatrix3x3Base<T> result(matrix);
		return result /= value;
	}

	template <typename T>
	ComputeVector3Base<T> operator*(const ComputeMatrix3x3Base<T>& matrix, const ComputeVector3Base<T>& vector)
	{
		return matrix.transform(vector);
	}

	template <typename T>
	ComputeMatrix3x3Base<T> CrossProductSkewSymmetricComputeMatrix3x3(const ComputeVector3Base<T>& vector)
	{
		return ComputeMatrix3x3Base<T>(
			T(0.0), vector[2], -vector[1],
			-vector[2], T(0.0), vector[0],
			vector[1], -vector[0], T(0.0)
		);
	}

	template <typename T>
	ComputeMatrix3x3Base<T> RotationEulerComputeMatrix3x3(const ComputeVector3Base<T>& vector)
	{
		const T cx = cos(vector.getX());
		const T sx = sin(vector.getX());

		const T cy = cos(vector.getY());
		const T sy = sin(vector.getY());

		const T cz = cos(vector.getZ());
		const T sz = sin(vector.getZ());

		const ComputeVector3Base<T> column0(
			cz * cy + sz * sx * sy,
			sz * cx,
			sz * sx * cy - cz * sy
		);

		const ComputeVector3Base<T> column1(
			cz * sx * sy - sz * cy,
			cz * cx,
			sz * sy + cz * sx * cy
		);

		const ComputeVector3Base<T> column2(
			cx * sy,
			-sx,
			cx * cy
		);

		return ComputeMatrix3x3Base<T>(column0, column1, column2);
	}

	template <typename T>
	ComputeMatrix3x3Base<T> RotationEulerComputeMatrix3x3(T pitch, T yaw, T roll)
	{
		return RotationEulerComputeMatrix3x3(ComputeVector3Base<T>(pitch, yaw, roll));
	}

	template <typename T>
	ComputeVector3Base<T> EulerAnglesFromRotationComputeMatrix3x3(const ComputeMatrix3x3Base<T>& rotation)
	{
		if (abs(rotation.getElement(2, 0)) < 1.0_ecv) {
			return ComputeVector3Base<T>(
				std::atan2(rotation.getElement(2, 1), rotation.getElement(2, 2)),
				-std::asin(rotation.getElement(2, 0)),
				std::atan2(rotation.getElement(1, 0), rotation.getElement(0, 0))
			);
		}

		return ComputeVector3Base<T>(
			std::atan2(rotation.getElement(0, 1), rotation.getElement(1, 1)),
			(rotation.getElement(2, 0) <= -1.0_ecv) ? Math::HalfPi : -Math::HalfPi,
			0.0_ecv
		);
	}

	template <typename T>
	ComputeMatrix3x3Base<T> ScaleComputeMatrix3x3(const ComputeVector3Base<T>& scale)
	{
		return ComputeMatrix3x3Base<T>(
			ComputeVector3Base<T>(scale.getX(), T(0.0), T(0.0)),
			ComputeVector3Base<T>(T(0.0), scale.getY(), T(0.0)),
			ComputeVector3Base<T>(T(0.0), T(0.0), scale.getZ())
		);
	}

	template <typename T>
	ComputeMatrix3x3Base<T> InvertComputeMatrix3x3(const ComputeMatrix3x3Base<T>& matrix)
	{
		ComputeMatrix3x3Base<T> result(matrix);
		return result.invert();
	}

	template <typename T>
	ComputeMatrix3x3Base<T> TransposeComputeMatrix3x3(const ComputeMatrix3x3Base<T>& matrix)
	{
		ComputeMatrix3x3Base<T> result(matrix);
		return result.transpose();
	}
}