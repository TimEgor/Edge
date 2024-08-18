#pragma once

#include "MTWeakReferencableBase.h"

namespace Edge
{
	template <typename T>
	class MTWeakReference
	{
	public:
		using Base = MTWeakReferencableBase<T>;

		using WeakReferenceHandle = MTWeakReferenceHandle<T>;
		using WeakReferenceHandleReference = MTReference<WeakReferenceHandle>;

		using ObjectReference = MTReference<T>;
		using ObjectConstReference = MTConstReference<T>;

		using ObjectType = T;

	protected:
		WeakReferenceHandleReference m_objectHandle;

		void releaseReference();

	public:
		MTWeakReference() = default;
		MTWeakReference(nullptr_t) : m_objectHandle(nullptr) {}
		MTWeakReference(const ObjectConstReference& object);
		MTWeakReference(const MTWeakReference<T>& reference);
		MTWeakReference(MTWeakReference<T>&& reference);
		virtual ~MTWeakReference() { releaseReference(); }

		MTWeakReference& operator=(const ObjectConstReference& object);
		MTWeakReference& operator=(const MTWeakReference<T>& reference);
		MTWeakReference& operator=(MTWeakReference<T>&& reference);
		bool operator==(const MTWeakReference<T>& reference) const;
		bool operator!=(const MTWeakReference<T>& reference) const;

		operator bool() const { return !isNull(); }
		bool isNull() const;

		ObjectReference getReference() const;

		void reset() { releaseReference(); }
	};
}

#define EDGE_MT_WEAK_REFERENCE_POSTFIX_BY_NAME_DECALRATION(TYPE, NAME, POSTFIX)	\
	using NAME##POSTFIX = Edge::MTWeakReference<TYPE>;

#define EDGE_MT_WEAK_REFERENCE(TYPE)	\
	EDGE_MT_WEAK_REFERENCE_POSTFIX_BY_NAME_DECALRATION(TYPE, TYPE, WeakReference)

#define EDGE_MT_WEAK_NAMED_REFERENCE(TYPE, NAME)	\
	EDGE_MT_WEAK_REFERENCE_POSTFIX_BY_NAME_DECALRATION(TYPE, NAME, WeakReference)

#include "MTWeakReference.hpp"