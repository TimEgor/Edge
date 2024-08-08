#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"

#include "PhysicsSceneReference.h"
#include "PhysicsWorld.h"

namespace Edge
{
	class PhysicsScene final : public NonCopyable, public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsScene>
	{
	private:
		PhysicsWorldWeakReference m_world;

	public:
		PhysicsScene(const PhysicsWorldReference& world);

		bool init();
		void release();

		void update(float deltaTime);

		PhysicsWorldWeakReference getWorld();
	};
}
