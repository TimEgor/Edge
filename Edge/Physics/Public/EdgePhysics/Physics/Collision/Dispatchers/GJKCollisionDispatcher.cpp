#include "GJKCollisionDispatcher.h"

#include "EdgePhysics/Physics/Collision/GJK/GJK.h"
#include "EdgePhysics/Physics/Collision/Manifold/PhysicsManifoldContactGenerator.h"

uint32_t Edge::GJKCollisionDispatcher::dispatch(const PhysicsEntityCollisionReference& collision1,
	const PhysicsEntityCollisionReference& collision2, PhysicsCollisionContactID contactID,
	ContactManifoldDispatchingResultCollection& results)
{
	GJK gjkTest;
	const GJK::Result gjkTestResult = gjkTest(collision1.getObjectRef(), collision2.getObjectRef(), 100);

	PhysicsCollisionContactPoint contactPoint;

	EPA epa;
	const bool epaResult = epa(collision1.getObjectRef(), collision2.getObjectRef(), gjkTestResult, 100, contactPoint);

	uint32_t contactPointCount = 0;

	if (epaResult) {
		PhysicsInstanceContactManifold manifold;

		manifold.m_contactID = contactID;

		ManifoldContactGenerator manifoldContactGenerator;
		manifoldContactGenerator.generate(collision1.getObjectRef(), collision2.getObjectRef(), contactPoint, manifold.m_manifoldData);

		contactPointCount = manifold.m_manifoldData.getContactPointCount();

		results.push_back(manifold);
	}

	return contactPointCount;
}
