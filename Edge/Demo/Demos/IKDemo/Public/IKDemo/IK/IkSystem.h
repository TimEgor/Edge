#pragma once

#include "IkJoint.h"
#include "IkLink.h"

#include <vector>

namespace EdgeDemo
{
	class IkSystem final
	{
	public:
		using LinkCollection = std::vector<IkLink*>;
		using JointCollection = std::vector<IkJoint*>;
		using LinkHierarchyContainer = std::vector<uint32_t>;

	private:
		LinkCollection m_links;
		JointCollection m_joints;

		Edge::Transform m_baseTransform;

		Edge::FloatVector3 m_targetPosition = Edge::FloatVector3Zero;

		IkLink* m_effector = nullptr;
		IkLink* m_root = nullptr;

	public:
		IkSystem() = default;

		void clear();

		void addLink(IkLink* link);
		void addJoint(IkJoint* joint);

		const LinkCollection& getLinks() const { return m_links; }
		const JointCollection& getJoints() const { return m_joints; }

		void setBaseTransform(const Edge::Transform& transform) { m_baseTransform = transform; }
		const Edge::Transform& getBaseTransform() const { return m_baseTransform; }

		void setTargetPosition(const Edge::FloatVector3& target) { m_targetPosition = target; }
		const Edge::FloatVector3& getTargetPosition() const { return m_targetPosition; }

		void setEffectorLink(IkLink* effector);
		IkLink* getEffectorLink() const { return m_effector; }

		void setRootLink(IkLink* root);
		IkLink* getRootLink() const { return m_root; }
	};
}
