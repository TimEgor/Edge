#include "PhysicsParticle.h"

void Edge::PhysicsParticle::updateTransformWithMotion(float deltaTime)
{
	if (!m_motion)
	{
		return;
	}

	PhysicsEntityTransformUnsafeNotificationAccessor transformAccessor(m_transform);

	ComputeVector position(transformAccessor.getPosition());
	position += ComputeVector(m_motion->getLinearVelocity()) * deltaTime;
	transformAccessor.setPosition(position.getFloatVector3());
}
