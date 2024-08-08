#pragma once


#include "Fireworks.h"

#include <vector>

#include "TinySimCommon/ObjectPool/ObjectPool.h"
#include "TinySimPhysics/Physics/Scene/IPhysicsScene.h"
#include "TinySimPhysics/Visualizer/IDebugVisualizationDataController.h"

namespace TS_DEMO
{
	class FireworksParticleController final
	{
		using ParticleHandle = TS::ObjectPoolHandle32;
		using ParticleCollection = TS::ObjectPool<FireworksParticle, ParticleHandle>;
		using ParticlePtrCollection = std::vector<FireworksParticle*>;

		static constexpr float minSpawningDelay = 2.0f;
		static constexpr float maxSpawningDelay = 4.0f;

		static constexpr uint32_t minParticleCount = 50;
		static constexpr uint32_t maxParticleCount = 150;

		static constexpr float minParticleLifetime = 2.0f;
		static constexpr float maxParticleLifetime = 3.0f;

		static constexpr float particleLifetimeRange = 0.5f;

		static constexpr float minExplosionForce = 0.2f;
		static constexpr float maxExplosionForce = 0.4f;

		static constexpr float explosionForceRange = 0.05f;

	private:
		ParticleCollection m_fireworksParticles;
		ParticlePtrCollection m_fireworksParticlePtrs;

		TS::PhysicsSceneReference m_physScene;

		TS::FloatVector3 m_minSpawnAreaPos = TS::FloatVector3Zero;
		TS::FloatVector3 m_maxSpawnAreaPos = TS::FloatVector3Zero;

		float m_spawningTimeDelay = 0.0f;

		void spawn();

		static TS::FloatVector3 generateColor();
		static TS::FloatVector3 generatePosition(const TS::FloatVector3& minPos, const TS::FloatVector3& maxPos);

	public:
		FireworksParticleController(const TS::PhysicsSceneReference& physScene,
			const TS::FloatVector3& minSpawnAreaPos, const TS::FloatVector3& maxSpawnAreaPos);
		~FireworksParticleController();

		void update(float deltaTime);
		void fillRenderData(TS::DebugVisualizationDataControllerReference& debugVisualizationData) const;
	};
}
