#include "PhysicsBody.h"

#include "EdgeCommon/Math/Const.h"

void Edge::PhysicsBody::updateTransformWithMotion(float deltaTime)
{
	if (!m_motion)
	{
		return;
	}

	ComputeVector position(m_transform->getPosition());
	ComputeQuaternion rotation(m_transform->getRotation());

	ComputeVector linearVelocity(m_motion->getLinearVelocity());

	position += linearVelocity * deltaTime;

	ComputeVector angularVelocity(m_motion->getAngularVelocity());
	angularVelocity *= deltaTime;

	const float rotationSpeed = angularVelocity.length3();
	const float translationSpeed = linearVelocity.length3();

	const bool isUpdated = translationSpeed > EDGE_EPSILON || rotationSpeed > EDGE_EPSILON;

	if (rotationSpeed > EDGE_EPSILON)
	{
		angularVelocity /= rotationSpeed;
		rotation *= computeQuaternionFromRotationAxis(angularVelocity, rotationSpeed);
		rotation.normalize();
	}

	m_transform->setPosition(position.getFloatVector3());
	m_transform->setRotation(rotation.getFloatQuaternion());

	if (isUpdated)
	{
		//onTransformUpdate();
	}
}
