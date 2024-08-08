#pragma once

#include "NonCopyable.h"

namespace Edge
{
	template <typename T>
	class Singleton : public NonCopyable
	{
	protected:
		Singleton() = default;

	public:
		virtual ~Singleton() = default;

		static T& getInstance();
	};

	template<typename T>
	inline T& Singleton<T>::getInstance()
	{
		static T uniqueInstance;
		return uniqueInstance;
	}
}
