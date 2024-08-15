#pragma once

#include "PhysicsEntityReference.h"

namespace Edge
{
	class PhysicsEntityWeakLinkObject
	{
		friend PhysicsEntity;

	private:
		PhysicsEntity* m_entity = nullptr;

		void setEntityLink(PhysicsEntity* entity);

	public:
		PhysicsEntityWeakLinkObject() = default;
		virtual ~PhysicsEntityWeakLinkObject();

		PhysicsEntityReference getEntity() const;

		bool isEntityLinkEqual(const PhysicsEntityWeakLinkObject& link) const;
	};
}
