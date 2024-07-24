#include "Cube.h"

#include "TinySimCommon/Math/Matrix.h"

TS_DEF_RENDERER::CubeShape TS_DEF_RENDERER::CubeShape::create(const TS::FloatVector3& size)
{
	return std::move(CubeShapeGenerator().generateShape(size));
}

void TS_DEF_RENDERER::CubeShapeGenerator::buildFaceIndices()
{
	m_indices.push_back(m_lastIndex + 0);
	m_indices.push_back(m_lastIndex + 1);
	m_indices.push_back(m_lastIndex + 2);
	m_indices.push_back(m_lastIndex + 1);
	m_indices.push_back(m_lastIndex + 2);
	m_indices.push_back(m_lastIndex + 3);

	m_lastIndex += 4;
}

void TS_DEF_RENDERER::CubeShapeGenerator::buildUpFace()
{
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, m_coords.m_z }, TS::FloatVector3UnitY });
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, -m_coords.m_z }, TS::FloatVector3UnitY });
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, m_coords.m_z }, TS::FloatVector3UnitY });
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, -m_coords.m_z }, TS::FloatVector3UnitY });

	buildFaceIndices();
}

void TS_DEF_RENDERER::CubeShapeGenerator::buildDownFace()
{
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, TS::FloatVector3NegativeUnitY });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, TS::FloatVector3NegativeUnitY });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, m_coords.m_z }, TS::FloatVector3NegativeUnitY });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, m_coords.m_z }, TS::FloatVector3NegativeUnitY });

	buildFaceIndices();
}

void TS_DEF_RENDERER::CubeShapeGenerator::buildFrontFace()
{
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, m_coords.m_z }, TS::FloatVector3UnitZ });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, m_coords.m_z }, TS::FloatVector3UnitZ });
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, m_coords.m_z }, TS::FloatVector3UnitZ });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, m_coords.m_z }, TS::FloatVector3UnitZ });

	buildFaceIndices();
}

void TS_DEF_RENDERER::CubeShapeGenerator::buildBackFace()
{
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, -m_coords.m_z }, TS::FloatVector3NegativeUnitZ });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, TS::FloatVector3NegativeUnitZ });
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, -m_coords.m_z }, TS::FloatVector3NegativeUnitZ });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, TS::FloatVector3NegativeUnitZ });

	buildFaceIndices();
}

void TS_DEF_RENDERER::CubeShapeGenerator::buildRightFace()
{
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, -m_coords.m_z }, TS::FloatVector3UnitX });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, TS::FloatVector3UnitX });
	m_vertices.push_back({ { m_coords.m_x, m_coords.m_y, m_coords.m_z }, TS::FloatVector3UnitX });
	m_vertices.push_back({ { m_coords.m_x, -m_coords.m_y, m_coords.m_z }, TS::FloatVector3UnitX });

	buildFaceIndices();
}

void TS_DEF_RENDERER::CubeShapeGenerator::buildLeftFace()
{
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, m_coords.m_z }, TS::FloatVector3NegativeUnitX });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, m_coords.m_z }, TS::FloatVector3NegativeUnitX });
	m_vertices.push_back({ { -m_coords.m_x, m_coords.m_y, -m_coords.m_z }, TS::FloatVector3NegativeUnitX });
	m_vertices.push_back({ { -m_coords.m_x, -m_coords.m_y, -m_coords.m_z }, TS::FloatVector3NegativeUnitX });

	buildFaceIndices();
}

TS_DEF_RENDERER::CubeShape TS_DEF_RENDERER::CubeShapeGenerator::generateShape(const TS::FloatVector3& size)
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

TS_DEF_RENDERER::LineCubeShape TS_DEF_RENDERER::LineCubeShape::create(const TS::FloatVector3& size)
{
	return std::move(LineCubeShapeGenerator().generateShape(size));
}

void TS_DEF_RENDERER::LineCubeShapeGenerator::buildVertices()
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

void TS_DEF_RENDERER::LineCubeShapeGenerator::buildIndices()
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

TS_DEF_RENDERER::LineCubeShape TS_DEF_RENDERER::LineCubeShapeGenerator::generateShape(const TS::FloatVector3& size)
{
	m_coords = { size.m_x * 0.5f, size.m_y * 0.5f, size.m_z * 0.5f };

	buildVertices();
	buildIndices();

	return std::move(LineCubeShape(std::move(m_vertices), std::move(m_indices)));
}
