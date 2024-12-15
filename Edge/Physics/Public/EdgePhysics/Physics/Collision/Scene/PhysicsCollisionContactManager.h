#pragma once

#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"
#include "EdgePhysics/Physics/Collision/PhysicsEntityCollision.h"

#include <unordered_map>


namespace Edge
{
}

namespace Edge
{
	class PhysicsCollisionDispatcher;
	class PhysicsCollisionDispatcherCollection;

	class PhysicsCollisionContactManager final
	{
	private:
		class DispatcherContext final
		{
		private:
			using DispatcherContainer = std::vector<PhysicsCollisionDispatcher*>;

			DispatcherContainer m_dispatchers;
			PhysicsCollisionDispatcherCollection* m_dispatcherCollection = nullptr;

		public:
			DispatcherContext() = default;

			bool init();
			void release();

			PhysicsCollisionDispatcher* getDispatcher(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2) const;
		};

		using ContactCollection = std::unordered_map<PhysicsCollisionContactID, PhysicsCollisionContact, PhysicsCollisionContactID::Hasher>;
		using ContactPartnerCollection = std::unordered_map<PhysicsSceneCollisionID, std::vector<PhysicsSceneCollisionID>>;

		using ContactPointCollection = std::vector<PhysicsInstancedCollisionContactPoint>;

		ContactCollection m_contacts;
		ContactPartnerCollection m_contactPartners;

		ContactPointCollection m_contactPoints;

		DispatcherContext* m_dispatcherContext = nullptr;

		PhysicsSceneCollisionManagerWeakReference m_collisionManager;

		void removeCollisionPartner(PhysicsSceneCollisionID baseCollision, PhysicsSceneCollisionID partnerCollision);
		ContactCollection::iterator removeContactFromCollections(ContactCollection::iterator removedIter, PhysicsCollisionContactID contactID);

		PhysicsCollisionContact* getContactInternal(PhysicsCollisionContactID contactID);

		void prepareContactPointCollection(uint32_t contactPointCount);

	public:
		PhysicsCollisionContactManager() = default;

		bool init(const PhysicsSceneCollisionManagerReference& collisionManager);
		void release();

		void addContact(PhysicsCollisionContactID contactID);
		void removeContact(PhysicsCollisionContactID contactID);

		const PhysicsCollisionContact* getContact(PhysicsCollisionContactID contactID) const;
		const PhysicsCollisionContact* getContact(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2) const;
		const PhysicsInstancedCollisionContactPoint* getContactPoint(PhysicsCollisionContactPointID pointID) const;

		void markContactsForChecking(const PhysicsEntityCollisionReference& collision);
		void markContactsForChecking(PhysicsSceneCollisionID changedCollision);

		void updateContacts();
		void applyCollision();
	};
}
