#pragma once

#include "PhysicsEntity.h"

namespace Edge
{
	EDGE_NAMED_REFERENCE(PhysicsPositionAndRotationBasedTransform, PhysicsBodyTransform);
	EDGE_NAMED_REFERENCE(PhysicsPositionAndRotationBasedMotion, PhysicsBodyMotion);

	class PhysicsBody : public PhysicsEntity
	{
	public:
		PhysicsBody(const PhysicsBodyTransformReference& transform)
			: PhysicsEntity(transform)
		{}

		PhysicsBodyTransformReference getBodyTransform() const { return m_transform.getObjectCast<PhysicsBodyTransformReference::ObjectType>(); }

		PhysicsBodyMotionReference getBodyMotion() const{ return m_motion.getObjectCast<PhysicsBodyMotionReference::ObjectType>(); }
		void setBodyMotion(const PhysicsBodyMotionReference& motion) { updateMotion(motion); }

		virtual void updateTransformWithMotion(float deltaTime) override;

		EDGE_PHYSICS_ENTITY_TYPE(BODY);
	};

	EDGE_REFERENCE(PhysicsBody);
}
