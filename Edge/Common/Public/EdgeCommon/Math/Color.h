#pragma once

#include "Vector.h"

namespace Edge
{
	struct NormalizedColorRGB final
	{
		union
		{
			FloatVector3 m_values = FloatVector3Zero;

			struct
			{
				float m_r, m_g, m_b;
			};
		};

		constexpr NormalizedColorRGB() = default;
		constexpr NormalizedColorRGB(const FloatVector3& values) : m_values(values) {}
		constexpr NormalizedColorRGB(float r, float g, float b) : m_values(r, g, b) {}
		constexpr NormalizedColorRGB(const NormalizedColorRGB& color) : m_values(color.m_values) {}
	};

	struct NormalizedColorRGBA final
	{
		union
		{
			FloatVector4 m_values = { FloatVector3Zero, 1.0f };

			struct
			{
				float m_r, m_g, m_b, m_a;
			};
		};

		constexpr NormalizedColorRGBA() = default;
		constexpr NormalizedColorRGBA(const FloatVector4& values) : m_values(values) {}
		constexpr NormalizedColorRGBA(float r, float g, float b, float a) : m_values(r, g, b, a) {}
		constexpr NormalizedColorRGBA(const NormalizedColorRGB& color) : m_values(color.m_values, 1.0f) {}
		constexpr NormalizedColorRGBA(const NormalizedColorRGBA& color) : m_values(color.m_values) {}
	};

	constexpr NormalizedColorRGB NormalizedColorWhite = NormalizedColorRGB(1.0f, 1.0f, 1.0f);
	constexpr NormalizedColorRGB NormalizedColorGray = NormalizedColorRGB(0.5f, 0.5f, 0.5f);
	constexpr NormalizedColorRGB NormalizedColorBlack = NormalizedColorRGB(0.0f, 0.0f, 0.0f);

	constexpr NormalizedColorRGB NormalizedColorRed = NormalizedColorRGB(1.0f, 0.0f, 0.0f);
	constexpr NormalizedColorRGB NormalizedColorGreen = NormalizedColorRGB(0.0f, 1.0f, 0.0f);
	constexpr NormalizedColorRGB NormalizedColorBlue = NormalizedColorRGB(0.0f, 0.0f, 1.0f);

	constexpr NormalizedColorRGB NormalizedColorSalmon = NormalizedColorRGB(0.9f, 0.6f, 0.5f);
	constexpr NormalizedColorRGB NormalizedColorBrown = NormalizedColorRGB(0.65f, 0.15f, 0.15f);
	constexpr NormalizedColorRGB NormalizedColorOrange = NormalizedColorRGB(1.0f, 0.5f, 0.0f);
	constexpr NormalizedColorRGB NormalizedColorYellow = NormalizedColorRGB(1.0f, 1.0f, 0.0f);
	constexpr NormalizedColorRGB NormalizedColorForestGreen = NormalizedColorRGB(0.15f, 0.55f, 0.15f);
	constexpr NormalizedColorRGB NormalizedColorCyan = NormalizedColorRGB(0.0f, 1.0f, 1.0f);
	constexpr NormalizedColorRGB NormalizedColorSteelBlue = NormalizedColorRGB(0.3f, 0.6f, 0.8f);
	constexpr NormalizedColorRGB NormalizedColorViolet = NormalizedColorRGB(0.6f, 0.0f, 0.85f);
	constexpr NormalizedColorRGB NormalizedColorMagneta = NormalizedColorRGB(1.0f, 0.0f, 1.0f);
}
