#pragma once

#include <cstdint>

#include "EdgeCommon/Patterns/NonCopyable.h"

namespace Edge
{
	class JobController;

	class Physics final : public NonCopyable
	{
	private:
		JobController* m_jobController = nullptr;

	public:
		struct InitParams final
		{
			uint32_t m_jobThreadCount = 4;
		};

		Physics() = default;

		bool init(const InitParams& params);
		void release();

		JobController& getJobController() const;
	};
}
