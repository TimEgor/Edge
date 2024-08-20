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
			entityPtr->setParticleMotion(createParticleMotion(particleMotionCreationParam));
		}

		if (param->m_collisionParam)
		{
			PhysicsEntityCollisionReference collision = new PhysicsEntityCollision();
			collision->setShape(param->m_collisionParam->m_shape);

			entityPtr->setCollision(collision);
		}

		transform->setPosition(param->m_position);
	}

	return particle;
}

Edge::PhysicsParticleMotionReference Edge::PhysicsParticleFactory::createParticleMotion(const ParticleMotionCreationParam* param)
{
	PhysicsPositionBasedMotion* motionPtr = new PhysicsPositionBasedMotion();

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

Edge::PhysicsEntityMotionReference Edge::PhysicsParticleFactory::createEntityMotion(const EntityMotionCreationParam* param)
{
	if (param && param->getType() != ParticleMotionCreationParam::EntityCreationParamType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Ñreation param type is invalid.");
		return nullptr;
	}

	const ParticleMotionCreationParam* bodyMotionCreationParam = static_cast<const ParticleMotionCreationParam*>(param);

	return createParticleMotion(bodyMotionCreationParam);
}
