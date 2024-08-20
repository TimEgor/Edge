#pragma once

#include "PhysicsEntityCollision.h"
#include "PhysicsGlobalCollisionQuery.h"
#include "PhysicsSceneCollisionManagerReference.h"

namespace Edge
{
	class PhysicsSceneCollisionCollection;
	class PhysicsBroadPhase;

	class PhysicsSceneCollisionManager final : public PhysicsGlobalCollisionQuery, public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsSceneCollisionManager>
	{
	private:
		PhysicsSceneCollisionCollection* m_collisionCollection = nullptr;
		PhysicsBroadPhase* m_broadPhase = nullptr;

		PhysicsSceneWeakReference m_scene;

		bool checkCollisionOwning(const PhysicsEntityCollisionReference& collision) const;

	public:
		PhysicsSceneCollisionManager() = default;

		bool init(const PhysicsSceneReference& scene);
		void release();

		void addCollision(const PhysicsEntityCollisionReference& collision);
		void removeCollision(const PhysicsEntityCollisionReference& collision);
		PhysicsEntityCollisionReference getCollision(PhysicsSceneCollisionID id);

		virtual void rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResultCollector& resultCollector) const override;
	};
}
