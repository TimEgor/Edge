#pragma once

namespace Edge
{
	class PhysicsEntityCollision;
	struct PhysicsContactManifold;
	struct PhysicsCollisionContactPoint;

	class ManifoldContactGenerator final
	{
	public:
		ManifoldContactGenerator() = default;

		void generate(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2,
			const PhysicsCollisionContactPoint& contactPoint, PhysicsContactManifold& manifold) const;

		void operator()(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2,
			const PhysicsCollisionContactPoint& contactPoint, PhysicsContactManifold& manifold) const
		{
			generate(collision1, collision2, contactPoint, manifold);
		}
	};
}
