#include "DebugDrawDemo.h"

#include "EdgeCommon/Math/Transform.h"

void EdgeDemo::DebugDrawDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	m_debugVisualizationDataController->addGrid(
		Edge::FloatVector3(0.0f, -2.0f, 0.0f),
		Edge::FloatVector3UnitY,
		Edge::FloatVector3UnitX,
		Edge::FloatVector2(5.0f, 5.0f),
		Edge::UInt32Vector2(10, 10)
	);

	m_debugVisualizationDataController->addPoint(Edge::FloatVector3(2.0f, 0.0f, 0.0f), Edge::NormalizedColorRed);
	m_debugVisualizationDataController->addPoint(Edge::FloatVector3(2.0f, 2.0f, 0.0f), Edge::NormalizedColorGreen);
	m_debugVisualizationDataController->addPoint(Edge::FloatVector3(2.0f, 4.0f, 0.0f), Edge::NormalizedColorBlue);

	m_debugVisualizationDataController->addLine(Edge::FloatVector3(3.0f, 0.0f, 0.0f), Edge::FloatVector3(3.0f, 0.0f, -1.0f), Edge::NormalizedColorRed);
	m_debugVisualizationDataController->addLine(Edge::FloatVector3(3.0f, 2.0f, 0.0f), Edge::FloatVector3(3.0f, 2.0f, -1.0f), Edge::NormalizedColorGreen);
	m_debugVisualizationDataController->addLine(Edge::FloatVector3(3.0f, 4.0f, 0.0f), Edge::FloatVector3(3.0f, 4.0f, -1.0f), Edge::NormalizedColorBlue);

	m_debugVisualizationDataController->addArrow(Edge::FloatVector3(4.0f, 0.0f, 0.0f), Edge::FloatVector3NegativeUnitZ, 0.2f, Edge::NormalizedColorRed);
	m_debugVisualizationDataController->addArrow(Edge::FloatVector3(4.0f, 2.0f, 0.0f), Edge::FloatVector3NegativeUnitZ, 0.2f, Edge::NormalizedColorGreen);
	m_debugVisualizationDataController->addArrow(Edge::FloatVector3(4.0f, 4.0f, 0.0f), Edge::FloatVector3NegativeUnitZ, 0.2f, Edge::NormalizedColorBlue);

	{
		Edge::Transform boxTransform;

		boxTransform.setOrigin(Edge::FloatVector3(6.0f, 0.0f, 0.0f));
		m_debugVisualizationDataController->addBox(boxTransform, Edge::NormalizedColorRed);
		boxTransform.setOrigin(Edge::FloatVector3(6.0f, 2.0f, 0.0f));
		m_debugVisualizationDataController->addBox(boxTransform, Edge::NormalizedColorGreen);
		boxTransform.setOrigin(Edge::FloatVector3(6.0f, 4.0f, 0.0f));
		m_debugVisualizationDataController->addBox(boxTransform, Edge::NormalizedColorBlue);
	}

	{
		Edge::Transform boxTransform;

		boxTransform.setOrigin(Edge::FloatVector3(8.0f, 0.0f, 0.0f));
		m_debugVisualizationDataController->addWireframeBox(boxTransform, Edge::NormalizedColorRed);
		boxTransform.setOrigin(Edge::FloatVector3(8.0f, 2.0f, 0.0f));
		m_debugVisualizationDataController->addWireframeBox(boxTransform, Edge::NormalizedColorGreen);
		boxTransform.setOrigin(Edge::FloatVector3(8.0f, 4.0f, 0.0f));
		m_debugVisualizationDataController->addWireframeBox(boxTransform, Edge::NormalizedColorBlue);
	}

	m_debugVisualizationDataController->addSphere(
		Edge::FloatVector3(10.0f, 0.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitY,
		0.5f,
		Edge::NormalizedColorRed
	);
	m_debugVisualizationDataController->addSphere(
		Edge::FloatVector3(10.0f, 2.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitY,
		0.5f,
		Edge::NormalizedColorGreen
	);
	m_debugVisualizationDataController->addSphere(
		Edge::FloatVector3(10.0f, 4.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitY,
		0.5f,
		Edge::NormalizedColorBlue
	);

	m_debugVisualizationDataController->addWireframeSphere(
		Edge::FloatVector3(12.0f, 0.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitY,
		0.5f,
		Edge::NormalizedColorRed
	);
	m_debugVisualizationDataController->addWireframeSphere(
		Edge::FloatVector3(12.0f, 2.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitY,
		0.5f,
		Edge::NormalizedColorGreen
	);
	m_debugVisualizationDataController->addWireframeSphere(
		Edge::FloatVector3(12.0f, 4.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitY,
		0.5f,
		Edge::NormalizedColorBlue
	);

	m_debugVisualizationDataController->addPlane(
		Edge::FloatVector3(14.0f, 0.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitX,
		Edge::FloatVector2(1.0f),
		Edge::NormalizedColorRed
	);
	m_debugVisualizationDataController->addPlane(
		Edge::FloatVector3(14.0f, 2.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitX,
		Edge::FloatVector2(1.0f),
		Edge::NormalizedColorGreen
	);
	m_debugVisualizationDataController->addPlane(
		Edge::FloatVector3(14.0f, 4.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitX,
		Edge::FloatVector2(1.0f),
		Edge::NormalizedColorBlue
	);

	m_debugVisualizationDataController->addWireframePlane(
		Edge::FloatVector3(16.0f, 0.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitX,
		Edge::FloatVector2(1.0f),
		Edge::NormalizedColorRed
	);
	m_debugVisualizationDataController->addWireframePlane(
		Edge::FloatVector3(16.0f, 2.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitX,
		Edge::FloatVector2(1.0f),
		Edge::NormalizedColorGreen
	);
	m_debugVisualizationDataController->addWireframePlane(
		Edge::FloatVector3(16.0f, 4.0f, 0.0f),
		Edge::FloatVector3NegativeUnitZ,
		Edge::FloatVector3UnitX,
		Edge::FloatVector2(1.0f),
		Edge::NormalizedColorBlue
	);

	{
		const Edge::ComputeVector3 polygonLocalVertex1(0.0f, 0.5f, 0.0f);
		const Edge::ComputeVector3 polygonLocalVertex2(0.5f, -0.5f, 0.0f);
		const Edge::ComputeVector3 polygonLocalVertex3(-0.5f, -0.5f, 0.0f);

		{
			const Edge::ComputeVector3 polygonPos(18.0f, 0.0f, 0.0f);
			m_debugVisualizationDataController->addPolygon(
				(polygonLocalVertex1 + polygonPos).getFloatVector3(),
				(polygonLocalVertex2 + polygonPos).getFloatVector3(),
				(polygonLocalVertex3 + polygonPos).getFloatVector3(),
				Edge::NormalizedColorRed
			);
		}

		{
			const Edge::ComputeVector3 polygonPos(18.0f, 2.0f, 0.0f);
			m_debugVisualizationDataController->addPolygon(
				(polygonLocalVertex1 + polygonPos).getFloatVector3(),
				(polygonLocalVertex2 + polygonPos).getFloatVector3(),
				(polygonLocalVertex3 + polygonPos).getFloatVector3(),
				Edge::NormalizedColorGreen
			);
		}

		{
			const Edge::ComputeVector3 polygonPos(18.0f, 4.0f, 0.0f);
			m_debugVisualizationDataController->addPolygon(
				(polygonLocalVertex1 + polygonPos).getFloatVector3(),
				(polygonLocalVertex2 + polygonPos).getFloatVector3(),
				(polygonLocalVertex3 + polygonPos).getFloatVector3(),
				Edge::NormalizedColorBlue
			);
		}

		{
			const Edge::ComputeVector3 polygonPos(20.0f, 0.0f, 0.0f);
			m_debugVisualizationDataController->addWireframePolygon(
				(polygonLocalVertex1 + polygonPos).getFloatVector3(),
				(polygonLocalVertex2 + polygonPos).getFloatVector3(),
				(polygonLocalVertex3 + polygonPos).getFloatVector3(),
				Edge::NormalizedColorRed
			);
		}

		{
			const Edge::ComputeVector3 polygonPos(20.0f, 2.0f, 0.0f);
			m_debugVisualizationDataController->addWireframePolygon(
				(polygonLocalVertex1 + polygonPos).getFloatVector3(),
				(polygonLocalVertex2 + polygonPos).getFloatVector3(),
				(polygonLocalVertex3 + polygonPos).getFloatVector3(),
				Edge::NormalizedColorGreen
			);
		}

		{
			const Edge::ComputeVector3 polygonPos(20.0f, 4.0f, 0.0f);
			m_debugVisualizationDataController->addWireframePolygon(
				(polygonLocalVertex1 + polygonPos).getFloatVector3(),
				(polygonLocalVertex2 + polygonPos).getFloatVector3(),
				(polygonLocalVertex3 + polygonPos).getFloatVector3(),
				Edge::NormalizedColorBlue
			);
		}
	}

	m_debugVisualizationDataController->addWorldText(
		Edge::FloatVector3(2.0f, 6.0f, 0.0f),
		Edge::FloatVector3UnitZ,
		Edge::FloatVector3UnitY,
		"Test",
		1.0f,
		Edge::NormalizedColorRed
	);
	m_debugVisualizationDataController->addWorldText(
		Edge::FloatVector3(2.0f, 8.0f, 0.0f),
		Edge::FloatVector3UnitZ,
		Edge::FloatVector3UnitY,
		"Test",
		1.0f,
		Edge::NormalizedColorGreen
	);
	m_debugVisualizationDataController->addWorldText(
		Edge::FloatVector3(2.0f, 10.0f, 0.0f),
		Edge::FloatVector3UnitZ,
		Edge::FloatVector3UnitY,
		"Test",
		1.0f,
		Edge::NormalizedColorBlue
	);
}
