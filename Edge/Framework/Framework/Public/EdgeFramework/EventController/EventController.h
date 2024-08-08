#pragma once

#include "EdgeCommon/ObjectPool/ObjectPool.h"

#include "Event.h"

#include <functional>

namespace Edge
{
	using EventDispatcher = std::function<void(const Event&)>;
	using EventDispatcherID = uint32_t;

	using InstancedEventID = uint32_t;
	using InstancedEventDispatcher = std::function<void(const InstancedEvent&)>;
	using InstancedEventDispatcherID = uint32_t;

	constexpr InstancedEventID InvalidInstancedEventID = 0;
	constexpr EventDispatcherID InvalidEventDispatcherID = 0;
	constexpr InstancedEventDispatcherID InvalidInstancedEventDispatcherID = 0;

	class EventController final
	{
		struct DispatcherData final
		{
			EventDispatcher m_dispatcher;
			EventType m_eventType = InvalidEventType;
			uint32_t m_orderIndex = -1;
		};

		using DispatcherPool = ObjectPool<DispatcherData, ObjectPoolHandle32>;
		using DispatcherPoolElementInfo = DispatcherPool::NewElementInfo;
		using DispatcherOrderCollection = std::vector<DispatcherData*>;
		using DispatcherOrdersCollection = std::unordered_map<EventType, DispatcherOrderCollection>;

		struct InstancedDispatcherData final
		{
			InstancedEventDispatcher m_dispatcher;
			InstancedEventID m_eventID = InvalidInstancedEventID;
			InstancedEventDispatcherID m_prevSiblingID = InvalidInstancedEventDispatcherID;
			InstancedEventDispatcherID m_nextSiblingID = InvalidInstancedEventDispatcherID;
		};

		using InstancedEventPool = ObjectPool<InstancedEventType, ObjectPoolHandle32>;
		using InstancedDispatcherPool = ObjectPool<InstancedDispatcherData, ObjectPoolHandle32>;
		using InstancedDispatcherPoolElementInfo = InstancedDispatcherPool::NewElementInfo;
		using InstancedDispatcherOrdersCollection = std::unordered_map<InstancedEventID, InstancedEventDispatcherID>;

	private:
		DispatcherPool m_dispatchers;
		DispatcherOrdersCollection m_dispatcherOrders;

		InstancedEventPool m_instancedEvents;
		InstancedDispatcherPool m_instancedDispatchers;
		InstancedDispatcherOrdersCollection m_instancedDispatcherOrders;

	public:
		EventController() = default;
		~EventController() { release(); }

		bool init();
		void release();

		bool registerEvent(EventType type);
		bool unregisterEvent(EventType type);

		EventDispatcherID addEventDispatcher(EventType type, const EventDispatcher& dispatcher);
		void removeEventDispatcher(EventDispatcherID dispatcherID);

		bool dispatchEvent(EventType type, const Event& event) const;

		InstancedEventID registerInstancedEvent(InstancedEventType eventType);
		bool unregisterInstancedEvent(InstancedEventID eventID);

		InstancedEventDispatcherID addInstanceEventDispatcher(InstancedEventID eventID, const InstancedEventDispatcher& dispatcher);
		void removeInstancedEventDispatcher(InstancedEventDispatcherID dispatcherID);

		bool dispatchInstancedEvent(InstancedEventID eventID, const InstancedEvent& event) const;
	};
}
