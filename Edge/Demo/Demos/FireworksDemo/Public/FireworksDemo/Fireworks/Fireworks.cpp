#include "Fireworks.h"

#include "TinySimCommon/Math/ComputeVector.h"

#include "TinySimPhysics/Physics/PhysicsCore.h"
#include "TinySimPhysics/Physics/Scene/IPhysicsParticleFactory.h"
#include "TinySimPhysics/Physics/Scene/IPhysicsScene.h"

TS_DEMO::FireworksParticle::FireworksParticle(FireworksParticleID id, const TS::PhysicsSceneReference& physScene,
                                              const TS::FloatVector3& color, float maxLifeTime,
                                              const TS::FloatVector3& initialPosition, const TS::FloatVector3& initialDir, float explosionForce)
		: m_color(color), m_maxLifeTime(maxLifeTime), m_id(id)
{
	TS::IPhysicsParticleFactory::ParticleCreationParam particleCreationParam;
	TS::IPhysicsParticleFactory::ParticleMotionCreationParam particleMotionCreationParam;
	particleCreationParam.m_position = initialPosition;
	particleCreationParam.m_motionCreationParam = &particleMotionCreationParam;

	particleMotionCreationParam.m_mass = particleMass;
	particleMotionCreationParam.m_gravityFactor = 0.5f;
	particleMotionCreationParam.m_linearDampingFactor = 0.3f;

	m_physParticleEntity = TS::GetPhysics().getEntityFactories().getParticleFactory().createParticleEntity(&particleCreationParam);

	TS::ComputeVector impulse(initialDir);
	impulse *= explosionForce;

	m_physParticleEntity->getMotion()->applyImpulse(impulse.getFloatVector3());

	physScene->addEntity(m_physParticleEntity);
}

TS_DEMO::FireworksParticle::~FireworksParticle()
{
	m_physParticleEntity->getSceneContext().getScene().getReference()->removeEntity(TS::PhysicsSceneEntityReference(m_physParticleEntity));
}

void TS_DEMO::FireworksParticle::update(float deltaTime)
{
	m_lifeTime += deltaTime;
}

bool TS_DEMO::FireworksParticle::isAlive() const
{
	return m_lifeTime < m_maxLifeTime;
}

TS::FloatVector3 TS_DEMO::FireworksParticle::getPosition() const
{
	return m_physParticleEntity->getTransform()->getPosition();
}

const TS::FloatVector3& TS_DEMO::FireworksParticle::getColor() const
{
	return m_color;
}
