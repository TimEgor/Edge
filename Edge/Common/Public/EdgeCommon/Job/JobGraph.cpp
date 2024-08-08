#include "JobGraph.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Assert/AssertCore.h"

#include "JobController.h"

void Edge::JobGraph::GraphJobData::JobGraphEvent::wait()
{
	std::unique_lock locker(m_graph->m_mutex);
	m_notifier.wait(locker, [this]() { return m_graph->m_jobCounter == 0; });
}

void Edge::JobGraph::GraphJobData::JobGraphEvent::set()
{
	m_notifier.notify_all();
}

Edge::JobGraph::GraphJobData::~GraphJobData()
{
	EDGE_SAFE_DESTROY(m_completionEvent);
}

void Edge::JobGraph::GraphJobData::completeJob()
{
	if (m_jobCounter-- == 1)
	{
		LockGuard locker(m_mutex);

		for (const auto& callback : m_completionCallback)
		{
			callback();
		}

		if (m_completionEvent)
		{
			m_completionEvent->set();
		}
	}
}

void Edge::JobGraph::GraphJobData::addCompletionCallback(const CompletionCallback& callback)
{
	if (callback)
	{
		LockGuard locker(m_mutex);
		if (m_jobCounter > 0)
		{
			m_completionCallback.push_back(callback);
		}
	}
	else
	{
		EDGE_ASSERT_FAIL_MESSAGE("Graph job completion callback is null.");
	}
}

void Edge::JobGraph::GraphJobData::setExecutionContext(JobController* controller)
{
	LockGuard locker(m_mutex);
	m_jobController = controller;
}

void Edge::JobGraph::GraphJobData::wait()
{
	if (isFinished())
	{
		return;
	}

	{
		LockGuard locker(m_mutex);
		if (!m_completionEvent)
		{
			m_completionEvent = new JobGraphEvent(this);
		}
	}

	m_completionEvent->wait();
}

bool Edge::JobGraph::GraphJobData::isFinished() const
{
	return m_jobCounter == 0;
}

void Edge::JobGraph::DependencyJobBase::removeChildDependencies()
{
	JobController* jobController = m_graphData->getJobController();

	for (size_t jobIndex = 0; jobIndex < m_dependencyJobs.size();)
	{
		const DependencyJobReference& childJob = m_dependencyJobs[jobIndex];

		if (childJob->removeParentDependency())
		{
			jobController->addJob(childJob.getObject());

			if (m_dependencyJobs.size() > 1)
			{
				m_dependencyJobs[jobIndex] = m_dependencyJobs.back();
			}

			m_dependencyJobs.pop_back();
		}
		else
		{
			++jobIndex;
		}
	}
}

void Edge::JobGraph::DependencyJobBase::operate()
{
	removeChildDependencies();

	m_graphData->completeJob();
}

bool Edge::JobGraph::DependencyJobBase::removeParentDependency()
{
	return m_parentCounter-- == 1;
}

void Edge::JobGraph::DependencyJob::operate()
{
	m_job->execute();

	DependencyJobBase::operate();
}

Edge::JobGraph::PreGraphDependencyJob::PreGraphDependencyJob(const GraphJobDataReference& graphData,
	const PostGraphDependencyJobReference& postGraphJob, const JobGraphReference& graph)
	: DependencyJobBase(graphData, "PreGraphJob"), m_graph(graph)
{
	JobController* jobController = graphData->getJobController();
	m_graph->setExecutionContext(jobController);

	GraphJobDataReference dependencyGraphData = m_graph->getGraphData();
	dependencyGraphData->addCompletionCallback([jobController, postGraphJob]()
		{
			jobController->addJob(postGraphJob.getObject());
		}
	);
}

void Edge::JobGraph::PreGraphDependencyJob::operate()
{
	JobController* jobController = m_graphData->getJobController();

	const JobCollection& dependencyGraphJobs = m_graph->getBaseJobs();
	for (const JobReference& dependencyJob : dependencyGraphJobs)
	{
		jobController->addJob(dependencyJob);
	}

	DependencyJobBase::operate();
}

void Edge::JobGraph::selfDestroy()
{
	delete this;
}

Edge::JobGraph::JobCollection&& Edge::JobGraph::getBaseJobs()
{
	return std::move(m_baseJobs);
}

Edge::JobGraph::GraphJobDataReference Edge::JobGraph::getGraphData() const
{
	return m_graphData;
}

void Edge::JobGraph::setExecutionContext(JobController* jobController)
{
	m_graphData->setExecutionContext(jobController);

	m_baseJobs = JobCollection();
}

void Edge::JobGraph::wait()
{
	m_graphData->wait();
}

bool Edge::JobGraph::isFinished() const
{
	return m_graphData->isFinished();
}

Edge::JobGraphBuilder::GraphBuildingContext::GraphBuildingContext()
{
	m_graphData = new JobGraph::GraphJobData();
}

Edge::JobGraphBuilder::~JobGraphBuilder()
{
	releaseContext();
}

Edge::JobGraph::DependencyJobReference* Edge::JobGraphBuilder::GraphBuildingContext::getJob(JobGraphJobID jobID)
{
	if (jobID.m_isGraphJob)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Job is graph typed.");
		return nullptr;
	}

	JobGraph::DependencyJobReference* job = nullptr;

	if (m_jobs.size() > jobID.m_index)
	{
		job = &m_jobs[jobID.m_index];
	}
	else
	{
		EDGE_ASSERT_FAIL_MESSAGE("Job index is invalid.");
		return nullptr;
	}

	return job;
}

Edge::JobGraph::DependencyJobReference* Edge::JobGraphBuilder::GraphBuildingContext::getGraphJob(JobGraphJobID jobID, bool isParent)
{
	if (!jobID.m_isGraphJob)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Job isn't graph typed.");
		return nullptr;
	}

	JobGraph::DependencyJobReference* job = nullptr;

	if (m_graphNodes.size() > jobID.m_index)
	{
		const GraphNode& graphNode = m_graphNodes[jobID.m_index];

		const JobGraphJobID graphJobID = isParent ? graphNode.m_postJobID : graphNode.m_preJobID;
		job = getJob(graphJobID);
	}
	else
	{
		EDGE_ASSERT_FAIL_MESSAGE("Graph job index is invalid.");
	}

	return job;
}

Edge::JobGraphBuilder::JobGraphJobID Edge::JobGraphBuilder::GraphBuildingContext::addDependencyJob(const JobGraph::DependencyJobReference& job)
{
	const JobGraphJobID jobId(false, m_lastJobIndex);

	m_jobs.emplace_back(job);

	m_dependencyCounterCollection[jobId] = 0;

	++m_lastJobIndex;
	++m_graphData->m_jobCounter;

	return jobId;
}

Edge::JobGraphBuilder::JobGraphJobID Edge::JobGraphBuilder::GraphBuildingContext::addGraphNode(JobGraphJobID preJobID, JobGraphJobID postJobID)
{
	const JobGraphJobID jobId(true, m_lastGraphIndex);

	m_graphNodes.emplace_back(GraphNode{ preJobID, postJobID });

	++m_lastGraphIndex;

	return jobId;
}

void Edge::JobGraphBuilder::initContext()
{
	if (!m_buildingContext)
	{
		m_buildingContext = new GraphBuildingContext();
	}
}

void Edge::JobGraphBuilder::releaseContext()
{
	EDGE_SAFE_DESTROY(m_buildingContext);
}

Edge::JobGraphBuilder::JobGraphJobID Edge::JobGraphBuilder::addJob(const JobReference& job)
{
	if (!job)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Job is invalid.");
		return JobGraphJobID(false, InvalidJobGraphJobIndex);
	}

	initContext();

	const JobGraph::DependencyJobReference graphJob = new JobGraph::DependencyJob(job, m_buildingContext->m_graphData);

	return m_buildingContext->addDependencyJob(graphJob);
}

Edge::JobGraphBuilder::JobGraphJobID Edge::JobGraphBuilder::addJobBefore(const JobReference& job, JobGraphJobID childJobID)
{
	const JobGraphJobID jobID = addJob(job);
	makeDependency(jobID, childJobID);

	return jobID;
}

Edge::JobGraphBuilder::JobGraphJobID Edge::JobGraphBuilder::addJobAfter(const JobReference& job, JobGraphJobID parentJobID)
{
	const JobGraphJobID jobID = addJob(job);
	makeDependency(parentJobID, jobID);

	return jobID;
}

Edge::JobGraphBuilder::JobGraphJobID Edge::JobGraphBuilder::addJobGraph(const JobGraphReference& graph)
{
	initContext();

	const JobGraph::PostGraphDependencyJobReference postGraphJob = new JobGraph::PostGraphDependencyJob(m_buildingContext->m_graphData);
	const JobGraphJobID postGraphJobID = m_buildingContext->addDependencyJob(postGraphJob.getObject());

	const JobGraph::DependencyJobReference preGraphJob = new JobGraph::PreGraphDependencyJob(m_buildingContext->m_graphData, postGraphJob, graph);
	const JobGraphJobID preGraphJobID = m_buildingContext->addDependencyJob(preGraphJob);

	return m_buildingContext->addGraphNode(preGraphJobID, postGraphJobID);
}

Edge::JobGraphBuilder::JobGraphJobID Edge::JobGraphBuilder::addJobGraphBefore(const JobGraphReference& graph, JobGraphJobID childJobID)
{
	const JobGraphJobID jobID = addJobGraph(graph);
	makeDependency(jobID, childJobID);

	return jobID;
}

Edge::JobGraphBuilder::JobGraphJobID Edge::JobGraphBuilder::addJobGraphAfter(const JobGraphReference& graph, JobGraphJobID parentJobID)
{
	const JobGraphJobID jobID = addJobGraph(graph);
	makeDependency(parentJobID, jobID);

	return jobID;
}

void Edge::JobGraphBuilder::makeDependency(JobGraphJobID parentJobID, JobGraphJobID childJobID)
{
	if (!m_buildingContext)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Job graph building context hasn't been inited.");
		return;
	}

	if (parentJobID == childJobID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Child and parent job ids are same.");
		return;
	}

	if (parentJobID.m_index == InvalidJobGraphJobIndex)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Parent job index is invalid.");
		return;
	}

	if (childJobID.m_index == InvalidJobGraphJobIndex)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Child job index is invalid.");
		return;
	}

	JobGraph::DependencyJobReference* parentJob;
	if (parentJobID.m_isGraphJob)
	{
		parentJob = m_buildingContext->getGraphJob(parentJobID, true);
	}
	else
	{
		parentJob = m_buildingContext->getJob(parentJobID);
	}

	if (!parentJob)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Parent job hasn't been found.");
		return;
	}

	JobGraph::DependencyJobReference* childJob;
	if (childJobID.m_isGraphJob)
	{
		childJob = m_buildingContext->getGraphJob(childJobID, false);
	}
	else
	{
		childJob = m_buildingContext->getJob(childJobID);
	}

	if (!childJob)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Child job hasn't been found.");
		return;
	}

	(*parentJob)->m_dependencyJobs.push_back(*childJob);
	++(*childJob)->m_parentCounter;
	++m_buildingContext->m_dependencyCounterCollection[childJobID];
}

Edge::JobGraphReference Edge::JobGraphBuilder::getGraph()
{
	if (!m_buildingContext)
	{
		return nullptr;
	}

	if (m_buildingContext->m_jobs.empty())
	{
		releaseContext();
		return nullptr;
	}

	std::vector<JobReference> m_baseJobs;

	for (const auto& jobDependencyCounter : m_buildingContext->m_dependencyCounterCollection)
	{
		if (jobDependencyCounter.second == 0)
		{
			const JobGraph::DependencyJobReference* job = m_buildingContext->getJob(jobDependencyCounter.first);
			if (!job)
			{
				EDGE_ASSERT_FAIL_MESSAGE("Graph job structure is invalid.");
				continue;
			}

			m_baseJobs.push_back(job->getObject());
		}
	}

	const JobGraph::GraphJobDataReference graphData = m_buildingContext->m_graphData;

	releaseContext();

	if (m_baseJobs.empty())
	{
		return nullptr;
	}

	return new JobGraph(std::move(m_baseJobs), graphData);
}
