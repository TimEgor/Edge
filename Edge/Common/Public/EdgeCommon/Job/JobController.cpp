#include "JobController.h"

#include "EdgeCommon/ThreadUtils.h"
#include "EdgeCommon/Assert/AssertCore.h"
#include "EdgeCommon/String/Format.h"

void Edge::JobController::threadFunction(JobController* jobController)
{
	while (true)
	{
		JobReference job = jobController->m_jobQueue.getJob();

		if (jobController->m_isStoped)
		{
			return;
		}

		if (job)
		{
			job->execute();
		}
	}
}

bool Edge::JobController::executeOnCurrentThread()
{
	JobReference job = m_jobQueue.tryGetJob();

	if (m_isStoped)
	{
		return false;
	}

	if (job)
	{
		job->execute();
	}

	return true;
}

bool Edge::JobController::init(uint32_t threadCount, const char* name)
{
	m_isStoped = false;

	m_jobQueue.init();

	for (uint32_t threadIndex = 0; threadIndex < threadCount; ++threadIndex)
	{
		std::thread thread([this]() { threadFunction(this); });

		if (name)
		{
			ThreadUtils::SetThreadName(thread.native_handle(), StringFormat("%s_%d", name, threadIndex).c_str());
		}

		m_threads.push_back(std::move(thread));
	}

	return true;
}

void Edge::JobController::release()
{
	m_isStoped = true;

	m_jobQueue.release();

	for (auto& thread : m_threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

void Edge::JobController::addJob(const JobReference& job)
{
	if (!job)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Job is null.");
		return;
	}

	job->setExecutionContext(this);

	m_jobQueue.addJob(job);
}

void Edge::JobController::addJobGraph(const JobGraphReference& jobGraph)
{
	if (!jobGraph)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Job graph is null.");
		return;
	}

	jobGraph->setExecutionContext(this);

	const JobGraph::JobCollection baseGraphJobs = jobGraph->getBaseJobs();

	for (const JobReference& job : baseGraphJobs)
	{
		addJob(job);
	}
}

void Edge::JobController::wait(const JobReference& job)
{
	if (job)
	{
		job->wait();
	}
}

void Edge::JobController::waitAndExecute(const JobReference& job)
{
	if (!job)
	{
		return;
	}

	while(!job->isFinished())
	{
		if (!executeOnCurrentThread())
		{
			break;;
		}
	}
}

void Edge::JobController::wait(const JobGraphReference& jobGraph)
{
	if (jobGraph)
	{
		jobGraph->wait();
	}
}

void Edge::JobController::waitAndExecute(const JobGraphReference& jobGraph)
{
	if (!jobGraph)
	{
		return;
	}

	while (!jobGraph->isFinished())
	{
		if (!executeOnCurrentThread())
		{
			break;
		}
	}
}

uint32_t Edge::JobController::getJobExecutorCount() const
{
	return m_threads.size();
}

uint32_t Edge::JobController::getHardwareThreadCount()
{
	return std::thread::hardware_concurrency();
}
