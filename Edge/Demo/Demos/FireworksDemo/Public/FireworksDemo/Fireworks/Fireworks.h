#pragma once

#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Entity/PhysicsParticle.h"
#include "EdgePhysics/Physics/Scene/PhysicsSceneReference.h"

namespace EdgeDemo
{
	using FireworksParticleID = uint32_t;
	constexpr FireworksParticleID InvalidFireworksParticleID = -1;

	class FireworksParticle final
	{
		static constexpr float particleMass = 0.1f;

	private:
		Edge::PhysicsParticleReference m_physParticleEntity;

		Edge::FloatVector3 m_color = Edge::FloatVector3One;
		float m_lifeTime = 0.0f;
		float m_maxLifeTime = 0.0f;

		const FireworksParticleID m_id = InvalidFireworksParticleID;

	public:
		FireworksParticle(FireworksParticleID id, const Edge::PhysicsSceneReference& physScene,
			const Edge::FloatVector3& color, float maxLifeTime,
			const Edge::FloatVector3& initialPosition, const Edge::FloatVector3& initialDir, float explosionForce);
		~FireworksParticle();

		void update(float deltaTime);
		bool isAlive() const;

		Edge::FloatVector3 getPosition() const;
		const Edge::FloatVector3& getColor() const;

		FireworksParticleID getID() const { return m_id; }
	};
}
