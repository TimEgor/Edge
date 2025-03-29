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
			ComputeVector3 m_position = ComputeVector3Zero;
			ComputeQuaternion m_rotation = ComputeQuaternionIdentity;

			EDGE_PHYSICS_ENTITY_CREATION_PARAM_TYPE(BODY)
		};

		struct BodyMotionCreationParam final : public EntityMotionCreationParam
		{
			ComputeVector3 m_inertia = ComputeVector3One; //Inertial tensor diagonal

			ComputeValueType m_linearDampingFactor = ComputeValueType(0.05);
			ComputeValueType m_angularDamping = ComputeValueType(0.05);

			EDGE_PHYSICS_ENTITY_CREATION_PARAM_TYPE(BODY)
		};

		PhysicsBodyFactory() = default;

		PhysicsBodyReference createBodyEntity(const BodyCreationParam* param = nullptr);
		PhysicsBodyMotionReference createBodyMotion(const BodyMotionCreationParam* param = nullptr);

		virtual PhysicsEntityReference createEntity(const EntityCreationParam* param) override;
		virtual PhysicsEntityMotionReference createEntityMotion(const EntityMotionCreationParam* param) override;
	};
}
