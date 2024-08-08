#pragma once

namespace Edge
{
	class NonCopyable
	{
	public:
		NonCopyable() = default;
		virtual ~NonCopyable() = default;

		NonCopyable(const NonCopyable&) = delete;

		void operator=(const NonCopyable&) = delete;
	};
}
