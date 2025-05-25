#pragma once

#include "PhysicsEntity.h"

namespace Edge
{
	EDGE_NAMED_REFERENCE(PhysicsPositionBasedTransform, PhysicsParticleTransform);
	EDGE_NAMED_REFERENCE(PhysicsPositionBasedMotion, PhysicsParticleMotion);

	class PhysicsParticle : public PhysicsEntity
	{
	public:
		PhysicsParticle(const PhysicsParticleTransformReference& transform)
			: PhysicsEntity(transform)
		{}

		PhysicsParticleTransformReference getParticleTransform() const { return m_transform.getObjectCast<PhysicsParticleTransformReference::ObjectType>(); }

		PhysicsParticleMotionReference getParticleMotion() const { return m_motion.getObjectCast<PhysicsParticleMotionReference::ObjectType>(); }
		void setParticleMotion(const PhysicsParticleMotionReference& motion) { updateMotion(motion); }

		virtual void updateTransformWithMotion(float deltaTime) override;

		EDGE_RTTI_VIRTUAL(PhysicsParticle, PhysicsEntity)
	};

	EDGE_REFERENCE(PhysicsParticle);
}