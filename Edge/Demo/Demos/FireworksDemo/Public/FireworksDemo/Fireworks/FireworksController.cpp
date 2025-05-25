#include "FireworksController.h"

#include "EdgeCommon/Random/Random.h"
#include "EdgeCommon/Math/ComputeVector3.h"

EdgeDemo::FireworksParticleController::FireworksParticleController(const Edge::PhysicsSceneReference& physScene,
	const Edge::ComputeVector3& minSpawnAreaPos, const Edge::ComputeVector3& maxSpawnAreaPos)
	: m_physScene(physScene), m_minSpawnAreaPos(minSpawnAreaPos), m_maxSpawnAreaPos(maxSpawnAreaPos)
{
	m_fireworksParticles.init();
}

EdgeDemo::FireworksParticleController::~FireworksParticleController()
{
	m_fireworksParticles.release();
}

void EdgeDemo::FireworksParticleController::spawn()
{
	const Edge::ComputeVector3 color = generateColor();
	const Edge::ComputeVector3 position = generatePosition(m_minSpawnAreaPos, m_maxSpawnAreaPos);

	const Edge::ComputeValueType baseLifetime = Edge::TypedRandom(minParticleLifetime, maxParticleLifetime);

	const Edge::ComputeValueType baseExplositionForce = Edge::TypedRandom(minExplosionForce, maxExplosionForce);

	const uint32_t particleCount = Edge::TypedRandom(minParticleCount, maxParticleCount);
	for (uint32_t particleIndex = 0; particleIndex < particleCount; ++particleIndex)
	{
		const Edge::ComputeValueType lifetime = baseLifetime + Edge::TypedRandom(particleLifetimeRange);
		const Edge::ComputeValueType explosionForce = baseExplositionForce + Edge::TypedRandom(explosionForceRange);

		Edge::ComputeVector3 dir(generatePosition(Edge::ComputeVector3NegativeOne, Edge::ComputeVector3One));
		dir.normalize();

		ParticleCollection::NewElementInfo newParticleInfo = m_fireworksParticles.addElementRaw();
		FireworksParticle* newParticle = new (newParticleInfo.m_elementPtr) FireworksParticle(
			newParticleInfo.m_elementHandle.getKey(), m_physScene, color, lifetime, position, dir, explosionForce);

		m_fireworksParticlePtrs.push_back(newParticle);
	}
}

Edge::ComputeVector3 EdgeDemo::FireworksParticleController::generateColor()
{
	Edge::ComputeVector3 color = Edge::ComputeVector3Zero;

	uint32_t elements[3] = { 0, 1, 2 };

	uint32_t colorElementIndex = Edge::TypedRandom(2);
	uint32_t colorElelement = elements[colorElementIndex];
	elements[colorElementIndex] = elements[2];
	color[colorElelement] = 1.0f;

	colorElementIndex = Edge::TypedRandom(1);
	colorElelement = elements[colorElementIndex];
	elements[colorElementIndex] = elements[1];
	color[colorElelement] = 0.0f;

	colorElelement = elements[0];
	color[colorElelement] = Edge::TypedRandom(1.0f);

	return color;
}

Edge::ComputeVector3 EdgeDemo::FireworksParticleController::generatePosition(const Edge::ComputeVector3& minPos, const Edge::ComputeVector3& maxPos)
{
	return Edge::ComputeVector3(
		Edge::TypedRandom(minPos.getX(), maxPos.getX()),
		Edge::TypedRandom(minPos.getY(), maxPos.getY()),
		Edge::TypedRandom(minPos.getZ(), maxPos.getZ())
	);
}

void EdgeDemo::FireworksParticleController::update(float deltaTime)
{
	for (size_t particleIndex = 0; particleIndex < m_fireworksParticlePtrs.size();)
	{
		FireworksParticle* particle = m_fireworksParticlePtrs[particleIndex];
		particle->update(deltaTime);

		if (!particle->isAlive())
		{
			m_fireworksParticles.removeElement(particle->getID());

			m_fireworksParticlePtrs[particleIndex] = m_fireworksParticlePtrs[m_fireworksParticlePtrs.size() - 1];
			m_fireworksParticlePtrs.pop_back();

			continue;
		}

		++particleIndex;
	}

	m_spawningTimeDelay -= deltaTime;
	if (m_spawningTimeDelay <= 0.0f)
	{
		spawn();

		m_spawningTimeDelay = Edge::TypedRandom(minSpawningDelay, maxSpawningDelay);
	}
}

void EdgeDemo::FireworksParticleController::fillRenderData(
	Edge::DebugVisualizationDataController& debugVisualizationData) const
{
	for (const FireworksParticle* particle : m_fireworksParticlePtrs)
	{
		debugVisualizationData.addPoint(particle->getPosition().getFloatVector3(), particle->getColor().getFloatVector3());
	}
}
