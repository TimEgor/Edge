#pragma once

#include "EdgeCommon/Job/JobGraph.h"

#include "EdgePhysics/Physics/Collision/PhysicsGlobalCollisionQuery.h"
#include "EdgePhysics/Physics/Collision/BroadPhases/PhysicsBroadPhase.h"
#include "EdgePhysics/Physics/Entity/Scene/PhysicsEntitySceneContextTypes.h"

#include "PhysicsCollisionSceneContextTypes.h"
#include "PhysicsSceneCollisionManagerReference.h"

#include <vector>

namespace Edge
{
	class PhysicsCollisionConstraintManager;
	class PhysicsSceneCollisionCollection;
	class PhysicsCollisionContactManager;
	class PhysicsBroadPhase;

	class PhysicsSceneCollisionManager final : public PhysicsGlobalCollisionQuery, public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsSceneCollisionManager>
	{
	private:
		struct CollisionFindingContext final : public DefaultDestroyingMTCountableObjectBase
		{
			std::vector<PhysicsBroadPhase::PhysicsSceneCollisionPairCollection> m_collisionCollector;
		};

		EDGE_MT_REFERENCE(CollisionFindingContext)

		PhysicsSceneCollisionCollection* m_collisionCollection = nullptr;
		PhysicsCollisionContactManager* m_contactManager = nullptr;
		PhysicsCollisionConstraintManager* m_contactConstraintManager = nullptr;

		PhysicsBroadPhase* m_broadPhase = nullptr;

		PhysicsSceneWeakReference m_scene;

		JobGraphReference getCollisionFindingJobGraph(uint32_t jobCount, const CollisionFindingContextReference& context, const std::vector<PhysicsSceneEntityID>& activeEntityIDs);
		void prepareCollisionContacts(const CollisionFindingContextReference& context) const;

		bool checkCollision(const PhysicsEntityCollisionReference& collision) const;

	public:
		PhysicsSceneCollisionManager() = default;

		bool init(const PhysicsSceneReference& scene);
		void release();

		JobGraphReference getPreparationJobGraph(const std::vector<PhysicsSceneEntityID>& activeEntityIDs);

		void addCollision(const PhysicsEntityCollisionReference& collision);
		void removeCollision(const PhysicsEntityCollisionReference& collision);
		PhysicsEntityCollisionReference getCollision(PhysicsSceneCollisionID id) const;

		void updateCollisionTransform(const PhysicsEntityCollisionReference& collision);

		virtual void rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResultCollector& resultCollector) const override;

		const PhysicsCollisionContactManager& getContactManager() const;
		PhysicsCollisionConstraintManager& getCollisionConstraintManager() const;

		PhysicsSceneWeakReference getScene() const;
	};
}
