#pragma once

#include "TinySimCommon/Math/Vector.h"

#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"

#include "Shape.h"
#include "Vertices.h"


namespace TS_DEF_RENDERER
{
	class CubeShape final : public Shape<SolidVertex>
	{
	private:
		VertexCollection m_vertices;
		IndexCollection m_indices;

	public:
		CubeShape() = default;
		CubeShape(VertexCollection&& vertices, IndexCollection&& indices)
			: m_vertices(std::move(vertices)), m_indices(std::move(indices)) {}
		CubeShape(const CubeShape&) = default;
		CubeShape(CubeShape&&) = default;

		CubeShape& operator=(const CubeShape&) = default;
		CubeShape& operator=(CubeShape&&) = default;

		virtual const VertexCollection& getVertices() const override { return m_vertices; }
		virtual const IndexCollection* getIndices() const override { return &m_indices; }

		static CubeShape create(const TS::FloatVector3& size);
	};

	class CubeShapeGenerator final
	{
	private:
		CubeShape::VertexCollection m_vertices;
		CubeShape::IndexCollection m_indices;

		TS::FloatVector3 m_coords;

		CubeShape::VertexIndex m_lastIndex = 0;

		void buildFaceIndices();

		void buildUpFace();
		void buildDownFace();
		void buildFrontFace();
		void buildBackFace();
		void buildRightFace();
		void buildLeftFace();

	public:
		CubeShapeGenerator() = default;

		CubeShape generateShape(const TS::FloatVector3& size);
	};

	class LineCubeShape final : public Shape<WireframeVertex>
	{
	private:
		VertexCollection m_vertices;
		IndexCollection m_indices;

	public:
		LineCubeShape() = default;
		LineCubeShape(VertexCollection&& vertices, IndexCollection&& indices)
			: m_vertices(std::move(vertices)), m_indices(std::move(indices)) {}
		LineCubeShape(const LineCubeShape&) = default;
		LineCubeShape(LineCubeShape&&) = default;

		LineCubeShape& operator=(const LineCubeShape&) = default;
		LineCubeShape& operator=(LineCubeShape&&) = default;

		virtual const VertexCollection& getVertices() const override { return m_vertices; }
		virtual const IndexCollection* getIndices() const override { return &m_indices; }

		static LineCubeShape create(const TS::FloatVector3& size);
	};

	class LineCubeShapeGenerator final
	{
	private:
		LineCubeShape::VertexCollection m_vertices;
		LineCubeShape::IndexCollection m_indices;

		TS::FloatVector3 m_coords;

		void buildVertices();
		void buildIndices();

	public:
		LineCubeShapeGenerator() = default;

		LineCubeShape generateShape(const TS::FloatVector3& size);
	};
}
