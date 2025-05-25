#pragma once

#include "PhysicsEntityTransform.h"

namespace Edge
{
	class PhysicsEntityMotion : public PhysicsEntityWeakLinkObject, public DefaultDestroyingMTCountableObjectBase
	{
	protected:
		ComputeValueType m_mass = 1.0;
		ComputeValueType m_invMass = 1.0;

		ComputeValueType m_gravityFactor = 1.0;

	public:
		PhysicsEntityMotion() = default;

		PhysicsEntityTransformReference getTransform() const;

		virtual ComputeVector3 getLinearVelocity() const = 0;
		virtual void getLinearVelocity(ComputeVector3& velocity) const = 0;
		virtual void setLinearVelocity(const ComputeVector3& velocity) = 0;

		virtual ComputeVector3 getPointLinearVelocity(const ComputeVector3& position) const = 0;
		virtual void getPointLinearVelocity(const ComputeVector3& position, ComputeVector3& velocity) const = 0;

		virtual ComputeVector3 getLocalPointLinearVelocity(const ComputeVector3& position) const = 0;
		virtual void getLocalPointLinearVelocity(const ComputeVector3& position, ComputeVector3& velocity) const = 0;

		virtual ComputeVector3 getAngularVelocity() const = 0;
		virtual void getAngularVelocity(ComputeVector3& velocity) const = 0;
		virtual void setAngularVelocity(const ComputeVector3& velocity) = 0;

		virtual ComputeVector3 getInverseInertia() const = 0;
		virtual void getInverseInertia(ComputeVector3& inertia) const = 0;
		virtual void setInertia(const ComputeVector3& inertia) = 0;

		virtual void getLocalInverseInertiaTensor(ComputeMatrix3x3& inertia) const = 0;
		virtual void getLocalInverseInertiaTensor(ComputeMatrix4x4& inertia) const = 0;
		virtual void getWorldInverseInertiaTensor(ComputeMatrix3x3& inertia) const = 0;
		virtual void getWorldInverseInertiaTensor(ComputeMatrix4x4& inertia) const = 0;

		virtual ComputeValueType getLinearDampingFactor() const = 0;
		virtual void setLinearDampingFactor(ComputeValueType factor) = 0;

		virtual ComputeValueType getAngularDampingFactor() const = 0;
		virtual void setAngularDampingFactor(ComputeValueType factor) = 0;

		virtual void applyForce(const ComputeVector3& force) = 0;
		virtual void applyForce(const ComputeVector3& force, const ComputeVector3& position) = 0;
		virtual void applyImpulse(const ComputeVector3& impulse) = 0;
		virtual void applyImpulse(const ComputeVector3& impulse, const ComputeVector3& position) = 0;
		virtual void applyTorque(const ComputeVector3& torque) = 0;
		virtual void applyAngularImpulse(const ComputeVector3& impulse) = 0;

		ComputeValueType getMass() const { return m_mass; }
		ComputeValueType getInverseMass() const { return m_invMass; }
		void setMass(ComputeValueType mass);

		ComputeValueType getGravityFactor() const { return m_gravityFactor; }
		void setGravityFactor(ComputeValueType factor);

		ComputeVector3 getMassCenter() const;
		void getMassCenter(ComputeVector3& center) const;

		virtual void applyAcceleration(float deltaTime, const ComputeVector3& gravity) = 0;
	};

	EDGE_REFERENCE(PhysicsEntityMotion);

	class PhysicsPositionBasedMotion : public PhysicsEntityMotion
	{
	protected:
		ComputeVector3 m_linearVelocity = ComputeVector3Zero;
		ComputeVector3 m_forceAccumulator = ComputeVector3Zero;

		ComputeValueType m_linearDampingFactor = 0.05f;

	public:
		PhysicsPositionBasedMotion() = default;

		virtual ComputeVector3 getLinearVelocity() const override { return m_linearVelocity; }
		virtual void getLinearVelocity(ComputeVector3& velocity) const override { velocity = m_linearVelocity; }
		virtual void setLinearVelocity(const ComputeVector3& velocity) override { m_linearVelocity = velocity; }

		virtual ComputeVector3 getPointLinearVelocity(const ComputeVector3& position) const override { return getLinearVelocity(); }
		virtual void getPointLinearVelocity(const ComputeVector3& position, ComputeVector3& velocity) const override { getLinearVelocity(velocity); }

		virtual ComputeVector3 getLocalPointLinearVelocity(const ComputeVector3& position) const override { return getLinearVelocity(); }
		virtual void getLocalPointLinearVelocity(const ComputeVector3& position, ComputeVector3& velocity) const override { getLinearVelocity(velocity); }

		virtual ComputeVector3 getAngularVelocity() const override { return ComputeVector3Zero; }
		virtual void getAngularVelocity(ComputeVector3& velocity) const override { velocity = ComputeVector3Zero; }
		virtual void setAngularVelocity(const ComputeVector3& velocity) override {}

		virtual ComputeVector3 getInverseInertia() const override { return ComputeVector3Zero; }
		virtual void getInverseInertia(ComputeVector3& inertia) const override { inertia = ComputeVector3Zero; }
		virtual void setInertia(const ComputeVector3& inertia) override {}

		virtual void getLocalInverseInertiaTensor(ComputeMatrix3x3& inertia) const override { inertia = ComputeMatrix3x3(); }
		virtual void getLocalInverseInertiaTensor(ComputeMatrix4x4& inertia) const override { inertia = ComputeMatrix4x4Identity; }
		virtual void getWorldInverseInertiaTensor(ComputeMatrix3x3& inertia) const override { inertia = ComputeMatrix3x3(); }
		virtual void getWorldInverseInertiaTensor(ComputeMatrix4x4& inertia) const override { inertia = ComputeMatrix4x4Identity; }

		virtual float getLinearDampingFactor() const override { return m_linearDampingFactor; }
		virtual void setLinearDampingFactor(float factor) override;

		virtual float getAngularDampingFactor() const override { return 0.0f; }
		virtual void setAngularDampingFactor(float factor) override {}

		virtual void applyForce(const ComputeVector3& force) override;
		virtual void applyImpulse(const ComputeVector3& impulse) override;
		virtual void applyForce(const ComputeVector3& force, const ComputeVector3& position) override { applyForce(force); }
		virtual void applyImpulse(const ComputeVector3& impulse, const ComputeVector3& position) override { applyImpulse(impulse); }
		virtual void applyTorque(const ComputeVector3& torque) override {}
		virtual void applyAngularImpulse(const ComputeVector3& impulse) override {}

		virtual void applyAcceleration(float deltaTime, const ComputeVector3& gravity) override;

		void clearForceAccumulator();
	};

	EDGE_REFERENCE(PhysicsPositionBasedMotion);

	class PhysicsPositionAndRotationBasedMotion : public PhysicsPositionBasedMotion
	{
	private:
		ComputeVector3 m_angularVelocity = ComputeVector3Zero;
		ComputeVector3 m_torqueAccumulator = ComputeVector3Zero;

		ComputeVector3 m_inverseInertia = ComputeVector3Zero;

		float m_angularDampingFactor = 0.05f;

	public:
		PhysicsPositionAndRotationBasedMotion() = default;

		virtual ComputeVector3 getPointLinearVelocity(const ComputeVector3& position) const override;
		virtual void getPointLinearVelocity(const ComputeVector3& position, ComputeVector3& velocity) const override;

		virtual ComputeVector3 getLocalPointLinearVelocity(const ComputeVector3& position) const override;
		virtual void getLocalPointLinearVelocity(const ComputeVector3& position, ComputeVector3& velocity) const override;

		virtual ComputeVector3 getAngularVelocity() const override { return m_angularVelocity; }
		virtual void getAngularVelocity(ComputeVector3& velocity) const override { velocity = m_angularVelocity; }
		virtual void setAngularVelocity(const ComputeVector3& velocity) override { m_angularVelocity = velocity; }

		virtual ComputeVector3 getInverseInertia() const override { return m_inverseInertia; }
		virtual void getInverseInertia(ComputeVector3& inertia) const override { inertia = m_inverseInertia; }
		virtual void setInertia(const ComputeVector3& inertia) override;

		virtual void getLocalInverseInertiaTensor(ComputeMatrix3x3& inertia) const override;
		virtual void getLocalInverseInertiaTensor(ComputeMatrix4x4& inertia) const override;
		virtual void getWorldInverseInertiaTensor(ComputeMatrix3x3& inertia) const override;
		virtual void getWorldInverseInertiaTensor(ComputeMatrix4x4& inertia) const override;

		virtual float getAngularDampingFactor() const override { return m_angularDampingFactor; }
		virtual void setAngularDampingFactor(float factor) override { m_angularDampingFactor = factor; }

		virtual void applyForce(const ComputeVector3& force) override { PhysicsPositionBasedMotion::applyForce(force); }
		virtual void applyForce(const ComputeVector3& force, const ComputeVector3& position) override;
		virtual void applyImpulse(const ComputeVector3& impulse) override { PhysicsPositionBasedMotion::applyImpulse(impulse); }
		virtual void applyImpulse(const ComputeVector3& impulse, const ComputeVector3& position) override;
		virtual void applyTorque(const ComputeVector3& torque) override;
		virtual void applyAngularImpulse(const ComputeVector3& impulse) override;

		virtual void applyAcceleration(float deltaTime, const ComputeVector3& gravity) override;

		void clearTorqueAccumulator();
	};
}
