#pragma once

#include "EdgePhysics/Physics/Constraint/PhysicsConstraint.h"

#include "PhysicsConstraintSceneContextTypes.h"

#include <vector>


namespace Edge
{
	class PhysicsSceneActiveConstraintCollection final
	{
	public:
		using ConstraintCollection = std::vector<PhysicsSceneConstraintID>;

	private:
		ConstraintCollection m_ids;

		PhysicsSceneConstraintManagerWeakReference m_manager;

	public:
		PhysicsSceneActiveConstraintCollection() = default;
		~PhysicsSceneActiveConstraintCollection() { release(); }

		bool init(const PhysicsSceneConstraintManagerReference& manager);
		void release();

		void addConstraint(const PhysicsConstraintReference& constraint);
		void removeConstraint(const PhysicsConstraintReference& constraint);

		const ConstraintCollection& getConstraints() const { return m_ids; }
	};
}
