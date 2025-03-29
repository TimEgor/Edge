#include "IkSolver.h"

#include "EdgeCommon/Math/ComputeDynamicMatrix.h"
#include "EdgeCommon/Math/Transform.h"

#include "IkSystem.h"

#include <complex>

void EdgeDemo::IkSolver::solve(const IkSystem& system, float deltaTime, const Edge::FloatVector3& deltaPosition)
{
	Edge::FloatDynamicVector x;

	{
		Edge::FloatDynamicVector b;
		Edge::FloatDynamicMatrix a;

		{
			b = Edge::FloatDynamicVector({ deltaPosition.m_x, deltaPosition.m_y, deltaPosition.m_z });
			const Edge::FloatDynamicMatrix coeff(getCoeff(system));

			const Edge::FloatDynamicMatrix transposedCoeff = TransposeDynamicMatrix(coeff);
			MultiplyDynamicMatrix(transposedCoeff, coeff, a);
			DynamicMatrixAddDiagonal(a, 1.0f);

			TransformDynamicVector(transposedCoeff, b, b);
		}

		solveSystem(a, b, x);
	}

	const IkSystem::JointCollection& joints = system.getJoints();
	EDGE_ASSERT(joints.size() == x.getElementCount());

	constexpr float angleLimit = 120.0f * Edge::Math::DegToRad;

	for (uint32_t jointIndex = 0; jointIndex < x.getElementCount(); ++jointIndex)
	{
		const float deltaValue = x.getElement(jointIndex);

		const float valueCoeff = 1.0f / std::max(1.0f, (fabs(deltaValue) / (angleLimit * deltaTime)));

		IkJoint* joint = joints[jointIndex];
		joint->applyValue(joint->getValue() + deltaValue * valueCoeff);
	}

	updateTransforms(system);
}

void EdgeDemo::IkSolver::solveSystem(const Edge::FloatDynamicMatrix& coeff, const Edge::FloatDynamicVector& result, Edge::FloatDynamicVector& out) const
{
	//Gauss-Elimination

	const uint32_t coeffRowCount = coeff.getRowCount();
	const uint32_t coeffColumnCount = coeff.getColumnCount();

	EDGE_ASSERT(coeffRowCount == coeffColumnCount);
	EDGE_ASSERT(result.getElementCount() == coeffRowCount);

	if (out.getElementCount() != coeffColumnCount)
	{
		out = Edge::FloatDynamicVector(coeffColumnCount);
	}

	for (uint32_t iteration = 0; iteration < 5; ++iteration)
	{
        float maxError = 0.0f;

        for (uint32_t i = 0; i < coeffRowCount; ++i)
		{
            float sigma = 0.0f;

            for (int j = 0; j < coeffRowCount; ++j)
			{
                if (j != i)
				{
                    sigma += coeff[i][j] * out[j];
                }
            }

            float newX = (result[i] - sigma) / coeff[i][i];

            float error = std::fabs(newX - out[i]);
            if (error > maxError)
			{
                maxError = error;
            }

            out[i] = newX;
        }

        if (maxError < 0.001f)
		{
			break;
        }
    }
}

Edge::FloatDynamicMatrix EdgeDemo::IkSolver::getCoeff(const IkSystem& system)
{
	const uint32_t jointCount = system.getJoints().size();
	Edge::FloatDynamicMatrix coeff(3, jointCount);

	const IkSystem::JointCollection& joints = system.getJoints();
	for (uint32_t jointIndex = 0; jointIndex < jointCount; ++jointIndex)
	{
		const IkJoint* joint = joints[jointIndex];
		const Edge::ComputeVector3 jointDerivative = joint->calcDerivative(system.getEffectorLink()->getWorldTransform().getOrigin());

		coeff.setElement(0, jointIndex, jointDerivative.getX());
		coeff.setElement(1, jointIndex, jointDerivative.getY());
		coeff.setElement(2, jointIndex, jointDerivative.getZ());
	}

	return coeff;
}

void EdgeDemo::IkSolver::solve(const IkSystem& system, float deltaTime)
{
	constexpr uint32_t iterationCount = 1;
	const float iterationDeltaTime = deltaTime / iterationCount;
	for (uint32_t iterationIndex = 0; iterationIndex < iterationCount; ++iterationIndex)
	{
		const Edge::ComputeVector3 targetPosition = system.getTargetPosition();
		const Edge::ComputeVector3 effectorPosition = Edge::Transform(system.getEffectorLink()->getWorldTransform()).getOrigin();
		const Edge::ComputeVector3 deltaPosition = targetPosition - effectorPosition;

		if (deltaPosition.isEqual(Edge::FloatVector3Zero, 0.01f))
		{
			break;
		}

		solve(system, iterationDeltaTime, deltaPosition.getFloatVector3());
	}
}

void EdgeDemo::IkSolver::updateTransforms(const IkSystem& system)
{
	IkLink* link = system.getRootLink();
	const Edge::Transform* parentTransform = &system.getBaseTransform();

	while (link)
	{
		const Edge::ComputeMatrix4x4 worldTranform = link->getLocalTransform().m_matrix * parentTransform->m_matrix;
		link->setWorldTransform(worldTranform);

		parentTransform = &link->getWorldTransform();
		link = link->getChildLink();
	}
}
