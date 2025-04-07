#pragma once

#include "Font.h"

#include <unordered_map>

namespace EdgeDefRender
{
	class FontController final
	{
	private:
		struct FontData final
		{
			Font m_font;
			uint32_t m_lastUsingFrame = 0;
		};

		using FontID = uint32_t;
		using FontCollection = std::unordered_map<FontID, FontData>;

		FontCollection m_fonts;


	public:
		FontController() = default;

		void release();

		void update();

		const Font* getFont(const char* fontName, uint32_t fontHeight);
	};
}

