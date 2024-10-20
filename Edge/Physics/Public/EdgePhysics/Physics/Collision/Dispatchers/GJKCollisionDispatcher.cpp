#include "GJKCollisionDispatcher.h"

#include "EdgePhysics/Physics/Collision/GJK/GJK.h"

void Edge::GJKCollisionDispatcher::dispatch(const PhysicsEntityCollisionReference& collision1,
	const PhysicsEntityCollisionReference& collision2, PhysicsCollisionContactID contactID,
	ContactDispatchingResultCollection& results)
{
	GJK gjkTest;
	const GJK::Result gjkTestResult = gjkTest(collision1.getObjectRef(), collision2.getObjectRef(), 100);

	PhysicsCollisionContactPoint contactPoint;

	EPA epa;
	const bool epaResult = epa(collision1.getObjectRef(), collision2.getObjectRef(), gjkTestResult, 100, contactPoint);

	if (epaResult) {
		contactPoint.m_contactID = contactID;
		results.push_back(contactPoint);
	}
}
