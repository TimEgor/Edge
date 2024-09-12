#include "TestCastDemo.h"

#include "EdgeCommon/Math/Const.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/PointCastingResultCollectors.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsTriangleShape.h"

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
	bodyCollisionCreationParam.m_shape = new Edge::PhysicsBoxShape(Edge::FloatVector3(0.5f, 0.5f, 0.5f));

	bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;
	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	m_testBox1 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testBox1);

	bodyCreationParam.m_position.m_y = 2.0f;

	m_testBox2 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testBox2);

	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(0.5f);

	bodyCreationParam.m_position.m_y = 4.0f;

	m_testSphere1 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testSphere1);

	bodyCreationParam.m_position.m_y = 6.0f;

	m_testSphere2 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testSphere2);

	bodyCollisionCreationParam.m_shape = new Edge::PhysicsTriangleShape(Edge::FloatVector3(0.0f, 0.5f, 0.0f), Edge::FloatVector3(0.5f, -0.5f, 0.0f), Edge::FloatVector3(-0.5f, -0.5f, 0.0f));
	bodyCreationParam.m_position.m_y = 8.0f;

	m_testTriangle1 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testTriangle1);

	bodyCreationParam.m_position.m_y = 10.0f;

	m_testTriangle2 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testTriangle2);

	return true;
}

void EdgeDemo::TestCastDemo::releaseDemo()
{
	m_physicsScene->removeEntity(m_testBox1.getObject());
	m_physicsScene->removeEntity(m_testBox2.getObject());

	m_physicsScene->removeEntity(m_testSphere1.getObject());
	m_physicsScene->removeEntity(m_testSphere2.getObject());

	m_physicsScene->removeEntity(m_testTriangle1.getObject());
	m_physicsScene->removeEntity(m_testTriangle2.getObject());

	m_testBox1.reset();
	m_testBox2.reset();

	m_testSphere1.reset();
	m_testSphere2.reset();

	m_testTriangle1.reset();
	m_testTriangle2.reset();
}

void EdgeDemo::TestCastDemo::updateDemoLogic(float deltaTime)
{
	updateLocalTime(deltaTime);

	{
		const float offsetX = cosf(m_localTime) * 2.0f;

		const Edge::FloatVector3& boxPosition = m_testBox1->getTransform()->getPosition();
		m_testBox1->getTransform()->setPosition(Edge::FloatVector3(offsetX, boxPosition.m_y, boxPosition.m_z));

		const Edge::FloatVector3& spherePosition = m_testSphere1->getTransform()->getPosition();
		m_testSphere1->getTransform()->setPosition(Edge::FloatVector3(offsetX, spherePosition.m_y, spherePosition.m_z));

		const Edge::FloatVector3& trianglePosition = m_testTriangle1->getTransform()->getPosition();
		m_testTriangle1->getTransform()->setPosition(Edge::FloatVector3(offsetX, trianglePosition.m_y, trianglePosition.m_z));
	}

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

	m_debugVisualizationDataController->addBox(m_testBox1->getTransform()->getWorldTransform());
	m_debugVisualizationDataController->addBox(m_testBox2->getTransform()->getWorldTransform());

	m_debugVisualizationDataController->addSphere(m_testSphere1->getTransform()->getWorldTransform().getOrigin(), Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.5f);
	m_debugVisualizationDataController->addSphere(m_testSphere2->getTransform()->getWorldTransform().getOrigin(), Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.5f);

	{
		const Edge::FloatVector3 polygonLocalVertex1(0.0f, 0.5f, 0.0f);
		const Edge::FloatVector3 polygonLocalVertex2(0.5f, -0.5f, 0.0f);
		const Edge::FloatVector3 polygonLocalVertex3(-0.5f, -0.5f, 0.0f);

		const Edge::FloatVector3& trianglePosition1 = m_testTriangle1->getTransform()->getPosition();
		m_debugVisualizationDataController->addPolygon(
			(polygonLocalVertex1 + trianglePosition1).getFloatVector3(),
			(polygonLocalVertex2 + trianglePosition1).getFloatVector3(),
			(polygonLocalVertex3 + trianglePosition1).getFloatVector3());

		const Edge::FloatVector3& trianglePosition2 = m_testTriangle2->getTransform()->getPosition();
		m_debugVisualizationDataController->addPolygon(
			(polygonLocalVertex1 + trianglePosition2).getFloatVector3(),
			(polygonLocalVertex2 + trianglePosition2).getFloatVector3(),
			(polygonLocalVertex3 + trianglePosition2).getFloatVector3());
	}

	if (hitCollisionCollector.hasHit())
	{
		m_debugVisualizationDataController->addWireframeSphere(hitCollisionCollector.getHitResult().m_result.m_hitPosition, Edge::FloatVector3UnitY, Edge::FloatVector3UnitX,
			0.1f, Edge::FloatVector3(0.0f, 0.0f, 1.0f));
	}
}
