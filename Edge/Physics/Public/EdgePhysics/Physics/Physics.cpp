#include "Physics.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Job/JobController.h"

bool Edge::Physics::init(const InitParams& params)
{
	m_jobController = new JobController();
	EDGE_CHECK_INITIALIZATION(m_jobController && m_jobController->init(params.m_jobThreadCount, "Edge Physics"));

	m_bodyFactory = new PhysicsBodyFactory();
	EDGE_CHECK_INITIALIZATION(m_bodyFactory);

	m_particleFactory = new PhysicsParticleFactory();
	EDGE_CHECK_INITIALIZATION(m_particleFactory);

	m_boxShapeFactory = new PhysicsBoxShapeFactory();
	EDGE_CHECK_INITIALIZATION(m_boxShapeFactory);

	return true;
}

void Edge::Physics::release()
{
	EDGE_SAFE_DESTROY(m_particleFactory);
	EDGE_SAFE_DESTROY(m_bodyFactory);

	EDGE_SAFE_DESTROY_WITH_RELEASING(m_jobController);
}

Edge::PhysicsBodyReference Edge::Physics::createBody(const PhysicsBodyFactory::BodyCreationParam* params) const
{
	EDGE_ASSERT(m_bodyFactory);
	return m_bodyFactory->createBodyEntity(params);
}

Edge::PhysicsParticleReference Edge::Physics::createParticle(const PhysicsParticleFactory::ParticleCreationParam* params) const
{
	EDGE_ASSERT(m_particleFactory);
	return m_particleFactory->createParticleEntity(params);
}

Edge::PhysicsBoxShapeReference Edge::Physics::createBoxShape(const FloatVector3& size) const
{
	EDGE_ASSERT(m_boxShapeFactory);
	return m_boxShapeFactory->createBoxShape(size);
}

Edge::JobController& Edge::Physics::getJobController() const
{
	EDGE_ASSERT(m_jobController);
	return *m_jobController;
}
