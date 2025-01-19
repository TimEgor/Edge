#include "SphereVsSphereCollisionDispatcher.h"

#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

uint32_t Edge::SphereVsSphereCollisionDispatcher::dispatch(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2, PhysicsCollisionContactID contactID, ContactManifoldDispatchingResultCollection& results)
{
	const PhysicsEntityCollisionShapeReference shape1 = collision1->getShape();
	const PhysicsEntityCollisionShapeReference shape2 = collision2->getShape();

	if (shape1->getType() != PhysicsSphereShape::PhysicsEntityCollisionShapeType
		|| shape2->getType() != PhysicsSphereShape::PhysicsEntityCollisionShapeType)
	{
		return 0;
	}

	const PhysicsSphereShape& sphere1 = shape1.getObjectCastRef<PhysicsSphereShape>();
	const PhysicsSphereShape& sphere2 = shape2.getObjectCastRef<PhysicsSphereShape>();

	const FloatVector3 position1 = collision1->getEntity()->getTransform()->getPosition();
	const FloatVector3 position2 = collision2->getEntity()->getTransform()->getPosition();

	const float radius1 = sphere1.getRadius();
	const float radius2 = sphere2.getRadius();

	ComputeVector delta = position2 - position1;
	const float distance = delta.getLength3();

	float depth = radius1 + radius2 - distance;

	if (depth < 0.0f)
	{
		return 0;
	}

	if (distance < Math::Epsilon)
	{
		depth = std::max(radius1, radius2);
		delta = FloatVector3UnitY * (radius1 + radius2);
	}

	const ComputeVector normal = NormalizeVector(delta);

	PhysicsCollisionContactPoint contactPoint;
	(position1 + normal * radius1).saveToFloatVector3(contactPoint.m_position1);
	(position2 - normal * radius2).saveToFloatVector3(contactPoint.m_position2);
	normal.saveToFloatVector3(contactPoint.m_normal);
	contactPoint.m_depth = depth;

	PhysicsInstanceContactManifold manifold;
	manifold.m_contactID = contactID;

	manifold.m_manifoldData.m_positions1.push_back(contactPoint.m_position1);
	manifold.m_manifoldData.m_positions2.push_back(contactPoint.m_position2);
	manifold.m_manifoldData.m_normal = contactPoint.m_normal;
	manifold.m_manifoldData.m_depth = contactPoint.m_depth;

	results.push_back(manifold);

	return 1;
}
