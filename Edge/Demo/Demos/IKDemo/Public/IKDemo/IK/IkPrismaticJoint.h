#pragma once

#include "EdgeCommon/Math/Transform.h"

#include "IkJoint.h"

namespace EdgeDemo
{
	class IkPrismaticJoint : public IkJoint
	{
	private:
		Edge::Transform m_initialLocalTransform = Edge::FloatMatrix4x4Identity;
		Edge::ComputeVector3 m_localAxis = Edge::FloatVector3Zero;
		Edge::ComputeValueType m_value = 0.0f;

	protected:
		virtual void setValue(float value) { m_value = value; }
		virtual void updateLinks() override;

	public:
		IkPrismaticJoint(IkLink* parentLink, IkLink* childLink, const Edge::ComputeVector3& localAxis);

		virtual Edge::ComputeVector3 calcDerivative(const Edge::ComputeVector3& effectorPosition) const override;
		virtual void applyValue(float value) override;
		virtual float getValue() const override { return m_value; }
	};
}
