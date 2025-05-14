#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include "PhysicsConstraint.h"

namespace Edge
{
	class TwoPhysicsEntityConstraint : public PhysicsConstraint
	{
	private:
		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		static bool validateEntity(const PhysicsEntityReference& entity);

	protected:
		bool validateEntities() const;

	public:
		TwoPhysicsEntityConstraint(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2);

		PhysicsEntityReference getEntity1() const;
		PhysicsEntityReference getEntity2() const;

		EDGE_RTTI_VIRTUAL(TwoPhysicsEntityConstraint, PhysicsConstraint)
	};
}