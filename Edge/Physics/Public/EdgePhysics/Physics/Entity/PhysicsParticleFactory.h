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
			ComputeVector3 m_position = ComputeVector3Zero;

			EDGE_PHYSICS_ENTITY_CREATION_PARAM_TYPE(PARTICAL)
		};

		struct ParticleMotionCreationParam final : public EntityMotionCreationParam
		{
			ComputeValueType m_linearDampingFactor = ComputeValueType(0.05);
			EDGE_PHYSICS_ENTITY_CREATION_PARAM_TYPE(PARTICAL)
		};

		PhysicsParticleFactory() = default;

		PhysicsParticleReference createParticleEntity(const ParticleCreationParam* param = nullptr);
		PhysicsParticleMotionReference createParticleMotion(const ParticleMotionCreationParam* param = nullptr);

		virtual PhysicsEntityReference createEntity(const EntityCreationParam* param) override;
		virtual PhysicsEntityMotionReference createEntityMotion(const EntityMotionCreationParam* param) override;
	};
}
