#include "Physics.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Job/JobController.h"

bool Edge::Physics::init(const InitParams& params)
{
	m_jobController = new JobController();
	EDGE_CHECK_INITIALIZATION(m_jobController && m_jobController->init(params.m_jobThreadCount, "Physics"));
}

void Edge::Physics::release()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_jobController);
}
