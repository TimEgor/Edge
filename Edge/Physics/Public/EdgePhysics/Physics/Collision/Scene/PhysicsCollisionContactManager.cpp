#include "PhysicsCollisionContactManager.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgePhysics/Physics/Collision/Dispatchers/GJKCollisionDispatcher.h"
#include "EdgePhysics/Physics/Collision/Dispatchers/PhysicsCollisionDispatcherCollection.h"
#include "EdgePhysics/Physics/Collision/Dispatchers/SphereVsSphereCollisionDispatcher.h"
#include "EdgePhysics/Physics/Collision/Manifold/PhysicsContactManifold.h"
#include "EdgePhysics/Physics/Collision/Scene/DefaultPhysicsEntityCollisionSceneContext.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"

#include "PhysicsCollisionConstraintManager.h"
#include "PhysicsSceneCollisionManager.h"

bool Edge::PhysicsCollisionContactManager::DispatcherContext::init()
{
#define CREATE_AND_ADD_DISPATCHER(DISPATCHER_TYPE, SHAPE_TYPE1, SHAPE_TYPE2)			\
	{																					\
		PhysicsCollisionDispatcher* newDispatcher = new DISPATCHER_TYPE();				\
		m_dispatchers.push_back(newDispatcher);											\
		m_dispatcherCollection->addDispatcher(SHAPE_TYPE1, SHAPE_TYPE2, newDispatcher);	\
	}

	m_dispatcherCollection = new PhysicsCollisionDispatcherCollection();
	EDGE_CHECK_INITIALIZATION(m_dispatcherCollection);

	CREATE_AND_ADD_DISPATCHER(SphereVsSphereCollisionDispatcher, PhysicsSphereShape::PhysicsEntityCollisionShapeType, PhysicsSphereShape::PhysicsEntityCollisionShapeType);

	PhysicsCollisionDispatcher* gjkDispatcher = new GJKCollisionDispatcher();
	m_dispatchers.push_back(gjkDispatcher);
	m_dispatcherCollection->setDefaultDispatcher(gjkDispatcher);

	return true;
}

void Edge::PhysicsCollisionContactManager::DispatcherContext::release()
{
	for (const auto dispatcher : m_dispatchers)
	{
		delete dispatcher;
	}

	EDGE_SAFE_DESTROY(m_dispatcherCollection);
}

Edge::PhysicsCollisionDispatcher* Edge::PhysicsCollisionContactManager::DispatcherContext::getDispatcher(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2) const
{
	EDGE_ASSERT(m_dispatcherCollection);
	return m_dispatcherCollection->getDispatcher(type1, type2);
}

void Edge::PhysicsCollisionContactManager::removeCollisionPartner(PhysicsSceneCollisionID baseCollision, PhysicsSceneCollisionID partnerCollision)
{
	auto& collisionPartnersCollection = m_contactPartners[baseCollision];
	const size_t partnerCount = collisionPartnersCollection.size();

	for (size_t partnerIndex = 0; partnerIndex < partnerCount; ++partnerIndex)
	{
		if (collisionPartnersCollection[partnerIndex] == partnerCollision)
		{
			collisionPartnersCollection[partnerIndex] = collisionPartnersCollection[partnerCount - 1];
			collisionPartnersCollection.pop_back();

			break;
		}
	}
}

Edge::PhysicsCollisionContactManager::ContactCollection::iterator Edge::PhysicsCollisionContactManager::removeContactFromCollections(ContactCollection::iterator removedIter, PhysicsCollisionContactID contactID)
{
	removeCollisionPartner(contactID.m_collisionID1, contactID.m_collisionID2);
	removeCollisionPartner(contactID.m_collisionID2, contactID.m_collisionID1);

	return m_contacts.erase(removedIter);
}

Edge::PhysicsCollisionContact* Edge::PhysicsCollisionContactManager::getContactInternal(PhysicsCollisionContactID contactID)
{
	const auto findIter = m_contacts.find(contactID);
	if (findIter != m_contacts.end())
	{
		return &findIter->second;
	}

	return nullptr;
}

void Edge::PhysicsCollisionContactManager::prepareContactPointCollection(uint32_t contactPointCount)
{
	m_contactPoints.clear();
	m_contactPoints.reserve(contactPointCount);
}

bool Edge::PhysicsCollisionContactManager::init(const PhysicsSceneCollisionManagerReference& collisionManager)
{
	m_collisionManager = collisionManager;
	EDGE_CHECK_INITIALIZATION(m_collisionManager);

	m_dispatcherContext = new DispatcherContext();
	EDGE_CHECK_INITIALIZATION(m_dispatcherContext && m_dispatcherContext->init());

	return true;
}

void Edge::PhysicsCollisionContactManager::release()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_dispatcherContext);

	m_collisionManager.reset();
}

void Edge::PhysicsCollisionContactManager::addContact(PhysicsCollisionContactID contactID)
{
	const auto findIter = m_contacts.find(contactID);
	if (findIter == m_contacts.end())
	{
		m_contacts.insert(std::make_pair(contactID, PhysicsCollisionContact()));

		m_contactPartners[contactID.m_collisionID1].push_back(contactID.m_collisionID2);
		m_contactPartners[contactID.m_collisionID2].push_back(contactID.m_collisionID1);
	}
	else
	{
		findIter->second.resetDirtyState();
	}
}

void Edge::PhysicsCollisionContactManager::removeContact(PhysicsCollisionContactID contactID)
{
	const auto findIter = m_contacts.find(contactID);
	if (findIter != m_contacts.end())
	{
		removeContactFromCollections(findIter, contactID);
	}
}

const Edge::PhysicsCollisionContact* Edge::PhysicsCollisionContactManager::getContact(PhysicsCollisionContactID contactID) const
{
	return const_cast<PhysicsCollisionContactManager*>(this)->getContactInternal(contactID);
}

const Edge::PhysicsCollisionContact* Edge::PhysicsCollisionContactManager::getContact(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2) const
{
	const DefaultPhysicsEntityCollisionSceneContextReference defaultSceneContext1 = CollisionUtil::GetDefaultCollisionSceneContext(collision1);
	const DefaultPhysicsEntityCollisionSceneContextReference defaultSceneContext2 = CollisionUtil::GetDefaultCollisionSceneContext(collision2);

	const PhysicsCollisionContactID contactID(defaultSceneContext1->getCollisionContextID(), defaultSceneContext2->getCollisionContextID());

	return getContact(contactID);
}

const Edge::PhysicsInstancedCollisionContactPoint* Edge::PhysicsCollisionContactManager::getContactPoint(PhysicsCollisionContactPointID contactPointID) const
{
	if (contactPointID < m_contactPoints.size())
	{
		return &m_contactPoints[contactPointID];
	}

	return nullptr;
}

const Edge::PhysicsCollisionContactManager::ContactPointCollection& Edge::PhysicsCollisionContactManager::getContactPoints() const
{
	return m_contactPoints;
}

void Edge::PhysicsCollisionContactManager::markContactsForChecking(const PhysicsEntityCollisionReference& collision)
{
	const DefaultPhysicsEntityCollisionSceneContextReference defaultSceneContext = CollisionUtil::GetDefaultCollisionSceneContext(collision);
	const PhysicsSceneCollisionID collisionID = defaultSceneContext->getCollisionID();

	markContactsForChecking(collisionID);
}

void Edge::PhysicsCollisionContactManager::markContactsForChecking(PhysicsSceneCollisionID changedCollision)
{
	const auto findIter = m_contactPartners.find(changedCollision);
	if (findIter == m_contactPartners.end())
	{
		return;
	}

	const auto& collisionPartnersCollection = m_contactPartners[changedCollision];
	const size_t partnerCount = collisionPartnersCollection.size();

	for (size_t partnerIndex = 0; partnerIndex < partnerCount; ++partnerIndex)
	{
		const PhysicsSceneCollisionID partnerCollisionID = collisionPartnersCollection[partnerIndex];

		const PhysicsCollisionContactID contactID(changedCollision, partnerCollisionID);
		m_contacts.at(contactID).markDirtyState();
	}
}

void Edge::PhysicsCollisionContactManager::updateContacts()
{
	EDGE_ASSERT(m_dispatcherContext);

	EDGE_PROFILE_BLOCK_EVENT("Update collision contacts");

	const PhysicsSceneCollisionManagerReference collisionManager = m_collisionManager.getReference();

	for (auto contactIter = m_contacts.begin(); contactIter != m_contacts.end();)
	{
		const PhysicsCollisionContactID contactID = contactIter->first;
		PhysicsCollisionContact contact = contactIter->second;

		if (contact.getDirtyState())
		{
			const PhysicsEntityCollisionReference collision1 = collisionManager->getCollision(contactID.m_collisionID1);
			const PhysicsEntityCollisionReference collision2 = collisionManager->getCollision(contactID.m_collisionID2);

			if (collision1->getWorldShapeAABB().isOverlapped(collision2->getWorldShapeAABB()))
			{
				contact.resetDirtyState();
			}
			else
			{
				contactIter = removeContactFromCollections(contactIter, contactID);
				continue;
			}
		}

		++contactIter;
	}

	uint32_t contactPointCount = 0;

	std::vector<PhysicsInstanceContactManifold> manifolds;

	for (auto contactIter = m_contacts.begin(); contactIter != m_contacts.end(); ++contactIter)
	{
		const PhysicsCollisionContactID contactID = contactIter->first;

		const PhysicsEntityCollisionReference collision1 = collisionManager->getCollision(contactID.m_collisionID1);
		const PhysicsEntityCollisionReference collision2 = collisionManager->getCollision(contactID.m_collisionID2);

		const PhysicsEntityCollisionShapeType shapeType1 = collision1->getShape()->getType();
		const PhysicsEntityCollisionShapeType shapeType2 = collision2->getShape()->getType();

		PhysicsCollisionDispatcher* dispatcher = m_dispatcherContext->getDispatcher(shapeType1, shapeType2);
		if (dispatcher)
		{
			const uint32_t collisionContactPointCount = dispatcher->dispatch(collision1, collision2, contactID, manifolds);
			contactPointCount += collisionContactPointCount;
		}
	}

	prepareContactPointCollection(contactPointCount);

	PhysicsCollisionConstraintManager& constraintManager = m_collisionManager.getReference()->getCollisionConstraintManager();
	constraintManager.prepareCollection(contactPointCount);

	for (const PhysicsInstanceContactManifold& manifold : manifolds)
	{
		const size_t initialContactIndex = m_contactPoints.size();

		EDGE_ASSERT(manifold.m_manifoldData.m_positions1.size() == manifold.m_manifoldData.m_positions2.size());

		for (uint32_t contactIndex = 0; contactIndex < manifold.m_manifoldData.m_positions1.size(); ++contactIndex)
		{
			PhysicsInstancedCollisionContactPoint& point = m_contactPoints.emplace_back();

			point.m_contactID = manifold.m_contactID;
			point.m_pointData.m_position1 = manifold.m_manifoldData.m_positions1[contactIndex];
			point.m_pointData.m_position2 = manifold.m_manifoldData.m_positions2[contactIndex];
			point.m_pointData.m_normal = manifold.m_manifoldData.m_normal;
			point.m_pointData.m_depth = manifold.m_manifoldData.m_depth;

			const PhysicsEntityCollisionReference collision1 = collisionManager->getCollision(point.m_contactID.m_collisionID1);
			const PhysicsEntityCollisionReference collision2 = collisionManager->getCollision(point.m_contactID.m_collisionID2);

			constraintManager.addContact(collision1->getEntity(), collision2->getEntity(), point.m_pointData);
		}

		const size_t postDispatchingContactIndex = m_contactPoints.size();

		PhysicsCollisionContact* contact = getContactInternal(manifold.m_contactID);
		contact->setCollisionPointCount(postDispatchingContactIndex - initialContactIndex);
		contact->setCollisionPointBaseIndex(initialContactIndex);
	}
}


void Edge::PhysicsCollisionContactManager::applyCollision()
{
	return;

	EDGE_PROFILE_BLOCK_EVENT("Apply collision contacts");

	const PhysicsSceneCollisionManagerReference collisionManager = m_collisionManager.getReference();

	const size_t contactPointCount = m_contactPoints.size();
	for (size_t contactPointIndex = 0; contactPointIndex < contactPointCount; ++contactPointIndex)
	{
		const PhysicsInstancedCollisionContactPoint contactPoint = m_contactPoints[contactPointIndex];

		const PhysicsEntityCollisionReference collision1 = collisionManager->getCollision(contactPoint.m_contactID.m_collisionID1);
		const PhysicsEntityCollisionReference collision2 = collisionManager->getCollision(contactPoint.m_contactID.m_collisionID2);

		const PhysicsEntityReference entity1 = collision1->getEntity();
		const PhysicsEntityReference entity2 = collision2->getEntity();

		const PhysicsEntityTransformReference transform1 = entity1->getTransform();
		const PhysicsEntityTransformReference transform2 = entity2->getTransform();

		const PhysicsEntityMotionReference motion1 = entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = entity2->getMotion();

		//TMP
		const ComputeVector contactPosition1 = contactPoint.m_pointData.m_position1;
		const ComputeVector contactPosition2 = contactPoint.m_pointData.m_position2;
		//const ComputeVector contactPosition2 = contactPosition1 - contactPoint.m_pointData.m_normal * contactPoint.m_pointData.m_depth;

		EDGE_ASSERT(motion1 || motion2);

		float invMass1 = 0.0f;
		float invMass2 = 0.0f;

		FloatVector3 velocity1 = FloatVector3Zero;
		FloatVector3 velocity2 = FloatVector3Zero;

		FloatVector3 angularLinVelocity1 = FloatVector3Zero;
		FloatVector3 angularLinVelocity2 = FloatVector3Zero;

		FloatVector3 angularFactor1 = FloatVector3Zero;
		FloatVector3 angularFactor2 = FloatVector3Zero;

		FloatVector3 contactRadius1 = FloatVector3Zero;
		FloatVector3 contactRadius2 = FloatVector3Zero;

		FloatMatrix3x3 worldInverseInertiaTensor1 = FloatMatrix3x3Identity;
		FloatMatrix3x3 worldInverseInertiaTensor2 = FloatMatrix3x3Identity;

		const ComputeVector contactNormal = contactPoint.m_pointData.m_normal;

		if (motion1)
		{
			invMass1 = motion1->getInverseMass();
			velocity1 = motion1->getLinearVelocity();

			FloatMatrix3x3 inverseInertiaTensor;
			motion1->getWorldInverseInertiaTensor(inverseInertiaTensor);
			const ComputeMatrix worldInverseInertiaTensor = inverseInertiaTensor;
			const ComputeVector contactRadius = contactPosition1 - transform1->getPosition();

			worldInverseInertiaTensor.saveToMatrix3x3(worldInverseInertiaTensor1);
			contactRadius.saveToFloatVector3(contactRadius1);

			CrossVector3(worldInverseInertiaTensor * CrossVector3(contactRadius, contactNormal), contactRadius).saveToFloatVector3(angularFactor1);
			CrossVector3(motion1->getAngularVelocity(), contactRadius).saveToFloatVector3(angularLinVelocity1);
		}

		if (motion2)
		{
			invMass2 = motion2->getInverseMass();
			velocity2 = motion2->getLinearVelocity();

			FloatMatrix3x3 inverseInertiaTensor;
			motion2->getWorldInverseInertiaTensor(inverseInertiaTensor);
			const ComputeMatrix worldInverseInertiaTensor = inverseInertiaTensor;
			const ComputeVector contactRadius = contactPosition2 - transform2->getPosition();

			worldInverseInertiaTensor.saveToMatrix3x3(worldInverseInertiaTensor2);
			contactRadius.saveToFloatVector3(contactRadius2);

			CrossVector3(worldInverseInertiaTensor * CrossVector3(contactRadius, contactNormal), contactRadius).saveToFloatVector3(angularFactor2);
			CrossVector3(motion2->getAngularVelocity(), contactRadius).saveToFloatVector3(angularLinVelocity2);
		}

		const float totalInvMass = invMass1 + invMass2;

		const ComputeVector velocityDelta = velocity1 + angularLinVelocity1 - velocity2 - angularLinVelocity2;
		const float relativeSpeed = DotVector3(contactNormal, velocityDelta);

		{
			const float elasticity1 = collision1->getElasticity();
			const float elasticity2 = collision2->getElasticity();
			const float elasticity = elasticity1 * elasticity2;

			const float angularFactor = DotVector3(angularFactor1 + angularFactor2, contactNormal);
			const float impulseValue = -(1.0f + elasticity) * relativeSpeed / (totalInvMass + angularFactor);
			const ComputeVector contactImpulse = contactNormal * impulseValue;

			if (motion1)
			{
				motion1->applyImpulse(contactImpulse.getFloatVector3(), contactPosition1.getFloatVector3());
			}

			if (motion2)
			{
				motion2->applyImpulse(NegateVector(contactImpulse).getFloatVector3(), contactPosition2.getFloatVector3());
			}
		}

		//Friction
		{
			const ComputeVector relativeVelocity = contactNormal * relativeSpeed;
			const ComputeVector tangent = velocityDelta - relativeVelocity;
			const ComputeVector relativeTangent = NormalizeVector(tangent);

			FloatVector3 angularFrictionFactor1 = FloatVector3Zero;
			FloatVector3 angularFrictionFactor2 = FloatVector3Zero;

			const float friction1 = collision1->getFriction();
			const float friction2 = collision2->getFriction();
			const float friction = friction1 * friction2;

			if (motion1)
			{
				const ComputeMatrix worldInverseInertiaTensor = worldInverseInertiaTensor1;
				const ComputeVector contactRadius = contactRadius1;

				CrossVector3(worldInverseInertiaTensor * CrossVector3(contactRadius, relativeTangent), contactRadius).saveToFloatVector3(angularFrictionFactor1);
			}

			if (motion2)
			{
				const ComputeMatrix worldInverseInertiaTensor = worldInverseInertiaTensor2;
				const ComputeVector contactRadius = contactRadius2;

				CrossVector3(worldInverseInertiaTensor * CrossVector3(contactRadius, relativeTangent), contactRadius).saveToFloatVector3(angularFrictionFactor2);
			}

			const float angularFrictionFactor = DotVector3(angularFrictionFactor1 + angularFrictionFactor2, relativeTangent);

			const float frictionImpulseValue = -friction / (totalInvMass + angularFrictionFactor);
			const ComputeVector frictionImpulse = tangent * frictionImpulseValue;

			if (motion1)
			{
				motion1->applyImpulse(frictionImpulse.getFloatVector3(), contactPosition1.getFloatVector3());
			}

			if (motion2)
			{
				motion2->applyImpulse(NegateVector(frictionImpulse).getFloatVector3(), contactPosition2.getFloatVector3());
			}
		}

		//Position adjustment
		{
			const ComputeVector contactPositionDelta = contactPosition2 - contactPosition1;

			const float totalMass = 1.0f / totalInvMass;
			const float adjustmentCoeff1 = invMass1 * totalMass;
			const float adjustmentCoeff2 = invMass2 * totalMass;

			transform1->setPosition((transform1->getPosition() + contactPositionDelta * adjustmentCoeff1).getFloatVector3());
			transform2->setPosition((transform2->getPosition() - contactPositionDelta * adjustmentCoeff2).getFloatVector3());
		}
	}
}
