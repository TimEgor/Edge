#pragma once

#include "EdgeFramework/Visualizer/FontProvider.h"

namespace EdgeWin32
{
	class Win32PlatformFontProvider final : public Edge::FontProvider
	{
	public:
		Win32PlatformFontProvider() = default;

		virtual GlyphDataCollection getFontGlyphsData(const char* font, uint32_t height) override;
	};
}
