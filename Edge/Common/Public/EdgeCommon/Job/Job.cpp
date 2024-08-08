#include "Job.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Assert/AssertCore.h"
#include "EdgeCommon/Profile/Profile.h"

void Edge::Job::JobEvent::wait()
{
	std::unique_lock locker(m_job->m_mutex);
	m_notifier.wait(locker, [this]() { return m_job->m_state == JobState::Finished; });
}

void Edge::Job::JobEvent::set()
{
	m_notifier.notify_all();
}

Edge::Job::~Job()
{
	EDGE_SAFE_DESTROY(m_completionEvent);
}

void Edge::Job::wait()
{
	if (isFinished())
	{
		return;
	}

	{
		LockGuard locker(m_mutex);
		if (!m_completionEvent)
		{
			m_completionEvent = new JobEvent(this);
		}
	}

	m_completionEvent->wait();
}

void Edge::Job::execute()
{
#ifdef EDGE_JOB_DEBUG
	EDGE_PROFILE_BLOCK_EVENT_CONTEXT("Job", getDbgName());
#endif

	m_state = JobState::Executing;

	operate();

	m_state = JobState::Finished;

	LockGuard locker(m_mutex);
	if (m_completionEvent)
	{
		m_completionEvent->set();
	}
}

bool Edge::Job::isFinished() const
{
	return m_state == JobState::Finished;
}

void Edge::Job::onJobQueueRegistration()
{
	m_state = JobState::Pending;
}

void Edge::LambdaJob::operate()
{
	if (!m_function)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Job lambda is null");
		return;
	}

	m_function();
}

Edge::LambdaJob::LambdaJob(const JobFunction& function)
	: m_function(function)
{
	EDGE_ASSERT_MESSAGE(function, "Job lambda is null");
}

Edge::LambdaJob::LambdaJob(const JobFunction& function, const char* dbgName)
	: Job(dbgName), m_function(function)
{
	EDGE_ASSERT_MESSAGE(function, "Job lambda is null");
}

Edge::JobReference Edge::createLambdaJob(const LambdaJob::JobFunction& function)
{
	return new LambdaJob(function);
}

Edge::JobReference Edge::createLambdaJob(const LambdaJob::JobFunction& function, const char* dbgName)
{
	return new LambdaJob(function, dbgName);
}
