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

		static constexpr Edge::ComputeValueType minSpawningDelay = 1.0f;
		static constexpr Edge::ComputeValueType maxSpawningDelay = 3.0f;

		static constexpr uint32_t minParticleCount = 150;
		static constexpr uint32_t maxParticleCount = 350;

		static constexpr Edge::ComputeValueType minParticleLifetime = 2.0f;
		static constexpr Edge::ComputeValueType maxParticleLifetime = 3.0f;

		static constexpr Edge::ComputeValueType particleLifetimeRange = 0.5f;

		static constexpr Edge::ComputeValueType minExplosionForce = 0.2f;
		static constexpr Edge::ComputeValueType maxExplosionForce = 0.4f;

		static constexpr Edge::ComputeValueType explosionForceRange = 0.05f;

	private:
		ParticleCollection m_fireworksParticles;
		ParticlePtrCollection m_fireworksParticlePtrs;

		Edge::PhysicsSceneReference m_physScene;

		Edge::ComputeVector3 m_minSpawnAreaPos = Edge::ComputeVector3Zero;
		Edge::ComputeVector3 m_maxSpawnAreaPos = Edge::ComputeVector3Zero;

		Edge::ComputeValueType m_spawningTimeDelay = 0.0f;

		void spawn();

		static Edge::ComputeVector3 generateColor();
		static Edge::ComputeVector3 generatePosition(const Edge::ComputeVector3& minPos, const Edge::ComputeVector3& maxPos);

	public:
		FireworksParticleController(const Edge::PhysicsSceneReference& physScene,
			const Edge::ComputeVector3& minSpawnAreaPos, const Edge::ComputeVector3& maxSpawnAreaPos);
		~FireworksParticleController();

		void update(float deltaTime);
		void fillRenderData(Edge::DebugVisualizationDataController& debugVisualizationData) const;
	};
}
