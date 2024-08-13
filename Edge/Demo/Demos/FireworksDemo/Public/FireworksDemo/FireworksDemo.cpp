#include "FireworksDemo.h"

#include "Fireworks/FireworksController.h"

#include "EdgeCommon/UtilsMacros.h"

bool EdgeDemo::FireworksDemo::initDemo()
{
	m_fireworksParticleController = new FireworksParticleController(
		m_physicsScene, Edge::FloatVector3(-5.0f, -5.0f, -5.0f), Edge::FloatVector3(5.0f, 5.0f, 5.0f));
	EDGE_CHECK_RETURN_FALSE(m_fireworksParticleController);

	return true;
}

void EdgeDemo::FireworksDemo::releaseDemo()
{
	EDGE_SAFE_DESTROY(m_fireworksParticleController);
}

void EdgeDemo::FireworksDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	m_fireworksParticleController->update(deltaTime);
	m_fireworksParticleController->fillRenderData(*m_debugVisualizationDataController);

	{
		Edge::Transform boxTransform;
		boxTransform.m_matrix.m_m11 = 10.0f;
		boxTransform.m_matrix.m_m22 = 10.0f;
		boxTransform.m_matrix.m_m33 = 10.0f;

		m_debugVisualizationDataController->addWireframeBox(boxTransform);
	}
}
