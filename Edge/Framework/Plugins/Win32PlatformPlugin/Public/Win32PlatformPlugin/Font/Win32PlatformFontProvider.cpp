#include "Win32PlatformFontProvider.h"

#include <algorithm>

#include "EdgeCommon/PlatformMacros.h"
#include "EdgeCommon/Assert/AssertCore.h"

EdgeWin32::Win32PlatformFontProvider::GlyphDataCollection EdgeWin32::Win32PlatformFontProvider::getFontGlyphsData(const char* fontName, uint32_t height)
{
	GlyphDataCollection result;

	result.m_height = height;

	LOGFONTA fontDesc{};
	ZeroMemory(&fontDesc, sizeof(LOGFONTA));
	fontDesc.lfHeight = height;
	fontDesc.lfWeight = FW_NORMAL;
	fontDesc.lfCharSet = DEFAULT_CHARSET;
	fontDesc.lfOutPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	fontDesc.lfQuality = ANTIALIASED_QUALITY;
	fontDesc.lfPitchAndFamily = VARIABLE_PITCH;
	strcpy_s(fontDesc.lfFaceName, LF_FACESIZE, fontName);

	const HFONT font = CreateFontIndirectA(&fontDesc);
	if (font)
	{
		const HDC deviceContext = CreateCompatibleDC(nullptr);
		if (deviceContext)
		{
			SelectObject(deviceContext, font);
			SetMapMode(deviceContext, MM_TEXT);

			TEXTMETRICA textMetric;
			if (GetTextMetricsA(deviceContext, &textMetric))
			{
				ABC widths[256];
				if (GetCharABCWidthsA(deviceContext, 0, 255, widths))
				{
					for (uint32_t charIndex1 = GlyphDataCollection::BeginCharIndex; charIndex1 < GlyphDataCollection::EndCharIndex; ++charIndex1)
					{
						const uint32_t glyphIndex1 = charIndex1 - GlyphDataCollection::BeginCharIndex;

						result.m_widths[glyphIndex1] = widths[charIndex1].abcB;

						for (uint32_t charIndex2 = GlyphDataCollection::BeginCharIndex; charIndex2 < GlyphDataCollection::EndCharIndex; ++charIndex2)
						{
							const uint32_t glyphIndex2 = charIndex2 - GlyphDataCollection::BeginCharIndex;

							const uint32_t spacing =
								widths[charIndex2].abcA +
								widths[charIndex1].abcB +
								widths[charIndex1].abcC;

							result.m_spacing[glyphIndex1][glyphIndex2] = spacing;
						}
					}

					const DWORD kerningPairCount = GetKerningPairsA(deviceContext, 0, nullptr);
					if (kerningPairCount > 0)
					{
						LPKERNINGPAIR pairs = new KERNINGPAIR[kerningPairCount];

						GetKerningPairsA(deviceContext, kerningPairCount, pairs);
						for (DWORD pairIndex = 0; pairIndex < kerningPairCount; ++pairIndex)
						{
							if (
								pairs[pairIndex].wFirst >= GlyphDataCollection::BeginCharIndex &&
								pairs[pairIndex].wFirst < GlyphDataCollection::EndCharIndex &&
								pairs[pairIndex].wSecond >= GlyphDataCollection::BeginCharIndex &&
								pairs[pairIndex].wSecond < GlyphDataCollection::EndCharIndex
								)
							{
								const uint32_t glyphIndex1 = pairs[pairIndex].wFirst - GlyphDataCollection::BeginCharIndex;
								const uint32_t glyphIndex2 = pairs[pairIndex].wSecond - GlyphDataCollection::BeginCharIndex;

								result.m_spacing[glyphIndex1][glyphIndex2] += pairs[pairIndex].iKernAmount;
							}
						}

						delete[] pairs;
					}

					MAT2 charTransform;
					ZeroMemory(&charTransform, sizeof(MAT2));
					charTransform.eM11.value = 1;
					charTransform.eM22.value = 1;

					uint32_t totalHeight = 0;
					uint32_t totalWidth = 0;

					for (uint32_t charIndex = GlyphDataCollection::BeginCharIndex; charIndex < GlyphDataCollection::EndCharIndex; ++charIndex)
					{
						const uint32_t glyphIndex = charIndex - GlyphDataCollection::BeginCharIndex;

						GLYPHMETRICS charMetrics;
						const uint32_t char_size =
							GetGlyphOutlineA(deviceContext, charIndex, GGO_GRAY8_BITMAP, &charMetrics, 0, nullptr, &charTransform);

						if (char_size != GDI_ERROR && char_size > 0)
						{
							totalHeight = std::max(totalHeight, charMetrics.gmBlackBoxY);
							totalWidth += charMetrics.gmBlackBoxX;
							result.m_heights[glyphIndex] = charMetrics.gmBlackBoxY;
						}
						else
						{
							result.m_heights[glyphIndex] = 0;
						}
					}

					result.m_atlasHeight = totalHeight;
					result.m_atlasWidth = totalWidth;
					result.m_dataSize = totalHeight * totalWidth;
					result.m_data = new uint8_t[result.m_dataSize];

					uint32_t offsetX = 0;

					for (uint32_t charIndex = GlyphDataCollection::BeginCharIndex; charIndex < GlyphDataCollection::EndCharIndex; ++charIndex)
					{
						GLYPHMETRICS charMetrics;
						const uint32_t char_size =
							GetGlyphOutlineA(deviceContext, charIndex, GGO_GRAY8_BITMAP, &charMetrics, 0, nullptr, &charTransform);

						if (char_size != GDI_ERROR && char_size > 0)
						{
							uint8_t* charData = new uint8_t[char_size];
							GetGlyphOutlineA(deviceContext, charIndex, GGO_GRAY8_BITMAP, &charMetrics, char_size, charData, &charTransform);

							const uint32_t srcPitch = (charMetrics.gmBlackBoxX + 3) & ~uint32_t(3);

							for (uint32_t offsetY = 0; offsetY < charMetrics.gmBlackBoxY; ++offsetY)
							{
								const uint8_t* charDataLineScr = charData + offsetY * srcPitch;
								uint8_t* charDataLineDst = result.m_data + offsetY * result.m_atlasWidth + offsetX;

								memcpy(charDataLineDst, charDataLineScr, charMetrics.gmBlackBoxX);
							}

							delete[] charData;
						}

						const uint32_t glyphIndex = charIndex - GlyphDataCollection::BeginCharIndex;
						result.m_x[glyphIndex] = offsetX;

						offsetX += charMetrics.gmBlackBoxX;
					}
				}
			}

			DeleteDC(deviceContext);
		}

		DeleteObject(font);
	}

	return result;
}
