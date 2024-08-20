#include "TestCastDemo.h"

#include "EdgeCommon/Math/Const.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/PointCastingResultCollectors.h"

void EdgeDemo::TestCastDemo::updateLocalTime(float deltaTime)
{
	m_localTime += deltaTime;

	const float maxLocalTime = EDGE_2_PI;
	while (m_localTime >= maxLocalTime)
	{
		m_localTime -= maxLocalTime;
	}
}

bool EdgeDemo::TestCastDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = 1.0f;
	bodyMotionCreationParam.m_gravityFactor = 0.0f;
	bodyMotionCreationParam.m_angularDamping = 0.2f;

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;
	bodyCollisionCreationParam.m_shape = Edge::GetPhysics().createBoxShape(Edge::FloatVector3(0.5f, 0.5f, 0.5f));

	bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;
	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	bodyCreationParam.m_position.m_x = 5.0f;

	m_testShapeEntity1 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testShapeEntity1);

	bodyCreationParam.m_position.m_x = 0.0f;

	bodyCreationParam.m_position.m_y = 5.0f;

	m_testShapeEntity2 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testShapeEntity2);

	bodyCreationParam.m_position.m_y = 10.0f;

	m_testShapeEntity3 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testShapeEntity3);

	return true;
}

void EdgeDemo::TestCastDemo::releaseDemo()
{
	m_physicsScene->removeEntity(m_testShapeEntity1.getObject());
	m_physicsScene->removeEntity(m_testShapeEntity2.getObject());
	m_physicsScene->removeEntity(m_testShapeEntity3.getObject());

	m_testShapeEntity1.reset();
	m_testShapeEntity2.reset();
	m_testShapeEntity3.reset();
}

void EdgeDemo::TestCastDemo::updateDemoLogic(float deltaTime)
{
	updateLocalTime(deltaTime);

	m_testShapeEntity1->getTransform()->setPosition(Edge::FloatVector3(cosf(m_localTime * 2.0f) * 2.0f, 0.0f, 0.0f));

	const Edge::Transform& cameraTransform = m_cameraController->getTransform();
	const Edge::FloatVector3& cameraPosition = cameraTransform.getOrigin();

	Edge::ComputeVector rayEndPos = cameraTransform.getAxisZ();
	rayEndPos *= 20.0f;
	rayEndPos += cameraPosition;

	Edge::FloatVector3 rayEnd;
	rayEndPos.saveToFloatVector3(rayEnd);

	Edge::ClosestPointCastingResultCollector hitCollisionCollector;
	m_physicsScene->getCollisionManager()->rayCast(cameraPosition, rayEnd, hitCollisionCollector);

	m_debugVisualizationDataController->clear();

	m_debugVisualizationDataController->addBox(m_testShapeEntity1->getTransform()->getWorldTransform());
	m_debugVisualizationDataController->addBox(m_testShapeEntity2->getTransform()->getWorldTransform());
	m_debugVisualizationDataController->addBox(m_testShapeEntity3->getTransform()->getWorldTransform());

	if (hitCollisionCollector.hasHit())
	{
		m_debugVisualizationDataController->addWireframeSphere(hitCollisionCollector.getHitResult().m_result.m_hitPosition, Edge::FloatVector3UnitY, Edge::FloatVector3UnitX,
			0.1f, Edge::FloatVector3(0.0f, 0.0f, 1.0f));
	}
}
