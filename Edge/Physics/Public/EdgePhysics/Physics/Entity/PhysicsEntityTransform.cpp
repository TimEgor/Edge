#include "PhysicsEntityTransform.h"

#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

void Edge::PhysicsPositionBasedTransform::setPosition(const FloatVector3& position)
{
	m_position = position;
}

Edge::Transform Edge::PhysicsPositionBasedTransform::getWorldTransform() const
{
	Transform transform;
	getWorldTransform(transform);

	return transform;
}

void Edge::PhysicsPositionBasedTransform::getWorldTransform(Transform& transform) const
{
	transform.setAxisX(FloatVector3UnitX);
	transform.setAxisY(FloatVector3UnitY);
	transform.setAxisZ(FloatVector3UnitZ);
	transform.setOrigin(m_position);
}

void Edge::PhysicsPositionBasedTransform::setWorldTransform(const Transform& transform)
{
	m_position = transform.getOrigin();
}

void Edge::PhysicsPositionAndRotationBasedTransform::setRotation(const FloatQuaternion& rotation)
{
	m_rotation = rotation;
}

Edge::Transform Edge::PhysicsPositionAndRotationBasedTransform::getWorldTransform() const
{
	Transform transform;
	getWorldTransform(transform);

	return transform;
}

void Edge::PhysicsPositionAndRotationBasedTransform::getWorldTransform(Transform& transform) const
{
	transform.setRotationQuaternion(m_rotation);
	transform.setOrigin(m_position);
}

void Edge::PhysicsPositionAndRotationBasedTransform::setWorldTransform(const Transform& transform)
{
	m_position = transform.getOrigin();
	m_rotation = transform.getRotationQuaternion();
}