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

			EDGE_RTTI_VIRTUAL(ParticleCreationParam, EntityCreationParam)
		};

		struct ParticleMotionCreationParam final : public EntityMotionCreationParam
		{
			ComputeValueType m_linearDampingFactor = 0.05_ecv;

			EDGE_RTTI_VIRTUAL(ParticleMotionCreationParam, EntityMotionCreationParam)
		};

		PhysicsParticleFactory() = default;

		PhysicsParticleReference createParticleEntity(const ParticleCreationParam* param = nullptr);
		PhysicsParticleMotionReference createParticleMotion(const ParticleMotionCreationParam* param = nullptr);

		virtual PhysicsEntityReference createEntity(const EntityCreationParam* param) override;
		virtual PhysicsEntityMotionReference createEntityMotion(const EntityMotionCreationParam* param) override;
	};
}