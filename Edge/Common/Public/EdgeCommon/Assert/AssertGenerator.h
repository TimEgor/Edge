#pragma once

#include <cstdint>

namespace Edge
{
	class AssertGenerator
	{
	public:
		AssertGenerator() = default;
		virtual ~AssertGenerator() = default;

		virtual void generateError(const char* message, const char* file, uint32_t line) = 0;
	};
}
