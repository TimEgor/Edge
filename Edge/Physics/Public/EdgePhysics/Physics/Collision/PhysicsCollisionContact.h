#pragma once

#include "EdgeCommon/Math/ComputeVector3.h"

#include "Scene/PhysicsCollisionSceneContextTypes.h"

namespace Edge
{
	union PhysicsCollisionContactID final
	{
		using ContactIDValue = uint64_t;
		static constexpr ContactIDValue InvalidContactIDValue
			= InvalidPhysicsSceneCollisionID << sizeof(PhysicsSceneCollisionID) | InvalidPhysicsSceneCollisionID;

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
			size_t operator()(const PhysicsCollisionContactID& id) const;
		};
	};

	struct PhysicsCollisionContactPoint final
	{
		struct CachedApplyingData final
		{
			ComputeValueType m_frictionLambda1 = 0.0;
			ComputeValueType m_frictionLambda2 = 0.0;
			ComputeValueType m_penetrationLambda = 0.0;
		};

		ComputeVector3 m_position1 = ComputeVector3Zero;
		ComputeVector3 m_position2 = ComputeVector3Zero;
		ComputeVector3 m_normal = ComputeVector3Zero;
		ComputeValueType m_depth = -Math::Max;

		CachedApplyingData m_cachedData;
	};

	struct PhysicsInstancedCollisionContactPoint final
	{
		PhysicsCollisionContactPoint m_pointData;
		PhysicsCollisionContactID m_contactID;
	};
}
