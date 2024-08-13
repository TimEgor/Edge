#pragma once

#include "EdgePhysics/Physics/PhysicsWorld.h"
#include "EdgePhysics/Physics/Scene/PhysicsScene.h"
#include "EdgePhysics/Physics/Utils/PhysicsTimeStepper.h"
#include "EdgePhysics/Visualizer/DebugVisualizationDataController.h"

#include "EdgeDemoFramework/CameraController/CameraController.h"

#include "Demo.h"

namespace EdgeDemo
{
	class CameraController;

	class PreInitedDemo : public Demo
	{
	protected:
		Edge::PhysicsSemiFixedTimeStepper m_timeStepper;

		Edge::PhysicsWorldReference m_physicsWorld;
		Edge::PhysicsSceneReference m_physicsScene;

		Edge::DebugVisualizationDataController* m_debugVisualizationDataController = nullptr;

		CameraController* m_cameraController = nullptr;

		virtual bool initPhysics();
		virtual bool initCameraController();

		virtual bool initDebugVisualizationData();

		virtual bool initDemo() { return true; }
		virtual void releaseDemo() {}

		virtual void updateDemoLogic(float deltaTime) {}
		virtual void prePhysStepDemoUpdate(float deltaTime) {}

	public:
		PreInitedDemo() = default;

		virtual bool init() override final;
		virtual void release() override final;

		virtual void updateLogic(float deltaTime) override final;
		virtual void prePhysStepUpdate(float deltaTime) override final;

		virtual void physUpdate(float deltaTime) override final;

		virtual Edge::DebugVisualizationDataController& getDebugVisualizationData() override { return *m_debugVisualizationDataController; }

		virtual const Edge::Transform& getCameraTransform() const override final { return m_cameraController->getTransform(); }
	};
}
