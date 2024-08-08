#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"

#include "Shape.h"
#include "Vertices.h"

#include <vector>


namespace EdgeDefRender
{
	class SphereShape final : public Shape<SolidVertex>
	{
	private:
		VertexCollection m_vertices;
		IndexCollection m_indices;

	public:
		SphereShape() = default;
		SphereShape(VertexCollection&& vertices, IndexCollection&& indices)
			: m_vertices(std::move(vertices)), m_indices(std::move(indices)) {}
		SphereShape(const SphereShape&) = default;
		SphereShape(SphereShape&&) = default;

		SphereShape& operator=(const SphereShape&) = default;
		SphereShape& operator=(SphereShape&&) = default;

		virtual const VertexCollection& getVertices() const override { return m_vertices; }
		virtual const IndexCollection* getIndices() const override { return &m_indices; }

		static SphereShape create(float radius, uint32_t stacks, uint32_t slices);
	};

	class SphereShapeGenerator final
	{
	private:
		SphereShape::VertexCollection m_vertices;
		SphereShape::IndexCollection m_indices;

		void generateIndices(uint32_t stacks, uint32_t slices);
		void generateVertices(float radius, uint32_t stacks, uint32_t slices);

	public:
		SphereShapeGenerator() = default;

		SphereShape generateShape(float radius, uint32_t stacks, uint32_t slices);
	};

	class LineSphereShape final : public Shape<WireframeVertex>
	{
	private:
		VertexCollection m_vertices;
		IndexCollection m_indices;

	public:
		LineSphereShape() = default;
		LineSphereShape(VertexCollection&& vertices, IndexCollection&& indices)
			: m_vertices(std::move(vertices)), m_indices(std::move(indices)) {}
		LineSphereShape(const LineSphereShape&) = default;
		LineSphereShape(LineSphereShape&&) = default;

		LineSphereShape& operator=(const LineSphereShape&) = default;
		LineSphereShape& operator=(LineSphereShape&&) = default;

		virtual const VertexCollection& getVertices() const override { return m_vertices; }
		virtual const IndexCollection* getIndices() const override { return &m_indices; }

		static LineSphereShape create(float radius, uint32_t stacks, uint32_t slices);
	};

	class LineSphereShapeGenerator final
	{
	private:
		LineSphereShape::VertexCollection m_vertices;
		LineSphereShape::IndexCollection m_indices;

		void generateIndices(uint32_t stacks, uint32_t slices);
		void generateVertices(float radius, uint32_t stacks, uint32_t slices);

	public:
		LineSphereShapeGenerator() = default;

		LineSphereShape generateShape(float radius, uint32_t stacks, uint32_t slices);
	};
}
