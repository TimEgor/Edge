#include "FireworksController.h"

#include "EdgeCommon/Random/Random.h"
#include "EdgeCommon/Math/ComputeVector.h"

EdgeDemo::FireworksParticleController::FireworksParticleController(const Edge::PhysicsSceneReference& physScene,
	const Edge::FloatVector3& minSpawnAreaPos, const Edge::FloatVector3& maxSpawnAreaPos)
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
	const Edge::FloatVector3 color = generateColor();
	const Edge::FloatVector3 position = generatePosition(m_minSpawnAreaPos, m_maxSpawnAreaPos);

	const float baseLifetime = Edge::RandomFloat(minParticleLifetime, maxParticleLifetime);

	const float baseExplositionForce = Edge::RandomFloat(minExplosionForce, maxExplosionForce);

	const uint32_t particleCount = Edge::RandomUInt32(minParticleCount, maxParticleCount);
	for (uint32_t particleIndex = 0; particleIndex < particleCount; ++particleIndex)
	{
		const float lifetime = baseLifetime + Edge::RandomFloat(particleLifetimeRange);
		const float explosionForce = baseExplositionForce + Edge::RandomFloat(explosionForceRange);

		Edge::ComputeVector dir(generatePosition(Edge::FloatVector3NegativeOne, Edge::FloatVector3One));
		dir.normalize();

		ParticleCollection::NewElementInfo newParticleInfo = m_fireworksParticles.addElementRaw();
		FireworksParticle* newParticle = new (newParticleInfo.m_elementPtr) FireworksParticle(
			newParticleInfo.m_elementHandle.getKey(), m_physScene, color, lifetime, position, dir.getFloatVector3(), explosionForce);

		m_fireworksParticlePtrs.push_back(newParticle);
	}
}

Edge::FloatVector3 EdgeDemo::FireworksParticleController::generateColor()
{
	Edge::FloatVector3 color = Edge::FloatVector3Zero;

	uint32_t elements[3] = { 0, 1, 2 };

	uint32_t colorElementIndex = Edge::RandomUInt32(2);
	uint32_t colorElelement = elements[colorElementIndex];
	elements[colorElementIndex] = elements[2];
	color[colorElelement] = 1.0f;

	colorElementIndex = Edge::RandomUInt32(1);
	colorElelement = elements[colorElementIndex];
	elements[colorElementIndex] = elements[1];
	color[colorElelement] = 0.0f;

	colorElelement = elements[0];
	color[colorElelement] = Edge::RandomFloat(1.0f);

	return color;
}

Edge::FloatVector3 EdgeDemo::FireworksParticleController::generatePosition(const Edge::FloatVector3& minPos, const Edge::FloatVector3& maxPos)
{
	return Edge::FloatVector3(
		Edge::RandomFloat(minPos.m_x, maxPos.m_x),
		Edge::RandomFloat(minPos.m_y, maxPos.m_y),
		Edge::RandomFloat(minPos.m_z, maxPos.m_z)
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

		m_spawningTimeDelay = Edge::RandomFloat(minSpawningDelay, maxSpawningDelay);
	}
}

void EdgeDemo::FireworksParticleController::fillRenderData(
	Edge::DebugVisualizationDataController& debugVisualizationData) const
{
	for (const FireworksParticle* particle : m_fireworksParticlePtrs)
	{
		debugVisualizationData.addPoint(particle->getPosition(), particle->getColor());
	}
}
