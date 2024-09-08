#include "PhysicsEntityCollision.h"

#include "PhysicsSceneCollisionManager.h"
#include "EdgeCommon/Math/Const.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

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

	const ComputeMatrix worldTransform = getTransform()->getWorldTransform().m_matrix;

	FloatVector3 points[8] = {
		bound.m_minPosition,
		FloatVector3(bound.m_maxPosition.m_x, bound.m_minPosition.m_y, bound.m_minPosition.m_z),
		FloatVector3(bound.m_minPosition.m_x, bound.m_minPosition.m_y, bound.m_maxPosition.m_z),
		FloatVector3(bound.m_maxPosition.m_x, bound.m_minPosition.m_y, bound.m_maxPosition.m_z),
		FloatVector3(bound.m_minPosition.m_x, bound.m_maxPosition.m_y, bound.m_minPosition.m_z),
		FloatVector3(bound.m_maxPosition.m_x, bound.m_maxPosition.m_y, bound.m_minPosition.m_z),
		FloatVector3(bound.m_minPosition.m_x, bound.m_maxPosition.m_y, bound.m_maxPosition.m_z),
		bound.m_maxPosition
	};

	ComputeVector minBoundPoint = FloatVector3(EDGE_FLT_MAX);
	ComputeVector maxBoundPoint = FloatVector3(-EDGE_FLT_MAX);

	for (uint32_t pointIndex = 0; pointIndex < 8; ++pointIndex)
	{
		ComputeVector transformBoundPoint = worldTransform * computeVectorFromPoint(points[pointIndex]);
		minBoundPoint = ComputeMath::vectorMin(transformBoundPoint.m_vector, minBoundPoint.m_vector);
		maxBoundPoint = ComputeMath::vectorMax(transformBoundPoint.m_vector, maxBoundPoint.m_vector);
	}

	minBoundPoint.saveToFloatVector3(bound.m_minPosition);
	maxBoundPoint.saveToFloatVector3(bound.m_maxPosition);

	return bound;
}

bool Edge::PhysicsEntityCollision::rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const
{
	if (!m_shape)
	{
		return false;
	}

	const PhysicsEntityTransformReference transform = getTransform();

	ComputeMatrix inverseTransform(transform->getWorldTransform().m_matrix);
	inverseTransform.inverse();

	const ComputeVector localOriginPosition = inverseTransform * computeVectorFromPoint(origin);
	const ComputeVector localEndPosition = inverseTransform * computeVectorFromPoint(end);

	if (m_shape->rayCast(localOriginPosition.getFloatVector3(), localEndPosition.getFloatVector3(), result))
	{
		const ComputeVector hitPos = transform->getWorldTransform().m_matrix * computeVectorFromPoint(result.m_hitPosition);
		hitPos.saveToFloatVector3(result.m_hitPosition);

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
