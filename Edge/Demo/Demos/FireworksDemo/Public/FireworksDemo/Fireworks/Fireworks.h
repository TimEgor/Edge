#pragma once

#include "TinySimCommon/Math/Vector.h"
#include "TinySimPhysics/Physics/Scene/IPhysicsParticleEntity.h"

#include "TinySimPhysics/Physics/Scene/PhysicsSceneReference.h"

namespace TS_DEMO
{
	using FireworksParticleID = uint32_t;
	constexpr FireworksParticleID InvalidFireworksParticleID = -1;

	class FireworksParticle final
	{
		static constexpr float particleMass = 0.1f;

	private:
		TS::PhysicsParticleEntityReference m_physParticleEntity;
		TS::FloatVector3 m_color = TS::FloatVector3One;
		float m_lifeTime = 0.0f;
		float m_maxLifeTime = 0.0f;

		const FireworksParticleID m_id = InvalidFireworksParticleID;

	public:
		FireworksParticle(FireworksParticleID id, const TS::PhysicsSceneReference& physScene,
			const TS::FloatVector3& color, float maxLifeTime,
			const TS::FloatVector3& initialPosition, const TS::FloatVector3& initialDir, float explosionForce);
		~FireworksParticle();

		void update(float deltaTime);
		bool isAlive() const;

		TS::FloatVector3 getPosition() const;
		const TS::FloatVector3& getColor() const;

		FireworksParticleID getID() const { return m_id; }
	};
}
