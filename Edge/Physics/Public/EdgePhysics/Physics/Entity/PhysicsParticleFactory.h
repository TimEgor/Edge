#pragma once

#include "PhysicsEntityFactory.h"
#include "PhysicsParticle.h"

namespace Edge
{
	class PhysicsParticleFactory : public PhysicsEntityFactory
	{
	public:
		struct ParticleCreationParam final : public EntityCreationParam
		{
			FloatVector3 m_position = FloatVector3Zero;

			EDGE_PHYSICS_ENTITY_CREATION_PARAM_TYPE(PARTICAL)
		};

		struct ParticleMotionCreationParam final : public EntityMotionCreationParam
		{
			float m_linearDampingFactor = 0.05f;
			EDGE_PHYSICS_ENTITY_CREATION_PARAM_TYPE(PARTICAL)
		};

		PhysicsParticleFactory() = default;

		PhysicsParticleReference createParticleEntity(const ParticleCreationParam* param = nullptr);
		PhysicsParticleMotionReference createParticleMotion(const PhysicsParticleReference& entity, const ParticleMotionCreationParam* param = nullptr);

		virtual PhysicsEntityReference createEntity(const EntityCreationParam* param) override;
		virtual PhysicsEntityMotionReference createEntityMotion(const PhysicsEntityReference& entity, const EntityMotionCreationParam* param) override;
	};
}
