#include "GJKCollisionDispatcher.h"

#include "EdgePhysics/Physics/Collision/GJK/GJK.h"
#include "EdgePhysics/Physics/Collision/Manifold/PhysicsManifoldContactGenerator.h"

uint32_t Edge::GJKCollisionDispatcher::dispatch(
	const PhysicsEntityCollisionReference& collision1,
	const PhysicsEntityCollisionReference& collision2,
	ContactManifoldDispatchingResultCollection& results
)
{
	GJK gjkTest;
	const GJK::TestResult gjkResult = gjkTest(collision1.getObjectRef(), collision2.getObjectRef(), 100, 0.0001_ecv);

	bool isCollided = false;

	PhysicsCollisionContactPoint contactPoint;
	if (gjkResult.m_testResult == GJK::Result::Intersection)
	{
		const ComputeVector3 contactDelta = gjkResult.m_point1 - gjkResult.m_point2;
		const ComputeValue contactOffset = contactDelta.getLength();

		contactPoint.m_position1 = gjkResult.m_point1;
		contactPoint.m_position2 = gjkResult.m_point2;
		contactPoint.m_normal = NormalizeComputeVector3(contactDelta);
		contactPoint.m_depth = contactOffset;

		isCollided = true;
	}
	else if (gjkResult.m_testResult == GJK::Result::Undetermined)
	{
		EPA epa;
		isCollided = epa(collision1.getObjectRef(), collision2.getObjectRef(), gjkResult, 100, contactPoint);
	}

	uint32_t contactPointCount = 0;

	if (isCollided)
	{
		PhysicsContactManifold manifold;

		ManifoldContactGenerator manifoldContactGenerator;
		manifoldContactGenerator.generate(collision1.getObjectRef(), collision2.getObjectRef(), contactPoint, manifold);

		contactPointCount = manifold.getContactPointCount();

		results.push_back(manifold);
	}

	return contactPointCount;
}
