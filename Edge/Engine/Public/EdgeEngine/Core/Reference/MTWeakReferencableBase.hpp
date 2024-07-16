#include "TinySimCommon/Multithreading/LockGuard.h"

template <typename T>
void Edge::MTWeakReferenceHandle<T>::selfDestroy()
{
	delete this;
}

template <typename T>
Edge::MTReference<T> Edge::MTWeakReferenceHandle<T>::getObject()
{
	LockGuard locker(m_lockState);
	return m_object;
}

template <typename T>
bool Edge::MTWeakReferenceHandle<T>::isNull()
{
	LockGuard locker(m_lockState);
	return m_object == nullptr;
}

template <typename T>
void Edge::MTWeakReferenceHandle<T>::reset()
{
	LockGuard locker(m_lockState);
	m_object = nullptr;
}

template <typename T>
Edge::MTWeakReferencableBase<T>::~MTWeakReferencableBase()
{
	LockGuard locker(m_lockState);

	if (m_handle)
	{
		m_handle->reset();
	}
}

template <typename T>
typename Edge::MTWeakReferencableBase<T>::WeakReferenceHandleReference Edge::MTWeakReferencableBase<T>::getWeakReferenceHandle() const
{
	LockGuard locker(m_lockState);

	if (!m_handle)
	{
		m_handle = new MTWeakReferenceHandle<T>(const_cast<T*>(static_cast<const T*>(this)));
	}

	return m_handle;
}