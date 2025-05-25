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

		NormalizedColorRGB& operator=(const FloatVector3& values) { m_values = values; return *this; }
		NormalizedColorRGB& operator=(const NormalizedColorRGB& color) { m_values = color.m_values; return *this; }
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

		NormalizedColorRGBA& operator=(const FloatVector4& values) { m_values = values; return *this; }
		NormalizedColorRGBA& operator=(const NormalizedColorRGB& color) { m_values = color.m_values; return *this; }
		NormalizedColorRGBA& operator=(const NormalizedColorRGBA& color) { m_values = color.m_values; return *this; }
	};

	inline constexpr NormalizedColorRGB NormalizedColorWhite = NormalizedColorRGB(1.0f, 1.0f, 1.0f);
	inline constexpr NormalizedColorRGB NormalizedColorGray = NormalizedColorRGB(0.5f, 0.5f, 0.5f);
	inline constexpr NormalizedColorRGB NormalizedColorBlack = NormalizedColorRGB(0.0f, 0.0f, 0.0f);

	inline constexpr NormalizedColorRGB NormalizedColorRed = NormalizedColorRGB(1.0f, 0.0f, 0.0f);
	inline constexpr NormalizedColorRGB NormalizedColorGreen = NormalizedColorRGB(0.0f, 1.0f, 0.0f);
	inline constexpr NormalizedColorRGB NormalizedColorBlue = NormalizedColorRGB(0.0f, 0.0f, 1.0f);

	inline constexpr NormalizedColorRGB NormalizedColorSalmon = NormalizedColorRGB(0.9f, 0.6f, 0.5f);
	inline constexpr NormalizedColorRGB NormalizedColorBrown = NormalizedColorRGB(0.65f, 0.15f, 0.15f);
	inline constexpr NormalizedColorRGB NormalizedColorOrange = NormalizedColorRGB(1.0f, 0.5f, 0.0f);
	inline constexpr NormalizedColorRGB NormalizedColorYellow = NormalizedColorRGB(1.0f, 1.0f, 0.0f);
	inline constexpr NormalizedColorRGB NormalizedColorForestGreen = NormalizedColorRGB(0.15f, 0.55f, 0.15f);
	inline constexpr NormalizedColorRGB NormalizedColorCyan = NormalizedColorRGB(0.0f, 1.0f, 1.0f);
	inline constexpr NormalizedColorRGB NormalizedColorSteelBlue = NormalizedColorRGB(0.3f, 0.6f, 0.8f);
	inline constexpr NormalizedColorRGB NormalizedColorViolet = NormalizedColorRGB(0.6f, 0.0f, 0.85f);
	inline constexpr NormalizedColorRGB NormalizedColorMagneta = NormalizedColorRGB(1.0f, 0.0f, 1.0f);
}
