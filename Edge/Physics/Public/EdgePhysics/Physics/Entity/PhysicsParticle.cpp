#include "PhysicsParticle.h"

void Edge::PhysicsParticle::updateTransformWithMotion(float deltaTime)
{
	if (!m_motion)
	{
		return;
	}

	PhysicsEntityTransformAccessor transformAccessor(m_transform);

	ComputeVector3 position(transformAccessor.getPosition());
	position += m_motion->getLinearVelocity() * deltaTime;
	transformAccessor.setPosition(position);
}
