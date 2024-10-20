#pragma once

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollisionShape.h"

#include <unordered_map>

namespace Edge
{
	class PhysicsCollisionDispatcher;

	class PhysicsCollisionDispatcherCollection final
	{
	private:
		struct DispatcherID final
		{
			using DispatcherIDValue = uint64_t;
			static constexpr DispatcherIDValue InvalidDispatcherIDValue = 0;

			union
			{
				struct
				{
					PhysicsEntityCollisionShapeType m_shapeType1;
					PhysicsEntityCollisionShapeType m_shapeType2;
				};

				DispatcherIDValue m_id = InvalidDispatcherIDValue;
			};

			DispatcherID() = default;
			DispatcherID(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2);

			bool operator==(const DispatcherID& id) const;

			struct Hasher
			{
				size_t operator()(const DispatcherID& k) const;
			};
		};

		using DispatcherCollection = std::unordered_map<DispatcherID, PhysicsCollisionDispatcher*, DispatcherID::Hasher>;

		DispatcherCollection m_dispatchers;

		PhysicsCollisionDispatcher* m_defaultDispatcher = nullptr;

	public:
		PhysicsCollisionDispatcherCollection() = default;

		void addDispatcher(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2, PhysicsCollisionDispatcher* dispatcher);
		void removeDispatcher(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2);

		void setDefaultDispatcher(PhysicsCollisionDispatcher* dispatcher);
		void resetDefaultDispatcher();

		PhysicsCollisionDispatcher* getDispatcher(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2) const;
	};
}
