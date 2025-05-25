#pragma once

#include "EdgeCommon/Multithreading/SpinLock.h"

#include "Reference.h"

namespace Edge
{
	template <typename T>
	class MTWeakReferenceHandle final : public MTCountableObjectBase
	{
	private:
		mutable SpinLock m_lockState;
		T* m_object = nullptr;

		virtual void selfDestroy() override;

	public:
		MTWeakReferenceHandle(T* object)
			: m_object(object) {}

		void reset();

		Reference<T> getObject();
		bool isNull();

	};

	template <typename T>
	class MTWeakReferencableBase
	{
	public:
		using WeakReferenceHandle = MTWeakReferenceHandle<T>;
		using WeakReferenceHandleReference = Reference<WeakReferenceHandle>;

		using ObjectReference = Reference<T>;
		using ObjectConstReference = ConstReference<T>;

	private:
		mutable SpinLock m_lockState;
		mutable WeakReferenceHandleReference m_handle;

	public:
		MTWeakReferencableBase() = default;
		MTWeakReferencableBase(const MTWeakReferencableBase&) {}
		~MTWeakReferencableBase();

		MTWeakReferencableBase& operator=(const MTWeakReferencableBase&) { return *this; }

		WeakReferenceHandleReference getWeakReferenceHandle() const;
	};
}

#include "MTWeakReferencableBase.hpp"