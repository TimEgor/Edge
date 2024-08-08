#pragma once

namespace Edge
{
	template <typename T>
	inline T GetAdjustment(T size, T alignment)
	{
		return alignment - (size & (alignment - 1));
	}

	template <typename T>
	inline T Align(T size, T alignment)
	{
		T adjustment = GetAdjustment(size, alignment);
		if (adjustment != alignment)
		{
			return size + adjustment;
		}

		return size;
	}
}