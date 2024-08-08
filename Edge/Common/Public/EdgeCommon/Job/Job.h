#pragma once

#include "EdgeCommon/Multithreading/LockGuard.h"
#include "EdgeCommon/Reference/MTReference.h"

#include <condition_variable>
#include <functional>

#ifndef EDGE_CONFIG_RETAIL
#define EDGE_JOB_DEBUG
#endif

namespace Edge
{
	enum class JobState
	{
		Undefined,
		Pending,
		Executing,
		Finished
	};

	class Job : public DefaultDestroyingMTCountableObjectBase
	{
		struct JobEvent final
		{
			std::condition_variable m_notifier;
			Job* m_job = nullptr;

			JobEvent(Job* job)
				: m_job(job) {}

			void wait();
			void set();
		};

		friend JobEvent;

	private:
		mutable std::mutex m_mutex;
		JobEvent* m_completionEvent = nullptr;

		std::atomic<JobState> m_state;

#ifdef EDGE_JOB_DEBUG
		const char* m_dbgName = nullptr;
#endif

	protected:
		virtual void operate() = 0;

	public:
		Job() = default;
		Job(const char* dbgName)
#ifdef EDGE_JOB_DEBUG
			: m_dbgName(dbgName)
#endif
		{}

		virtual ~Job();

		void wait();
		void execute();

		bool isFinished() const;

		void onJobQueueRegistration();

		JobState getState() const { return m_state; }

#ifdef EDGE_JOB_DEBUG
		const char* getDbgName() const { return m_dbgName; }
#endif
	};

	EDGE_MT_REFERENCE(Job);

	class LambdaJob final : public Job
	{
	public:
		using JobFunction = std::function<void()>;

	private:
		JobFunction m_function;

		virtual void operate() override;

	public:
		LambdaJob(const JobFunction& function);
		LambdaJob(const JobFunction& function, const char* dbgName);
	};

	JobReference createLambdaJob(const LambdaJob::JobFunction& function);
	JobReference createLambdaJob(const LambdaJob::JobFunction& function, const char* dbgName);
}
