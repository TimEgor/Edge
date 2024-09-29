#pragma once

#include "EdgeCommon/HashedType.h"

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollisionShape.h"

#include "PhysicsEntityMotion.h"
#include "PhysicsEntityReference.h"

namespace Edge
{
	class PhysicsEntityFactory
	{
	public:
		using EntityCreationParamType = HashedType::Type;

		struct EntityMotionCreationParam : public HashedType
		{
			float m_mass = 1.0f;
			float m_gravityFactor = 1.0f;

			EntityMotionCreationParam() = default;
			virtual ~EntityMotionCreationParam() = default;

			virtual EntityCreationParamType getType() const = 0;
		};

		struct EntityCollisionCreationParam final
		{
			PhysicsEntityCollisionShapeReference m_shape;

			float m_friction = 1.0f;
			float m_elasticity = 0.5f;
		};

		struct EntityCreationParam : public HashedType
		{
			EntityMotionCreationParam* m_motionCreationParam = nullptr;
			EntityCollisionCreationParam* m_collisionParam = nullptr;

			EntityCreationParam() = default;
			virtual ~EntityCreationParam() = default;

			virtual EntityCreationParamType getType() const = 0;
		};

		PhysicsEntityFactory() = default;
		virtual ~PhysicsEntityFactory() = default;

		virtual PhysicsEntityReference createEntity(const EntityCreationParam* param = nullptr) = 0;
		virtual PhysicsEntityMotionReference createEntityMotion(const EntityMotionCreationParam* param = nullptr) = 0;
	};

#define EDGE_PHYSICS_ENTITY_CREATION_PARAM_TYPE(PHYSICS_ENTITY_CREATION_PARAM_TYPE) \
	EDGE_HASH_TYPE(#PHYSICS_ENTITY_CREATION_PARAM_TYPE, Edge::PhysicsEntityFactory::EntityCreationParamType, EntityCreationParam)
}
