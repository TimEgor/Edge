#include "Sphere.h"

#include "TinySimCommon/Math/ComputeVector.h"
#include "TinySimCommon/Math/Const.h"
#include "TinySimCommon/Math/Matrix.h"

TS_DEF_RENDERER::SphereShape TS_DEF_RENDERER::SphereShape::create(float radius, uint32_t stacks, uint32_t slices)
{
	return std::move(SphereShapeGenerator().generateShape(radius, stacks, slices));
}

void TS_DEF_RENDERER::SphereShapeGenerator::generateIndices(uint32_t stacks, uint32_t slices)
{
	for (uint32_t i = 1; i <= slices; ++i)
	{
		m_indices.push_back(0);
		m_indices.push_back(i + 1);
		m_indices.push_back(i);
	}

	const uint32_t ringVertexCount = slices + 1;

	uint32_t baseIndex = 1;
	for (uint32_t i = 0; i < stacks - 2; ++i)
	{
		for (uint32_t j = 0; j < slices; ++j)
		{
			m_indices.push_back(baseIndex + i * ringVertexCount + j);
			m_indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			m_indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			m_indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			m_indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			m_indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	const uint32_t southPoleIndex = m_vertices.size() - 1;

	baseIndex = southPoleIndex - ringVertexCount;
	for (uint32_t i = 0; i < slices; ++i)
	{
		m_indices.push_back(southPoleIndex);
		m_indices.push_back(baseIndex + i);
		m_indices.push_back(baseIndex + i + 1);
	}
}

void TS_DEF_RENDERER::SphereShapeGenerator::generateVertices(float radius, uint32_t stacks, uint32_t slices)
{
	SphereShape::Vertex topVertex;
	topVertex.m_position.m_y = radius;
	topVertex.m_normal = TS::FloatVector3UnitY;

	SphereShape::Vertex bottomVertex;
	bottomVertex.m_position.m_y = -radius;
	bottomVertex.m_normal = TS::FloatVector3NegativeUnitY;

	m_vertices.push_back(topVertex);

	const float phiStep = TS::TS_PI / stacks;
	const float thetaStep = 2.0f * TS::TS_PI / slices;

	for (uint32_t i = 1; i <= stacks - 1; ++i)
	{
		const float phi = i * phiStep;

		for (uint32_t j = 0; j <= slices; ++j)
		{
			const float theta = j * thetaStep;

			SphereShape::Vertex v;

			v.m_position.m_x = radius * sinf(phi) * cosf(theta);
			v.m_position.m_y = radius * cosf(phi);
			v.m_position.m_z = radius * sinf(phi) * sinf(theta);

			TS::ComputeVector computeNormal(v.m_position);
			computeNormal.normalize();
			computeNormal.saveToFloatVector3(v.m_normal);

			m_vertices.push_back(v);
		}
	}

	m_vertices.push_back(bottomVertex);
}

TS_DEF_RENDERER::SphereShape TS_DEF_RENDERER::SphereShapeGenerator::generateShape(float radius, uint32_t stacks, uint32_t slices)
{
	m_vertices.clear();
	m_indices.clear();

	generateVertices(radius, stacks, slices);
	generateIndices(stacks, slices);

	return std::move(SphereShape(std::move(m_vertices), std::move(m_indices)));
}

TS_DEF_RENDERER::LineSphereShape TS_DEF_RENDERER::LineSphereShape::create(float radius, uint32_t stacks, uint32_t slices)
{
	return std::move(LineSphereShapeGenerator().generateShape(radius, stacks, slices));
}

void TS_DEF_RENDERER::LineSphereShapeGenerator::generateIndices(uint32_t stacks, uint32_t slices)
{
	for (uint32_t i = 1; i <= slices; ++i)
	{
		m_indices.push_back(0);
		m_indices.push_back(i + 1);
		m_indices.push_back(i);
	}

	const uint32_t ringVertexCount = slices + 1;

	uint32_t baseIndex = 1;
	for (uint32_t i = 0; i < stacks - 2; ++i)
	{
		for (uint32_t j = 0; j < slices; ++j)
		{
			m_indices.push_back(baseIndex + i * ringVertexCount + j);
			m_indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			m_indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			m_indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			m_indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			m_indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	const uint32_t southPoleIndex = m_vertices.size() - 1;

	baseIndex = southPoleIndex - ringVertexCount;
	for (uint32_t i = 0; i < slices; ++i)
	{
		m_indices.push_back(southPoleIndex);
		m_indices.push_back(baseIndex + i);
		m_indices.push_back(baseIndex + i + 1);
	}
}

void TS_DEF_RENDERER::LineSphereShapeGenerator::generateVertices(float radius, uint32_t stacks, uint32_t slices)
{
	LineSphereShape::Vertex topVertex;
	topVertex.m_position.m_y = radius;

	LineSphereShape::Vertex bottomVertex;
	bottomVertex.m_position.m_y = -radius;

	m_vertices.push_back(topVertex);

	const float phiStep = TS::TS_PI / stacks;
	const float thetaStep = 2.0f * TS::TS_PI / slices;

	for (uint32_t i = 1; i <= stacks - 1; ++i)
	{
		const float phi = i * phiStep;

		for (uint32_t j = 0; j <= slices; ++j)
		{
			const float theta = j * thetaStep;

			LineSphereShape::Vertex v;

			v.m_position.m_x = radius * sinf(phi) * cosf(theta);
			v.m_position.m_y = radius * cosf(phi);
			v.m_position.m_z = radius * sinf(phi) * sinf(theta);

			m_vertices.push_back(v);
		}
	}

	m_vertices.push_back(bottomVertex);
}

TS_DEF_RENDERER::LineSphereShape TS_DEF_RENDERER::LineSphereShapeGenerator::generateShape(float radius, uint32_t stacks, uint32_t slices)
{
	m_vertices.clear();
	m_indices.clear();

	generateVertices(radius, stacks, slices);
	generateIndices(stacks, slices);

	return std::move(LineSphereShape(std::move(m_vertices), std::move(m_indices)));
}
