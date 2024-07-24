#pragma once

#include "TinySimCommon/Math/Vector.h"

namespace TS_DEF_RENDERER
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
		PackedColor(const TS::FloatVector4& color)
		{
			m_r = static_cast<uint8_t>(color.m_x * 255.0f);
			m_g = static_cast<uint8_t>(color.m_y * 255.0f);
			m_b = static_cast<uint8_t>(color.m_z * 255.0f);
			m_a = static_cast<uint8_t>(color.m_w * 255.0f);
		}
	};
}
