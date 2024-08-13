#pragma once

#include "EdgeCommon/Math/Transform.h"
#include "EdgeCommon/Reference/MTReference.h"

namespace Edge
{
	class PhysicsEntityTransform : public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsEntityTransform() = default;
		virtual ~PhysicsEntityTransform() = default;

		virtual FloatVector3 getPosition() const = 0;
		virtual void getPosition(FloatVector3& position) const = 0;
		virtual void setPosition(const FloatVector3& position) = 0;

		virtual FloatQuaternion getRotation() const = 0;
		virtual void getRotation(FloatQuaternion& rotation) const = 0;
		virtual void setRotation(const FloatQuaternion& rotation) = 0;

		virtual Transform getWorldTransform() const = 0;
		virtual void getWorldTransform(Transform& transform) const = 0;
		virtual void setWorldTransform(const Transform& transform) = 0;
	};

	EDGE_MT_REFERENCE(PhysicsEntityTransform);

	class PhysicsPositionBasedTransform : public PhysicsEntityTransform
	{
	protected:
		FloatVector3 m_position = FloatVector3Zero;

	public:
		PhysicsPositionBasedTransform() = default;

		virtual FloatVector3 getPosition() const override { return m_position; }
		virtual void getPosition(FloatVector3& position) const override { position = m_position; }
		virtual void setPosition(const FloatVector3& position) override;

		virtual FloatQuaternion getRotation() const override { return FloatQuaternionIdentity; }
		virtual void getRotation(FloatQuaternion& rotation) const override { rotation = FloatQuaternionIdentity; }
		virtual void setRotation(const FloatQuaternion& rotation) override {}

		virtual Transform getWorldTransform() const override;
		virtual void getWorldTransform(Transform& transform) const override;
		virtual void setWorldTransform(const Transform& transform) override;
	};

	EDGE_MT_REFERENCE(PhysicsPositionBasedTransform);

	class PhysicsPositionAndRotationBasedTransform : public PhysicsPositionBasedTransform
	{
	private:
		FloatQuaternion m_rotation = FloatQuaternionIdentity;

	public:
		PhysicsPositionAndRotationBasedTransform() = default;

		virtual FloatQuaternion getRotation() const override { return m_rotation; }
		virtual void getRotation(FloatQuaternion& rotation) const override { rotation = m_rotation; }
		virtual void setRotation(const FloatQuaternion& rotation) override;

		virtual Transform getWorldTransform() const override;
		virtual void getWorldTransform(Transform& transform) const override;
		virtual void setWorldTransform(const Transform& transform) override;
	};

	EDGE_MT_REFERENCE(PhysicsPositionAndRotationBasedTransform);
}
