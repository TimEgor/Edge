#pragma once

#include "EdgeCommon/Math/Transform.h"

#include "IkJoint.h"

namespace EdgeDemo
{
	class IkHingeJoint : public IkJoint
	{
	private:
		Edge::Transform m_initialLocalTransform = Edge::FloatMatrix4x4Identity;
		Edge::FloatVector3 m_localAxis = Edge::FloatVector3Zero;
		float m_value = 0.0f;

	protected:
		virtual void setValue(float value) { m_value = value; }
		virtual void updateLinks() override;

	public:
		IkHingeJoint(IkLink* parentLink, IkLink* childLink, const Edge::FloatVector3& localAxis);

		virtual Edge::FloatVector3 calcDerivative(const Edge::FloatVector3& effectorPosition) const override;
		virtual void applyValue(float value) override;
		virtual float getValue() const override { return m_value; }
	};
}
