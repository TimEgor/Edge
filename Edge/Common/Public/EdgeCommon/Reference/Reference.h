#pragma once

#include "MTCountableObjectBase.h"

#include <type_traits>

namespace Edge
{
	template<typename T>
	class Reference;

	template <typename T>
	class ConstReference
	{
	public:
		using ObjectType = T;

	protected:
		const T* m_object = nullptr;

		void release();
		void assign(const T* object);

	public:
		ConstReference() = default;
		ConstReference(nullptr_t) : m_object(nullptr) {}
		ConstReference(T* object) : ConstReference(const_cast<const T*>(object)) {}
		ConstReference(const T* object);
		ConstReference(const ConstReference<T>& reference);
		ConstReference(ConstReference<T>&& reference);
		ConstReference(const Reference<T>& reference);

		template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
		ConstReference(const ConstReference<U>& reference) : ConstReference(reference.getObject()) {}
		template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
		ConstReference(ConstReference<U>&& reference);
		template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
		ConstReference(const Reference<U>& reference);

		virtual ~ConstReference() { release(); }

		ConstReference& operator=(const ConstReference<T>& reference);
		ConstReference& operator=(ConstReference<T>&& reference);
		bool operator==(const ConstReference<T>& reference) const;
		bool operator!=(const ConstReference<T>& reference) const;
		const T* operator->() const { return m_object; }
		const T& operator*() const { return *m_object; }

		operator const T*() const { return m_object; }

		bool isNull() const { return m_object == nullptr; }

		const T* getObject() const { return m_object; }
		const T& getObjectRef() const { return *m_object; }

		template <typename CastType>
		const CastType* getObjectCast() const { return reinterpret_cast<CastType*>(m_object); }
		template <typename CastType>
		const CastType& getObjectCastRef() const { return reinterpret_cast<CastType&>(*m_object); }

		void reset() { release(); }
	};

	template <typename T>
	class Reference : public ConstReference<T>
	{
	public:
		Reference() = default;
		Reference(T* object) : ConstReference<T>(object) {}
		Reference(const Reference<T>& reference) : ConstReference<T>(reference) {}
		Reference(Reference<T>&& reference) : ConstReference<T>(std::move(reference)) {}

		template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
		Reference(const Reference<U>& reference);
		template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
		Reference(Reference<U>&& reference);

		Reference& operator=(const Reference<T>& reference);
		Reference& operator=(Reference<T>&& reference);
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

#define EDGE_REFERENCE_POSTFIX_BY_NAME_DECALRATION(TYPE, NAME, POSTFIX, CONST_POSTFIX)	\
	using NAME##POSTFIX = Edge::Reference<TYPE>;										\
	using NAME##CONST_POSTFIX = Edge::ConstReference<TYPE>;

#define EDGE_REFERENCE(TYPE)	\
	EDGE_REFERENCE_POSTFIX_BY_NAME_DECALRATION(TYPE, TYPE, Reference, ConstReference)

#define EDGE_NAMED_REFERENCE(TYPE, NAME)	\
	EDGE_REFERENCE_POSTFIX_BY_NAME_DECALRATION(TYPE, NAME, Reference, ConstReference)

#include "Reference.hpp"
