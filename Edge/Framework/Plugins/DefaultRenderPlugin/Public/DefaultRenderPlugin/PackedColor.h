#pragma once

#include "EdgeCommon/Math/Vector.h"

namespace EdgeDefRender
{
	union PackedColor final
	{
		struct
		{
			uint8_t m_r;
			uint8_t m_g;
			uint8_t m_b;
			uint8_t m_a;
		};

		uint32_t m_data = 0;

		PackedColor() = default;
		PackedColor(const Edge::NormalizedColorRGBA& color)
		{
			m_r = static_cast<uint8_t>(color.m_r * 255.0f);
			m_g = static_cast<uint8_t>(color.m_g * 255.0f);
			m_b = static_cast<uint8_t>(color.m_b * 255.0f);
			m_a = static_cast<uint8_t>(color.m_a * 255.0f);
		}
	};
}
