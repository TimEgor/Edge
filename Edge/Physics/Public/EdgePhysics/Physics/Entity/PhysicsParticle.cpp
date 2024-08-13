#include "PhysicsParticle.h"

void Edge::PhysicsParticle::updateTransformWithMotion(float deltaTime)
{
	if (!m_motion)
	{
		return;
	}

	ComputeVector position(m_transform->getPosition());
	position += ComputeVector(m_motion->getLinearVelocity()) * deltaTime;
	m_transform->setPosition(position.getFloatVector3());
}
