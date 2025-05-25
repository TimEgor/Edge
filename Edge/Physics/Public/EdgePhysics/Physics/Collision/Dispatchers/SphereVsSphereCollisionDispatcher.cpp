#include "SphereVsSphereCollisionDispatcher.h"

#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

uint32_t Edge::SphereVsSphereCollisionDispatcher::dispatch(
	const PhysicsEntityCollisionReference& collision1,
	const PhysicsEntityCollisionReference& collision2,
	PhysicsCollisionContactID contactID,
	ContactManifoldDispatchingResultCollection& results
)
{
	const PhysicsEntityCollisionShapeReference shape1 = collision1->getShape();
	const PhysicsEntityCollisionShapeReference shape2 = collision2->getShape();

	if (!RTTI::IsObjectBasedOn<PhysicsSphereShape>(shape1.getObjectRef()) || !RTTI::IsObjectBasedOn<PhysicsSphereShape>(shape2.getObjectRef()))
	{
		return 0;
	}

	const PhysicsSphereShape& sphere1 = shape1.getObjectCastRef<PhysicsSphereShape>();
	const PhysicsSphereShape& sphere2 = shape2.getObjectCastRef<PhysicsSphereShape>();

	const ComputeVector3 position1 = collision1->getEntity()->getTransform()->getPosition();
	const ComputeVector3 position2 = collision2->getEntity()->getTransform()->getPosition();

	const ComputeValueType radius1 = sphere1.getRadius();
	const ComputeValueType radius2 = sphere2.getRadius();

	ComputeVector3 delta = position2 - position1;
	const ComputeValueType distance = delta.getLength();

	ComputeValueType depth = radius1 + radius2 - distance;

	if (depth < 0.0_ecv)
	{
		return 0;
	}

	if (distance < Math::Epsilon)
	{
		depth = std::max(radius1, radius2);
		delta = ComputeVector3UnitY * (radius1 + radius2);
	}


	PhysicsCollisionContactPoint contactPoint;
	contactPoint.m_normal = NormalizeComputeVector3(delta);
	contactPoint.m_position1 = position1 + contactPoint.m_normal * radius1;
	contactPoint.m_position2 = position2 - contactPoint.m_normal * radius2;
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
