#include "FireworksDemo.h"

#include "Fireworks/FireworksController.h"

bool TS_DEMO::FireworksDemo::initDemo()
{
	m_fireworksParticleController = new FireworksParticleController(
		m_physicsScene, TS::FloatVector3(-5.0f, -5.0f, -5.0f), TS::FloatVector3(5.0f, 5.0f, 5.0f));
	TS_CHECK_RETURN_FALSE(m_fireworksParticleController);

	return true;
}

void TS_DEMO::FireworksDemo::releaseDemo()
{
	TS_SAFE_DESTROY(m_fireworksParticleController);
}

void TS_DEMO::FireworksDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	m_fireworksParticleController->update(deltaTime);
	m_fireworksParticleController->fillRenderData(m_debugVisualizationDataController);

	{
		TS::Transform boxTransform;
		boxTransform.m_matrix.m_m11 = 10.0f;
		boxTransform.m_matrix.m_m22 = 10.0f;
		boxTransform.m_matrix.m_m33 = 10.0f;

		m_debugVisualizationDataController->addWireframeBox(boxTransform);
	}
}
