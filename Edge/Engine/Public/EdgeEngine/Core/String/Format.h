#pragma once

#include <memory>
#include <string>

namespace Edge
{
	template <typename ...Args>
	std::string StringFormat(const char* format, Args... args)
	{
		int newStrSize = std::snprintf(nullptr, 0, format, args...) + 1;
		if (newStrSize > 0)
		{
			size_t size = static_cast<size_t>(newStrSize);
			std::unique_ptr<char[]> tmpBuffer(new char[size]);

			std::snprintf(tmpBuffer.get(), size, format, args...);
			return std::string(tmpBuffer.get(), tmpBuffer.get() + size - 1);
		}

		return std::string();
	}
}