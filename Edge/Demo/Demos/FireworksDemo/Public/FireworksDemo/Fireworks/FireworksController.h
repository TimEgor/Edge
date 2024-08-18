#pragma once

#include "Fireworks.h"

#include "EdgeCommon/ObjectPool/ObjectPool.h"

#include "EdgePhysics/Physics/Scene/PhysicsScene.h"
#include "EdgePhysics/Visualizer/DebugVisualizationDataController.h"

#include <vector>

namespace EdgeDemo
{
	class FireworksParticleController final
	{
		using ParticleHandle = Edge::ObjectPoolHandle32;
		using ParticleCollection = Edge::ObjectPool<FireworksParticle, ParticleHandle>;
		using ParticlePtrCollection = std::vector<FireworksParticle*>;

		static constexpr float minSpawningDelay = 1.0f;
		static constexpr float maxSpawningDelay = 3.0f;

		static constexpr uint32_t minParticleCount = 150;
		static constexpr uint32_t maxParticleCount = 350;

		static constexpr float minParticleLifetime = 2.0f;
		static constexpr float maxParticleLifetime = 3.0f;

		static constexpr float particleLifetimeRange = 0.5f;

		static constexpr float minExplosionForce = 0.2f;
		static constexpr float maxExplosionForce = 0.4f;

		static constexpr float explosionForceRange = 0.05f;

	private:
		ParticleCollection m_fireworksParticles;
		ParticlePtrCollection m_fireworksParticlePtrs;

		Edge::PhysicsSceneReference m_physScene;

		Edge::FloatVector3 m_minSpawnAreaPos = Edge::FloatVector3Zero;
		Edge::FloatVector3 m_maxSpawnAreaPos = Edge::FloatVector3Zero;

		float m_spawningTimeDelay = 0.0f;

		void spawn();

		static Edge::FloatVector3 generateColor();
		static Edge::FloatVector3 generatePosition(const Edge::FloatVector3& minPos, const Edge::FloatVector3& maxPos);

	public:
		FireworksParticleController(const Edge::PhysicsSceneReference& physScene,
			const Edge::FloatVector3& minSpawnAreaPos, const Edge::FloatVector3& maxSpawnAreaPos);
		~FireworksParticleController();

		void update(float deltaTime);
		void fillRenderData(Edge::DebugVisualizationDataController& debugVisualizationData) const;
	};
}
