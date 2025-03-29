#pragma once

namespace Edge
{
	template <typename T>
	ComputeMatrix2x2Base<T>& ComputeMatrix2x2Base<T>::operator=(const ComputeMatrix2x2Base<T>& matrix)
	{
		m_matrix = matrix.m_matrix;

		return *this;
	}

	template <typename T>
	ComputeMatrix2x2Base<T>& ComputeMatrix2x2Base<T>::operator+=(const ComputeMatrix2x2Base<T>& matrix)
	{
		m_column1 += matrix.m_column1;
		m_column2 += matrix.m_column2;

		return *this;
	}

	template <typename T>
	ComputeMatrix2x2Base<T>& ComputeMatrix2x2Base<T>::operator-=(const ComputeMatrix2x2Base<T>& matrix)
	{
		m_column1 -= matrix.m_column1;
		m_column2 -= matrix.m_column2;

		return *this;
	}

	template <typename T>
	ComputeMatrix2x2Base<T>& ComputeMatrix2x2Base<T>::operator*=(const ComputeMatrix2x2Base<T>& matrix)
	{
		ComputeMatrix2x2Base<T> result;

		result.m_matrix[0][0] = m_matrix[0][0] * matrix.m_matrix[0][0] + m_matrix[1][0] * matrix.m_matrix[0][1];
		result.m_matrix[0][1] = m_matrix[0][1] * matrix.m_matrix[0][0] + m_matrix[1][1] * matrix.m_matrix[0][1];

		result.m_matrix[1][0] = m_matrix[0][0] * matrix.m_matrix[1][0] + m_matrix[1][0] * matrix.m_matrix[1][1];
		result.m_matrix[1][1] = m_matrix[0][1] * matrix.m_matrix[1][0] + m_matrix[1][1] * matrix.m_matrix[1][1];

		*this = result;
		return *this;
	}

	template <typename T>
	ComputeMatrix2x2Base<T>& ComputeMatrix2x2Base<T>::operator*=(T value)
	{
		m_column1 *= value;
		m_column2 *= value;

		return *this;
	}

	template <typename T>
	ComputeMatrix2x2Base<T>& ComputeMatrix2x2Base<T>::operator/=(T value)
	{
		m_column1 /= value;
		m_column2 /= value;

		return *this;
	}

	template <typename T>
	bool ComputeMatrix2x2Base<T>::operator==(const ComputeMatrix2x2Base<T>& matrix) const
	{
		return isEqual(matrix);
	}

	template <typename T>
	bool ComputeMatrix2x2Base<T>::operator!=(const ComputeMatrix2x2Base<T>& matrix) const
	{
		return !isEqual(matrix);
	}

	template <typename T>
	FloatMatrix2x2 ComputeMatrix2x2Base<T>::getFloatMatrix2x2() const
	{
		FloatMatrix2x2 result;
		getFloatMatrix2x2(result);

		return result;
	}

	template <typename T>
	const ComputeVector2Base<T>& ComputeMatrix2x2Base<T>::getColumn(uint32_t index) const
	{
		EDGE_ASSERT(index < 2);
		return m_columns[index];
	}

	template <typename T>
	ComputeVector2Base<T>& ComputeMatrix2x2Base<T>::getColumn(uint32_t index)
	{
		EDGE_ASSERT(index < 2);
		return m_columns[index];
	}

	template <typename T>
	ComputeVector2Base<T> ComputeMatrix2x2Base<T>::getRow(uint32_t index) const
	{
		return ComputeVector2(m_matrix.m_rows[0][index], m_matrix.m_rows[1][index]);
	}

	template <typename T>
	void ComputeMatrix2x2Base<T>::setColumn(uint32_t index, const ComputeVector2Base<T>& column)
	{
		EDGE_ASSERT(index < 2);
		m_columns[index] = column;
	}

	template <typename T>
	void ComputeMatrix2x2Base<T>::setRow(uint32_t index, const ComputeVector2Base<T>& row)
	{
		EDGE_ASSERT(index < 3);

		m_matrix.m_rows[0][index] = row.getX();
		m_matrix.m_rows[1][index] = row.getY();
	}

	template <typename T>
	ComputeMatrix2x2Base<T>& ComputeMatrix2x2Base<T>::negate()
	{
		m_column1 = -m_column1;
		m_column2 = -m_column2;

		return *this;
	}

	template <typename T>
	ComputeMatrix2x2Base<T>& ComputeMatrix2x2Base<T>::transpose()
	{
		ComputeMatrix2x2Base<T> transposed;

		transposed.setColumn(0, getRow(0));
		transposed.setColumn(1, getRow(1));

		*this = transposed;
		return *this;
	}

	template <typename T>
	T ComputeMatrix2x2Base<T>::getDeterminant() const
	{
		return m_matrix[0][0] * m_matrix[1][1] - m_matrix[1][0] * m_matrix[0][1];
	}

	template <typename T>
	ComputeMatrix2x2Base<T>& ComputeMatrix2x2Base<T>::invert()
	{
		const ComputeValueType determinant = getDeterminant();

		EDGE_ASSERT(abs(determinant) > Math::Epsilon);

		ComputeMatrix2x2Base<T> inverted(
			m_matrix[1][1], -m_matrix[0][1],
			-m_matrix[1][0], m_matrix[0][0]
		);

		inverted *= ComputeValueType(1.0) / determinant;

		*this = inverted;
		return *this;
	}

	template <typename T>
	ComputeVector2Base<T> ComputeMatrix2x2Base<T>::transform(const ComputeVector2Base<T>& vector) const
	{
		ComputeVector2 result;
		transform(vector, result);

		return result;
	}

	template <typename T>
	void ComputeMatrix2x2Base<T>::transform(const ComputeVector2Base<T>& vector, ComputeVector2Base<T>& out) const
	{
		out[0] = m_matrix[0][0] * vector[0] + m_matrix[1][0] * vector[1];
		out[1] = m_matrix[0][1] * vector[0] + m_matrix[1][1] * vector[1];
	}

	template <typename T>
	bool ComputeMatrix2x2Base<T>::isEqual(const ComputeMatrix2x2Base<T>& matrix, T epsilon) const
	{
		if (m_column1.isEqual(matrix.m_column1, epsilon)) { return false; }
		if (m_column2.isEqual(matrix.m_column2, epsilon)) { return false; }

		return true;
	}

	template <typename T>
	ComputeMatrix2x2Base<T> operator+(const ComputeMatrix2x2Base<T>& matrix1, const ComputeMatrix2x2Base<T>& matrix2)
	{
		ComputeMatrix2x2Base<T> result(matrix1);
		return result += matrix2;
	}

	template <typename T>
	ComputeMatrix2x2Base<T> operator-(const ComputeMatrix2x2Base<T>& matrix1, const ComputeMatrix2x2Base<T>& matrix2)
	{
		ComputeMatrix2x2Base<T> result(matrix1);
		return result -= matrix2;
	}

	template <typename T>
	ComputeMatrix2x2Base<T> operator-(const ComputeMatrix2x2Base<T>& matrix)
	{
		ComputeMatrix2x2Base<T> result(matrix);
		return result.negate();
	}

	template <typename T>
	ComputeMatrix2x2Base<T> operator*(const ComputeMatrix2x2Base<T>& matrix1, const ComputeMatrix2x2Base<T>& matrix2)
	{
		ComputeMatrix2x2Base<T> result(matrix1);
		return result *= matrix2;
	}

	template <typename T>
	ComputeMatrix2x2Base<T> operator*(const ComputeMatrix2x2Base<T>& matrix, T value)
	{
		ComputeMatrix2x2Base<T> result(matrix);
		return result *= value;
	}

	template <typename T>
	ComputeMatrix2x2Base<T> operator*(T value, const ComputeMatrix2x2Base<T>& matrix)
	{
		ComputeMatrix2x2Base<T> result(matrix);
		return result *= value;
	}

	template <typename T>
	ComputeMatrix2x2Base<T> operator/(const ComputeMatrix2x2Base<T>& matrix, T value)
	{
		ComputeMatrix2x2Base<T> result(matrix);
		return result /= value;
	}

	template <typename T>
	ComputeMatrix2x2Base<T> operator/(T value, const ComputeMatrix2x2Base<T>& matrix)
	{
		ComputeMatrix2x2Base<T> result(matrix);
		return result /= value;
	}

	template <typename T>
	ComputeVector2Base<T> operator*(const ComputeMatrix2x2Base<T>& matrix, const ComputeVector2Base<T>& vector)
	{
		return matrix.transform(vector);
	}

	template <typename T>
	ComputeMatrix2x2Base<T> InvertComputeMatrix2x2(const ComputeMatrix2x2Base<T>& matrix)
	{
		ComputeMatrix2x2Base<T> result(matrix);
		return result.invert();
	}

	template <typename T>
	ComputeMatrix2x2Base<T> TransposeComputeMatrix2x2(const ComputeMatrix2x2Base<T>& matrix)
	{
		ComputeMatrix2x2Base<T> result(matrix);
		return result.transpose();
	}
}