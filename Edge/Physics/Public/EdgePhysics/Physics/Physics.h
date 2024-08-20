#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"

#include "Collision/Shapes/PhysicsBoxShapeFactory.h"
#include "Entity/PhysicsBodyFactory.h"
#include "Entity/PhysicsParticleFactory.h"

#include <cstdint>

namespace Edge
{
	class JobController;

	class PhysicsBoxShapeFactory;

	class Physics final : public NonCopyable
	{
	private:
		JobController* m_jobController = nullptr;

		PhysicsBodyFactory* m_bodyFactory = nullptr;
		PhysicsParticleFactory* m_particleFactory = nullptr;

		PhysicsBoxShapeFactory* m_boxShapeFactory = nullptr;

	public:
		struct InitParams final
		{
			uint32_t m_jobThreadCount = 4;
		};

		Physics() = default;

		bool init(const InitParams& params);
		void release();

		PhysicsBodyReference createBody(const PhysicsBodyFactory::BodyCreationParam* params) const;
		PhysicsParticleReference createParticle(const PhysicsParticleFactory::ParticleCreationParam* params) const;

		PhysicsBoxShapeReference createBoxShape(const FloatVector3& size) const;

		JobController& getJobController() const;
	};
}
