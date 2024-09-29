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
			entityPtr->setBodyMotion(createBodyMotion(bodyMotionCreationParam));
		}

		if (param->m_collisionParam)
		{
			PhysicsEntityCollisionReference collision = new PhysicsEntityCollision();
			collision->setShape(param->m_collisionParam->m_shape);

			entityPtr->setCollision(collision);
		}

		transform->setPosition(param->m_position);
		transform->setRotation(param->m_rotation);
	}

	return body;
}

Edge::PhysicsBodyMotionReference Edge::PhysicsBodyFactory::createBodyMotion(const BodyMotionCreationParam* param)
{
	PhysicsPositionAndRotationBasedMotion* motionPtr = new PhysicsPositionAndRotationBasedMotion();

	if (param)
	{
		motionPtr->setMass(param->m_mass);
		motionPtr->setGravityFactor(param->m_gravityFactor);
		motionPtr->setLinearDampingFactor(param->m_linearDampingFactor);

		motionPtr->setInertia(param->m_inertia);
		motionPtr->setAngularDampingFactor(param->m_angularDamping);
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

Edge::PhysicsEntityMotionReference Edge::PhysicsBodyFactory::createEntityMotion(const EntityMotionCreationParam* param)
{
	if (param && param->getType() != BodyMotionCreationParam::EntityCreationParamType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Ñreation param type is invalid.");
		return nullptr;
	}

	const BodyMotionCreationParam* bodyMotionCreationParam = static_cast<const BodyMotionCreationParam*>(param);

	return createBodyMotion(bodyMotionCreationParam);
}
