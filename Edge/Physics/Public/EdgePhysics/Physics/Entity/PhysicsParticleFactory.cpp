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

		const EntityCollisionCreationParam* collisionParam = param->m_collisionParam;
		if (collisionParam)
		{
			PhysicsEntityCollisionReference collision = new PhysicsEntityCollision();
			collision->setShape(collisionParam->m_shape);
			collision->setFriction(collisionParam->m_friction);
			collision->setElasticity(collisionParam->m_elasticity);

			entityPtr->setCollision(collision);
		}

		transform->setPosition(param->m_position);
	}

	return particle;
}

Edge::PhysicsParticleMotionReference Edge::PhysicsParticleFactory::createParticleMotion(const ParticleMotionCreationParam* param)
{
	PhysicsPositionBasedMotion* motionPtr = new PhysicsPositionBasedMotion();

	if (param)
	{
		motionPtr->setMass(param->m_mass);
		motionPtr->setGravityFactor(param->m_gravityFactor);
		motionPtr->setLinearDampingFactor(param->m_linearDampingFactor);
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
