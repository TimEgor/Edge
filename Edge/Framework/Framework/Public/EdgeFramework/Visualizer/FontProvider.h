#pragma once

#include <cstdint>

namespace Edge
{
	class FontProvider
	{
	public:
		struct GlyphDataCollection final
		{
			static constexpr uint32_t BeginCharIndex = ' ';
			static constexpr uint32_t EndCharIndex = 256;
			static constexpr uint32_t GlyphCount = EndCharIndex - BeginCharIndex;

			uint8_t* m_data = nullptr;
			uint32_t m_dataSize = 0;

			uint32_t m_atlasHeight = 0;
			uint32_t m_atlasWidth = 0;

			uint16_t m_height = 0;

			uint16_t m_widths[GlyphCount];
			uint16_t m_heights[GlyphCount];
			int16_t m_offsetY[GlyphCount];
			int16_t m_spacing[GlyphCount][GlyphCount];
			uint16_t m_x[GlyphCount];
		};

		FontProvider() = default;
		virtual ~FontProvider() = default;

		virtual GlyphDataCollection getFontGlyphsData(const char* font, uint32_t height) = 0;
	};
}
