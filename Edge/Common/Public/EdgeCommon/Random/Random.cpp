#include "Random.h"

#include <random>

float Edge::RandomFloat(float max)
{
	std::random_device rd;

	std::uniform_real_distribution range(0.0f, max);
	return range(std::mt19937(rd()));
}

float Edge::RandomFloat(float min, float max)
{
	std::random_device rd;

	std::uniform_real_distribution range(min, max);
	return range(std::mt19937(rd()));
}

int Edge::RandomInt(int max)
{
	std::random_device rd;

	std::uniform_int_distribution range(0, max);
	return range(std::mt19937(rd()));
}

int Edge::RandomInt(int min, int max)
{
	std::random_device rd;

	std::uniform_int_distribution range(min, max);
	return range(std::mt19937(rd()));
}

uint32_t Edge::RandomUInt32(uint32_t max)
{
	std::random_device rd;

	std::uniform_int_distribution range(0u, max);
	return range(std::mt19937(rd()));
}

uint32_t Edge::RandomUInt32(uint32_t min, uint32_t max)
{
	std::random_device rd;

	std::uniform_int_distribution range(min, max);
	return range(std::mt19937(rd()));
}
