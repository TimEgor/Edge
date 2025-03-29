#pragma once

#include "EdgeCommon/Math/Transform.h"
#include "EdgeCommon/Reference/MTReference.h"

#include "PhysicsEntityWeakLinkObject.h"

namespace Edge
{
	class PhysicsEntityTransformNotificationFreeAccessor;

	class PhysicsEntityTransform : public PhysicsEntityWeakLinkObject, public DefaultDestroyingMTCountableObjectBase
	{
		friend PhysicsEntityTransformNotificationFreeAccessor;

	protected:
		void makeTransformChangingNotification() const;

		virtual void setPositionRaw(const ComputeVector3& position) = 0;
		virtual void setRotationRaw(const ComputeQuaternion& rotation) = 0;
		virtual void setWorldTransformRaw(const Transform& transform) = 0;

	public:
		PhysicsEntityTransform() = default;

		virtual ComputeVector3 getPosition() const = 0;
		virtual void getPosition(ComputeVector3& position) const = 0;
		virtual void setPosition(const ComputeVector3& position) = 0;

		virtual ComputeQuaternion getRotation() const = 0;
		virtual void getRotation(ComputeQuaternion& rotation) const = 0;
		virtual void setRotation(const ComputeQuaternion& rotation) = 0;

		virtual Transform getWorldTransform() const = 0;
		virtual void getWorldTransform(Transform& transform) const = 0;
		virtual void setWorldTransform(const Transform& transform) = 0;
	};

	EDGE_MT_REFERENCE(PhysicsEntityTransform);

	class PhysicsPositionBasedTransform : public PhysicsEntityTransform
	{
	protected:
		ComputeVector3 m_position = ComputeVector3Zero;

		virtual void setPositionRaw(const ComputeVector3& position) override;
		virtual void setRotationRaw(const ComputeQuaternion& rotation) override {}
		virtual void setWorldTransformRaw(const Transform& transform) override;

	public:
		PhysicsPositionBasedTransform() = default;

		virtual ComputeVector3 getPosition() const override { return m_position; }
		virtual void getPosition(ComputeVector3& position) const override { position = m_position; }
		virtual void setPosition(const ComputeVector3& position) override;

		virtual ComputeQuaternion getRotation() const override { return FloatQuaternionIdentity; }
		virtual void getRotation(ComputeQuaternion& rotation) const override { rotation = FloatQuaternionIdentity; }
		virtual void setRotation(const ComputeQuaternion& rotation) override {}

		virtual Transform getWorldTransform() const override;
		virtual void getWorldTransform(Transform& transform) const override;
		virtual void setWorldTransform(const Transform& transform) override;
	};

	EDGE_MT_REFERENCE(PhysicsPositionBasedTransform);

	class PhysicsPositionAndRotationBasedTransform : public PhysicsPositionBasedTransform
	{
	protected:
		ComputeQuaternion m_rotation = ComputeQuaternionIdentity;

		virtual void setRotationRaw(const ComputeQuaternion& rotation) override;
		virtual void setWorldTransformRaw(const Transform& transform) override;

	public:
		PhysicsPositionAndRotationBasedTransform() = default;

		virtual ComputeQuaternion getRotation() const override { return m_rotation; }
		virtual void getRotation(ComputeQuaternion& rotation) const override { rotation = m_rotation; }
		virtual void setRotation(const ComputeQuaternion& rotation) override;

		virtual Transform getWorldTransform() const override;
		virtual void getWorldTransform(Transform& transform) const override;
		virtual void setWorldTransform(const Transform& transform) override;
	};

	EDGE_MT_REFERENCE(PhysicsPositionAndRotationBasedTransform);

	class PhysicsEntityTransformNotificationFreeAccessor
	{
	private:
		const PhysicsEntityTransformReference m_transform;

	public:
		PhysicsEntityTransformNotificationFreeAccessor(const PhysicsEntityTransformReference& transform);
		virtual ~PhysicsEntityTransformNotificationFreeAccessor() = default;

		virtual ComputeVector3 getPosition() const;
		virtual void getPosition(ComputeVector3& position) const;
		virtual void setPosition(const ComputeVector3& position);

		virtual ComputeQuaternion getRotation() const;
		virtual void getRotation(ComputeQuaternion& rotation) const;
		virtual void setRotation(const ComputeQuaternion& rotation);

		virtual Transform getWorldTransform() const;
		virtual void getWorldTransform(Transform& transform) const;
		virtual void setWorldTransform(const Transform& transform);

		virtual void makeTransformChangingNotification();
	};

	class PhysicsEntityTransformAccessor final : public NonCopyable, public PhysicsEntityTransformNotificationFreeAccessor
	{
	private:
		bool m_isChanged = false;

	public:
		PhysicsEntityTransformAccessor(const PhysicsEntityTransformReference& transform)
			: PhysicsEntityTransformNotificationFreeAccessor(transform) {}
		~PhysicsEntityTransformAccessor();

		virtual void setPosition(const ComputeVector3& position) override;
		virtual void setRotation(const ComputeQuaternion& rotation) override;
		virtual void setWorldTransform(const Transform& transform) override;

		virtual void makeTransformChangingNotification() override;
	};
}
