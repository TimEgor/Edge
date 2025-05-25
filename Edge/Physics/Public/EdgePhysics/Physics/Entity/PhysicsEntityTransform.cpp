#include "PhysicsEntityTransform.h"

#include "PhysicsEntity.h"

void Edge::PhysicsEntityTransform::makeTransformChangingNotification() const
{
	const PhysicsEntityReference entity = getEntity();
	if (entity)
	{
		entity->makeTransformChangingNotification();
	}
}

void Edge::PhysicsPositionBasedTransform::setPositionRaw(const ComputeVector3& position)
{
	m_position = position;
}

void Edge::PhysicsPositionBasedTransform::setWorldTransformRaw(const Transform& transform)
{
	m_position = transform.getOrigin();
}

void Edge::PhysicsPositionBasedTransform::setPosition(const ComputeVector3& position)
{
	setPositionRaw(position);
	makeTransformChangingNotification();
}

Edge::Transform Edge::PhysicsPositionBasedTransform::getWorldTransform() const
{
	Transform transform;
	getWorldTransform(transform);

	return transform;
}

void Edge::PhysicsPositionBasedTransform::getWorldTransform(Transform& transform) const
{
	transform.setAxisX(ComputeVector3UnitX);
	transform.setAxisY(ComputeVector3UnitY);
	transform.setAxisZ(ComputeVector3UnitZ);
	transform.setOrigin(m_position);
}

void Edge::PhysicsPositionBasedTransform::setWorldTransform(const Transform& transform)
{
	setWorldTransformRaw(transform);
	makeTransformChangingNotification();
}

void Edge::PhysicsPositionAndRotationBasedTransform::setRotationRaw(const ComputeQuaternion& rotation)
{
	m_rotation = rotation;
}

void Edge::PhysicsPositionAndRotationBasedTransform::setWorldTransformRaw(const Transform& transform)
{
	m_position = transform.getOrigin();
	m_rotation = transform.getRotationQuaternion();
}

void Edge::PhysicsPositionAndRotationBasedTransform::setRotation(const ComputeQuaternion& rotation)
{
	setRotationRaw(rotation);
	makeTransformChangingNotification();
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
	setWorldTransformRaw(transform);
	makeTransformChangingNotification();
}

Edge::PhysicsEntityTransformNotificationFreeAccessor::PhysicsEntityTransformNotificationFreeAccessor(const PhysicsEntityTransformReference& transform)
	: m_transform(transform)
{
	EDGE_ASSERT(transform);
}

Edge::ComputeVector3 Edge::PhysicsEntityTransformNotificationFreeAccessor::getPosition() const
{
	return m_transform->getPosition();
}

void Edge::PhysicsEntityTransformNotificationFreeAccessor::getPosition(ComputeVector3& position) const
{
	m_transform->getPosition(position);
}

void Edge::PhysicsEntityTransformNotificationFreeAccessor::setPosition(const ComputeVector3& position)
{
	m_transform->setPositionRaw(position);
}

Edge::ComputeQuaternion Edge::PhysicsEntityTransformNotificationFreeAccessor::getRotation() const
{
	return m_transform->getRotation();
}

void Edge::PhysicsEntityTransformNotificationFreeAccessor::getRotation(ComputeQuaternion& rotation) const
{
	m_transform->getRotation(rotation);
}

void Edge::PhysicsEntityTransformNotificationFreeAccessor::setRotation(const ComputeQuaternion& rotation)
{
	m_transform->setRotationRaw(rotation);
}

Edge::Transform Edge::PhysicsEntityTransformNotificationFreeAccessor::getWorldTransform() const
{
	return m_transform->getWorldTransform();
}

void Edge::PhysicsEntityTransformNotificationFreeAccessor::getWorldTransform(Transform& transform) const
{
	m_transform->getWorldTransform(transform);
}

void Edge::PhysicsEntityTransformNotificationFreeAccessor::setWorldTransform(const Transform& transform)
{
	m_transform->setWorldTransformRaw(transform);
}

void Edge::PhysicsEntityTransformNotificationFreeAccessor::makeTransformChangingNotification()
{
	m_transform->makeTransformChangingNotification();
}

Edge::PhysicsEntityTransformAccessor::~PhysicsEntityTransformAccessor()
{
	if (m_isChanged)
	{
		makeTransformChangingNotification();
	}
}

void Edge::PhysicsEntityTransformAccessor::setPosition(const ComputeVector3& position)
{
	PhysicsEntityTransformNotificationFreeAccessor::setPosition(position);
	m_isChanged = true;
}

void Edge::PhysicsEntityTransformAccessor::setRotation(const ComputeQuaternion& rotation)
{
	PhysicsEntityTransformNotificationFreeAccessor::setRotation(rotation);
	m_isChanged = true;
}

void Edge::PhysicsEntityTransformAccessor::setWorldTransform(const Transform& transform)
{
	PhysicsEntityTransformNotificationFreeAccessor::setWorldTransform(transform);
	m_isChanged = true;
}

void Edge::PhysicsEntityTransformAccessor::makeTransformChangingNotification()
{
	PhysicsEntityTransformNotificationFreeAccessor::makeTransformChangingNotification();
	m_isChanged = false;
}
