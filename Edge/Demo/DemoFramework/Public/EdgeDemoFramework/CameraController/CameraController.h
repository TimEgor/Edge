#pragma once

namespace Edge
{
	struct Transform;
}

namespace EdgeDemo
{
	class CameraController
	{
	public:
		CameraController() = default;
		virtual ~CameraController() = default;

		virtual void update(float deltaTime) = 0;

		virtual const Edge::Transform& getTransform() const = 0;
		virtual Edge::Transform& getTransform() = 0;
	};
}
