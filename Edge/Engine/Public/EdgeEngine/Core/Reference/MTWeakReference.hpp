template <typename T>
void Edge::MTWeakReference<T>::releaseReference()
{
	m_objectHandle.reset();
}

template <typename T>
Edge::MTWeakReference<T>::MTWeakReference(const ObjectConstReference& object)
{
	if (object)
	{
		m_objectHandle = object->getWeakReferenceHandle();
	}
}

template <typename T>
Edge::MTWeakReference<T>::MTWeakReference(const MTWeakReference<T>& reference)
	: m_objectHandle(reference.m_objectHandle) {}

template <typename T>
Edge::MTWeakReference<T>::MTWeakReference(MTWeakReference<T>&& reference)
	: m_objectHandle(reference.m_objectHandle)
{
	reference.m_objectHandle.reset();
}

template <typename T>
Edge::MTWeakReference<T>& Edge::MTWeakReference<T>::operator=(const ObjectConstReference& object)
{
	if (object)
	{
		m_objectHandle = object->getWeakReferenceHandle();
	}

	return *this;
}

template <typename T>
Edge::MTWeakReference<T>& Edge::MTWeakReference<T>::operator=(const MTWeakReference<T>& reference)
{
	m_objectHandle = reference.m_objectHandle;
	return *this;
}

template <typename T>
Edge::MTWeakReference<T>& Edge::MTWeakReference<T>::operator=(MTWeakReference<T>&& reference)
{
	m_objectHandle = reference.m_objectHandle;
	reference.m_objectHandle = nullptr;
	return *this;
}

template <typename T>
bool Edge::MTWeakReference<T>::operator==(const MTWeakReference<T>& reference) const
{
	return m_objectHandle == reference.m_objectHandle;
}

template <typename T>
bool Edge::MTWeakReference<T>::operator!=(const MTWeakReference<T>& reference) const
{
	return m_objectHandle != reference.m_objectHandle;
}

template <typename T>
bool Edge::MTWeakReference<T>::isNull() const
{
	return !m_objectHandle || m_objectHandle->isNull();
}

template <typename T>
typename Edge::MTWeakReference<T>::ObjectReference Edge::MTWeakReference<T>::getReference() const
{
	return m_objectHandle ? m_objectHandle->getObject() : nullptr;
}
