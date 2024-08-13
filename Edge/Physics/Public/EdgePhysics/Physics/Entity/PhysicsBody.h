#pragma once

#include "PhysicsEntity.h"

namespace Edge
{
	EDGE_MT_NAMED_REFERENCE(PhysicsPositionAndRotationBasedTransform, PhysicsBodyTransform);
	EDGE_MT_NAMED_REFERENCE(PhysicsPositionAndRotationBasedMotion, PhysicsBodyMotion);

	class PhysicsBody : public PhysicsEntity
	{
	public:
		PhysicsBody(const PhysicsBodyTransformReference& transform)
			: PhysicsEntity(transform)
		{}

		PhysicsBodyTransformReference getBodyTransform() const { return m_transform.getObjectCast<PhysicsBodyTransformReference::ObjectType>(); }

		PhysicsBodyMotionReference getBodyMotion() const{ return m_motion.getObjectCast<PhysicsBodyMotionReference::ObjectType>(); }
		void setBodyMotion(const PhysicsBodyMotionReference& motion) { m_motion = motion; }

		virtual void updateTransformWithMotion(float deltaTime) override;

		EDGE_PHYSICS_ENTITY_TYPE(BODY);
	};

	EDGE_MT_REFERENCE(PhysicsBody);
}
