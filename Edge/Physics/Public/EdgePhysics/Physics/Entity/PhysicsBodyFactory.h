#pragma once

#include "PhysicsBody.h"
#include "PhysicsEntityFactory.h"

namespace Edge
{
	class PhysicsBodyFactory : public PhysicsEntityFactory
	{
	public:
		struct BodyCreationParam final : public EntityCreationParam
		{
			FloatVector3 m_position = FloatVector3Zero;
			FloatQuaternion m_rotation = FloatQuaternionIdentity;

			EDGE_PHYSICS_ENTITY_CREATION_PARAM_TYPE(BODY)
		};

		struct BodyMotionCreationParam final : public EntityMotionCreationParam
		{
			FloatVector3 m_inertia = FloatVector3One;

			float m_linearDampingFactor = 0.05f;
			float m_angularDamping = 0.05f;

			EDGE_PHYSICS_ENTITY_CREATION_PARAM_TYPE(BODY)
		};

		PhysicsBodyFactory() = default;

		PhysicsBodyReference createBodyEntity(const BodyCreationParam* param = nullptr);
		PhysicsBodyMotionReference createBodyMotion(const PhysicsBodyReference& entity, const BodyMotionCreationParam* param = nullptr);

		virtual PhysicsEntityReference createEntity(const EntityCreationParam* param) override;
		virtual PhysicsEntityMotionReference createEntityMotion(const PhysicsEntityReference& entity, const EntityMotionCreationParam* param) override;
	};
}
