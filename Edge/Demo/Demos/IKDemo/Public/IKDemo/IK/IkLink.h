#pragma once

#include "EdgeCommon/Math/Matrix.h"
#include "EdgeCommon/Math/Transform.h"

namespace EdgeDemo
{
	class IkLink final
	{
	private:
		Edge::Transform m_worldTransform = Edge::FloatMatrix4x4Identity;
		Edge::Transform m_localTransform = Edge::FloatMatrix4x4Identity;

		IkLink* m_parent = nullptr;
		IkLink* m_child = nullptr;

	public:
		IkLink() = default;

		const Edge::Transform& getWorldTransform() const { return m_worldTransform; }
		void setWorldTransform(const Edge::Transform& transform) { m_worldTransform = transform; }
		const Edge::Transform& getLocalTransform() const { return m_localTransform; }
		void setLocalTransform(const Edge::Transform& transform) { m_localTransform = transform; }

		IkLink* getParentLink() const { return m_parent; }
		void setParentLink(IkLink* link);

		IkLink* getChildLink() const { return m_child; }
	};
}
