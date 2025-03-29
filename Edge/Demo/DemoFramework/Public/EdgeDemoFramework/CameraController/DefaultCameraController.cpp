#include "DefaultCameraController.h"

#include "EdgeCommon/Math/Transform.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceController.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceKeyCache.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceKeyUtils.h"
#include "EdgeFramework/Input/InputDeviceController/Devices/Keyboard.h"
#include "EdgeFramework/Input/InputDeviceController/Devices/Mouse.h"

#include <cmath>

void EdgeDemo::DefaultCameraController::update(float deltaTime)
{
	static constexpr Edge::ComputeValueType cameraMovingSpeed = 15.0_ecv;
	static constexpr Edge::ComputeValueType cameraRotationSpeed = 30.0_ecv;

	const Edge::InputDeviceController& inputController = Edge::FrameworkCore::getInstance().getApplication().getInputDeviceController();

	const Edge::InputDeviceKeyCache::DeviceKeyCache* keyboardKeyCache = inputController.getDeviceKeyCache(Edge::KeyboardInputDevice::getDeviceType());
	const Edge::InputDeviceKeyCache::DeviceKeyCache* mouseKeyCache = inputController.getDeviceKeyCache(Edge::MouseInputDevice::getDeviceType());
	if (!keyboardKeyCache || !mouseKeyCache)
	{
		return;
	}

	const Edge::InputDeviceKeyData& keyboardKeyData = keyboardKeyCache->m_currentKeyData;
	const Edge::InputDeviceKeyData& mouseKeyData = mouseKeyCache->m_currentKeyData;

	Edge::ComputeVector3 cameraEntityPosition = m_cameraTransform.getOrigin();
	Edge::ComputeVector3 rightDir = m_cameraTransform.getAxisX();
	Edge::ComputeVector3 upDir = m_cameraTransform.getAxisY();
	Edge::ComputeVector3 forwardDir = m_cameraTransform.getAxisZ();


	Edge::ComputeValueType pitchAngle = asin(-m_cameraTransform.m_matrix.getElement(1, 2));
	Edge::ComputeValueType yawAngle = 0.0_ecv;

	if (cos(pitchAngle) > Edge::Math::Epsilon)
	{
		yawAngle = atan2(m_cameraTransform.m_matrix.getElement(0, 2), m_cameraTransform.m_matrix.getElement(2, 2));
	}

	const Edge::FloatVector2 mouseDelta(
		mouseKeyData.m_values[GetMouseKey(Edge::MouseKeys::X)],
		mouseKeyData.m_values[GetMouseKey(Edge::MouseKeys::Y)]
	);

	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(mouseKeyData, GetMouseKey(Edge::MouseKeys::Wheel)))
	{
		cameraEntityPosition += rightDir * (-mouseDelta.m_x * cameraMovingSpeed * deltaTime);
		cameraEntityPosition += upDir * (mouseDelta.m_y * cameraMovingSpeed * deltaTime);
	}
	else {
		if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::W)))
		{
			cameraEntityPosition += forwardDir * (cameraMovingSpeed * deltaTime);
		}
		if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::S)))
		{
			cameraEntityPosition += forwardDir * (-cameraMovingSpeed * deltaTime);
		}
		if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::D)))
		{
			cameraEntityPosition += rightDir * (cameraMovingSpeed * deltaTime);
		}
		if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::A)))
		{
			cameraEntityPosition += rightDir * (-cameraMovingSpeed * deltaTime);
		}


		if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(mouseKeyData, GetMouseKey(Edge::MouseKeys::Right)))
		{
			pitchAngle += -mouseDelta.m_y * cameraRotationSpeed * deltaTime * Edge::Math::DegToRad;

			pitchAngle = std::min(pitchAngle, Edge::Math::HalfPi - Edge::Math::Epsilon);
			pitchAngle = std::max(pitchAngle, -Edge::Math::HalfPi + Edge::Math::Epsilon);

			yawAngle += mouseDelta.m_x * cameraRotationSpeed * deltaTime * Edge::Math::DegToRad;

			if (yawAngle >= Edge::Math::Pi2)
			{
				yawAngle -= Edge::Math::Pi2;
			}
			else if (yawAngle <= -Edge::Math::Pi2)
			{
				yawAngle += Edge::Math::Pi2;
			}
		}

	}

	Edge::ComputeMatrix4x4 cameraTransform = Edge::ComputeMatrix4x4Identity;
	cameraTransform *= TranslationComputeMatrix4x4(cameraEntityPosition);
	cameraTransform *= Edge::RotationEulerComputeMatrix4x4(pitchAngle, yawAngle, 0.0_ecv);
	m_cameraTransform.m_matrix = cameraTransform;
}
