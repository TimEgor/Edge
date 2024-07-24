#pragma once

namespace TS_DEF_RENDERER
{
	template<typename VertexType>
	class Shape
	{
	public:
		using Vertex = VertexType;
		using VertexIndex = uint16_t;

		using VertexCollection = std::vector<Vertex>;
		using IndexCollection = std::vector<VertexIndex>;

		Shape() = default;
		virtual ~Shape() = default;

		virtual const VertexCollection& getVertices() const = 0;
		virtual const IndexCollection* getIndices() const { return nullptr; }
	};
}
