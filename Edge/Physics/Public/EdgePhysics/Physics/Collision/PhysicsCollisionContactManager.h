#pragma once

#include "PhysicsCollisionContact.h"
#include "PhysicsEntityCollision.h"

#include <unordered_map>

namespace Edge
{
	class PhysicsCollisionContactManager final
	{
	private:
		using ContactCollection = std::unordered_map<PhysicsCollisionContactID, PhysicsCollisionContact, PhysicsCollisionContactID::Hasher>;
		using ContactPartnerCollection = std::unordered_map<PhysicsSceneCollisionID, std::vector<PhysicsSceneCollisionID>>;

		using ContactPointCollection = std::vector<PhysicsCollisionContactPoint>;

		ContactCollection m_contacts;
		ContactPartnerCollection m_contactPartners;

		ContactPointCollection m_contactPoints;

		PhysicsSceneCollisionManagerWeakReference m_collisionManager;

		void removeCollisionPartner(PhysicsSceneCollisionID baseCollision, PhysicsSceneCollisionID partnerCollision);
		ContactCollection::iterator removeContactFromCollections(ContactCollection::iterator removedIter, PhysicsCollisionContactID contactID);

	public:
		PhysicsCollisionContactManager() = default;

		bool init(const PhysicsSceneCollisionManagerReference& collisionManager);
		void release();

		void addContact(PhysicsCollisionContactID contactID);
		void removeContact(PhysicsCollisionContactID contactID);

		const PhysicsCollisionContact* getContact(PhysicsCollisionContactID contactID) const;
		const PhysicsCollisionContact* getContact(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2) const;
		const PhysicsCollisionContactPoint* getContactPoint(PhysicsCollisionContactPointID pointID) const;

		void markContactsForChecking(const PhysicsEntityCollisionReference& collision);
		void markContactsForChecking(PhysicsSceneCollisionID changedCollision);

		void updateContacts();
		void applyCollision();
	};
}