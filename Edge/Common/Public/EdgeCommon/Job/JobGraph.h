#pragma once

#include "EdgeCommon/Reference/MTReference.h"
#include "EdgeCommon/Multithreading/Mutex.h"

#include "Job.h"

#include <vector>
#include <functional>


namespace Edge
{
	class JobController;

	class JobGraph;
	EDGE_MT_REFERENCE(JobGraph);

	class JobGraph final : public DefaultDestroyingMTCountableObjectBase
	{
	public:
		class GraphJobData final : public DefaultDestroyingMTCountableObjectBase
		{
			struct JobGraphEvent final
			{
				std::condition_variable m_notifier;
				GraphJobData* m_graph = nullptr;

				JobGraphEvent(GraphJobData* graph)
					: m_graph(graph) {}

				void wait();
				void set();
			};

			friend JobGraphEvent;

			friend class JobGraphBuilder;

		public:
			using CompletionCallback = std::function<void()>;
			using CompletionCallbackCollection = std::vector<CompletionCallback>;

		private:
			CompletionCallbackCollection m_completionCallback;
			std::atomic<uint32_t> m_jobCounter;
			JobController* m_jobController = nullptr;
			JobGraphEvent* m_completionEvent = nullptr;

			std::mutex m_mutex;

		public:
			GraphJobData() = default;
			~GraphJobData();

			JobController* getJobController() const { return m_jobController; }
			void completeJob();

			void addCompletionCallback(const CompletionCallback& callback);

			void setExecutionContext(JobController* controller);

			void wait();
			bool isFinished() const;
		};

		EDGE_MT_REFERENCE(GraphJobData);

		class DependencyJobBase;
		EDGE_MT_NAMED_REFERENCE(DependencyJobBase, DependencyJob);

		class DependencyJobBase : public Job
		{
			friend class JobGraphBuilder;

		public:
			using DependencyCollection = std::vector<DependencyJobReference>;

		protected:
			DependencyCollection m_dependencyJobs;

			GraphJobDataReference m_graphData;
			std::atomic<uint32_t> m_parentCounter;

			void removeChildDependencies();

			virtual void operate() override;
		public:
			DependencyJobBase(const GraphJobDataReference& graphData, const char* dbgName)
				: Job(dbgName), m_graphData(graphData) {}

			bool removeParentDependency();
		};

		class DependencyJob final : public DependencyJobBase
		{
		private:
			JobReference m_job;

			virtual void operate() override;
		public:
			DependencyJob(const JobReference& job, const GraphJobDataReference& graphData)
				: DependencyJobBase(graphData, "GraphJob"), m_job(job) {}
		};

		class PostGraphDependencyJob final : public DependencyJobBase
		{
		public:
			PostGraphDependencyJob(const GraphJobDataReference& graphData)
				: DependencyJobBase(graphData, "PostGraphJob") {}
		};

		EDGE_MT_REFERENCE(PostGraphDependencyJob);

		class PreGraphDependencyJob final : public DependencyJobBase
		{
		private:
			JobGraphReference m_graph;

			virtual void operate() override;
		public:
			PreGraphDependencyJob(const GraphJobDataReference& graphData,
				const PostGraphDependencyJobReference& postGraphJob, const JobGraphReference& graph);
		};

		using JobCollection = std::vector<JobReference>;

	private:
		JobCollection m_baseJobs;
		GraphJobDataReference m_graphData;

		virtual void selfDestroy() override;

	public:
		JobGraph(JobCollection&& baseJobs, GraphJobDataReference data)
			: m_baseJobs(std::move(baseJobs)), m_graphData(data) {}

		JobCollection&& getBaseJobs();
		GraphJobDataReference getGraphData() const;

		void setExecutionContext(JobController* jobController);

		void wait();
		bool isFinished() const;
	};

	class JobGraphBuilder final
	{
	public:
		struct JobGraphJobID final
		{
			union
			{
				struct
				{
					uint32_t m_isGraphJob : 1;
					uint32_t m_index : 31;
				};

				uint32_t m_value;
			};

			JobGraphJobID(uint32_t id)
				: m_value(id) {}

			JobGraphJobID(bool isGraph, uint32_t index)
				: m_isGraphJob(isGraph), m_index(index) {}

			bool operator==(JobGraphJobID id) const
			{
				return id.m_value == m_value;
			}

			operator uint32_t() const
			{
				return m_value;
			}
		};

		static constexpr uint32_t InvalidJobGraphJobIndex = 1u << 30;

	private:
		struct GraphBuildingContext final
		{
			struct GraphNode final
			{
				JobGraphJobID m_preJobID = JobGraphJobID(false, InvalidJobGraphJobIndex);
				JobGraphJobID m_postJobID = JobGraphJobID(false, InvalidJobGraphJobIndex);
			};

			struct GraphJobInfo final
			{
				JobGraph::DependencyJobReference* m_job = nullptr;
				JobGraphJobID m_jobID = JobGraphJobID(false, InvalidJobGraphJobIndex);
			};

			std::vector<JobGraph::DependencyJobReference> m_jobs;
			std::vector<GraphNode> m_graphNodes;

			std::vector<JobGraphJobID> m_baseJobIDs;

			std::unordered_map<uint32_t, uint32_t> m_dependencyCounterCollection;

			JobGraph::GraphJobDataReference m_graphData;

			uint32_t m_lastJobIndex = 0;
			uint32_t m_lastGraphIndex = 0;

			GraphBuildingContext();

			JobGraph::DependencyJobReference* getJob(JobGraphJobID jobID);
			GraphJobInfo getGraphJob(JobGraphJobID jobID, bool isParent);

			JobGraphJobID addDependencyJob(const JobGraph::DependencyJobReference& job, bool addToCollection = true);
			JobGraphJobID addGraphNode(JobGraphJobID preJobID, JobGraphJobID postJobID);
		};

		GraphBuildingContext* m_buildingContext = nullptr;

		void initContext();
		void releaseContext();

	public:
		JobGraphBuilder() = default;
		~JobGraphBuilder();

		JobGraphJobID addJob(const JobReference& job);
		JobGraphJobID addJobBefore(const JobReference& job, JobGraphJobID childJobID);
		JobGraphJobID addJobAfter(const JobReference& job, JobGraphJobID parentJobID);

		JobGraphJobID addJobGraph(const JobGraphReference& graph);
		JobGraphJobID addJobGraphBefore(const JobGraphReference& graph, JobGraphJobID childJobID);
		JobGraphJobID addJobGraphAfter(const JobGraphReference& graph, JobGraphJobID parentJobID);

		void makeDependency(JobGraphJobID parentJobID, JobGraphJobID childJobID);

		JobGraphReference getGraph();
	};
}
