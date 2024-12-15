#pragma once

#include "EdgeCommon/Math/Const.h"
#include "EdgeCommon/Math/Vector.h"

#include "Scene/PhysicsCollisionSceneContextTypes.h"

namespace Edge
{
	using PhysicsCollisionContactPointID = uint32_t;

	union PhysicsCollisionContactID final
	{
		using ContactIDValue = uint64_t;
		static constexpr ContactIDValue InvalidContactIDValue = InvalidPhysicsSceneCollisionID << sizeof(PhysicsSceneCollisionID) | InvalidPhysicsSceneCollisionID;

		struct
		{
			PhysicsSceneCollisionID m_collisionID1;
			PhysicsSceneCollisionID m_collisionID2;
		};

		ContactIDValue m_id = InvalidContactIDValue;

		PhysicsCollisionContactID() = default;
		PhysicsCollisionContactID(PhysicsSceneCollisionID id1, PhysicsSceneCollisionID id2);

		bool operator==(const PhysicsCollisionContactID& id) const;

		bool isValid() const;

		struct Hasher
		{
			size_t operator()(const PhysicsCollisionContactID& k) const;
		};
	};

	class PhysicsCollisionContact final
	{
	private:
		PhysicsCollisionContactPointID m_collisionPointCount = 0;
		PhysicsCollisionContactPointID m_collisionPointBaseIndex = 0;

		bool m_dirtyState = false;

	public:
		PhysicsCollisionContact() = default;

		PhysicsCollisionContactPointID getCollisionPointCount() const { return m_collisionPointCount; }
		void setCollisionPointCount(PhysicsCollisionContactPointID count) { m_collisionPointCount = count; }
		PhysicsCollisionContactPointID getCollisionPointBaseIndex() const { return m_collisionPointBaseIndex; }
		void setCollisionPointBaseIndex(PhysicsCollisionContactPointID index) { m_collisionPointBaseIndex = index; }

		bool getDirtyState() const { return m_dirtyState; }
		void markDirtyState() { m_dirtyState = true; }
		void resetDirtyState() { m_dirtyState = false; }
	};

	struct PhysicsCollisionContactPoint final
	{
		FloatVector3 m_position1 = FloatVector3Zero;
		FloatVector3 m_position2 = FloatVector3Zero;
		FloatVector3 m_normal = FloatVector3Zero;
		float m_depth = -EDGE_FLT_MAX;
	};

	struct PhysicsInstancedCollisionContactPoint final
	{
		PhysicsCollisionContactPoint m_pointData;
		PhysicsCollisionContactID m_contactID;
	};
}
