#pragma once

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollisionShape.h"

#include "PhysicsEntityMotion.h"
#include "PhysicsEntityReference.h"

namespace Edge
{
	class PhysicsEntityFactory
	{
	public:
		struct EntityMotionCreationParam
		{
			ComputeValueType m_mass = ComputeValueType(1.0);
			ComputeValueType m_gravityFactor = ComputeValueType(1.0);

			EntityMotionCreationParam() = default;
			virtual ~EntityMotionCreationParam() = default;

			EDGE_RTTI_VIRTUAL_BASE(EntityMotionCreationParam)
		};

		struct EntityCollisionCreationParam final
		{
			PhysicsEntityCollisionShapeReference m_shape;

			ComputeValueType m_friction = ComputeValueType(1.0);
			ComputeValueType m_elasticity = ComputeValueType(0.5);
		};

		struct EntityCreationParam
		{
			EntityMotionCreationParam* m_motionCreationParam = nullptr;
			EntityCollisionCreationParam* m_collisionParam = nullptr;

			EntityCreationParam() = default;
			virtual ~EntityCreationParam() = default;

			EDGE_RTTI_VIRTUAL_BASE(EntityCreationParam)
		};

		PhysicsEntityFactory() = default;
		virtual ~PhysicsEntityFactory() = default;

		virtual PhysicsEntityReference createEntity(const EntityCreationParam* param = nullptr) = 0;
		virtual PhysicsEntityMotionReference createEntityMotion(const EntityMotionCreationParam* param = nullptr) = 0;
	};
}