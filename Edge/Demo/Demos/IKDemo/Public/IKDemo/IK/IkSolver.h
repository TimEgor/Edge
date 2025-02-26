#pragma once

#include "EdgeCommon/Math/DynamicMatrix.h"
#include "EdgeCommon/Math/Vector.h"

namespace EdgeDemo
{
	class IkSystem;

	class IkSolver final
	{
	private:
		void solve(const IkSystem& system, float deltaTime, const Edge::FloatVector3& deltaPosition);
		void solveSystem(const Edge::FloatDynamicMatrix& coeff, const Edge::FloatDynamicVector& result, Edge::FloatDynamicVector& out) const;
		Edge::FloatDynamicMatrix getCoeff(const IkSystem& system);

	public:
		IkSolver() = default;

		void solve(const IkSystem& system, float deltaTime);
		void updateTransforms(const IkSystem& system);
	};
}
