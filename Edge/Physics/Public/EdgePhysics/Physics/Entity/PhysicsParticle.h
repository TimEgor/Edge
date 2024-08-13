#pragma once

#include "PhysicsEntity.h"

namespace Edge
{
	EDGE_MT_NAMED_REFERENCE(PhysicsPositionBasedTransform, PhysicsParticleTransform);
	EDGE_MT_NAMED_REFERENCE(PhysicsPositionBasedMotion, PhysicsParticleMotion);

	class PhysicsParticle : public PhysicsEntity
	{
	public:
		PhysicsParticle(const PhysicsParticleTransformReference& transform)
			: PhysicsEntity(transform)
		{}

		PhysicsParticleTransformReference getParticleTransform() const { return m_transform.getObjectCast<PhysicsParticleTransformReference::ObjectType>(); }

		PhysicsParticleMotionReference getParticleMotion() const { return m_motion.getObjectCast<PhysicsParticleMotionReference::ObjectType>(); }
		void setParticleMotion(const PhysicsParticleMotionReference& motion) { m_motion = motion; }

		virtual void updateTransformWithMotion(float deltaTime) override;

		EDGE_PHYSICS_ENTITY_TYPE(PARTICLE);
	};

	EDGE_MT_REFERENCE(PhysicsParticle);
}
