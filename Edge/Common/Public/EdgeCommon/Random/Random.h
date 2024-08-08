#pragma once

#include <cstdint>

namespace Edge
{
	float RandomFloat(float max);
	float RandomFloat(float min, float max);

	int RandomInt(int max);
	int RandomInt(int min, int max);

	uint32_t RandomUInt32(uint32_t max);
	uint32_t RandomUInt32(uint32_t min, uint32_t max);
}
