#include "PhysicsBody.h"

void Edge::PhysicsBody::updateTransformWithMotion(float deltaTime)
{
	if (!m_motion)
	{
		return;
	}

	PhysicsEntityTransformAccessor transformAccessor(m_transform);

	ComputeVector3 position = transformAccessor.getPosition();
	ComputeQuaternion rotation = transformAccessor.getRotation();

	//
	const ComputeVector3 linearDelta = m_motion->getLinearVelocity() * deltaTime;
	position += linearDelta;

	const ComputeVector3 angularDelta = m_motion->getAngularVelocity() * deltaTime;
	const ComputeValueType rotationSpeed = angularDelta.getLength();

	if (rotationSpeed > Math::Epsilon)
	{
		rotation = ComputeQuaternion(angularDelta, rotationSpeed) * rotation;
		rotation.normalize();
	}

	//
	transformAccessor.setPosition(position);
	transformAccessor.setRotation(rotation);
}
