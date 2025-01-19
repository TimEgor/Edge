#include "TestGJKCollisionDemo.h"

#include "EdgeCommon/Random/Random.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/GJK/GJK.h"
#include "EdgePhysics/Physics/Collision/Manifold/PhysicsContactManifold.h"
#include "EdgePhysics/Physics/Collision/Manifold/PhysicsManifoldContactGenerator.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceController.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceKeyCache.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceKeyUtils.h"
#include "EdgeFramework/Input/InputDeviceController/Devices/InputDeviceKeyData.h"
#include "EdgeFramework/Input/InputDeviceController/Devices/Keyboard.h"

void EdgeDemo::TestGJKCollisionDemo::updateDynamicBoxTransform(float deltaTime)
{
	constexpr float linearChangingSpeed = 3.0f;
	constexpr float angularChangingSpeed = 45.0f;

	const Edge::InputDeviceController& inputController = Edge::FrameworkCore::getInstance().getApplication().getInputDeviceController();

	const Edge::InputDeviceKeyCache::DeviceKeyCache* keyboardKeyCache = inputController.getDeviceKeyCache(Edge::KeyboardInputDevice::getDeviceType());
	if (!keyboardKeyCache)
	{
		return;
	}

	const Edge::InputDeviceKeyData& keyboardKeyData = keyboardKeyCache->m_currentKeyData;

	Edge::Transform dynamicBoxTransform = m_dynamicBox->getTransform()->getWorldTransform();

	Edge::ComputeVector position = dynamicBoxTransform.getOrigin();

	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

	Edge::GetAnglesFromRotationMatrix(dynamicBoxTransform.getRotationComputeMatrix(), pitch, yaw, roll);

	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::ArrowUp)))
	{
		position += Edge::FloatVector3UnitY * linearChangingSpeed * deltaTime;
	}
	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::ArrowDown)))
	{
		position -= Edge::FloatVector3UnitY * linearChangingSpeed * deltaTime;
	}
	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::ArrowRight)))
	{
		position += Edge::FloatVector3UnitX * linearChangingSpeed * deltaTime;
	}
	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::ArrowLeft)))
	{
		position -= Edge::FloatVector3UnitX * linearChangingSpeed * deltaTime;
	}

	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::ShiftRight)))
	{
		roll += deltaTime * angularChangingSpeed * Edge::Math::DegToRad;
	}
	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::ControlRight)))
	{
		roll -= deltaTime * angularChangingSpeed * Edge::Math::DegToRad;
	}

	dynamicBoxTransform.setOrigin(position.getFloatVector3());
	Edge::FloatQuaternion rotation = Edge::ComputeQuaternion().setupFromRollPitchYaw(pitch, yaw, roll).getFloatQuaternion();
	dynamicBoxTransform.setRotationQuaternion(rotation);

	m_dynamicBox->getTransform()->setWorldTransform(dynamicBoxTransform);
}

bool EdgeDemo::TestGJKCollisionDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;
	bodyCollisionCreationParam.m_shape = new Edge::PhysicsBoxShape(Edge::FloatVector3One);

	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	m_staticBox = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_staticBox);

	bodyCreationParam.m_position = Edge::FloatVector3(1.0f, 0.0f, 0.0f);
	//bodyCreationParam.m_rotation = Edge::ComputeQuaternionFromRollPitchYaw(45.0f * EDGE_DEG_TO_RAD, 45.0f * EDGE_DEG_TO_RAD, 45.0f * EDGE_DEG_TO_RAD).getFloatQuaternion();


	m_dynamicBox = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_dynamicBox);

	return true;
}

void EdgeDemo::TestGJKCollisionDemo::releaseDemo()
{
	m_physicsScene->removeEntity(m_staticBox.getObject());
	m_physicsScene->removeEntity(m_dynamicBox.getObject());

	m_staticBox.reset();
	m_dynamicBox.reset();
}

void EdgeDemo::TestGJKCollisionDemo::updateDemoLogic(float deltaTime)
{
	updateDynamicBoxTransform(deltaTime);

	m_debugVisualizationDataController->clear();

	Edge::GJK gjkTest;
	Edge::NormalizedColorRGB color = Edge::NormalizedColorWhite;
	const Edge::GJK::Result collisionTestResult = gjkTest(m_staticBox->getCollision().getObjectRef(), m_dynamicBox->getCollision().getObjectRef(), 100);

	Edge::EPA epa;
	Edge::PhysicsCollisionContactPoint contactPoint;
	const bool contactResult = epa.getContactPoint(
		m_staticBox->getCollision().getObjectRef(), m_dynamicBox->getCollision().getObjectRef(),
		collisionTestResult, 100, contactPoint);

	if (contactResult)
	{
		color = Edge::NormalizedColorRed;

		m_debugVisualizationDataController->addSphere(contactPoint.m_position1,
			Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.07f, Edge::NormalizedColorOrange);
		m_debugVisualizationDataController->addSphere(contactPoint.m_position2,
			Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.07f, Edge::NormalizedColorMagneta);

		Edge::PhysicsContactManifold manifold;
		Edge::ManifoldContactGenerator manifoldContactGenerator;
		manifoldContactGenerator.generate(m_staticBox->getCollision().getObjectRef(), m_dynamicBox->getCollision().getObjectRef(), contactPoint, manifold);

		const uint32_t contactPointCount = manifold.m_positions1.size();

		for (uint32_t contactPointIndex = 0; contactPointIndex < contactPointCount; ++contactPointIndex)
		{
			const Edge::FloatVector3& position1 = manifold.m_positions1[contactPointIndex];
			const Edge::FloatVector3& position2 = manifold.m_positions2[contactPointIndex];

			m_debugVisualizationDataController->addSphere(position1,
				Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.05f, Edge::NormalizedColorViolet);
			m_debugVisualizationDataController->addSphere(position2,
				Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.05f, Edge::NormalizedColorForestGreen);

			m_debugVisualizationDataController->addArrow(position1, manifold.m_normal, 0.1f, Edge::NormalizedColorBlue);
		}
	}
	else if (collisionTestResult.m_testResult == Edge::GJK::Result::TestResult::OverIterationTesting)
	{
		color = Edge::NormalizedColorBrown;
	}

	m_debugVisualizationDataController->addWireframeBox(m_staticBox->getTransform()->getWorldTransform(),
		m_staticBox->getCollision()->getShape().getObjectCastRef<Edge::PhysicsBoxShape>().getSize(), color);

	m_debugVisualizationDataController->addWireframeBox(m_dynamicBox->getTransform()->getWorldTransform(),
		m_dynamicBox->getCollision()->getShape().getObjectCastRef<Edge::PhysicsBoxShape>().getSize(), color);
}
