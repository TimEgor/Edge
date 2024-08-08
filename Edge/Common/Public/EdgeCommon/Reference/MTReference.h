#pragma once

#include "MTCountableObjectBase.h"

#include <type_traits>

namespace Edge
{
	template<typename T>
	class MTReference;

	template <typename T>
	class MTConstReference
	{
	public:
		using ObjectType = T;

	protected:
		const T* m_object = nullptr;

		void releaseReference();
		void assign(const T* object);

	public:
		MTConstReference() = default;
		MTConstReference(nullptr_t) : m_object(nullptr) {}
		MTConstReference(T* object) : MTConstReference(const_cast<const T*>(object)) {}
		MTConstReference(const T* object);
		MTConstReference(const MTConstReference<T>& reference);
		MTConstReference(MTConstReference<T>&& reference);
		MTConstReference(const MTReference<T>& reference);

		template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
		MTConstReference(const MTConstReference<U>& reference) : MTConstReference(reference.getObject()) {}
		template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
		MTConstReference(MTConstReference<U>&& reference);
		template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
		MTConstReference(const MTReference<U>& reference);

		virtual ~MTConstReference() { releaseReference(); }

		MTConstReference& operator=(T* object) { return operator=(const_cast<const T*>(object)); }
		MTConstReference& operator=(const T* object);
		MTConstReference& operator=(const MTConstReference<T>& reference);
		MTConstReference& operator=(MTConstReference<T>&& reference);
		bool operator==(const MTConstReference<T>& reference) const;
		bool operator!=(const MTConstReference<T>& reference) const;
		const T* operator->() const { return m_object; }
		const T& operator*() const { return *m_object; }

		operator bool() const { return m_object; }
		bool isNull() const { return m_object == nullptr; }

		const T* getObject() const { return m_object; }
		const T& getObjectRef() const { return *m_object; }

		template <typename CastType>
		const CastType* getObjectCast() const { return reinterpret_cast<CastType*>(m_object); }
		template <typename CastType>
		const CastType& getObjectCastRef() const { return reinterpret_cast<CastType&>(*m_object); }

		void reset() { releaseReference(); }
	};

	template <typename T>
	class MTReference : public MTConstReference<T>
	{
	public:
		MTReference() = default;
		MTReference(T* object)
			: MTConstReference<T>(object) {}
		MTReference(const MTReference<T>& reference)
			: MTConstReference<T>(reference) {}
		MTReference(MTReference<T>&& reference)
			: MTConstReference<T>(std::move(reference)) {}

		template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
		MTReference(const MTReference<U>& reference);
		template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
		MTReference(MTReference<U>&& reference);

		MTReference& operator=(T* object);
		MTReference& operator=(const MTReference<T>& reference);
		MTReference& operator=(MTReference<T>&& reference);
		T* operator->() const { return getObject(); }

		T& operator*() const { return getObjectRef(); }

		T* getObject() const { return const_cast<T*>(m_object); }
		T& getObjectRef() const { return *getObject(); }

		template <typename CastType>
		CastType* getObjectCast() const { return static_cast<CastType*>(getObject()); }
		template <typename CastType>
		CastType& getObjectCastRef() const { return static_cast<CastType&>(getObjectRef()); }
	};
}

#define EDGE_MT_REFERENCE_POSTFIX_BY_NAME_DECALRATION(TYPE, NAME, POSTFIX, CONST_POSTFIX)	\
	using NAME##POSTFIX = Edge::MTReference<TYPE>;											\
	using NAME##CONST_POSTFIX = Edge::MTConstReference<TYPE>;

#define EDGE_MT_REFERENCE(TYPE)	\
	EDGE_MT_REFERENCE_POSTFIX_BY_NAME_DECALRATION(TYPE, TYPE, Reference, ConstReference)

#define EDGE_MT_NAMED_REFERENCE(TYPE, NAME)	\
	EDGE_MT_REFERENCE_POSTFIX_BY_NAME_DECALRATION(TYPE, NAME, Reference, ConstReference)

#include "MTReference.hpp"