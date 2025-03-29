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
		static constexpr Edge::ComputeValueType particleMass = 0.1f;

	private:
		Edge::PhysicsParticleReference m_physParticleEntity;

		Edge::ComputeVector3 m_color = Edge::FloatVector3One;
		Edge::ComputeValueType m_lifeTime = 0.0f;
		Edge::ComputeValueType m_maxLifeTime = 0.0f;

		const FireworksParticleID m_id = InvalidFireworksParticleID;

	public:
		FireworksParticle(FireworksParticleID id, const Edge::PhysicsSceneReference& physScene,
			const Edge::ComputeVector3& color, float maxLifeTime,
			const Edge::ComputeVector3& initialPosition, const Edge::ComputeVector3& initialDir, Edge::ComputeValueType explosionForce);
		~FireworksParticle();

		void update(float deltaTime);
		bool isAlive() const;

		Edge::ComputeVector3 getPosition() const;
		const Edge::ComputeVector3& getColor() const;

		FireworksParticleID getID() const { return m_id; }
	};
}
