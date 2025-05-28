#include "Cube.h"

#include "EdgeCommon/Math/Matrix.h"

EdgeDefRender::CubeShape EdgeDefRender::CubeShape::create(const Edge::FloatVector3& size)
{
	return std::move(CubeShapeGenerator().generateShape(size));
}

void EdgeDefRender::CubeShapeGenerator::buildFaceIndices()
{
	m_indices.push_back(m_lastIndex + 0);
	m_indices.push_back(m_lastIndex + 1);
	m_indices.push_back(m_lastIndex + 2);
	m_indices.push_back(m_lastIndex + 1);
	m_indices.push_back(m_lastIndex + 2);
	m_indices.push_back(m_lastIndex + 3);

	m_lastIndex += 4;
}

void EdgeDefRender::CubeShapeGenerator::buildUpFace()
{
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, m_coords.m_z }, Edge::FloatVector3UnitY, {0.0f, 0.0f} });
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3UnitY, {0.0f, 1.0f} });
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, m_coords.m_z }, Edge::FloatVector3UnitY, {1.0f, 0.0f} });
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3UnitY, {1.0f, 1.0f} });

	buildFaceIndices();
}

void EdgeDefRender::CubeShapeGenerator::buildDownFace()
{
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3NegativeUnitY, {0.0f, 0.0f} });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3NegativeUnitY, {0.0f, 1.0f} });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, m_coords.m_z }, Edge::FloatVector3NegativeUnitY, {1.0f, 0.0f} });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, m_coords.m_z }, Edge::FloatVector3NegativeUnitY, {1.0f, 1.0f} });

	buildFaceIndices();
}

void EdgeDefRender::CubeShapeGenerator::buildFrontFace()
{
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, m_coords.m_z }, Edge::FloatVector3UnitZ, {0.0f, 0.0f} });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, m_coords.m_z }, Edge::FloatVector3UnitZ, {0.0f, 1.0f} });
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, m_coords.m_z }, Edge::FloatVector3UnitZ, {1.0f, 0.0f} });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, m_coords.m_z }, Edge::FloatVector3UnitZ, {1.0f, 1.0f} });

	buildFaceIndices();
}

void EdgeDefRender::CubeShapeGenerator::buildBackFace()
{
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3NegativeUnitZ, {0.0f, 0.0f} });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3NegativeUnitZ, {0.0f, 1.0f} });
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3NegativeUnitZ, {1.0f, 0.0f} });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3NegativeUnitZ, {1.0f, 1.0f} });

	buildFaceIndices();
}

void EdgeDefRender::CubeShapeGenerator::buildRightFace()
{
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3UnitX, {0.0f, 0.0f} });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3UnitX, {0.0f, 1.0f} });
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, m_coords.m_z }, Edge::FloatVector3UnitX, {1.0f, 0.0f} });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, m_coords.m_z }, Edge::FloatVector3UnitX, {1.0f, 1.0f} });

	buildFaceIndices();
}

void EdgeDefRender::CubeShapeGenerator::buildLeftFace()
{
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, m_coords.m_z }, Edge::FloatVector3NegativeUnitX, {0.0f, 0.0f} });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, m_coords.m_z }, Edge::FloatVector3NegativeUnitX, {0.0f, 1.0f} });
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3NegativeUnitX, {1.0f, 0.0f} });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, Edge::FloatVector3NegativeUnitX, {1.0f, 1.0f} });

	buildFaceIndices();
}

EdgeDefRender::CubeShape EdgeDefRender::CubeShapeGenerator::generateShape(const Edge::FloatVector3& size)
{
	m_vertices.clear();
	m_indices.clear();

	m_lastIndex = 0;

	m_vertices.reserve(24);
	m_indices.reserve(36);

	m_coords = { size.m_x * 0.5f, size.m_y * 0.5f, size.m_z * 0.5f };

	buildUpFace();
	buildDownFace();
	buildFrontFace();
	buildBackFace();
	buildRightFace();
	buildLeftFace();

	return std::move(CubeShape(std::move(m_vertices), std::move(m_indices)));
}

EdgeDefRender::LineCubeShape EdgeDefRender::LineCubeShape::create(const Edge::FloatVector3& size)
{
	return std::move(LineCubeShapeGenerator().generateShape(size));
}

void EdgeDefRender::LineCubeShapeGenerator::buildVertices()
{
	m_vertices.clear();
	m_vertices.reserve(8);

	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, m_coords.m_z } });
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, m_coords.m_z } });
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, -m_coords.m_z } });
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, -m_coords.m_z } });

	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, m_coords.m_z } });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, m_coords.m_z } });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, -m_coords.m_z } });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, -m_coords.m_z } });
}

void EdgeDefRender::LineCubeShapeGenerator::buildIndices()
{
	m_indices.clear();
	m_indices.reserve(24);

	//
	m_indices.push_back(0);
	m_indices.push_back(1);

	m_indices.push_back(1);
	m_indices.push_back(2);

	m_indices.push_back(2);
	m_indices.push_back(3);

	m_indices.push_back(3);
	m_indices.push_back(0);

	//
	m_indices.push_back(4);
	m_indices.push_back(5);

	m_indices.push_back(5);
	m_indices.push_back(6);

	m_indices.push_back(6);
	m_indices.push_back(7);

	m_indices.push_back(7);
	m_indices.push_back(4);

	//
	m_indices.push_back(0);
	m_indices.push_back(4);

	m_indices.push_back(1);
	m_indices.push_back(5);

	m_indices.push_back(2);
	m_indices.push_back(6);

	m_indices.push_back(3);
	m_indices.push_back(7);
}

EdgeDefRender::LineCubeShape EdgeDefRender::LineCubeShapeGenerator::generateShape(const Edge::FloatVector3& size)
{
	m_coords = { size.m_x * 0.5f, size.m_y * 0.5f, size.m_z * 0.5f };

	buildVertices();
	buildIndices();

	return std::move(LineCubeShape(std::move(m_vertices), std::move(m_indices)));
}
