#pragma once

#include "PhysicsEntityTransform.h"

namespace Edge
{
	class PhysicsEntityMotion : public PhysicsEntityWeakLinkObject, public DefaultDestroyingMTCountableObjectBase
	{
	protected:
		float m_mass = 1.0f;
		float m_invMass = 1.0f;

		float m_gravityFactor = 1.0f;

		float m_friction = 0.5f;

		PhysicsEntityTransformReference getTransform() const;

	public:
		PhysicsEntityMotion() = default;

		virtual FloatVector3 getLinearVelocity() const = 0;
		virtual void getLinearVelocity(FloatVector3& velocity) const = 0;
		virtual void setLinearVelocity(const FloatVector3& velocity) = 0;

		virtual FloatVector3 getAngularVelocity() const = 0;
		virtual void getAngularVelocity(FloatVector3& velocity) const = 0;
		virtual void setAngularVelocity(const FloatVector3& velocity) = 0;

		virtual FloatVector3 getInverseInertia() const = 0;
		virtual void getInverseInertia(FloatVector3& inertia) const = 0;
		virtual void setInertia(const FloatVector3& inertia) = 0;

		virtual void getInverseInertiaTensor(FloatMatrix3x3& inertia) const = 0;
		virtual void getWorldInverseInertiaTensor(FloatMatrix3x3& inertia) const = 0;

		virtual float getLinearDampingFactor() const = 0;
		virtual void setLinearDampingFactor(float factor) = 0;

		virtual float getAngularDampingFactor() const = 0;
		virtual void setAngularDampingFactor(float factor) = 0;

		virtual void applyForce(const FloatVector3& force) = 0;
		virtual void applyForce(const FloatVector3& force, const FloatVector3& position) = 0;
		virtual void applyImpulse(const FloatVector3& impulse) = 0;
		virtual void applyImpulse(const FloatVector3& impulse, const FloatVector3& position) = 0;
		virtual void applyTorque(const FloatVector3& torque) = 0;
		virtual void applyAngularImpulse(const FloatVector3& impulse) = 0;

		float getMass() const { return m_mass; }
		float getInverseMass() const { return m_invMass; }
		void setMass(float mass);

		float getGravityFactor() const { return m_gravityFactor; }
		void setGravityFactor(float factor);

		float getFriction() const { return m_friction; }
		void setFriction(float friction);

		virtual void applyAcceleration(float deltaTime, const FloatVector3& gravity) = 0;
	};

	EDGE_MT_REFERENCE(PhysicsEntityMotion);

	class PhysicsPositionBasedMotion : public PhysicsEntityMotion
	{
	protected:
		FloatVector3 m_linearVelocity = FloatVector3Zero;
		FloatVector3 m_forceAccumulator = FloatVector3Zero;

		float m_linearDampingFactor = 0.05f;

	public:
		PhysicsPositionBasedMotion() = default;

		virtual FloatVector3 getLinearVelocity() const override { return m_linearVelocity; }
		virtual void getLinearVelocity(FloatVector3& velocity) const override { velocity = m_linearVelocity; }
		virtual void setLinearVelocity(const FloatVector3& velocity) override { m_linearVelocity = velocity; }

		virtual FloatVector3 getAngularVelocity() const override { return FloatVector3Zero; }
		virtual void getAngularVelocity(FloatVector3& velocity) const override { velocity = FloatVector3Zero; }
		virtual void setAngularVelocity(const FloatVector3& velocity) override {}

		virtual FloatVector3 getInverseInertia() const override { return FloatVector3Zero; }
		virtual void getInverseInertia(FloatVector3& inertia) const override { inertia = FloatVector3Zero; }
		virtual void setInertia(const FloatVector3& inertia) override {}

		virtual void getInverseInertiaTensor(FloatMatrix3x3& inertia) const override { inertia = FloatMatrix3x3(); }
		virtual void getWorldInverseInertiaTensor(FloatMatrix3x3& inertia) const override { inertia = FloatMatrix3x3(); }

		virtual float getLinearDampingFactor() const override { return m_linearDampingFactor; }
		virtual void setLinearDampingFactor(float factor) override;

		virtual float getAngularDampingFactor() const override { return 0.0f; }
		virtual void setAngularDampingFactor(float factor) override {}

		virtual void applyForce(const FloatVector3& force) override;
		virtual void applyImpulse(const FloatVector3& impulse) override;
		virtual void applyForce(const FloatVector3& force, const FloatVector3& position) override { applyForce(force); }
		virtual void applyImpulse(const FloatVector3& impulse, const FloatVector3& position) override { applyImpulse(impulse); }
		virtual void applyTorque(const FloatVector3& torque) override {}
		virtual void applyAngularImpulse(const FloatVector3& impulse) override {}

		virtual void applyAcceleration(float deltaTime, const FloatVector3& gravity) override;

		void clearForceAccumulator();
	};

	EDGE_MT_REFERENCE(PhysicsPositionBasedMotion);

	class PhysicsPositionAndRotationBasedMotion : public PhysicsPositionBasedMotion
	{
	private:
		FloatVector3 m_angularVelocity = FloatVector3Zero;
		FloatVector3 m_torqueAccumulator = FloatVector3Zero;

		FloatVector3 m_inverseInertia = FloatVector3Zero;

		float m_angularDampingFactor = 0.05f;

	public:
		PhysicsPositionAndRotationBasedMotion() = default;

		virtual FloatVector3 getAngularVelocity() const override { return m_angularVelocity; }
		virtual void getAngularVelocity(FloatVector3& velocity) const override { velocity = m_angularVelocity; }
		virtual void setAngularVelocity(const FloatVector3& velocity) override { m_angularVelocity = velocity; }

		virtual FloatVector3 getInverseInertia() const override { return m_inverseInertia; }
		virtual void getInverseInertia(FloatVector3& inertia) const override { inertia = m_inverseInertia; }
		virtual void setInertia(const FloatVector3& inertia) override;

		virtual void getInverseInertiaTensor(FloatMatrix3x3& inertia) const override;
		virtual void getWorldInverseInertiaTensor(FloatMatrix3x3& inertia) const override;

		virtual float getAngularDampingFactor() const override { return m_angularDampingFactor; }
		virtual void setAngularDampingFactor(float factor) override { m_angularDampingFactor = factor; }

		virtual void applyForce(const FloatVector3& force, const FloatVector3& position) override;
		virtual void applyImpulse(const FloatVector3& impulse, const FloatVector3& position) override;
		virtual void applyTorque(const FloatVector3& torque) override;
		virtual void applyAngularImpulse(const FloatVector3& impulse) override;

		virtual void applyAcceleration(float deltaTime, const FloatVector3& gravity) override;

		void clearTorqueAccumulator();
	};
}
