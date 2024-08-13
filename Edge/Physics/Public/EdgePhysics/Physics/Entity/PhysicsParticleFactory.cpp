#include "PhysicsParticleFactory.h"

Edge::PhysicsParticleReference Edge::PhysicsParticleFactory::createParticleEntity(const ParticleCreationParam* param)
{
	PhysicsParticleTransformReference transform = new PhysicsPositionAndRotationBasedTransform();
	PhysicsParticle* entityPtr = new PhysicsParticle(transform);
	PhysicsParticleReference particle = entityPtr;

	if (param)
	{
		if (param->m_motionCreationParam && param->m_motionCreationParam->getType() == ParticleMotionCreationParam::EntityCreationParamType)
		{
			const ParticleMotionCreationParam* particleMotionCreationParam = static_cast<const ParticleMotionCreationParam*>(param->m_motionCreationParam);
			entityPtr->setParticleMotion(createParticleMotion(particle, particleMotionCreationParam));
		}

		//if (param->m_collisionParam)
		//{
		//	ManagedPhysicsEntityCollision* collision = new ManagedPhysicsEntityCollision(body->getTransform());

		//	collision->setShape(param->m_collisionParam->m_shape);

		//	entityPtr->setCollision(collision);
		//}

		transform->setPosition(param->m_position);
	}

	return particle;
}

Edge::PhysicsParticleMotionReference Edge::PhysicsParticleFactory::createParticleMotion(
	const PhysicsParticleReference& entity, const ParticleMotionCreationParam* param)
{
	PhysicsPositionBasedMotion* motionPtr = new PhysicsPositionBasedMotion(entity->getParticleTransform());

	const ParticleMotionCreationParam* bodyMotionCreationParam = static_cast<const ParticleMotionCreationParam*>(param);
	if (param)
	{
		motionPtr->setMass(bodyMotionCreationParam->m_mass);
		motionPtr->setGravityFactor(bodyMotionCreationParam->m_gravityFactor);
		motionPtr->setLinearDampingFactor(bodyMotionCreationParam->m_linearDampingFactor);
	}

	return motionPtr;
}

Edge::PhysicsEntityReference Edge::PhysicsParticleFactory::createEntity(const EntityCreationParam* param)
{
	if (param && (param->getType() != ParticleCreationParam::EntityCreationParamType))
	{
		EDGE_ASSERT_FAIL_MESSAGE("Ñreation param type is invalid.");
		return nullptr;
	}

	const ParticleCreationParam* particleCreationParam = static_cast<const ParticleCreationParam*>(param);
	return createParticleEntity(particleCreationParam);
}

Edge::PhysicsEntityMotionReference Edge::PhysicsParticleFactory::createEntityMotion(
	const PhysicsEntityReference& entity, const EntityMotionCreationParam* param)
{
	if (!entity || entity->getType() == PhysicsParticle::PhysicsEntityType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity type is invalid.");
		return nullptr;
	}

	if (param && param->getType() != ParticleMotionCreationParam::EntityCreationParamType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Ñreation param type is invalid.");
		return nullptr;
	}

	PhysicsParticleReference bodyEntity = entity.getObjectCast<PhysicsParticle>();
	const ParticleMotionCreationParam* bodyMotionCreationParam = static_cast<const ParticleMotionCreationParam*>(param);

	return createParticleMotion(bodyEntity, bodyMotionCreationParam);
}
