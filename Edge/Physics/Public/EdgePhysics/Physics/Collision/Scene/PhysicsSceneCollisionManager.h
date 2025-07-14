#pragma once

#include "EdgeCommon/Job/JobGraph.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"
#include "EdgePhysics/Physics/Collision/PhysicsGlobalCollisionQuery.h"
#include "EdgePhysics/Physics/Collision/BroadPhases/PhysicsBroadPhase.h"
#include "EdgePhysics/Physics/Collision/Manifold/PhysicsContactManifold.h"
#include "EdgePhysics/Physics/Entity/Scene/PhysicsEntitySceneContextTypes.h"

#include "PhysicsCollisionContactManager.h"
#include "PhysicsCollisionSceneContextTypes.h"
#include "PhysicsSceneCollisionManagerReference.h"

#include <vector>


namespace Edge
{
	class PhysicsSceneCollisionCollection;
	class PhysicsBroadPhase;

	class PhysicsSceneCollisionManager final : public PhysicsGlobalCollisionQuery, public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsSceneCollisionManager>
	{
	private:
		struct CollisionFindingContext final : public DefaultDestroyingMTCountableObjectBase
		{
			using CollisionPairCollections = std::vector<PhysicsBroadPhase::PhysicsSceneCollisionPairCollection>;

			CollisionPairCollections m_collisionCollections;
		};

		EDGE_REFERENCE(CollisionFindingContext);

		struct CollisionDispatchingContext final : public DefaultDestroyingMTCountableObjectBase
		{
			using CollisionManifoldCollections = std::vector<PhysicsCollisionContactManager::CollisionManifoldCollection>;
			using CollisionContactIDCollection = std::vector<PhysicsCollisionContactID>;
			using CollisionManifoldContactIDCollections = std::vector<CollisionContactIDCollection>;
			using CollisionContactPointCountCollection = std::vector<uint32_t>;

			CollisionManifoldCollections m_manifoldCollections;
			CollisionManifoldContactIDCollections m_manifoldContactIDCollections;
			CollisionContactPointCountCollection m_contactPointCountCollection;
		};

		EDGE_REFERENCE(CollisionDispatchingContext);

		PhysicsSceneCollisionCollection* m_collisionCollection = nullptr;
		PhysicsCollisionContactManager* m_contactManager = nullptr;

		PhysicsBroadPhase* m_broadPhase = nullptr;

		PhysicsSceneWeakReference m_scene;

		JobGraphReference getCollisionFindingJobGraph(uint32_t jobCount, const CollisionFindingContextReference& findingContext, const std::vector<PhysicsSceneEntityID>& activeEntityIDs);
		JobGraphReference getCollisionDispatchingJobGraph(uint32_t jobCount, const CollisionDispatchingContextReference& dispatchingContext, const CollisionFindingContextReference& findingContext);

		bool checkCollision(const PhysicsEntityCollisionReference& collision) const;

	public:
		PhysicsSceneCollisionManager() = default;

		bool init(const PhysicsSceneReference& scene);
		void release();

		JobGraphReference getPreparationJobGraph(const std::vector<PhysicsSceneEntityID>& activeEntityIDs);

		JobGraphReference getPreSolvingJobGraph(ComputeValueType deltaTime);
		JobGraphReference getVelocitySolvingJobGraph(ComputeValueType deltaTime);
		JobGraphReference getPositionSolvingJobGraph(ComputeValueType deltaTime);

		JobGraphReference getPostConstraintSolvingJobGraph();

		void addCollision(const PhysicsEntityCollisionReference& collision);
		void removeCollision(const PhysicsEntityCollisionReference& collision);
		PhysicsEntityCollisionReference getCollision(PhysicsSceneCollisionID id) const;

		void updateCollisionTransform(const PhysicsEntityCollisionReference& collision);

		virtual void rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResultCollector& resultCollector) const override;

		PhysicsSceneWeakReference getScene() const;
	};
}
