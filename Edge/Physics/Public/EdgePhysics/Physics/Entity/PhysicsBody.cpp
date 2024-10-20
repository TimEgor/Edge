#include "PhysicsBody.h"

#include "EdgeCommon/Math/Const.h"

void Edge::PhysicsBody::updateTransformWithMotion(float deltaTime)
{
	if (!m_motion)
	{
		return;
	}

	PhysicsEntityTransformUnsafeNotificationAccessor transformAccessor(m_transform);

	ComputeVector position(transformAccessor.getPosition());
	ComputeQuaternion rotation(transformAccessor.getRotation());

	ComputeVector linearVelocity(m_motion->getLinearVelocity());

	position += linearVelocity * deltaTime;

	ComputeVector angularVelocity(m_motion->getAngularVelocity());
	angularVelocity *= deltaTime;

	const float rotationSpeed = angularVelocity.length3Sqr();

	if (rotationSpeed > EDGE_EPSILON_SQR)
	{
		angularVelocity /= rotationSpeed;
		rotation *= ComputeQuaternionFromRotationAxis(angularVelocity, rotationSpeed);
		rotation.normalize();
	}

	transformAccessor.setPosition(position.getFloatVector3());
	transformAccessor.setRotation(rotation.getFloatQuaternion());
}
