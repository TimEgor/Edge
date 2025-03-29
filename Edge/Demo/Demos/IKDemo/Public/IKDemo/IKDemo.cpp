#include "IKDemo.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceController.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceKeyCache.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceKeyUtils.h"
#include "EdgeFramework/Input/InputDeviceController/Devices/Keyboard.h"

void EdgeDemo::IkDemo::updateTarget(float deltaTime)
{
	static constexpr float movingSpeed = 1.0f;

	const Edge::InputDeviceController& inputController = Edge::FrameworkCore::getInstance().getApplication().getInputDeviceController();

	const Edge::InputDeviceKeyCache::DeviceKeyCache* keyboardKeyCache = inputController.getDeviceKeyCache(Edge::KeyboardInputDevice::getDeviceType());

	if (!keyboardKeyCache)
	{
		return;
	}

	const Edge::InputDeviceKeyData& keyboardKeyData = keyboardKeyCache->m_currentKeyData;

	const float translation = movingSpeed * deltaTime;

	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::ArrowUp)))
	{
		m_target.m_y += translation;
	}
	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::ArrowDown)))
	{
		m_target.m_y -= translation;
	}
	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::ArrowRight)))
	{
		m_target.m_x += translation;
	}
	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::ArrowLeft)))
	{
		m_target.m_x -= translation;
	}
}

bool EdgeDemo::IkDemo::initDemo()
{
	m_ikLinks.reserve(5);

	IkLink& link1 = m_ikLinks.emplace_back();
	IkLink& link2 = m_ikLinks.emplace_back();
	IkLink& link3 = m_ikLinks.emplace_back();
	IkLink& link4 = m_ikLinks.emplace_back();
	//IkLink& link5 = m_ikLinks.emplace_back();

	link2.setLocalTransform(Edge::TranslationComputeMatrix4x4(Edge::ComputeVector3UnitY));
	link2.setParentLink(&link1);

	link3.setLocalTransform(Edge::TranslationComputeMatrix4x4(Edge::ComputeVector3UnitY));
	link3.setParentLink(&link2);

	link4.setLocalTransform(Edge::TranslationComputeMatrix4x4(Edge::ComputeVector3UnitY));
	link4.setParentLink(&link3);
	
	//link5.setLocalTransform(Edge::TranslationComputeMatrix4x4(Edge::ComputeVector3UnitY));
	//link5.setParentLink(&link4);

	m_ikJoints.reserve(4);

	IkHingeJoint& hinge1 = m_ikJoints.emplace_back(nullptr, &link1, Edge::FloatVector3UnitZ);
	IkHingeJoint& hinge2 = m_ikJoints.emplace_back(&link1, &link2, Edge::FloatVector3UnitZ);
	IkHingeJoint& hinge3 = m_ikJoints.emplace_back(&link2, &link3, Edge::FloatVector3UnitZ);
	//IkHingeJoint& hinge4 = m_ikJoints.emplace_back(&link3, &link4, Edge::FloatVector3UnitZ);

	m_ikSystem.addLink(&link1);
	m_ikSystem.addLink(&link2);
	m_ikSystem.addLink(&link3);
	//m_ikSystem.addLink(&link4);

	m_ikSystem.addJoint(&hinge1);
	m_ikSystem.addJoint(&hinge2);
	m_ikSystem.addJoint(&hinge3);
	//m_ikSystem.addJoint(&hinge4);

	m_ikSystem.setRootLink(&link1);
	m_ikSystem.setEffectorLink(&link4);

	m_ikSolver.updateTransforms(m_ikSystem);

	m_target = Edge::FloatVector3(2.0f, 2.0f, 0.0f);

	return true;
}

void EdgeDemo::IkDemo::releaseDemo()
{

}

void EdgeDemo::IkDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	updateTarget(deltaTime);

	m_ikSystem.setTargetPosition(m_target);
	m_ikSolver.solve(m_ikSystem, deltaTime);

	{
		IkLink* link = m_ikSystem.getRootLink();
		const Edge::Transform* parentTransform = &link->getWorldTransform();
		m_debugVisualizationDataController->addWireframeSphere(*parentTransform, 0.1f);

		while (link)
		{
			const Edge::Transform* newParentTransform = &link->getWorldTransform();
			m_debugVisualizationDataController->addWireframeSphere(*newParentTransform, 0.1f);
			m_debugVisualizationDataController->addLine(parentTransform->getOrigin().getFloatVector3(), newParentTransform->getOrigin().getFloatVector3());

			parentTransform = newParentTransform;
			link = link->getChildLink();
		}
	}

	m_debugVisualizationDataController->addWireframeSphere(m_ikSystem.getEffectorLink()->getWorldTransform(), 0.15f, Edge::NormalizedColorBlue);
	m_debugVisualizationDataController->addWireframeSphere(m_ikSystem.getTargetPosition(), 0.13f, Edge::NormalizedColorGreen);
}
