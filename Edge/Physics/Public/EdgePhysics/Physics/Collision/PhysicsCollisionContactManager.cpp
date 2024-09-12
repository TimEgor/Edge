#include "PhysicsCollisionContactManager.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Profile/Profile.h"

#include "DefaultPhysicsEntityCollisionSceneContext.h"
#include "PhysicsSceneCollisionManager.h"
#include "Shapes/PhysicsSphereShape.h"

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

bool Edge::PhysicsCollisionContactManager::init(const PhysicsSceneCollisionManagerReference& collisionManager)
{
	m_collisionManager = collisionManager;
	EDGE_CHECK_INITIALIZATION(m_collisionManager);

	return true;
}

void Edge::PhysicsCollisionContactManager::release()
{
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
	const auto findIter = m_contacts.find(contactID);
	if (findIter != m_contacts.end())
	{
		return &findIter->second;
	}

	return nullptr;
}

const Edge::PhysicsCollisionContact* Edge::PhysicsCollisionContactManager::getContact(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2) const
{
	const DefaultPhysicsEntityCollisionSceneContextReference defaultSceneContext1 = CollisionUtil::GetDefaultCollisionSceneContext(collision1);
	const DefaultPhysicsEntityCollisionSceneContextReference defaultSceneContext2 = CollisionUtil::GetDefaultCollisionSceneContext(collision2);

	const PhysicsCollisionContactID contactID(defaultSceneContext1->getCollisionContextID(), defaultSceneContext2->getCollisionContextID());

	return getContact(contactID);
}

const Edge::PhysicsCollisionContactPoint* Edge::PhysicsCollisionContactManager::getContactPoint(PhysicsCollisionContactPointID contactPointID) const
{
	if (contactPointID < m_contactPoints.size())
	{
		return &m_contactPoints[contactPointID];
	}

	return nullptr;
}

void Edge::PhysicsCollisionContactManager::markContactsForChecking(const PhysicsEntityCollisionReference& collision)
{
	const DefaultPhysicsEntityCollisionSceneContextReference defaultSceneContext = CollisionUtil::GetDefaultCollisionSceneContext(collision);
	const PhysicsSceneEntityID collisionID = defaultSceneContext->getCollisionID();

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
	EDGE_PROFILE_BLOCK_EVENT("Update collision contacts")

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

	m_contactPoints.clear();

	for (auto contactIter = m_contacts.begin(); contactIter != m_contacts.end(); ++contactIter)
	{
		const PhysicsCollisionContactID contactID = contactIter->first;
		PhysicsCollisionContact contact = contactIter->second;

		const PhysicsEntityCollisionReference collision1 = collisionManager->getCollision(contactID.m_collisionID1);
		const PhysicsEntityCollisionReference collision2 = collisionManager->getCollision(contactID.m_collisionID2);

		const PhysicsEntityCollisionShapeReference shape1 = collision1->getShape();
		const PhysicsEntityCollisionShapeReference shape2 = collision2->getShape();

		if (shape1->getType() == PhysicsSphereShape::PhysicsEntityCollisionShapeType
			&& shape2->getType() == PhysicsSphereShape::PhysicsEntityCollisionShapeType)
		{
			const PhysicsSphereShape& sphere1 = shape1.getObjectCastRef<PhysicsSphereShape>();
			const PhysicsSphereShape& sphere2 = shape2.getObjectCastRef<PhysicsSphereShape>();

			const FloatVector3 position1 = collision1->getEntity()->getTransform()->getPosition();
			const FloatVector3 position2 = collision2->getEntity()->getTransform()->getPosition();

			const float radius1 = sphere1.getRadius();
			const float radius2 = sphere2.getRadius();

			ComputeVector delta = position2 - position1;
			const float distance = delta.length3();

			float depth = radius1 + radius2 - distance;

			if (depth < 0.0f)
			{
				continue;
			}

			if (distance < EDGE_EPSILON)
			{
				depth = std::max(radius1, radius2);
				delta = FloatVector3UnitY * (radius1 + radius2);
			}

			const ComputeVector normal = normalizeVector(delta);

			PhysicsCollisionContactPoint contactPoint;
			contactPoint.m_contactID = contactID;
			(position1 + normal * radius1).saveToFloatVector3(contactPoint.m_position);
			normal.saveToFloatVector3(contactPoint.m_normal);
			contactPoint.m_depth = depth;

			contact.setCollisionPointCount(1);
			contact.setCollisionPointBaseIndex(m_contactPoints.size());

			m_contactPoints.push_back(contactPoint);
		}
	}
}


void Edge::PhysicsCollisionContactManager::applyCollision()
{
	EDGE_PROFILE_BLOCK_EVENT("Apply collision contacts")

		const PhysicsSceneCollisionManagerReference collisionManager = m_collisionManager.getReference();

	const size_t contactPointCount = m_contactPoints.size();
	for (size_t contactPointIndex = 0; contactPointIndex < contactPointCount; ++contactPointIndex)
	{
		const PhysicsCollisionContactPoint contactPoint = m_contactPoints[contactPointIndex];

		const PhysicsEntityCollisionReference collision1 = collisionManager->getCollision(contactPoint.m_contactID.m_collisionID1);
		const PhysicsEntityCollisionReference collision2 = collisionManager->getCollision(contactPoint.m_contactID.m_collisionID2);

		const PhysicsEntityReference entity1 = collision1->getEntity();
		const PhysicsEntityReference entity2 = collision2->getEntity();

		const PhysicsEntityTransformReference transform1 = entity1->getTransform();
		const PhysicsEntityTransformReference transform2 = entity2->getTransform();

		const PhysicsEntityMotionReference motion1 = entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = entity2->getMotion();

		EDGE_ASSERT(motion1 || motion2);

		float invMass1 = 0.0f;
		float invMass2 = 0.0f;

		FloatVector3 velocity1 = FloatVector3Zero;
		FloatVector3 velocity2 = FloatVector3Zero;

		if (motion1)
		{
			invMass1 = motion1->getInverseMass();
			velocity1 = motion1->getLinearVelocity();
		}

		if (motion2)
		{
			invMass2 = motion2->getInverseMass();
			velocity2 = motion2->getLinearVelocity();
		}

		const float totalInvMass = invMass1 + invMass2;
		const float totalMass = 1.0f / totalInvMass;

		const ComputeVector contactNormal = contactPoint.m_normal;

		const ComputeVector velocityDelta = velocity1 - velocity2;
		const float relativeSpeed = dotVector3(contactNormal, velocityDelta);
		if (relativeSpeed > 0)
		{
			const float impulseValue = -2.0f * relativeSpeed * totalMass;
			const ComputeVector contactImpulse = contactNormal * impulseValue;

			const ComputeVector contactPosition1 = contactPoint.m_position;
			const ComputeVector contactPosition2 = contactPosition1 + contactPoint.m_normal * contactPoint.m_depth;

			if (motion1)
			{
				motion1->applyImpulse(contactImpulse.getFloatVector3(), contactPosition1.getFloatVector3());
			}

			if (motion2)
			{
				motion2->applyImpulse(negateVector(contactImpulse).getFloatVector3(), contactPosition2.getFloatVector3());
			}

			//Position adjustment
			{

				const ComputeVector contactPositionDelta = contactPosition2 - contactPosition1;

				const float adjustmentCoeff1 = invMass1 * totalMass;
				const float adjustmentCoeff2 = invMass2 * totalMass;

				transform1->setPosition((transform1->getPosition() + contactPositionDelta * adjustmentCoeff1).getFloatVector3());
				transform2->setPosition((transform2->getPosition() + contactPositionDelta * adjustmentCoeff2).getFloatVector3());
			}
		}
	}
}
