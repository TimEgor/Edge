#include "PhysicsManifoldContactGenerator.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"
#include "EdgePhysics/Physics/Collision/PhysicsEntityCollision.h"
#include "EdgePhysics/Physics/Collision/PhysicsEntityCollisionShape.h"

#include "ClippingPoly.h"
#include "PhysicsContactManifold.h"

void Edge::ManifoldContactGenerator::generate(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2,
                                              const PhysicsCollisionContactPoint& contactPoint, PhysicsContactManifold& manifold) const
{
	PhysicsEntityCollisionShape::SupportingFaceVertexCollection supportingFace1;
	collision1.getSupportingFace(-contactPoint.m_normal, supportingFace1);

	PhysicsEntityCollisionShape::SupportingFaceVertexCollection supportingFace2;
	collision2.getSupportingFace(contactPoint.m_normal, supportingFace2);

	if (supportingFace1.size() >= 2 && supportingFace2.size() >= 3)
	{
		PhysicsEntityCollisionShape::SupportingFaceVertexCollection clippedFace;

		if (supportingFace1.size() >= 3)
		{
			ClippingPoly::ClipPolyVsPoly(supportingFace2, supportingFace1, contactPoint.m_normal, clippedFace);
		}
		else if (supportingFace1.size() == 2)
		{
			ClippingPoly::ClipPolyVsEdge(supportingFace2, supportingFace1[0], supportingFace1[1], contactPoint.m_normal, clippedFace);
		}

		const ComputeVector3 faceOrigin = supportingFace1[0];
		const ComputeVector3 edge = supportingFace1[1] - faceOrigin;

		ComputeVector3 faceNormal;
		if (supportingFace1.size() >= 3)
		{
			faceNormal = CrossComputeVector3(edge, supportingFace1[2] - faceOrigin);
		}
		else
		{
			faceNormal = CrossComputeVector3(CrossComputeVector3(edge, contactPoint.m_normal), edge);
		}

		const ComputeValueType faceNormalLength = faceNormal.getLength();
		if (faceNormalLength > ComputeValueType(0.0))
		{
			for (const ComputeVector3& p2 : clippedFace)
			{
				const ComputeValueType distance = DotComputeVector3(p2 - faceOrigin, faceNormal);
				static constexpr ComputeValueType distanceTolerance = ComputeValueType(0.001);
				if (distance <= ComputeValueType(0.0) || sqrt(distance) < distanceTolerance * faceNormalLength)
				{
					const ComputeVector3 p1 = p2 - (distance / faceNormalLength) * faceNormal;

					manifold.m_positions1.push_back(p1);
					manifold.m_positions2.push_back(p2);
				}
			}
		}
	}

	EDGE_ASSERT(manifold.m_positions1.size() == manifold.m_positions2.size());

	if (manifold.m_positions1.empty())
	{
		manifold.m_positions1.push_back(contactPoint.m_position1);
		manifold.m_positions2.push_back(contactPoint.m_position2);
	}

	manifold.m_normal = contactPoint.m_normal;
	manifold.m_depth = contactPoint.m_depth;
}
