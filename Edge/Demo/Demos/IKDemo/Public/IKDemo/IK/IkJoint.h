#pragma once

#include "EdgeCommon/Math/ComputeVector3.h"

namespace EdgeDemo
{
	class IkLink;

	class IkJoint
	{
	private:
		IkLink* m_parentLink = nullptr;
		IkLink* m_childLink = nullptr;

	protected:
		virtual void updateLinks() = 0;

	public:
		IkJoint(IkLink* parentLink, IkLink* childLink)
			: m_parentLink(parentLink), m_childLink(childLink) {}
		virtual ~IkJoint() = default;

		virtual Edge::ComputeVector3 calcDerivative(const Edge::ComputeVector3& effectorPosition) const = 0;
		virtual void applyValue(float value) = 0;
		virtual float getValue() const = 0;

		IkLink* getParentLink() const { return m_parentLink; }
		IkLink* getChildLink() const { return m_childLink; }
	};
}
