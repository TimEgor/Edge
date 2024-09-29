#include "SphereVsSphereCollisionDispatcher.h"

#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

void Edge::SphereVsSphereCollisionDispatcher::dispatch(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2, PhysicsCollisionContactID contactID, ContactDispatchingResultCollection& results)
{
	const PhysicsEntityCollisionShapeReference shape1 = collision1->getShape();
	const PhysicsEntityCollisionShapeReference shape2 = collision2->getShape();

	if (shape1->getType() != PhysicsSphereShape::PhysicsEntityCollisionShapeType
		|| shape2->getType() != PhysicsSphereShape::PhysicsEntityCollisionShapeType)
	{
		return;
	}

	const PhysicsSphereShape& sphere1 = shape1.getObjectCastRef<PhysicsSphereShape>();
	const PhysicsSphereShape& sphere2 = shape2.getObjectCastRef<PhysicsSphereShape>();

	const FloatVector3 position1 = collision1->getEntity()->getTransform()->getPosition();
	const FloatVector3 position2 = collision2->getEntity()->getTransform()->getPosition();

	const float radius1 = sphere1.getRadius();
	const float radius2 = sphere2.getRadius();

	ComputeVector delta = position2 - position1;
	const float distance = delta.length3();

	float depth = radius1 + radius2 - distance;

	if (depth < 0.0f)
	{
		return;
	}

	if (distance < EDGE_EPSILON)
	{
		depth = std::max(radius1, radius2);
		delta = FloatVector3UnitY * (radius1 + radius2);
	}

	const ComputeVector normal = normalizeVector(delta);

	PhysicsCollisionContactPoint contactPoint;
	contactPoint.m_contactID = contactID;
	(position1 + normal * radius1).saveToFloatVector3(contactPoint.m_position);
	normal.saveToFloatVector3(contactPoint.m_normal);
	contactPoint.m_depth = depth;

	results.push_back(contactPoint);
}
