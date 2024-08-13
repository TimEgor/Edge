#include "Fireworks.h"

#include "EdgeCommon/Math/ComputeVector.h"
#include "EdgePhysics/Physics/Physics.h"

#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

EdgeDemo::FireworksParticle::FireworksParticle(FireworksParticleID id, const Edge::PhysicsSceneReference& physScene,
	const Edge::FloatVector3& color, float maxLifeTime,
	const Edge::FloatVector3& initialPosition, const Edge::FloatVector3& initialDir, float explosionForce)
	: m_color(color), m_maxLifeTime(maxLifeTime), m_id(id)
{
	Edge::PhysicsParticleFactory::ParticleCreationParam particleCreationParam;
	Edge::PhysicsParticleFactory::ParticleMotionCreationParam particleMotionCreationParam;
	particleCreationParam.m_position = initialPosition;
	particleCreationParam.m_motionCreationParam = &particleMotionCreationParam;

	particleMotionCreationParam.m_mass = particleMass;
	particleMotionCreationParam.m_gravityFactor = 0.5f;
	particleMotionCreationParam.m_linearDampingFactor = 0.3f;

	m_physParticleEntity = Edge::GetPhysics().createParticle(&particleCreationParam);

	Edge::ComputeVector impulse(initialDir);
	impulse *= explosionForce;

	m_physParticleEntity->getMotion()->applyImpulse(impulse.getFloatVector3());

	physScene->addEntity(m_physParticleEntity);
}

EdgeDemo::FireworksParticle::~FireworksParticle()
{
	Edge::PhysicsSceneReference scene = m_physParticleEntity->getScene();
	scene->removeEntity(m_physParticleEntity.getObject());
}

void EdgeDemo::FireworksParticle::update(float deltaTime)
{
	m_lifeTime += deltaTime;
}

bool EdgeDemo::FireworksParticle::isAlive() const
{
	return m_lifeTime < m_maxLifeTime;
}

Edge::FloatVector3 EdgeDemo::FireworksParticle::getPosition() const
{
	return m_physParticleEntity->getTransform()->getPosition();
}

const Edge::FloatVector3& EdgeDemo::FireworksParticle::getColor() const
{
	return m_color;
}
