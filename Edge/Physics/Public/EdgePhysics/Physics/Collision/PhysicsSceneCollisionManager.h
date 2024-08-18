#pragma once

#include "PhysicsEntityCollision.h"
#include "PhysicsSceneCollisionManagerReference.h"

namespace Edge
{
	class PhysicsSceneCollisionCollection;

	class PhysicsSceneCollisionManager final : public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsSceneCollisionManager>
	{
	private:
		PhysicsSceneCollisionCollection* m_collisionCollection = nullptr;

		PhysicsSceneWeakReference m_scene;

		bool checkCollisionOwning(const PhysicsEntityCollisionReference& collision) const;

	public:
		PhysicsSceneCollisionManager() = default;

		bool init(const PhysicsSceneReference& scene);
		void release();

		void addCollision(const PhysicsEntityCollisionReference& collision);
		void removeCollision(const PhysicsEntityCollisionReference& collision);
	};
}
