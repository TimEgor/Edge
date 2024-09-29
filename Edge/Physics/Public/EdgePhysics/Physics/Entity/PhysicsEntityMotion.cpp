#include "PhysicsEntityMotion.h"

#include <algorithm>

#include "PhysicsEntity.h"

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

void Edge::PhysicsEntityMotion::setMass(float mass)
{
	if (mass < 0.0f)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set up negative mass value.");
		return;
	}

	m_mass = mass;
	m_invMass = 1.0f / mass;
}

void Edge::PhysicsEntityMotion::setGravityFactor(float factor)
{
	if (0.0f > factor || factor > 1.0f)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set up invalid gravity factor value.");
		return;
	}

	m_gravityFactor = factor;
}

void Edge::PhysicsEntityMotion::setFriction(float friction)
{
	if (0.0f > friction || friction > 1.0f)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set up invalid friction value.");
		return;
	}

	m_friction = friction;
}

void Edge::PhysicsPositionBasedMotion::setLinearDampingFactor(float factor)
{
	if (0.0f > factor || factor > 1.0f)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set up invalid linear damping factor value.");
		return;
	}

	m_linearDampingFactor = factor;
}

void Edge::PhysicsPositionBasedMotion::applyForce(const FloatVector3& force)
{
	ComputeVector forceAccumulator(m_forceAccumulator);
	forceAccumulator += force;
	forceAccumulator.saveToFloatVector3(m_forceAccumulator);
}

void Edge::PhysicsPositionBasedMotion::applyImpulse(const FloatVector3& impulse)
{
	ComputeVector linearVelocity(m_linearVelocity);
	linearVelocity += ComputeVector(impulse) * m_invMass;
	linearVelocity.saveToFloatVector3(m_linearVelocity);
}

void Edge::PhysicsPositionBasedMotion::applyAcceleration(float deltaTime, const FloatVector3& gravity)
{
	ComputeVector linearVelocity(m_linearVelocity);

	linearVelocity += ((ComputeVector(gravity) * m_gravityFactor) + (ComputeVector(m_forceAccumulator) * m_invMass)) * deltaTime;

	linearVelocity *= std::max(0.0f, 1.0f - m_linearDampingFactor * deltaTime);

	linearVelocity.saveToFloatVector3(m_linearVelocity);

	clearForceAccumulator();
}

void Edge::PhysicsPositionBasedMotion::clearForceAccumulator()
{
	m_forceAccumulator = FloatVector3Zero;
}

void Edge::PhysicsPositionAndRotationBasedMotion::setInertia(const FloatVector3& inertia)
{
	ComputeVector computeInertia(inertia);
	computeInertia.reciprocal();
	computeInertia.saveToFloatVector3(m_inverseInertia);
}

void Edge::PhysicsPositionAndRotationBasedMotion::getInverseInertiaTensor(FloatMatrix3x3& inertia) const
{
	inertia = FloatMatrix3x3();
	inertia.m_m11 = m_inverseInertia.m_x;
	inertia.m_m22 = m_inverseInertia.m_y;
	inertia.m_m33 = m_inverseInertia.m_z;
}

void Edge::PhysicsPositionAndRotationBasedMotion::getWorldInverseInertiaTensor(FloatMatrix3x3& inertia) const
{
	FloatMatrix3x3 inverseInertiaTensor;
	getInverseInertiaTensor(inverseInertiaTensor);

	const ComputeMatrix rotation = computeMatrixFromRotationQuaternion(getTransform()->getRotation());
	const ComputeMatrix worldInverseInertiaTensor = transposeMatrix(rotation) * ComputeMatrix(inverseInertiaTensor) * rotation;

	worldInverseInertiaTensor.saveToMatrix3x3(inertia);
}

void Edge::PhysicsPositionAndRotationBasedMotion::applyForce(const FloatVector3& force, const FloatVector3& position)
{
	PhysicsPositionBasedMotion::applyForce(force);

	ComputeVector localApplyingPoint = position;
	localApplyingPoint -= getTransform()->getPosition();
	const ComputeVector torque = crossVector3(localApplyingPoint, force);

	applyTorque(torque.getFloatVector3());
}

void Edge::PhysicsPositionAndRotationBasedMotion::applyImpulse(const FloatVector3& impulse, const FloatVector3& position)
{
	PhysicsPositionBasedMotion::applyImpulse(impulse);

	ComputeVector localApplyingPoint = position;
	localApplyingPoint -= getTransform()->getPosition();
	const ComputeVector angularImpulse = crossVector3(localApplyingPoint, impulse);

	applyAngularImpulse(angularImpulse.getFloatVector3());
}

void Edge::PhysicsPositionAndRotationBasedMotion::applyTorque(const FloatVector3& torque)
{
	ComputeVector torqueAccumulator(m_torqueAccumulator);
	torqueAccumulator += torque;
	torqueAccumulator.saveToFloatVector3(m_torqueAccumulator);
}

void Edge::PhysicsPositionAndRotationBasedMotion::applyAngularImpulse(const FloatVector3& impulse)
{
	FloatMatrix3x3 inverseInertiaTensor;
	getWorldInverseInertiaTensor(inverseInertiaTensor);
	const ComputeMatrix worldInverseInertiaTensor = inverseInertiaTensor;

	ComputeVector angularVelocity(m_angularVelocity);
	angularVelocity += worldInverseInertiaTensor * ComputeVector(impulse);
	angularVelocity.saveToFloatVector3(m_angularVelocity);
}

void Edge::PhysicsPositionAndRotationBasedMotion::applyAcceleration(float deltaTime, const FloatVector3& gravity)
{
	FloatMatrix3x3 inverseInertiaTensor;
	getWorldInverseInertiaTensor(inverseInertiaTensor);
	const ComputeMatrix worldInverseInertiaTensor = inverseInertiaTensor;

	ComputeVector linearVelocity(m_linearVelocity);
	ComputeVector angularVelocity(m_angularVelocity);

	linearVelocity += ((ComputeVector(gravity) * m_gravityFactor) + (ComputeVector(m_forceAccumulator) * m_invMass)) * deltaTime;
	angularVelocity += worldInverseInertiaTensor * ComputeVector(m_torqueAccumulator) * deltaTime;

	linearVelocity *= std::max(0.0f, 1.0f - m_linearDampingFactor * deltaTime);
	angularVelocity *= std::max(0.0f, 1.0f - m_angularDampingFactor * deltaTime);

	linearVelocity.saveToFloatVector3(m_linearVelocity);
	angularVelocity.saveToFloatVector3(m_angularVelocity);

	clearForceAccumulator();
	clearTorqueAccumulator();
}

void Edge::PhysicsPositionAndRotationBasedMotion::clearTorqueAccumulator()
{
	m_torqueAccumulator = FloatVector3Zero;
}
