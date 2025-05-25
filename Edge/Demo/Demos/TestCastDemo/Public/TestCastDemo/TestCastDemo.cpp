#include "TestCastDemo.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/PointCastingResultCollectors.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"

void EdgeDemo::TestCastDemo::updateLocalTime(float deltaTime)
{
	m_localTime += deltaTime;

	const float maxLocalTime = Edge::Math::Pi2;
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
	bodyCollisionCreationParam.m_shape = new Edge::PhysicsBoxShape(Edge::ComputeVector3One);

	bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;
	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	m_testBox1 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testBox1);

	bodyCreationParam.m_position.setY(2.0f);

	m_testBox2 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testBox2);

	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(0.5f);

	bodyCreationParam.m_position.setY(4.0f);

	m_testSphere1 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testSphere1);

	bodyCreationParam.m_position.setY(6.0f);

	m_testSphere2 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_testSphere2);

	return true;
}

void EdgeDemo::TestCastDemo::releaseDemo()
{
	m_physicsScene->removeEntity(m_testBox1);
	m_physicsScene->removeEntity(m_testBox2);

	m_physicsScene->removeEntity(m_testSphere1);
	m_physicsScene->removeEntity(m_testSphere2);

	m_testBox1.reset();
	m_testBox2.reset();

	m_testSphere1.reset();
	m_testSphere2.reset();
}

void EdgeDemo::TestCastDemo::updateDemoLogic(float deltaTime)
{
	updateLocalTime(deltaTime);

	{
		const float offsetX = cosf(m_localTime) * 2.0f;

		const Edge::ComputeVector3& boxPosition = m_testBox2->getTransform()->getPosition();
		m_testBox2->getTransform()->setPosition(Edge::ComputeVector3(offsetX, boxPosition.getY(), boxPosition.getZ()));

		const Edge::ComputeVector3& spherePosition = m_testSphere2->getTransform()->getPosition();
		m_testSphere2->getTransform()->setPosition(Edge::ComputeVector3(offsetX, spherePosition.getY(), spherePosition.getZ()));
	}

	const Edge::Transform& cameraTransform = m_cameraController->getTransform();
	const Edge::ComputeVector3& cameraPosition = cameraTransform.getOrigin();

	Edge::ComputeVector3 rayEndPos = cameraTransform.getAxisZ();
	rayEndPos *= 20.0f;
	rayEndPos += cameraPosition;

	Edge::ClosestPointCastingResultCollector hitCollisionCollector;
	m_physicsScene->getCollisionManager()->rayCast(cameraPosition, rayEndPos, hitCollisionCollector);

	m_debugVisualizationDataController->clear();

	m_debugVisualizationDataController->addBox(m_testBox1->getTransform()->getWorldTransform());
	m_debugVisualizationDataController->addBox(m_testBox2->getTransform()->getWorldTransform());

	m_debugVisualizationDataController->addSphere(m_testSphere1->getTransform()->getWorldTransform().getOrigin().getFloatVector3(), Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.5f);
	m_debugVisualizationDataController->addSphere(m_testSphere2->getTransform()->getWorldTransform().getOrigin().getFloatVector3(), Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.5f);

	if (hitCollisionCollector.hasHit())
	{
		const Edge::ComputeVector3 hitPosition = hitCollisionCollector.getHitResult().m_result.m_hitPosition;
		m_debugVisualizationDataController->addWireframeSphere(hitPosition.getFloatVector3(), Edge::FloatVector3UnitY, Edge::FloatVector3UnitX,
			0.1f, Edge::FloatVector3(0.0f, 0.0f, 1.0f));
	}
}
