#pragma once

#include "EdgeCommon/Math/Transform.h"

#include "CameraController.h"

namespace EdgeDemo
{
	class DefaultCameraController final : public CameraController
	{
	private:
		Edge::Transform m_cameraTransform;

	public:
		DefaultCameraController() = default;

		virtual void update(float deltaTime) override;

		void setTransform(const Edge::Transform& transform) { m_cameraTransform = transform; }
		virtual const Edge::Transform& getTransform() const override { return m_cameraTransform; }
		virtual Edge::Transform& getTransform() override { return m_cameraTransform; }
	};
}
