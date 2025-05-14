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

			EDGE_RTTI_VIRTUAL(BodyCreationParam, EntityCreationParam)
		};

		struct BodyMotionCreationParam final : public EntityMotionCreationParam
		{
			ComputeVector3 m_inertia = ComputeVector3One; //Inertial tensor diagonal

			ComputeValueType m_linearDampingFactor = 0.05_ecv;
			ComputeValueType m_angularDamping = 0.05_ecv;

			EDGE_RTTI_VIRTUAL(BodyMotionCreationParam, EntityMotionCreationParam)
		};

		PhysicsBodyFactory() = default;

		PhysicsBodyReference createBodyEntity(const BodyCreationParam* param = nullptr);
		PhysicsBodyMotionReference createBodyMotion(const BodyMotionCreationParam* param = nullptr);

		virtual PhysicsEntityReference createEntity(const EntityCreationParam* param) override;
		virtual PhysicsEntityMotionReference createEntityMotion(const EntityMotionCreationParam* param) override;
	};
}