#pragma once

#include "EdgeFramework/Visualizer/FontProvider.h"

namespace Edge
{
	class GraphicDevice;
	class Texture2D;
}

namespace EdgeDefRender
{
	class Font final
	{
		static constexpr uint32_t GlyphCount = Edge::FontProvider::GlyphDataCollection::GlyphCount;

	private:
		Edge::Texture2D* m_atlas = nullptr;

		uint16_t m_height;

		uint16_t m_widths[GlyphCount];
		uint16_t m_heights[GlyphCount];
		int16_t m_offsetY[GlyphCount];
		uint16_t m_spacing[GlyphCount][GlyphCount];
		uint16_t m_x[GlyphCount];

	public:
		Font() = default;
		~Font();

		bool init(const Edge::FontProvider::GlyphDataCollection& glyphData, Edge::GraphicDevice& device);
		void release();

		Edge::Texture2D* getAtlas() const;

		uint16_t getHeight() const;

		uint16_t getGlyphWidth(uint32_t index) const;
		uint16_t getGlyphHeight(uint32_t index) const;
		int16_t getGlyphOffsetY(uint32_t index) const;
		uint16_t getGlyphPairSpacing(uint32_t index1, uint32_t index2) const;
		uint16_t getGlyphPosition(uint32_t index) const;
	};
}
