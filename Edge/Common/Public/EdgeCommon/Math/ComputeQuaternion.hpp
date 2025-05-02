#pragma once

namespace Edge
{
	template <typename T>
	ComputeQuaternionBase<T>::ComputeQuaternionBase(const ComputeMatrix3x3Base<T>& matrix)
	{
		setupFromRotationMatrix3x3(matrix);
	}

	template <typename T>
	ComputeQuaternionBase<T>::ComputeQuaternionBase(const ComputeMatrix4x4Base<T>& matrix)
	{
		setupFromRotationMatrix4x4(matrix);
	}

	template <typename T>
	ComputeQuaternionBase<T>::ComputeQuaternionBase(const ComputeVector3Base<T>& axis, T angle)
	{
		setupFromAxisAngle(axis, angle);
	}

	template <typename T>
	ComputeQuaternionBase<T>& ComputeQuaternionBase<T>::operator=(const ComputeQuaternionBase<T>& quaternion)
	{
		m_quaternion = quaternion.m_quaternion;
		return *this;
	}

	template <typename T>
	bool ComputeQuaternionBase<T>::operator==(const ComputeQuaternionBase<T>& quaternion) const
	{
		return isEqual(quaternion);
	}

	template <typename T>
	bool ComputeQuaternionBase<T>::operator!=(const ComputeQuaternionBase<T>& quaternion) const
	{
		return !isEqual(quaternion);
	}

	template <typename T>
	ComputeQuaternionBase<T>& ComputeQuaternionBase<T>::operator*=(const ComputeQuaternionBase<T>& quaternion)
	{
		const T x =
			m_quaternion.m_elements.m_w * quaternion.m_quaternion.m_elements.m_x +
			m_quaternion.m_elements.m_x * quaternion.m_quaternion.m_elements.m_w +
			m_quaternion.m_elements.m_y * quaternion.m_quaternion.m_elements.m_z -
			m_quaternion.m_elements.m_z * quaternion.m_quaternion.m_elements.m_y;
		const T y =
			m_quaternion.m_elements.m_w * quaternion.m_quaternion.m_elements.m_y -
			m_quaternion.m_elements.m_x * quaternion.m_quaternion.m_elements.m_z +
			m_quaternion.m_elements.m_y * quaternion.m_quaternion.m_elements.m_w +
			m_quaternion.m_elements.m_z * quaternion.m_quaternion.m_elements.m_x;
		const T z =
			m_quaternion.m_elements.m_w * quaternion.m_quaternion.m_elements.m_z +
			m_quaternion.m_elements.m_x * quaternion.m_quaternion.m_elements.m_y -
			m_quaternion.m_elements.m_y * quaternion.m_quaternion.m_elements.m_x +
			m_quaternion.m_elements.m_z * quaternion.m_quaternion.m_elements.m_w;
		const T w =
			m_quaternion.m_elements.m_w * quaternion.m_quaternion.m_elements.m_w -
			m_quaternion.m_elements.m_x * quaternion.m_quaternion.m_elements.m_x -
			m_quaternion.m_elements.m_y * quaternion.m_quaternion.m_elements.m_y -
			m_quaternion.m_elements.m_z * quaternion.m_quaternion.m_elements.m_z;

		*this = ComputeQuaternionBase<T>(x, y, z, w);
		return *this;
	}

	template <typename T>
	ComputeQuaternionBase<T>& ComputeQuaternionBase<T>::setupFromRotationMatrix3x3(const ComputeMatrix3x3Base<T>& matrix)
	{
		const T trace = matrix.getElement(0, 0) + matrix.getElement(1, 1) + matrix.getElement(2, 2);

		if (trace < T(0.0))
		{
			uint32_t i = 0;
			if (matrix.getElement(1, 1) > matrix.getElement(0, 0))
			{
				i = 1;
			}
			if (matrix.getElement(2, 2) > matrix.getElement(i, i))
			{
				i = 2;
			}

			if (i == 0)
			{
				const T r = sqrt(matrix.getElement(0, 0) - (matrix.getElement(1, 1) + matrix.getElement(2, 2)) + T(1));
				const T s = T(0.5) / r;

				m_quaternion.m_elements.m_x = T(0.5) * s;
				m_quaternion.m_elements.m_y = (matrix.getElement(1, 0) + matrix.getElement(0, 1)) * s;
				m_quaternion.m_elements.m_z = (matrix.getElement(0, 2) + matrix.getElement(2, 0)) * s;
				m_quaternion.m_elements.m_w = (matrix.getElement(1, 2) - matrix.getElement(2, 1)) * s;
			}
			else if (i == 1)
			{
				const T r = sqrt(matrix.getElement(1, 1) - (matrix.getElement(2, 2) + matrix.getElement(0, 0)) + T(1));
				const T s = T(0.5) / r;

				m_quaternion.m_elements.m_x = (matrix.getElement(1, 0) + matrix.getElement(0, 1)) * s;
				m_quaternion.m_elements.m_y = T(0.5) * s;
				m_quaternion.m_elements.m_z = (matrix.getElement(2, 1) + matrix.getElement(1, 2)) * s;
				m_quaternion.m_elements.m_w = (matrix.getElement(2, 0) - matrix.getElement(0, 2)) * s;
			}
			else
			{
				const T r = sqrt(matrix.getElement(2, 2) - (matrix.getElement(0, 0) + matrix.getElement(1, 1)) + T(1));
				const T s = T(0.5) / r;

				m_quaternion.m_elements.m_x = (matrix.getElement(0, 2) + matrix.getElement(2, 0)) * s;
				m_quaternion.m_elements.m_y = (matrix.getElement(2, 1) + matrix.getElement(1, 2)) * s;
				m_quaternion.m_elements.m_z = T(0.5) * s;
				m_quaternion.m_elements.m_w = (matrix.getElement(0, 1) - matrix.getElement(1, 0)) * s;
			}
		}
		else
		{
			const T r = sqrt(trace + T(1.0));
			const T s = T(0.5) / r;

			m_quaternion.m_elements.m_x = (matrix.getElement(1, 2) - matrix.getElement(2, 1)) * s;
			m_quaternion.m_elements.m_y = (matrix.getElement(2, 0) - matrix.getElement(0, 2)) * s;
			m_quaternion.m_elements.m_z = (matrix.getElement(0, 1) - matrix.getElement(1, 0)) * s;
			m_quaternion.m_elements.m_w = T(0.5) * r;
		}

		return *this;
	}

	template <typename T>
	ComputeQuaternionBase<T>& ComputeQuaternionBase<T>::setupFromRotationMatrix4x4(const ComputeMatrix4x4Base<T>& matrix)
	{
		setupFromRotationMatrix3x3(
			ComputeMatrix3x3Base<T>(
				matrix.getColumn(0).getXYZ(),
				matrix.getColumn(1).getXYZ(),
				matrix.getColumn(2).getXYZ()
			)
		);

		return *this;
	}

	template <typename T>
	ComputeQuaternionBase<T>& ComputeQuaternionBase<T>::setupFromAxisAngle(const ComputeVector3Base<T>& axis, T angle)
	{
		const ComputeVector3 normAxis = NormalizeComputeVector3(axis);

		const T halfAngle = angle * T(0.5);
		const T halfAngleSin = sin(halfAngle);
		const T halfAngleCos = cos(halfAngle);

		m_quaternion.m_elements.m_x = normAxis.getX() * halfAngleSin;
		m_quaternion.m_elements.m_y = normAxis.getY() * halfAngleSin;
		m_quaternion.m_elements.m_z = normAxis.getZ() * halfAngleSin;
		m_quaternion.m_elements.m_w = halfAngleCos;

		return *this;
	}

	template <typename T>
	ComputeQuaternionBase<T>& ComputeQuaternionBase<T>::setupFromRollPitchYaw(const ComputeVector3Base<T>& angles)
	{
		return setupFromRollPitchYaw(angles.getX(), angles.getY(), angles.getZ());
	}

	template <typename T>
	ComputeQuaternionBase<T>& ComputeQuaternionBase<T>::setupFromRollPitchYaw(ValueType pitch, ValueType yaw, ValueType roll)
	{
		const ValueType cx = std::cos(pitch * T(0.5));
		const ValueType sx = std::sin(pitch * T(0.5));
		const ValueType cy = std::cos(yaw * T(0.5));
		const ValueType sy = std::sin(yaw * T(0.5));
		const ValueType cz = std::cos(roll * T(0.5));
		const ValueType sz = std::sin(roll * T(0.5));

		m_quaternion.m_elements.m_x = cz * cy * cx + sz * sy * sx;
		m_quaternion.m_elements.m_y = cz * cy * sx - sz * sy * cx;
		m_quaternion.m_elements.m_z = cz * sy * cx + sz * cy * sx;
		m_quaternion.m_elements.m_w = sz * cy * cx - cz * sy * sx;

		return *this;
	}

	template <typename T>
	T ComputeQuaternionBase<T>::getLength() const
	{
		return std::sqrt(getLengthSqr());
	}

	template <typename T>
	T ComputeQuaternionBase<T>::getLengthSqr() const
	{
		return dot(*this);
	}

	template <typename T>
	T ComputeQuaternionBase<T>::dot(const ComputeQuaternionBase<T>& quaternion) const
	{
		return
			m_quaternion.m_elements.m_x * quaternion.m_quaternion.m_elements.m_x +
			m_quaternion.m_elements.m_y * quaternion.m_quaternion.m_elements.m_y +
			m_quaternion.m_elements.m_z * quaternion.m_quaternion.m_elements.m_z +
			m_quaternion.m_elements.m_w * quaternion.m_quaternion.m_elements.m_w;
	}

	template <typename T>
	ComputeQuaternionBase<T>& ComputeQuaternionBase<T>::normalize()
	{
		const T length = getLength();
		if (length <= Math::TypedEpsilon<T>())
		{
			return *this;
		}

		m_quaternion.m_elements.m_x /= length;
		m_quaternion.m_elements.m_y /= length;
		m_quaternion.m_elements.m_z /= length;
		m_quaternion.m_elements.m_w /= length;

		return *this;
	}

	template <typename T>
	ComputeQuaternionBase<T>& ComputeQuaternionBase<T>::conjugate()
	{
		m_quaternion.m_elements.m_x = -m_quaternion.m_elements.m_x;
		m_quaternion.m_elements.m_y = -m_quaternion.m_elements.m_y;
		m_quaternion.m_elements.m_z = -m_quaternion.m_elements.m_z;

		return *this;
	}

	template <typename T>
	ComputeQuaternionBase<T>& ComputeQuaternionBase<T>::invert()
	{
		return conjugate() / getLength();
	}

	template <typename T>
	ComputeVector3Base<T> ComputeQuaternionBase<T>::rotate(const ComputeVector3Base<T>& vector) const
	{
		ComputeVector3Base<T> result;
		rotate(vector, result);

		return result;
	}

	template <typename T>
	void ComputeQuaternionBase<T>::rotate(const ComputeVector3Base<T>& vector, ComputeVector3Base<T>& out) const
	{
		EDGE_ASSERT(isUnit());

		const ComputeQuaternionBase<T> vQ(vector.getX(), vector.getY(), vector.getZ(), T(0.0));
		const ComputeQuaternionBase<T> conjugatedQ = ConjugateComputeQuaternion(*this);

		out = (*this * vQ * conjugatedQ).getXYZ();
	}

	template <typename T>
	bool ComputeQuaternionBase<T>::isEqual(const ComputeQuaternionBase<T>& quaternion, T epsilon) const
	{
		return
			Math::IsApproxEqual(m_quaternion.m_elements.m_x, quaternion.m_quaternion.m_elements.m_x, epsilon) &&
			Math::IsApproxEqual(m_quaternion.m_elements.m_y, quaternion.m_quaternion.m_elements.m_y, epsilon) &&
			Math::IsApproxEqual(m_quaternion.m_elements.m_z, quaternion.m_quaternion.m_elements.m_z, epsilon) &&
			Math::IsApproxEqual(m_quaternion.m_elements.m_w, quaternion.m_quaternion.m_elements.m_w, epsilon);
	}

	template <typename T>
	bool ComputeQuaternionBase<T>::isUnit() const
	{
		return Math::IsApproxEqual(getLengthSqr(), T(1.0), T(0.00001));
	}

	template <typename T>
	bool ComputeQuaternionBase<T>::isZero() const
	{
		return Math::IsApproxEqual(getLengthSqr(), T(0.0), T(0.00001));
	}

	template <typename T>
	ComputeMatrix3x3Base<T> ComputeQuaternionBase<T>::getRotationMatrix3x3() const
	{
		ComputeMatrix3x3Base<T> matrix;
		getRotationMatrix3x3(matrix);

		return matrix;
	}

	template <typename T>
	void ComputeQuaternionBase<T>::getRotationMatrix3x3(ComputeMatrix3x3Base<T>& matrix) const
	{
		const T tx = m_quaternion.m_elements.m_x + m_quaternion.m_elements.m_x;
		const T ty = m_quaternion.m_elements.m_y + m_quaternion.m_elements.m_y;
		const T tz = m_quaternion.m_elements.m_z + m_quaternion.m_elements.m_z;

		const T xx = tx * m_quaternion.m_elements.m_x;
		const T yy = ty * m_quaternion.m_elements.m_y;
		const T zz = tz * m_quaternion.m_elements.m_z;
		const T xy = tx * m_quaternion.m_elements.m_y;
		const T xz = tx * m_quaternion.m_elements.m_z;
		const T xw = tx * m_quaternion.m_elements.m_w;
		const T yz = ty * m_quaternion.m_elements.m_z;
		const T yw = ty * m_quaternion.m_elements.m_w;
		const T zw = tz * m_quaternion.m_elements.m_w;

		matrix = ComputeMatrix3x3Base<T>(
			(T(1.0) - yy) - zz, xy + zw, xz - yw,
			xy - zw, (T(1.0) - zz) - xx, yz + xw,
			xz + yw, yz - xw, (T(1.0) - xx) - yy
		);
	}

	template <typename T>
	ComputeMatrix4x4Base<T> ComputeQuaternionBase<T>::getRotationMatrix4x4() const
	{
		ComputeMatrix4x4Base<T> matrix;
		getRotationMatrix4x4(matrix);

		return matrix;
	}

	template <typename T>
	void ComputeQuaternionBase<T>::getRotationMatrix4x4(ComputeMatrix4x4Base<T>& matrix) const
	{
		ComputeMatrix3x3Base<T> matrix3x3;
		getRotationMatrix3x3(matrix3x3);

		matrix = matrix3x3;
		matrix.setElement(3, 3, T(1.0));
	}

	template <typename T>
	T ComputeQuaternionBase<T>::getAxisAngle(const ComputeVector3Base<T>& axis) const
	{
		return std::atan(getXYZ().dot(axis) / getW()) * T(2.0);
	}

	template <typename T>
	ComputeVector3Base<T> ComputeQuaternionBase<T>::getEulerAngles() const
	{
		ComputeVector3Base<T> angles;
		getAngles(angles);

		return angles;
	}

	template <typename T>
	void ComputeQuaternionBase<T>::getEulerAngles(ComputeVector3Base<T>& angles) const
	{
		const T sinr_cosp = T(2.0) * (m_quaternion.m_elements.m_w * m_quaternion.m_elements.m_x + m_quaternion.m_elements.m_y * m_quaternion.m_elements.m_z);
		const T cosr_cosp = T(1.0) - T(2.0) * (m_quaternion.m_elements.m_x * m_quaternion.m_elements.m_x + m_quaternion.m_elements.m_y * m_quaternion.m_elements.m_y);
		const T sinp = T(2.0) * (m_quaternion.m_elements.m_w * m_quaternion.m_elements.m_y - m_quaternion.m_elements.m_z * m_quaternion.m_elements.m_x);
		const T siny_cosp = T(2.0) * (m_quaternion.m_elements.m_w * m_quaternion.m_elements.m_z + m_quaternion.m_elements.m_x * m_quaternion.m_elements.m_y);
		const T cosy_cosp = T(1.0) - T(2.0) * (m_quaternion.m_elements.m_y * m_quaternion.m_elements.m_y + m_quaternion.m_elements.m_z * m_quaternion.m_elements.m_z);

		if (std::abs(sinp) >= T(1.0))
		{
			angles.setY(std::copysign(Math::HalfPi, sinp));
		}
		else
		{
			angles.setY(std::asin(sinp));
		}

		angles.setX(std::atan2(sinr_cosp, cosr_cosp));
		angles.setZ(std::atan2(siny_cosp, cosy_cosp));
	}

	template <typename T>
	ComputeQuaternionBase<T> operator*(const ComputeQuaternionBase<T>& quaternion1, const ComputeQuaternionBase<T>& quaternion2)
	{
		ComputeQuaternionBase<T> result(quaternion1);
		return result *= quaternion2;
	}

	template <typename T>
	ComputeQuaternionBase<T> ConjugateComputeQuaternion(const ComputeQuaternionBase<T>& quaternion)
	{
		ComputeQuaternionBase<T> result(quaternion);
		return result.conjugate();
	}
}