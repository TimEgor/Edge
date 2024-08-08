#include "FireworksController.h"

#include "TinySimCommon/Core/Random/Random.h"
#include "TinySimCommon/Math/ComputeVector.h"

TS_DEMO::FireworksParticleController::FireworksParticleController(const TS::PhysicsSceneReference& physScene,
                                                                  const TS::FloatVector3& minSpawnAreaPos, const TS::FloatVector3& maxSpawnAreaPos)
	: m_physScene(physScene), m_minSpawnAreaPos(minSpawnAreaPos), m_maxSpawnAreaPos(maxSpawnAreaPos)
{
	m_fireworksParticles.init();
}

TS_DEMO::FireworksParticleController::~FireworksParticleController()
{
	m_fireworksParticles.release();
}

void TS_DEMO::FireworksParticleController::spawn()
{
	const TS::FloatVector3 color = generateColor();
	const TS::FloatVector3 position = generatePosition(m_minSpawnAreaPos, m_maxSpawnAreaPos);

	const float baseLifetime = TS::RandomFloat(minParticleLifetime, maxParticleLifetime);

	const float baseExplositionForce = TS::RandomFloat(minExplosionForce, maxExplosionForce);

	const uint32_t particleCount = TS::RandomUInt32(minParticleCount, maxParticleCount);
	for (uint32_t particleIndex = 0; particleIndex < particleCount; ++particleIndex)
	{
		const float lifetime = baseLifetime + TS::RandomFloat(particleLifetimeRange);
		const float explosionForce = baseExplositionForce + TS::RandomFloat(explosionForceRange);

		TS::ComputeVector dir(generatePosition(TS::FloatVector3NegativeOne, TS::FloatVector3One));
		dir.normalize();

		ParticleCollection::NewElementInfo newParticleInfo = m_fireworksParticles.addElementRaw();
		FireworksParticle* newParticle = new (newParticleInfo.m_elementPtr) FireworksParticle(
			newParticleInfo.m_elementHandle.getKey(), m_physScene, color, lifetime, position, dir.getFloatVector3(), explosionForce);

		m_fireworksParticlePtrs.push_back(newParticle);
	}
}

TS::FloatVector3 TS_DEMO::FireworksParticleController::generateColor()
{
	TS::FloatVector3 color = TS::FloatVector3Zero;

	uint32_t elements[3] = { 0, 1, 2 };

	uint32_t colorElementIndex = TS::RandomUInt32(2);
	uint32_t colorElelement = elements[colorElementIndex];
	elements[colorElementIndex] = elements[2];
	color[colorElelement] = 1.0f;

	colorElementIndex = TS::RandomUInt32(1);
	colorElelement = elements[colorElementIndex];
	elements[colorElementIndex] = elements[1];
	color[colorElelement] = 0.0f;

	colorElelement = elements[0];
	color[colorElelement] = TS::RandomFloat(1.0f);

	return color;
}

TS::FloatVector3 TS_DEMO::FireworksParticleController::generatePosition(const TS::FloatVector3& minPos, const TS::FloatVector3& maxPos)
{
	return TS::FloatVector3(
		TS::RandomFloat(minPos.m_x, maxPos.m_x),
		TS::RandomFloat(minPos.m_y, maxPos.m_y),
		TS::RandomFloat(minPos.m_z, maxPos.m_z)
	);
}

void TS_DEMO::FireworksParticleController::update(float deltaTime)
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

		m_spawningTimeDelay = TS::RandomFloat(minSpawningDelay, maxSpawningDelay);
	}
}

void TS_DEMO::FireworksParticleController::fillRenderData(
	TS::DebugVisualizationDataControllerReference& debugVisualizationData) const
{
	for (const FireworksParticle* particle : m_fireworksParticlePtrs)
	{
		debugVisualizationData->addPoint(particle->getPosition(), particle->getColor());
	}
}
