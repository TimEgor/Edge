#pragma once

#include "EdgeCommon/Job/JobGraph.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"
#include "EdgePhysics/Physics/Collision/PhysicsEntityCollision.h"
#include "EdgePhysics/Physics/Collision/Dispatchers/PhysicsCollisionDispatcherCollection.h"

namespace Edge
{
	class PhysicsCollisionConstraintManager;

	class PhysicsCollisionContactManager final
	{
	public:
		using CollisionManifoldCollection = PhysicsCollisionDispatcher::ContactManifoldDispatchingResultCollection;

	private:
		class DispatcherContext final
		{
		private:
			using DispatcherContainer = std::vector<PhysicsCollisionDispatcher*>;

			DispatcherContainer m_dispatchers;
			PhysicsCollisionDispatcherCollection* m_dispatcherCollection = nullptr;

		public:
			DispatcherContext() = default;

			bool init();
			void release();

			PhysicsCollisionDispatcher* getDispatcher(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2) const;
		};

		class ContactCache final
		{
		public:
			using ContactPointCollection = std::vector<PhysicsCollisionContactPoint>;
			using ContactCollection = std::unordered_map<PhysicsCollisionContactID, ContactPointCollection, PhysicsCollisionContactID::Hasher>;

		private:
			static constexpr uint32_t CacheContainerCount = 2;

			ContactCollection m_cacheCollection[CacheContainerCount];
			uint32_t m_writingContainerIndex = 0;

			uint32_t getNextContainerIndex() const;

		public:
			ContactCache() = default;

			void prepareCache(uint32_t manifoldCount);

			ContactCollection& getWritingCollection();
			const ContactCollection& getReadingCollection() const;
		};

		DispatcherContext* m_dispatcherContext = nullptr;
		ContactCache* m_contactCache = nullptr;

		PhysicsCollisionConstraintManager* m_contactConstraintManager = nullptr;

		PhysicsSceneCollisionManagerWeakReference m_collisionManager;

	public:
		PhysicsCollisionContactManager() = default;

		bool init(const PhysicsSceneCollisionManagerReference& collisionManager);
		void release();

		JobGraphReference getPreSolvingJobGraph(ComputeValueType deltaTime);
		JobGraphReference getVelocitySolvingJobGraph(ComputeValueType deltaTime);
		JobGraphReference getPositionSolvingJobGraph(ComputeValueType deltaTime);

		void prepareContacts(uint32_t manifoldCount, uint32_t pointCount);
		void addManifold(
			PhysicsCollisionContactID contactID,
			const PhysicsContactManifold& manifold,
			const PhysicsEntityReference& entity1,
			const PhysicsEntityReference& entity2
		);

		void cacheConstraintDatas();

		uint32_t dispatchCollision(
			const PhysicsEntityCollisionReference& collision1,
			const PhysicsEntityCollisionReference& collision2,
			CollisionManifoldCollection& result
		) const; // return collision contact point count
	};
}
