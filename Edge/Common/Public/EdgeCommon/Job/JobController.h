#pragma once

#include "Job.h"
#include "JobGraph.h"
#include "JobQueue.h"

#include <vector>


namespace Edge
{
	class JobController final
	{
		using ThreadCollection = std::vector<std::thread>;

	private:
		ThreadCollection m_threads;
		JobQueue m_jobQueue;

		std::atomic_bool m_isStoped = false;

		static void threadFunction(JobController* jobController);

		bool executeOnCurrentThread();

	public:
		JobController() = default;
		~JobController() { release(); }

		bool init(uint32_t threadCount, const char* name = "TSJob");
		void release();

		void addJob(const JobReference& job);
		void addJobGraph(const JobGraphReference& jobGraph);

		void wait(const JobReference& job);
		void waitAndExecute(const JobReference& job);

		void wait(const JobGraphReference& jobGraph);
		void waitAndExecute(const JobGraphReference& jobGraph);

		static uint32_t getHardwareThreadCount();
	};
}
