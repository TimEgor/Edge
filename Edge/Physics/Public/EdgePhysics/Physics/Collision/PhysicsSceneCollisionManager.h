#pragma once

#include "EdgeCommon/Job/JobGraph.h"

#include "PhysicsEntityCollision.h"
#include "PhysicsGlobalCollisionQuery.h"
#include "PhysicsSceneCollisionManagerReference.h"
#include "BroadPhases/PhysicsBroadPhase.h"

#include <vector>

namespace Edge
{
	class PhysicsSceneCollisionCollection;
	class PhysicsCollisionContactManager;
	class PhysicsBroadPhase;

	class PhysicsSceneCollisionManager final : public PhysicsGlobalCollisionQuery, public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsSceneCollisionManager>
	{
	private:
		struct CollisionFindingContext final
		{
			std::vector<PhysicsBroadPhase::PhysicsSceneCollisionPairCollection> m_collisionCollector;
		};

		PhysicsSceneCollisionCollection* m_collisionCollection = nullptr;
		PhysicsCollisionContactManager* m_contactManager = nullptr;

		PhysicsBroadPhase* m_broadPhase = nullptr;

		PhysicsSceneWeakReference m_scene;

		JobGraphReference getCollisionFindingJobGraph(uint32_t jobCount, CollisionFindingContext* context, const std::vector<PhysicsSceneEntityID>& activeEntityIDs);
		void prepareCollisionContacts(CollisionFindingContext* context) const;

		bool checkCollision(const PhysicsEntityCollisionReference& collision) const;

	public:
		PhysicsSceneCollisionManager() = default;

		bool init(const PhysicsSceneReference& scene);
		void release();

		JobGraphReference getUpdateJobGraph(float deltaTime, const std::vector<PhysicsSceneEntityID>& activeEntityIDs);

		void addCollision(const PhysicsEntityCollisionReference& collision);
		void removeCollision(const PhysicsEntityCollisionReference& collision);
		PhysicsEntityCollisionReference getCollision(PhysicsSceneCollisionID id) const;

		void updateCollisions(const std::vector<PhysicsSceneEntityID>& ids);

		void updateCollisionTransform(const PhysicsEntityCollisionReference& collision);

		virtual void rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResultCollector& resultCollector) const override;

		const PhysicsCollisionContactManager& getContactManager() const;

		PhysicsSceneWeakReference getScene() const;
	};
}
