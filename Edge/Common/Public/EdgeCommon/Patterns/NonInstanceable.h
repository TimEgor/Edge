#pragma once

namespace Edge
{
	class NonInstanceable
	{
	public:
		NonInstanceable() = delete;
		virtual ~NonInstanceable() = default;
	};
}
