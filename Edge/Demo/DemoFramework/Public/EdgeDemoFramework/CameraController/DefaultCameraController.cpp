#include "DefaultCameraController.h"

#include "EdgeCommon/Math/Const.h"
#include "EdgeCommon/Math/ComputeMath/ComputeMatrix.h"
#include "EdgeCommon/Math/ComputeMath/ComputeVector.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceController.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceKeyCache.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceKeyUtils.h"
#include "EdgeFramework/Input/InputDeviceController/Devices/Keyboard.h"
#include "EdgeFramework/Input/InputDeviceController/Devices/Mouse.h"

#include <cmath>

void EdgeDemo::DefaultCameraController::update(float deltaTime)
{
	static constexpr float cameraMovingSpeed = 5.0f;
	static constexpr float cameraRotationSpeed = 10.0f;

	const Edge::InputDeviceController& inputController = Edge::FrameworkCore::getInstance().getApplication().getInputDeviceController();

	const Edge::InputDeviceKeyCache::DeviceKeyCache* keyboardKeyCache = inputController.getDeviceKeyCache(Edge::KeyboardInputDevice::getDeviceType());
	const Edge::InputDeviceKeyCache::DeviceKeyCache* mouseKeyCache = inputController.getDeviceKeyCache(Edge::MouseInputDevice::getDeviceType());
	if (!keyboardKeyCache || !mouseKeyCache)
	{
		return;
	}

	const Edge::InputDeviceKeyData& keyboardKeyData = keyboardKeyCache->m_currentKeyData;
	const Edge::InputDeviceKeyData& mouseKeyData = mouseKeyCache->m_currentKeyData;

	Edge::ComputeMath::Vector cameraEntityPosition = Edge::ComputeMath::vector3Load(m_cameraTransform.getOrigin());
	Edge::ComputeMath::Vector rightDir = Edge::ComputeMath::vector3Load(m_cameraTransform.getAxisX());
	Edge::ComputeMath::Vector upDir = Edge::ComputeMath::vector3Load(m_cameraTransform.getAxisY());
	Edge::ComputeMath::Vector forwardDir = Edge::ComputeMath::vector3Load(m_cameraTransform.getAxisZ());

	Edge::ComputeMath::Matrix cameraTransform = Edge::ComputeMath::matrix4x4Load(Edge::FloatMatrix4x4Identity);

	float pitchAngle = asin(-m_cameraTransform.m_matrix.m_m32);
	float yawAngle = 0.0f;

	if (cosf(pitchAngle) > EDGE_EPSILON)
	{
		yawAngle = atan2f(m_cameraTransform.m_matrix.m_m31, m_cameraTransform.m_matrix.m_m33);
	}

	const Edge::FloatVector2 mouseDelta(
		mouseKeyData.m_values[GetMouseKey(Edge::MouseKeys::X)],
		mouseKeyData.m_values[GetMouseKey(Edge::MouseKeys::Y)]
	);

	if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(mouseKeyData, GetMouseKey(Edge::MouseKeys::Wheel)))
	{
		cameraEntityPosition = Edge::ComputeMath::vectorAdd(
			Edge::ComputeMath::vectorScale(rightDir, -mouseDelta.m_x * cameraMovingSpeed * deltaTime),
			cameraEntityPosition
		);

		cameraEntityPosition = Edge::ComputeMath::vectorAdd(
			Edge::ComputeMath::vectorScale(upDir, mouseDelta.m_y * cameraMovingSpeed * deltaTime),
			cameraEntityPosition
		);
	}
	else {
		if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::W)))
		{
			cameraEntityPosition = Edge::ComputeMath::vectorAdd(
				Edge::ComputeMath::vectorScale(forwardDir, cameraMovingSpeed * deltaTime),
				cameraEntityPosition
			);
		}
		if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::S)))
		{
			cameraEntityPosition = Edge::ComputeMath::vectorAdd(
				Edge::ComputeMath::vectorScale(forwardDir, -cameraMovingSpeed * deltaTime),
				cameraEntityPosition
			);
		}
		if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::D)))
		{
			cameraEntityPosition = Edge::ComputeMath::vectorAdd(
				Edge::ComputeMath::vectorScale(rightDir, cameraMovingSpeed * deltaTime),
				cameraEntityPosition
			);
		}
		if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(keyboardKeyData, GetKeyboardKey(Edge::KeyboardKeys::A)))
		{
			cameraEntityPosition = Edge::ComputeMath::vectorAdd(
				Edge::ComputeMath::vectorScale(rightDir, -cameraMovingSpeed * deltaTime),
				cameraEntityPosition
			);
		}


		if (Edge::InputDeviceKeyUtils::IsInputDeviceKeyPressed(mouseKeyData, GetMouseKey(Edge::MouseKeys::Right)))
		{
			pitchAngle += -mouseDelta.m_y * cameraRotationSpeed * deltaTime * EDGE_DEG_TO_RAD;

			pitchAngle = std::min(pitchAngle, EDGE_HALF_PI - EDGE_EPSILON);
			pitchAngle = std::max(pitchAngle, -EDGE_HALF_PI + EDGE_EPSILON);

			yawAngle += mouseDelta.m_x * cameraRotationSpeed * deltaTime * EDGE_DEG_TO_RAD;

			if (yawAngle >= EDGE_2_PI)
			{
				yawAngle -= EDGE_2_PI;
			}
			else if (yawAngle <= -EDGE_2_PI)
			{
				yawAngle += EDGE_2_PI;
			}
		}

	}

	cameraTransform = Edge::ComputeMath::matrixMultiply(cameraTransform, Edge::ComputeMath::matrixRotationRollPitchYaw(pitchAngle, yawAngle, 0.0f));
	cameraTransform = Edge::ComputeMath::matrixMultiply(cameraTransform, Edge::ComputeMath::matrixTranslation(cameraEntityPosition));
	m_cameraTransform.m_matrix = Edge::ComputeMath::matrix4x4Save(cameraTransform);
}
