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

void Edge::PhysicsPositionBasedTransform::setPositionRaw(const FloatVector3& position)
{
	m_position = position;
}

void Edge::PhysicsPositionBasedTransform::setWorldTransformRaw(const Transform& transform)
{
	m_position = transform.getOrigin();
}

void Edge::PhysicsPositionBasedTransform::setPosition(const FloatVector3& position)
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
	transform.setAxisX(FloatVector3UnitX);
	transform.setAxisY(FloatVector3UnitY);
	transform.setAxisZ(FloatVector3UnitZ);
	transform.setOrigin(m_position);
}

void Edge::PhysicsPositionBasedTransform::setWorldTransform(const Transform& transform)
{
	setWorldTransformRaw(transform);
	makeTransformChangingNotification();
}

void Edge::PhysicsPositionAndRotationBasedTransform::setRotationRaw(const FloatQuaternion& rotation)
{
	m_rotation = rotation;
}

void Edge::PhysicsPositionAndRotationBasedTransform::setWorldTransformRaw(const Transform& transform)
{
	m_position = transform.getOrigin();
	m_rotation = transform.getRotationQuaternion();
}

void Edge::PhysicsPositionAndRotationBasedTransform::setRotation(const FloatQuaternion& rotation)
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

Edge::PhysicsEntityTransformUnsafeNotificationAccessor::PhysicsEntityTransformUnsafeNotificationAccessor(const PhysicsEntityTransformReference& transform)
	: m_transform(transform)
{
	EDGE_ASSERT(transform);
}

Edge::PhysicsEntityTransformUnsafeNotificationAccessor::~PhysicsEntityTransformUnsafeNotificationAccessor()
{
	if (m_isChanged)
	{
		makeTransformChangingNotification();
	}
}

Edge::FloatVector3 Edge::PhysicsEntityTransformUnsafeNotificationAccessor::getPosition() const
{
	return m_transform->getPosition();
}

void Edge::PhysicsEntityTransformUnsafeNotificationAccessor::getPosition(FloatVector3& position) const
{
	return m_transform->getPosition(position);
}

void Edge::PhysicsEntityTransformUnsafeNotificationAccessor::setPosition(const FloatVector3& position)
{
	m_transform->setPositionRaw(position);
	m_isChanged = true;
}

Edge::FloatQuaternion Edge::PhysicsEntityTransformUnsafeNotificationAccessor::getRotation() const
{
	return m_transform->getRotation();
}

void Edge::PhysicsEntityTransformUnsafeNotificationAccessor::getRotation(FloatQuaternion& rotation) const
{
	return m_transform->getRotation(rotation);
}

void Edge::PhysicsEntityTransformUnsafeNotificationAccessor::setRotation(const FloatQuaternion& rotation)
{
	m_transform->setRotationRaw(rotation);
	m_isChanged = true;
}

Edge::Transform Edge::PhysicsEntityTransformUnsafeNotificationAccessor::getWorldTransform() const
{
	return m_transform->getWorldTransform();
}

void Edge::PhysicsEntityTransformUnsafeNotificationAccessor::getWorldTransform(Transform& transform) const
{
	return m_transform->getWorldTransform(transform);
}

void Edge::PhysicsEntityTransformUnsafeNotificationAccessor::setWorldTransform(const Transform& transform)
{
	m_transform->setWorldTransformRaw(transform);
	m_isChanged = true;
}

void Edge::PhysicsEntityTransformUnsafeNotificationAccessor::makeTransformChangingNotification()
{
	m_transform->makeTransformChangingNotification();
	m_isChanged = false;
}
