#include "Fireworks.h"

#include "EdgeCommon/Math/ComputeVector3.h"
#include "EdgePhysics/Physics/Physics.h"

#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

EdgeDemo::FireworksParticle::FireworksParticle(FireworksParticleID id, const Edge::PhysicsSceneReference& physScene,
	const Edge::ComputeVector3& color, float maxLifeTime, const Edge::ComputeVector3& initialPosition,
	const Edge::ComputeVector3& initialDir, Edge::ComputeValueType explosionForce)
	: m_color(color), m_maxLifeTime(maxLifeTime), m_id(id)
{
	Edge::PhysicsParticleFactory::ParticleCreationParam particleCreationParam;
	Edge::PhysicsParticleFactory::ParticleMotionCreationParam particleMotionCreationParam;
	particleCreationParam.m_position = initialPosition;
	particleCreationParam.m_motionCreationParam = &particleMotionCreationParam;

	particleMotionCreationParam.m_mass = particleMass;
	particleMotionCreationParam.m_gravityFactor = 0.2f;
	particleMotionCreationParam.m_linearDampingFactor = 0.3f;

	m_physParticleEntity = Edge::GetPhysics().createParticle(&particleCreationParam);

	Edge::ComputeVector3 impulse(initialDir);
	impulse *= explosionForce;

	m_physParticleEntity->getMotion()->applyImpulse(impulse);

	physScene->addEntity(m_physParticleEntity);
}

EdgeDemo::FireworksParticle::~FireworksParticle()
{
	Edge::PhysicsSceneReference scene = m_physParticleEntity->getScene();
	scene->removeEntity(m_physParticleEntity);
}

void EdgeDemo::FireworksParticle::update(float deltaTime)
{
	m_lifeTime += deltaTime;
}

bool EdgeDemo::FireworksParticle::isAlive() const
{
	return m_lifeTime < m_maxLifeTime;
}

Edge::ComputeVector3 EdgeDemo::FireworksParticle::getPosition() const
{
	return m_physParticleEntity->getTransform()->getPosition();
}

const Edge::ComputeVector3& EdgeDemo::FireworksParticle::getColor() const
{
	return m_color;
}
