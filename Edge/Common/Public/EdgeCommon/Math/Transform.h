#pragma once

#include "ComputeQuaternion.h"

namespace Edge
{
	using TransformMatrix = FloatMatrix4x4;

	struct Transform final
	{
		TransformMatrix m_matrix = FloatMatrix4x4Identity;

		Transform() = default;
		Transform(const TransformMatrix& matrix) : m_matrix(matrix) {}

		const FloatVector3& getAxisX() const { return m_matrix.m_row1.m_xyz; }
		void setAxisX(const FloatVector3& axis) { m_matrix.m_row1.m_xyz = axis; }
		const FloatVector3& getAxisY() const { return m_matrix.m_row2.m_xyz; }
		void setAxisY(const FloatVector3& axis) { m_matrix.m_row2.m_xyz = axis; }
		const FloatVector3& getAxisZ() const { return m_matrix.m_row3.m_xyz; }
		void setAxisZ(const FloatVector3& axis) { m_matrix.m_row3.m_xyz = axis; }
		const FloatVector3& getOrigin() const { return m_matrix.m_row4.m_xyz; }
		void setOrigin(const FloatVector3& origin) { m_matrix.m_row4.m_xyz = origin; }

		FloatMatrix3x3 getRotationMatrix() const;
		void getRotationMatrix(FloatMatrix3x3& rotation) const;
		ComputeMatrix getRotationComputeMatrix() const;
		void getRotationComputeMatrix(ComputeMatrix& rotation) const;
		void setRotationMatrix(const FloatMatrix3x3& rotation);

		FloatQuaternion getRotationQuaternion() const;
		void getRotationQuaternion(FloatQuaternion& rotation) const;
		ComputeQuaternion getRotationComputeQuaternion() const;
		void getRotationComputeQuaternion(ComputeQuaternion& rotation) const;
		void setRotationQuaternion(const FloatQuaternion& rotation);
	};
}
