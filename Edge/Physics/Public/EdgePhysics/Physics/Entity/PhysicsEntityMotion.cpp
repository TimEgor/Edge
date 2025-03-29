#include "PhysicsEntityMotion.h"

#include "PhysicsEntity.h"

#include <algorithm>

Edge::PhysicsEntityTransformReference Edge::PhysicsEntityMotion::getTransform() const
{
	const PhysicsEntityReference entity = getEntity();
	if (!entity)
	{
		return nullptr;
	}

	const PhysicsEntityTransformReference transform = entity->getTransform();
	if (!transform)
	{
		return nullptr;
	}

	if (!transform->isEntityLinkEqual(*this))
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity links aren't equal.");
		return nullptr;
	}

	return transform;
}

void Edge::PhysicsEntityMotion::setMass(ComputeValueType mass)
{
	if (ComputeValueType(mass) < 0.0)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set up negative mass value.");
		return;
	}

	m_mass = mass;
	m_invMass = ComputeValueType(1.0) / mass;
}

void Edge::PhysicsEntityMotion::setGravityFactor(ComputeValueType factor)
{
	if (ComputeValueType(0.0) > factor || factor > ComputeValueType(1.0))
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set up invalid gravity factor value.");
		return;
	}

	m_gravityFactor = factor;
}

Edge::ComputeVector3 Edge::PhysicsEntityMotion::getMassCenter() const
{
	return getTransform()->getPosition();
}

void Edge::PhysicsEntityMotion::getMassCenter(ComputeVector3& center) const
{
	return getTransform()->getPosition(center);
}

void Edge::PhysicsPositionBasedMotion::setLinearDampingFactor(ComputeValueType factor)
{
	if (ComputeValueType(0.0) > factor || factor > ComputeValueType(1.0))
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set up invalid linear damping factor value.");
		return;
	}

	m_linearDampingFactor = factor;
}

void Edge::PhysicsPositionBasedMotion::applyForce(const ComputeVector3& force)
{
	m_forceAccumulator += force;
}

void Edge::PhysicsPositionBasedMotion::applyImpulse(const ComputeVector3& impulse)
{
	m_linearVelocity += impulse * m_invMass;
}

void Edge::PhysicsPositionBasedMotion::applyAcceleration(float deltaTime, const ComputeVector3& gravity)
{
	m_linearVelocity += ((gravity * m_gravityFactor) + (m_forceAccumulator * m_invMass)) * deltaTime;
	m_linearVelocity *= std::max(ComputeValueType(0.0), ComputeValueType(1.0) - m_linearDampingFactor * deltaTime);

	clearForceAccumulator();
}

void Edge::PhysicsPositionBasedMotion::clearForceAccumulator()
{
	m_forceAccumulator = ComputeVector3Zero;
}

Edge::ComputeVector3 Edge::PhysicsPositionAndRotationBasedMotion::getPointLinearVelocity(const ComputeVector3& position) const
{
	ComputeVector3 velocity;
	getPointLinearVelocity(position, velocity);
	return velocity;
}

void Edge::PhysicsPositionAndRotationBasedMotion::getPointLinearVelocity(const ComputeVector3& position, ComputeVector3& velocity) const
{
	ComputeVector3 localPoint = position;
	localPoint -= getMassCenter();
	getLocalPointLinearVelocity(localPoint, velocity);
}

Edge::ComputeVector3 Edge::PhysicsPositionAndRotationBasedMotion::getLocalPointLinearVelocity(
	const ComputeVector3& position) const
{
	ComputeVector3 velocity;
	getLocalPointLinearVelocity(position, velocity);
	return velocity;
}

void Edge::PhysicsPositionAndRotationBasedMotion::getLocalPointLinearVelocity(const ComputeVector3& position, ComputeVector3& velocity) const
{
	velocity = m_linearVelocity + CrossComputeVector3(m_angularVelocity, position);
}

void Edge::PhysicsPositionAndRotationBasedMotion::setInertia(const ComputeVector3& inertia)
{
	m_inverseInertia = ComputeReciprocalComputeVector3(inertia);
}

void Edge::PhysicsPositionAndRotationBasedMotion::getLocalInverseInertiaTensor(ComputeMatrix3x3& inertia) const
{
	inertia = ComputeMatrix3x3Zero;
	inertia.setElement(0, 0, m_inverseInertia.getX());
	inertia.setElement(1, 1, m_inverseInertia.getY());
	inertia.setElement(2, 2, m_inverseInertia.getZ());
}

void Edge::PhysicsPositionAndRotationBasedMotion::getLocalInverseInertiaTensor(ComputeMatrix4x4& inertia) const
{
	inertia = ComputeMatrix4x4Identity;
	inertia.setElement(0, 0, m_inverseInertia.getX());
	inertia.setElement(1, 1, m_inverseInertia.getY());
	inertia.setElement(2, 2, m_inverseInertia.getZ());
}

void Edge::PhysicsPositionAndRotationBasedMotion::getWorldInverseInertiaTensor(ComputeMatrix3x3& inertia) const
{
	const ComputeMatrix3x3 rotation = getTransform()->getRotation().getRotationMatrix3x3();

	//ComputeMatrix3x3 localInverseInertiaTensor;
	//getLocalInverseInertiaTensor(localInverseInertiaTensor);

	//inertia = rotation * localInverseInertiaTensor * TransposeComputeMatrix3x3(rotation);

	const ComputeMatrix3x3 rotatedLocalInverseInertiaTensor(
		MultiplyComputeVector3Elements(ComputeVector3(m_inverseInertia.getX()), rotation.getColumn(0)),
		MultiplyComputeVector3Elements(ComputeVector3(m_inverseInertia.getY()), rotation.getColumn(1)),
		MultiplyComputeVector3Elements(ComputeVector3(m_inverseInertia.getZ()), rotation.getColumn(2))
	);

	inertia = rotation * TransposeComputeMatrix3x3(rotatedLocalInverseInertiaTensor);
}

void Edge::PhysicsPositionAndRotationBasedMotion::getWorldInverseInertiaTensor(ComputeMatrix4x4& inertia) const
{
	ComputeMatrix3x3 inertia3x3;
	getWorldInverseInertiaTensor(inertia3x3);

	inertia = inertia3x3;
	inertia.setElement(3, 3, ComputeValueType(1.0));
}

void Edge::PhysicsPositionAndRotationBasedMotion::applyForce(const ComputeVector3& force, const ComputeVector3& position)
{
	PhysicsPositionBasedMotion::applyForce(force);

	const ComputeVector3 localApplyingPoint = position - getMassCenter();
	const ComputeVector3 torque = CrossComputeVector3(localApplyingPoint, force);

	applyTorque(torque);
}

void Edge::PhysicsPositionAndRotationBasedMotion::applyImpulse(const ComputeVector3& impulse, const ComputeVector3& position)
{
	PhysicsPositionBasedMotion::applyImpulse(impulse);

	const ComputeVector3 localApplyingPoint = position - getMassCenter();
	const ComputeVector3 angularImpulse = CrossComputeVector3(localApplyingPoint, impulse);

	applyAngularImpulse(angularImpulse);
}

void Edge::PhysicsPositionAndRotationBasedMotion::applyTorque(const ComputeVector3& torque)
{
	m_torqueAccumulator += torque;
}

void Edge::PhysicsPositionAndRotationBasedMotion::applyAngularImpulse(const ComputeVector3& impulse)
{
	ComputeMatrix3x3 worldInverseInertiaTensor;
	getWorldInverseInertiaTensor(worldInverseInertiaTensor);

	m_angularVelocity += worldInverseInertiaTensor * impulse;
}

void Edge::PhysicsPositionAndRotationBasedMotion::applyAcceleration(float deltaTime, const ComputeVector3& gravity)
{
	ComputeMatrix3x3 worldInverseInertiaTensor;
	getWorldInverseInertiaTensor(worldInverseInertiaTensor);

	m_linearVelocity += ((gravity * m_gravityFactor) + (m_forceAccumulator * m_invMass)) * deltaTime;

	m_angularVelocity += worldInverseInertiaTensor * (m_torqueAccumulator * deltaTime);

	m_linearVelocity *= std::max(ComputeValueType(0.0), ComputeValueType(1.0) - m_linearDampingFactor * deltaTime);
	m_angularVelocity *= std::max(ComputeValueType(0.0), ComputeValueType(1.0) - m_angularDampingFactor * deltaTime);

	clearForceAccumulator();
	clearTorqueAccumulator();
}

void Edge::PhysicsPositionAndRotationBasedMotion::clearTorqueAccumulator()
{
	m_torqueAccumulator = ComputeVector3Zero;
}
