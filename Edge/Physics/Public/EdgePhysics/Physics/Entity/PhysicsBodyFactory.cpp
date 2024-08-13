#include "PhysicsBodyFactory.h"

Edge::PhysicsBodyReference Edge::PhysicsBodyFactory::createBodyEntity(const BodyCreationParam* param)
{
	PhysicsBodyTransformReference transform = new PhysicsPositionAndRotationBasedTransform();
	PhysicsBody* entityPtr = new PhysicsBody(transform);
	PhysicsBodyReference body = entityPtr;

	if (param)
	{
		if (param->m_motionCreationParam && param->m_motionCreationParam->getType() == BodyMotionCreationParam::EntityCreationParamType)
		{
			const BodyMotionCreationParam* bodyMotionCreationParam = static_cast<const BodyMotionCreationParam*>(param->m_motionCreationParam);
			entityPtr->setBodyMotion(createBodyMotion(body, bodyMotionCreationParam));
		}

		//if (param->m_collisionParam)
		//{
		//	ManagedPhysicsEntityCollision* collision = new ManagedPhysicsEntityCollision(body->getTransform());

		//	collision->setShape(param->m_collisionParam->m_shape);

		//	entityPtr->setCollision(collision);
		//}

		transform->setPosition(param->m_position);
		transform->setRotation(param->m_rotation);
	}

	return body;
}

Edge::PhysicsBodyMotionReference Edge::PhysicsBodyFactory::createBodyMotion(const PhysicsBodyReference& entity, const BodyMotionCreationParam* param)
{
	PhysicsPositionAndRotationBasedMotion* motionPtr = new PhysicsPositionAndRotationBasedMotion(entity->getBodyTransform());

	const BodyMotionCreationParam* bodyMotionCreationParam = static_cast<const BodyMotionCreationParam*>(param);
	if (param)
	{
		motionPtr->setMass(bodyMotionCreationParam->m_mass);
		motionPtr->setGravityFactor(bodyMotionCreationParam->m_gravityFactor);
		motionPtr->setLinearDampingFactor(bodyMotionCreationParam->m_linearDampingFactor);

		motionPtr->setInertia(bodyMotionCreationParam->m_inertia);
		motionPtr->setAngularDampingFactor(bodyMotionCreationParam->m_angularDamping);
	}

	return motionPtr;
}

Edge::PhysicsEntityReference Edge::PhysicsBodyFactory::createEntity(const EntityCreationParam* param)
{
	if (param && (param->getType() != BodyCreationParam::EntityCreationParamType))
	{
		EDGE_ASSERT_FAIL_MESSAGE("Ñreation param type is invalid.");
		return nullptr;
	}

	const BodyCreationParam* bodyCreationParam = static_cast<const BodyCreationParam*>(param);
	return createBodyEntity(bodyCreationParam);
}

Edge::PhysicsEntityMotionReference Edge::PhysicsBodyFactory::createEntityMotion(const PhysicsEntityReference& entity, const EntityMotionCreationParam* param)
{
	if (!entity || entity->getType() == PhysicsBody::PhysicsEntityType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity type is invalid.");
		return nullptr;
	}

	if (param && param->getType() != BodyMotionCreationParam::EntityCreationParamType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Ñreation param type is invalid.");
		return nullptr;
	}

	PhysicsBodyReference bodyEntity = entity.getObjectCast<PhysicsBody>();
	const BodyMotionCreationParam* bodyMotionCreationParam = static_cast<const BodyMotionCreationParam*>(param);

	return createBodyMotion(bodyEntity, bodyMotionCreationParam);
}
