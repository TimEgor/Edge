#pragma once

#include "EdgeCommon/Multithreading/Mutex.h"

#include "Job.h"

#include <deque>

namespace Edge
{
	class JobQueue final
	{
		std::deque<JobReference> m_queue;
		std::condition_variable m_wakeCondition;
		std::mutex m_mutex;

		std::atomic_bool m_isReleased = true;

	public:
		JobQueue() = default;
		~JobQueue() { release(); }

		void init();
		void release();

		void addJob(const JobReference& job);
		JobReference getJob();
		JobReference tryGetJob();
	};
}
