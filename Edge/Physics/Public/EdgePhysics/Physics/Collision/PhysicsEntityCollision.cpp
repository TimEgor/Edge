#include "PhysicsEntityCollision.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include "Scene/PhysicsSceneCollisionManager.h"

Edge::PhysicsEntityTransformReference Edge::PhysicsEntityCollision::getTransform() const
{
	const PhysicsEntityReference entity = getEntity();
	if (!entity)
	{
		return nullptr;
	}

	const PhysicsEntityTransformReference transform = entity->getTransform();
	if (!transform)
	{
		return nullptr;
	}

	if (!transform->isEntityLinkEqual(*this))
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity links aren't equal.");
		return nullptr;
	}

	return transform;
}

void Edge::PhysicsEntityCollision::setShape(const PhysicsEntityCollisionShapeReference& shape)
{
	if (m_shape && m_sceneContext)
	{
		m_sceneContext->getCollisionManager().getReference()->removeCollision(this);
	}

	m_shape = shape;

	if (m_shape && m_sceneContext)
	{
		m_sceneContext->getCollisionManager().getReference()->addCollision(this);
	}
}

Edge::AABB3 Edge::PhysicsEntityCollision::getWorldShapeAABB() const
{
	if (!m_shape)
	{
		return AABB3();
	}

	AABB3 bound = m_shape->getAABB();

	const ComputeMatrix4x4 worldTransform = getTransform()->getWorldTransform().m_matrix;

	ComputeVector3 points[8] = {
		bound.m_minPosition,
		ComputeVector3(bound.m_maxPosition.getX(), bound.m_minPosition.getY(), bound.m_minPosition.getZ()),
		ComputeVector3(bound.m_minPosition.getX(), bound.m_minPosition.getY(), bound.m_maxPosition.getZ()),
		ComputeVector3(bound.m_maxPosition.getX(), bound.m_minPosition.getY(), bound.m_maxPosition.getZ()),
		ComputeVector3(bound.m_minPosition.getX(), bound.m_maxPosition.getY(), bound.m_minPosition.getZ()),
		ComputeVector3(bound.m_maxPosition.getX(), bound.m_maxPosition.getY(), bound.m_minPosition.getZ()),
		ComputeVector3(bound.m_minPosition.getX(), bound.m_maxPosition.getY(), bound.m_maxPosition.getZ()),
		bound.m_maxPosition
	};

	ComputeVector3 minBoundPoint(Math::Max);
	ComputeVector3 maxBoundPoint(-Math::Max);

	for (uint32_t pointIndex = 0; pointIndex < 8; ++pointIndex)
	{
		const ComputeVector3 transformBoundPoint = (worldTransform * ComputeVector4FromPoint(points[pointIndex])).getXYZ();
		minBoundPoint = MinComputeVector3(transformBoundPoint, minBoundPoint);
		maxBoundPoint = MinComputeVector3(transformBoundPoint, maxBoundPoint);
	}

	bound.m_minPosition = minBoundPoint;
	bound.m_maxPosition = maxBoundPoint;

	return bound;
}

Edge::ComputeVector3 Edge::PhysicsEntityCollision::getFurthestKeyPoint(const ComputeVector3& direction) const
{
	if (!m_shape)
	{
		return ComputeVector3Zero;
	}

	const PhysicsEntityTransformReference transform = getTransform();

	const ComputeVector4 localDirection = InvertComputeMatrix4x4(transform->getWorldTransform().m_matrix) * ComputeVector4(direction);

	const ComputeVector3 localPoint = m_shape->getFurthestKeyPoint(localDirection.getXYZ());
	const ComputeVector3 point = (transform->getWorldTransform().m_matrix * ComputeVector4FromPoint(localPoint)).getXYZ();

	return point;
}

Edge::ComputeVector3 Edge::PhysicsEntityCollision::getSupportingPoint(const ComputeVector3& direction) const
{
	if (!m_shape)
	{
		return ComputeVector3Zero;
	}

	const PhysicsEntityTransformReference transform = getTransform();

	const ComputeVector4 localDirection = InvertComputeMatrix4x4(transform->getWorldTransform().m_matrix) * ComputeVector4(direction);

	const ComputeVector3 localPoint = m_shape->getSupportingPoint(localDirection.getXYZ());
	const ComputeVector3 point = (transform->getWorldTransform().m_matrix * ComputeVector4FromPoint(localPoint)).getXYZ();

	return point;
}

Edge::ComputeValue Edge::PhysicsEntityCollision::getSupportingRadius() const
{
	if (!m_shape)
	{
		return 0.0_ecv;
	}

	return m_shape->getSupportingRadius();
}

void Edge::PhysicsEntityCollision::getSupportingFace(const ComputeVector3& direction,
                                                     PhysicsEntityCollisionShape::SupportingFaceVertexCollection& vertices) const
{
	vertices.clear();

	if (!m_shape)
	{
		return;
	}

	const PhysicsEntityTransformReference transform = getTransform();

	const ComputeVector4 localDirection = InvertComputeMatrix4x4(transform->getWorldTransform().m_matrix) * ComputeVector4(direction);

	m_shape->getSupportingFace(localDirection.getXYZ(), vertices);

	for (ComputeVector3& vertex : vertices)
	{
		vertex = (transform->getWorldTransform().m_matrix * ComputeVector4FromPoint(vertex)).getXYZ();
	}
}

bool Edge::PhysicsEntityCollision::rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResult& result) const
{
	if (!m_shape)
	{
		return false;
	}

	const PhysicsEntityTransformReference transform = getTransform();

	const ComputeMatrix4x4 inverseTransform = InvertComputeMatrix4x4(transform->getWorldTransform().m_matrix);

	const ComputeVector3 localOriginPosition = (inverseTransform * ComputeVector4FromPoint(origin)).getXYZ();
	const ComputeVector3 localEndPosition = (inverseTransform * ComputeVector4FromPoint(end)).getXYZ();

	if (m_shape->rayCast(localOriginPosition, localEndPosition, result))
	{
		result.m_hitPosition = (transform->getWorldTransform().m_matrix * ComputeVector4FromPoint(result.m_hitPosition)).getXYZ();

		return true;
	}

	return false;
}

void Edge::PhysicsEntityCollision::setSceneContext(const PhysicsEntityCollisionSceneContextReference& context)
{
	if (context && m_sceneContext)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Collision scene context has been already set.");
		return;
	}

	m_sceneContext = context;
}

Edge::PhysicsSceneCollisionManagerReference Edge::PhysicsEntityCollision::getCollisionManager() const
{
	return m_sceneContext ? m_sceneContext->getCollisionManager().getReference() : nullptr;
}

void Edge::PhysicsEntityCollision::setFriction(ComputeValueType friction)
{
	if (0.0f > friction || friction > 1.0f)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set up invalid friction value.");
		return;
	}

	m_friction = friction;
}

void Edge::PhysicsEntityCollision::setElasticity(ComputeValueType elasticity)
{
	if (0.0f > elasticity || elasticity > 1.0f)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set up invalid elasticity value.");
		return;
	}

	m_elasticity = elasticity;
}
